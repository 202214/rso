#include <Ice/Ice.h>
#include "Chat.h"

using namespace Chat;
using namespace std;

Ice::CommunicatorPtr iceCommunicator;
Ice::ObjectAdapterPtr adapter;
UserPrx user;
ServerPrx server;
string name;

class UserI : public User
{
	public:
  		virtual void sendMessage(const UserPrx& user, const string& message, const ::Ice::Current& = ::Ice::Current()) override;
  		virtual void whisp(const UserPrx& user, const string& message, const ::Ice::Current& = ::Ice::Current()) override;
  		virtual string getName(const ::Ice::Current& = ::Ice::Current()) override;
		
};

void UserI::sendMessage(const UserPrx& user, const string& message, const ::Ice::Current&) {
        auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << ctime(&currentTime) << " [GLOBAL] " << user->getName() << ": " << message << endl;
}

void UserI::whisp(const UserPrx& user, const string& message, const ::Ice::Current&) {
        auto currentTime = chrono::system_clock::to_time_t(chrono::system_clock::now());
        cout << ctime(&currentTime) << " [WHISP] " << user->getName() << ": " << message << endl;
}

string UserI::getName(const ::Ice::Current&) {
	return name;
}

int main(int argc, char* argv[]) {
 	try {
            iceCommunicator = Ice::initialize();
            int serverPort = 10000;
            Ice::ObjectPrx base = iceCommunicator->stringToProxy("Server:default -p " + to_string(serverPort));
            server = ServerPrx::checkedCast(base);
            if (!server)
                throw "Invalid proxy";
        } catch (const Ice::Exception& ex) {
            cerr << ex << endl;
        }
	cout << "Your nickname: ";
	cin >> name;
	cout << endl;
        UserPtr object = new UserI();
        int port = 9999;
        adapter = iceCommunicator->createObjectAdapterWithEndpoints("User" + name, "default -p " + to_string(port));
        user = UserPrx::uncheckedCast(adapter->addWithUUID(object));
        adapter->activate();
	server->registerUser(user);
	while (true) {
		string message;
		cin >> message;
		server->sendMessage(user, message);
	}	
    	return 0;
}
