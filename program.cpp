#include <iostream>
#include <fstream>
#include "DoublyLinkedList.h"
#include "WallPost.h"
#include "Wall.h"
#include "User.h"
#include "UserNetwork.h"
using namespace std;


void createUser(UserNetwork& network) {
	string username, password, realName, city;

	cout << "Please enter your desired username" << endl;
	
	cin >> username;

	if (network.userAlreadyExists(username)) {
		cout << "Sorry that username already exists, please try again" << endl;
		createUser(network);
		return;
	}
	cout << "Please enter your password" << endl;
	cin >> password;
	cout << "Please enter your real name" << endl;
	cin >> realName;
	cout << "Please enter your city" << endl;
	cin >> city;

	
	User user = User(username, password, realName, city);

	

	network.addUser(user); // maybe a memory leak
	//delete user;
}

// returns to main menu if user not found
bool login(string username, string password, UserNetwork network) {
	if (!network.userAlreadyExists(username)) {
		cout << "User not found. Returning to main menu." << endl;
		return false;
	}
	User user = network.findUser(username);
	if (user.getPassword() == password) {
		cout << '\n' << user.getWall()->toString();
		return true;
	}
}


void mainMenu(UserNetwork& network) {
	cout << "Type 'a' to create a new user, type 'b' to Log in, type 'c' to quit" << endl;
	char option;
	cin >> option;
	switch (option) {
			case 'a':
			{
				createUser(network);
				break;
			}
			case 'b':
			{
				string username, password;
				cout << "Enter your username" << endl;
				cin >> username;
				cout << "Enter your password" << endl;
				cin >> password;
				bool logged_in = login(username, password, network);
				if (!logged_in)
					cout << "Sorry invalid username or password. Please try again" << endl;
					mainMenu(network);
				break;
			}
			case 'c':
			{
				exit(0);
				break;
			}
			default:
			{
				cout << "Sorry that was not a valid option, please try again." << endl;
				mainMenu(network);
			}
		}
}




int main() {

	UserNetwork network = UserNetwork();
	network.readFromFile();
	
	mainMenu(network);

	//cout << network.toString() << endl;
	network.toFile();
	network.readFromFile();
	//cout << network.toString() << endl;

	return 0;
}
