module Chat 
{

	interface User 
	{
  		void sendMessage(User* user, string message);
  		void whisp(User* user, string message);
  		string getName();
	};

	sequence<User*> UserList;

	interface ChatServer 
	{
	  	UserList getUsers();
	  	void registerUser(User* user);
		void whisp(User* from, string to, string message);
		void sendMessage(User* from, string message);
	};
};
