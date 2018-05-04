#include "Menu.h"

void Menu::printMainMenu() {
	cout << endl;
        cout << "-----MAIN MENU-----" << endl;
        cout << "1. Create room" << endl;
        cout << "2. Join room" << endl;
        cout << "3. Change password" << endl;
        cout << "4. Commands help" << endl;	
        cout << "0. Exit" << endl;
        cout << endl;
}

void Menu::printHelp() {
	cout << endl;
        cout << "-----COMMANDS HELP-----" << endl;
        cout << "1. EVERYWHERE" << endl;
        cout << "/w <nick> - whisp to user" << endl;
        cout << "2. INSIDE ROOM" << endl;
        cout << "/list - list users" << endl;
	cout << "/leave - leave room" << endl;
        cout << "/help - show this" << endl;
        cout << endl;
}

