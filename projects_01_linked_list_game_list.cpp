/**
 * Project 1: GameList implemented using linked list
 */
#include "game_list.h"
#include "Array.h"
#include "Bridges.h"
#include "DataSource.h"
#include "SLelement.h"
#include "menu.h"
#include <cstdio>

GameList::GameList() {
  // Class constructor
  length = 0;
  listData = NULL;
}

GameList::~GameList() {
  // Post: List is empty; all items have been deallocated.
  makeEmpty();
}

void GameList::makeEmpty() {
  bridges::SLelement<std::string> *tempPos = listData;

  while (tempPos != NULL) {
    bridges::SLelement<std::string> *toBeDeleted = tempPos;
    tempPos = tempPos->getNext();
    delete toBeDeleted;
  }
  listData = nullptr;
  length = 0;
}

bool GameList::isFull() const {
  // Returns true if there is no room for another game
  //  on the free store; false otherwise.
  bridges::SLelement<std::string> *location;
  try {
    location = new bridges::SLelement<std::string>;
    delete location;
    return false;
  } catch (std::bad_alloc exception) {
    return true;
  }
}

int GameList::getLength() const {
  // Post: Number of items in the list is returned.
  return length;
}

void GameList::getGame(std::string title, std::string &gameDetails,
                       bool &found) {
  bridges::SLelement<std::string> *tempPos = listData;
  while (tempPos != NULL) {
    if (tempPos->getValue() == title) {
      found = true;
      gameDetails = tempPos->getLabel();
      tempPos = tempPos->getNext();
    } else {
      tempPos = tempPos->getNext();
    }
  }
}

void GameList::putGame(std::string title, std::string gameDetails,
                       double rating) {
  // create new game object
  bridges::SLelement<std::string> *newGame;
  newGame = new bridges::SLelement<std::string>(title, gameDetails);
  length += 1;
  // add item at beginning
  if (listData == NULL || listData->getValue() >= title) {
    newGame->setNext(listData);
    listData = newGame;
  } else {
    // determine position of insertion
    bridges::SLelement<std::string> *tempPos = listData;
    while (tempPos->getNext() != NULL &&
           tempPos->getNext()->getValue() < title) {
      tempPos = tempPos->getNext();
    }
    newGame->setNext(tempPos->getNext());
    tempPos->setNext(newGame);
  }
}

void GameList::deleteGame(std::string title) {
  // TODO Add code here.
  bridges::SLelement<std::string> *currentNode = listData;
  bridges::SLelement<std::string> *nodeRemove = currentNode->getNext();
  bridges::SLelement<std::string> *nodeSucceed = nodeRemove->getNext();
  bool found = false;
  // delete first node
  if ((currentNode->getValue() == title) && (currentNode == listData)) {
    listData = listData->getNext();
    delete currentNode;
    length--;
    return;
    // delete any other node
  } else {
    while (currentNode->getNext() != NULL) {
      bridges::SLelement<std::string> *nodeRemove = currentNode->getNext();
      bridges::SLelement<std::string> *nodeSucceed = nodeRemove->getNext();
      if (nodeRemove->getValue() == title) {
        found = true;
        currentNode->setNext(nodeSucceed);
        delete nodeRemove;

        length--;
        return;
      }
      currentNode = currentNode->getNext();
    }
  }
  if (found == false) {
    std::cout << " [" << title << " Not Found In List]";
  }
  // search through list to find element that matches
  // switch pointer to element
  // delete pointer from element
  // delete element
  // don't use currPos
}

void GameList::resetList() { currentPos = NULL; }

void GameList::getNextGame(std::string &title, std::string &gameDetails) {
  if (currentPos == NULL) {
    currentPos = listData;
  } else {
    currentPos = currentPos->getNext();
  }
  title = currentPos->getValue();
  gameDetails = currentPos->getLabel();
}
