#include <Ice/Ice.h>
#include "Chat.h"

using namespace Chat;
using namespace std;

UserList users;

class ChatServerI : public ChatServer
{
	public:
		virtual void registerUser(const ::Chat::UserPrx&, const ::Ice::Current& = ::Ice::Current()) override;
		virtual ::Chat::UserList getUsers(const ::Ice::Current& = ::Ice::Current()) override;
		virtual void whisp(const ::Chat::UserPrx&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) override;
		virtual void sendMessage(const ::Chat::UserPrx&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) override;
		
};

void ChatServerI::registerUser(const UserPrx& user, const Ice::Current&) {
	users.push_back(user);
}

UserList ChatServerI::getUsers(const Ice::Current&) {
	return users;
}

void ChatServerI::whisp(const UserPrx& from, const string& to, const string& message, const Ice::Current&) {
        for (auto& user : users) {
		if (user->getName() == to) {
			user->whisp(from, message);
		}         
        }
}

void ChatServerI::sendMessage(const UserPrx& from, const string& message, const Ice::Current&) {
        for (auto& user : users) {
		user->sendMessage(from, message);       
        }
}

int main(int argc, char* argv[]) {
    Ice::CommunicatorPtr iceCommunicator;
    try {
        iceCommunicator = Ice::initialize(argc, argv);
        int serverPort = 10000;
        Ice::ObjectAdapterPtr adapter = iceCommunicator->createObjectAdapterWithEndpoints("ServerAdapter", "default -p " + to_string(serverPort));
        Ice::ObjectPtr object = new ChatServerI();
        adapter->add(object, iceCommunicator->stringToIdentity("Server"));
        adapter->activate();
        iceCommunicator->waitForShutdown();
    } catch(const std::exception& e)
    {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
