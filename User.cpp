#include "User.h"
#include <stdio.h>
#include <string>
#include <algorithm>



User::User(User const& user) { 
	this->wall = new Wall(*(user.getWall()));
	this->friendRequests = user.getFriendRequests();
	this->friends = user.getFriends();
	this->username = user.getUsername();
	this->password = user.getPassword();
	this->realName = user.getRealName();
	this->city = user.getCity();
	this->friendPointers = user.getFriendPointers();
}


User::User(string username_, string password_, string realName_, string city_) {
	this->wall = new Wall();
	this->username = username_;
	this->wall->setUsername(username_);
	this->password = password_;
	this->realName = realName_;
	this->city = city_;
}


//Finish changing to string implementation
User::User(const string userString_) {

	this->wall = new Wall();
	
	std::string userString = userString_;
	std::string friendString, friendRequestString, singleUsername;
	std::string nextUserDelimiter = "\n________________________________\n";
	//initialize some position markers and strings to hold results
	size_t usernameEndPos, passwordEndPos, realNameEndPos, cityEndPos, wallEndPos, friendsEndPos,friendRequestEndPos;
	//std::string username, password, realName, city, ;

	//pull out username
	usernameEndPos = userString.find("\n");
	this->username = userString.substr(10, usernameEndPos - 10);
	this->wall->setUsername(this->username);
	userString.erase(0, usernameEndPos + 1);

	//password
	passwordEndPos = userString.find("\n");
	this->password = userString.substr(10, passwordEndPos - 10);
	userString.erase(0, passwordEndPos + 1);

	//real name
	realNameEndPos = userString.find("\n");
	this->realName = userString.substr(11, realNameEndPos - 11);
	userString.erase(0, realNameEndPos + 1);

	//city
	cityEndPos = userString.find("\n");
	this->city = userString.substr(6, cityEndPos - 6);
	userString.erase(0, cityEndPos + 1);
	//cout << "got past city in string constructor...."  << endl;
	
	//friends
	friendsEndPos = userString.find("\n");
	friendString = userString.substr(9, friendsEndPos - 9);
	//now we split friendstring up by the spaces to get the usernames out

	while ((friendsEndPos = friendString.find(", ")) != std::string::npos) {
		singleUsername = friendString.substr(0, friendsEndPos);
 		
 		this->addFriend(singleUsername);
		friendString.erase(0, friendsEndPos+2);
	}
	userString.erase(0, userString.find("\n") + 1);

	//friend requests
	friendRequestEndPos = userString.find("\n\nWall: \n\n");
	friendRequestString = userString.substr(17, friendRequestEndPos - 17);


	//again, same format, split by the commas to parse usernames
	while ((friendRequestEndPos = friendRequestString.find(", ")) != std::string::npos) {
		singleUsername = friendRequestString.substr(0, friendRequestEndPos);
 		
 		this->friendRequests.insert(friendRequests.begin(),singleUsername);
		friendRequestString.erase(0, friendRequestEndPos+2);
	}

	
	userString.erase(0, userString.find("\n\nWall: \n\n") + 10);

	//wall
	//now all that is left in userString is wall since we erased as we parsed the rest
	//printf the wall string
	
	wallEndPos = userString.find(nextUserDelimiter);
	userString = userString.substr(0, wallEndPos);
	this->wall->readWallPostsFromString(userString);
	
}



User::~User() {
	delete wall;
}

User& User::operator=(const User& copy) {
	username = copy.getUsername();
	password = copy.getPassword();
	realName = copy.getRealName();
	city = copy.getCity();
	delete wall;
	wall = new Wall(*(copy.getWall()));
	this->friendRequests = copy.getFriendRequests();
	this->friends = copy.getFriends();
	this->friendPointers = copy.getFriendPointers();
	return *this;
}

//
/* Getters and Setters */
//

Wall* User::getWall() const {
	return this->wall;
}

string User::getPassword() const {
	return this->password;
}


void User::setUsername(string username_) {
	this->username = username_;
}

string User::getUsername() const{
	return this->username;
}

void User::setRealName(string realName_){
	this->realName = realName_;
}

string User::getRealName() const{
	return this->realName;
}

void User::setCity(string city_){
	this->city = city_;
}

string User::getCity() const{
	return this->city;
}

void User::setPassword(string password_){
	this->password = password_;
}
	 
void User::addPost(WallPost post_){
	this->wall->addPost(post_);
}

void User::deletePost(int pos) {
	this->wall->deletePost(pos);
}

void User::addResponse(int pos, WallPostResponse response_) {
	this->wall->addResponse(pos, response_);
}

void User::deleteResponse(int postPos, int responsePos) {
	this->wall->deleteResponse(postPos, responsePos);
}


string User::toString() const {
	//cout << "inside User:toString" << endl;
	string endString = "Username: " + this->getUsername() + "\n";
	endString += "Password: " + this->password + "\n";
	endString += "Real Name: " + this->getRealName() + "\n";
	endString += "City: " + this->getCity() + "\n";
	endString += this->friendsToString();
	endString += this->friendRequestsToString();

	endString += "\n\nWall: \n\n" + this->wall->toString() + "\n";
	endString += "________________________________\n";
	return endString;
}

//
/* Helpers for printing friends/requests*/
//

string User::friendsToString() const{
	string endString = "";
	endString += "Friends: ";
	
	for (int i = 0; i < this->friends.size(); i++) {
		try {
			endString += getFriends().at(i) + ", ";
		} catch (int& e) {
			cout << "Error: No friends at this index" << endl;
		}
	}

	return endString + "\n";
}

string User::friendRequestsToString() const {
	string endString = "";
	endString += "Friend Requests: ";
	
	// ITERATOR IS NOT WORKING HERE, had to switch to regular for loop
	
	for (int i = 0; i < this->friendRequests.size(); i++) {
		try {
			endString += getFriendRequests().at(i) + ", ";
		} catch (int& e) {
			cout << "Error: No friend requests at this index" << endl;
		}
	}

	return endString;
}

//
/* Getters and setters for friends and friendRequests arrays*/
//

vector<string> User::getFriendRequests() const{
	return this->friendRequests;	
}

void User::setFriendRequests(vector<string> friendRequests_){
	this->friendRequests = friendRequests_;
}

vector<string> User::getFriends() const{
	return this->friends;
}
	
	
void User::setFriends(vector<string> friends_){
	this->friends = friends_;
}

void User::setFriendPointers(UserNetwork& network) { // Only setting first friend
	int index;
	for (int i = 0; i < this->getFriends().size(); ++i) {
		index = network.findUser(getFriends().at(i));
		//cout << index << endl;
		//cout << "adding " << network.getUsers()->at(index).getUsername() << " to " << this->getUsername() << "'s friendPointers" << endl;
		this->friendPointers.insert(friendPointers.end(), &(network.getUsers()->at(index)));
	}
}

vector<User*> User:: getFriendPointers() const {
	return this->friendPointers;
}

//
/* General methods for friends and friend requests*/
//


void User::sendFriendRequest(string potentialFriendUsername, UserNetwork* myNetwork) {

	if (potentialFriendUsername == this->getUsername()) {
		cout << "You can't send a friend request to yourself!!" << endl;
		return;
	}
	for (auto iter = myNetwork->getUsers()->begin(); iter != myNetwork->getUsers()->end(); iter++) {
		if (iter->getUsername() == potentialFriendUsername) {
			vector<string> requests = iter->getFriendRequests();
			vector<string> friends = iter->getFriends();

			//make sure potentialFriend doesn't already have a request from us
			if (std::find(requests.begin(), requests.end(), this->getUsername()) == requests.end()
				&& std::find(friends.begin(), friends.end(), this->getUsername()) == friends.end()) {
	    		
	    		//now we have to set since our iterator uses get, which is const
	        	int acceptorIndex = myNetwork->findUser(potentialFriendUsername);
	        	// copy of this user made using copy ctor
				User friendCopy = User(myNetwork->getUsers()->at(acceptorIndex));
				// Send friendRequest to this user
				friendCopy.addFriendRequest(this->getUsername());
				// Update other user on network
				myNetwork->getUsers()->at(acceptorIndex) = friendCopy;
	        	
	        	/* test:
	        	try {
	        		cout << "iter->getFriendRequests[0] is : "  << iter->getFriendRequests().at(0) <<endl;
	        	} catch (int& e) {
        			cout << "Error: setFR didn't work!!!!" << endl;
    			} */
	    	}
	   		else {
	   			cout << "Error: You have already sent this user a friend request or you are already friends" << endl;
	   		}
	   		break; //once we find the user we should stop looking
	  	}
	}
}


void User::acceptFriendRequest(string usernameToAdd, UserNetwork* myNetwork){
    //remove request and add friend for this user, then add friend for other user
	if (usernameToAdd == this->getUsername()) {
		cout << "You can't be friends with yourself!!" << endl;
		return;
	}
	for (auto iter = myNetwork->getUsers()->begin(); iter != myNetwork->getUsers()->end(); iter++) {
		try {
			//first deal with this user
			if (iter->getUsername() == this->getUsername()){
				//find this user on network
				int indexOfThisInNetwork = myNetwork->findUser(this->getUsername());
				//make a copy of this so we can set the god damned changes in network scope
				User thisCopy = User(myNetwork->getUsers()->at(indexOfThisInNetwork));
				//find index of request in acceptor's friend requests
				vector<string> requests = thisCopy.getFriendRequests();
				auto it = std::find(requests.begin(), requests.end(), usernameToAdd);
				int index = std::distance(requests.begin(), it);
				thisCopy.deleteFriendRequest(index);  //delete the request
				thisCopy.addFriend(usernameToAdd);   //add the friend

				myNetwork->getUsers()->at(indexOfThisInNetwork) = thisCopy;


			}

			//next deal with other user
			if (iter->getUsername() == usernameToAdd) {

				int acceptorIndex = myNetwork->findUser(usernameToAdd);
		       	// copy of this user made using copy ctor
				User friendCopy = User(myNetwork->getUsers()->at(acceptorIndex));
				// Send friendRequest to this user
				friendCopy.addFriend(this->getUsername());
				// Update other user on network
				myNetwork->getUsers()->at(acceptorIndex) = friendCopy;
		    }
		} catch (int& e) {}    
  	}
}

//helper for accept friend request
void User::addFriend(string newFriendUsername) {
	this->friends.insert(friends.begin() + 0, newFriendUsername);
}

void User::addFriendRequest(string newFriendRequestUsername) {
	this->friendRequests.insert(friendRequests.begin() + 0, newFriendRequestUsername);
}


void User::deleteFriendRequest(int index){
	if (index < 0 || index > friendRequests.size() - 1)
		cout << "Error: No friend request at this index." << endl;
    else
    	friendRequests.erase(friendRequests.begin() + index);
}

void User::deleteFriendRequest(string usernameOfFriendToDelete, UserNetwork* myNetwork) {
	for (auto iter = myNetwork->getUsers()->begin(); iter != myNetwork->getUsers()->end(); iter++) {

		try {
			if (iter->getUsername() == this->getUsername()){
				//find this user on network
				int indexOfThisInNetwork = myNetwork->findUser(this->getUsername());
				//make a copy of this so we can set the god damned changes in network scope
				User thisCopy = User(myNetwork->getUsers()->at(indexOfThisInNetwork));

				vector<string> requests = thisCopy.getFriendRequests();
				auto it = std::find(requests.begin(), requests.end(), usernameOfFriendToDelete);
				int index = std::distance(requests.begin(), it);

				//delete the request
				thisCopy.deleteFriendRequest(index);
				// Update this on network
				myNetwork->getUsers()->at(indexOfThisInNetwork) = thisCopy;

				cout << "Friend request removed successfully " << endl;
			}
		} catch (int& e) {}
	}
}


//also delete this from the other persons friend list
void User::deleteFriend(string usernameOfFriendToDelete, UserNetwork* myNetwork){
    
    for (auto iter = myNetwork->getUsers()->begin(); iter != myNetwork->getUsers()->end(); iter++) {
		
		//first deal with this user
		try {
			if (iter->getUsername() == this->getUsername()){
				//find this user on network
				int indexOfThisInNetwork = myNetwork->findUser(this->getUsername());
				//make a copy of this so we can set the god damned changes in network scope
				User thisCopy = User(myNetwork->getUsers()->at(indexOfThisInNetwork));
				//find index of request in this's friend requests

				vector<string> requests = thisCopy.getFriendRequests();
				auto it = std::find(requests.begin(), requests.end(), usernameOfFriendToDelete);
				int index = std::distance(requests.begin(), it);
	

				//delete them from our friend's list:
				//first make a copy
				vector<string> thisFriendsListCopy = thisCopy.getFriends();
				//then remove @ our ex friend's index from it
				thisFriendsListCopy.erase(thisFriendsListCopy.begin() + index);
				//then set thisCopy's friends list
				thisCopy.setFriends(thisFriendsListCopy);
				// Update this on network
				myNetwork->getUsers()->at(indexOfThisInNetwork) = thisCopy;
			}

			//next deal with other user
			if (iter->getUsername() == usernameOfFriendToDelete) {

				int deleteeIndex = myNetwork->findUser(usernameOfFriendToDelete);
		       	// copy of this user made using copy ctor
				User friendCopy = User(myNetwork->getUsers()->at(deleteeIndex));
				
				// find index of this user in friend's friend list
				vector<string> friends = friendCopy.getFriends();
				auto it = std::find(friends.begin(), friends.end(), this->getUsername());
				int indexToDelete = std::distance(friends.begin(), it);

				//delete us from their friend's list
				//first make a copy
				//then remove us from it
				friends.erase( friends.begin() + indexToDelete);
				//then set friendCopy's friends list
				friendCopy.setFriends(friends);
				// Update other user on network
				myNetwork->getUsers()->at(deleteeIndex) = friendCopy;
			}
		} catch (int& e) {}
	} 
}

bool operator==(const User& left, const User& right) {
	return left.getUsername() == right.getUsername();		
}

bool operator !=(const User& left, const User& right) {
	return !(left == right);
}
