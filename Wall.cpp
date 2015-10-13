#include "Wall.h"
#include <sstream>
#include <string>
#include <vector>

// Destructor deletes data allocated for wallPosts pointer
Wall::~Wall() {
	delete wallPosts;
	this->username.clear(); //not sure if we want to do this or not
}

string Wall::getUsername() {
	return this->username;
}

void Wall::setUsername(string username_) {
	this->username = username_;
}

// Uses function from DoublyLinkedList template
void Wall::addPost(WallPost post) {
	this->wallPosts->addToEnd(post);
}

void Wall::deletePost(WallPost post) {
	this->wallPosts->deleteByValue(post);
}


// Writes out all WallPosts on the wall to one string
string Wall::toString() {
	string endString = string();
	Node<WallPost>* tmp = this->wallPosts->getHead();
	while (tmp) {
		// data refers to WallPost
		// call toString method of each WallPost
		endString.append(tmp->data.toString());
		//add a separator
		endString.append("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		//Iterate through all WallPosts
		tmp = tmp->next;
	}
	return endString;
}

void Wall::readWallPostsFromString (const string fullWallString_) {
	

	//set our between-post separator 
	std::string fullWallString = fullWallString_;
	std::string nextPostDelimiter = "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	
	
	//initialize some position markers and strings to hold results
	size_t postEndPos, timeEndPos, authorEndPos;
	std::string post, content, author, time;
	
	//loop through full posts (looking for our big delimiter)
	while ((postEndPos = fullWallString.find(nextPostDelimiter)) != std::string::npos) {
		post = fullWallString.substr(0, postEndPos);
			//now we have a full post, time to grab our date string from between "On" and "\n"
			timeEndPos = post.find("\n");
			time = post.substr(3, timeEndPos - 3);
			post.erase(0, timeEndPos + 1); //add 1 to remove our "\n" delimiter too
			//now we pull the author
			authorEndPos = post.find(" wrote:\n");
			author = post.substr(0, authorEndPos);
			post.erase(0, authorEndPos + 8); // add 8 because " wrote:\n" is 8 characters long
			// content is just what is left over in post now that we've stripped the rest
			content = post;
			
			addPost(WallPost(content, author, time));
			
		fullWallString.erase(0, postEndPos + nextPostDelimiter.length());
	}
}











