// Basic file for testing implementations

#include "DoublyLinkedList.h"
#include "WallPost.h"
#include "Wall.h"
#include "User.h"
#include "UserNetwork.h"

int main()
{ 
  
  WallPost myPost = WallPost("Hi this is my first post", "Jonathan Easterman");
  cout << myPost << endl;

  WallPost otherPost = WallPost();
  otherPost.setContent("And this is my second post");
  otherPost.setAuthor("Jonathan Easterman");
  otherPost.setTimePosted();
  cout << otherPost.getAuthor() << otherPost.getContent() << otherPost.getTimePosted() << endl;
  cout << otherPost << endl;
/*
  Wall myWall = Wall();

  WallPost wallPost = WallPost("Here is my wall!", "WallPost creator");

  myWall.addPost(myPost);
//segfault
  cout << "make it here?" << endl;
  myWall.addPost(otherPost);

  myWall.deletePost(0);
  myWall.addPost(wallPost);


  


  Wall newWall = Wall(myWall);
  
  myWall.deletePost(0);
  
  cout << newWall.toString() << endl;
  
 
  cout << myWall.toString() << endl;
  cout << "\n\n^%^%^&%^&%^&------DESIRED CONTENT ABOVE%$^$%^$%^%$\n\n";
  
  cout << myWall.toString() << endl;
  
  string myWallStr = myWall.toString();
  Wall myOtherWall = Wall();
  myOtherWall.readWallPostsFromString(myWallStr);

  cout << myOtherWall.toString() << endl;*/

  User Ish = User("feshies", "pass123", "Ishi von Meier", "Goleta, CA");
  Ish.addPost(otherPost);
  User Jon = User("jonny", "pass234", "Jonathan Beasterman", "Queefville, CA");/*
  Jon.addPost(myPost);
  cout << Ish.toString() << endl;
  cout << "\n\n^%^%^&%^&%^&------DESIRED CONTENT ABOVE%$^$%^$%^%$\n\n";
  string ishUserString = Ish.toString();
  //Ish.readUserFromString(ishUserString);

  cout << Ish.toString() << endl;

  
  UserNetwork myNetwork = UserNetwork();
  myNetwork.addUser(Ish);
  cout << "trying to add duplicate user..." << endl;
  myNetwork.addUser(Ish);
  cout << "trying to add second user..." << endl;
  myNetwork.addUser(Jon);
  cout<< "trying to delete first User....." <<endl;
  myNetwork.deleteUser(Ish);

  cout << "trying toString(): ....." << endl;
  string stringToRead = myNetwork.toString();
  cout << myNetwork.toString() << endl;
  
  cout << "trying to write to file....." << endl;
  myNetwork.toFile();
  cout << "trying to read from a file ....." <<endl;
  UserNetwork copyNetwork = UserNetwork();
  copyNetwork.readFromFile();
  cout << copyNetwork.toString() << endl;
  
  cout << "WE GOT THE FUCKING STRING FROM THE FILE" << endl;
  
  cout << "\n\n^%^%^&%^&%^&------DESIRED CONTENT ABOVE%$^$%^$%^%$\n\n";

  copyNetwork.readUserNetworkFromString(stringToRead);
  cout << "string we read: ...." << endl;
  cout << copyNetwork.toString() << endl;
  

  cout << "end of program!" << endl;*/

  return 0;
}
