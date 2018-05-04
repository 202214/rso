#include <Ice/Ice.h>
#include <Chat.h>
using namespace std;
using namespace Chat;

class ChatServerI : public virtual ChatServer {
    public:
        virtual void registerUser(const UserPrx& user, const ::Ice::Current& = ::Ice::Current()) override;
        virtual UserList getUsers(const ::Ice::Current& = ::Ice::Current()) override;
        virtual void whisp(const ::Chat::UserPrx&, const ::std::string&, const ::std::string&, const ::Ice::Current& = ::Ice::Current()) override;
        virtual void sendMessage(const UserPrx& from, const string& message, const ::Ice::Current& = ::Ice::Current()) override ;
        virtual ~ChatServerI() {}
    private:
        UserList users;
};

void ChatServerI::registerUser(const UserPrx& user, const ::Ice::Current&) {

}

UserList ChatServerI::getUsers(const ::Ice::Current&) {
    return users;
}

void ChatServerI::whisp(const ::Chat::UserPrx& user, const ::std::string& to, const ::std::string& message, const ::Ice::Current&) {

}

void ChatServerI::sendMessage(const UserPrx& from, const string& message, const ::Ice::Current&) {

}

int
main(int argc, char* argv[])
{
int status = 0;
Ice::CommunicatorPtr ic;
try {
ic = Ice::initialize(argc, argv);
Ice::ObjectAdapterPtr adapter
= ic->createObjectAdapterWithEndpoints(
"SimplePrinterAdapter",
"default -p 10000");
Ice::ObjectPtr object = new ChatServerI;
adapter->add(object,
ic->stringToIdentity("SimplePrinter"));
adapter->activate();
ic->waitForShutdown();
} catch (const Ice::Exception& e) {
cerr << e << endl;
status = 1;
} catch (const char* msg) {
cerr << msg << endl;
status = 1;
}
if (ic) {
try {
ic->destroy();
} catch (const Ice::Exception& e) {
cerr << e << endl;
status = 1;
}
}
return status;
}
