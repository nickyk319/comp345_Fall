#include "GameEngine.h"
#include <iostream>



GameEngine::GameEngine() {
	state = GameState::start;
	//map = nullptr;
	ol = new OrdersList();
	deck = new Deck();
	numOfPlayers = 0;
}



//promt the user to give a path for a map
void GameEngine::loadMap() {
	//bool validFile = true;
	//// 1. ask for player input for a map file path
	//do{
	//	validFile = true;
	//	cout << "Please select a map: ";
	//	string path = "";
	//	cin >> path;
	//	// 2. create a maploader instance // 3. pass the file path to maploader
	//	MapLoader* ml = new MapLoader();
	//	ml->setMapFile(path);

	//	try {
	//		// 4. load map(MapLoader.readMap()), and make your game engine store the map that was loaded
	//		ml->readMap();
	//	}
	//	// 5. if load fails(file path not found or other error), repeat 1-4
	//	catch (string e) {
	//		cout << "error code: " << e << endl;
	//		validFile = false;
	//	}
	//} while (!validFile);
	//map = ml->worldMap;
	cout << "The map has been succesfullly loaded! Now you can go to next step -- validateMap! " << endl;
	setState(GameState::map_loaded);
}

//To see if the map is valid or invaild
void GameEngine::validateMap() {
	// 1. use the Map.validate() function to validate map.
	if (/*map->validate()*/ true) {
		cout << "The map you loaded is valide! Now you can go to next step -- addplayer!" << endl;
		setState(GameState::map_validated);
	}
	else {
		cout << "Invalid map" << endl;
	}

}

void GameEngine::addPlayer() {
	// 1. ask for user input for number of players
	cout << "Enter the number of players you have!(2-5): ";
	cin >> numOfPlayers; // add input validation
	// 2. use loop to create players and put them into a playerlist

	//for (int i = 0; i < numOfPlayers; i++) {
	//	playerList.puch_back(new Player());
	//}
	// 3. players added successfully, print message.
	cout << "Valid number of players are created. Now you can go to next step -- assignCountries" << endl;
	setState(GameState::players_added);
}

void GameEngine::assignCountries() {

	//for (int i = 0; i < map->territories.size(); ++i) {
	//	map->territories.at(i)->pID = i % numOfPlayers;
	//}

	cout << "Countries have been sucessfully assigned to each player. Now you can go to the next step -- issueOrder" << endl;
	setState(GameState::assign_reinforcement);
}

// function for assign reinforcement? 

void GameEngine::issueOrder() {
	// call the issue order function of each player
	//for (Player* p : playerList) {
	//	p->issueOrder();
	//}
	// issue order frunction should return an order pointer.
	// store the returned order into order list (ol).
	cout << "Orders have been issued secessfully. If you finished making orders, now you can go the the next step -- endIssueOrders" << endl;
	setState(GameState::issue_orders);
}

void GameEngine::endIssueOrders() {
	cout << "Now you can not issue orders anymore. You can go te the next step -- executeOrders" << endl;
	state = GameState::execute_orders;
}

void GameEngine::executeOrder() {
	// loop over order list (ol), and call the validate() and execute() function of each order
	//for (Order* o : *ol->olist) {
	//	o->validate(); 
	//	o->execute();
	//}
	cout << "Orders have been executed succesfully. If you finished executing orders, now you can go to next step -- endExecuteOrders or cheakwinner" << endl;

	setState(GameState::execute_orders);
}

void GameEngine::endExecuteOrders() {
	cout << "Now you can not execute orders anymore. You can go te the next step -- checkwinner" << endl;
	state = GameState::assign_reinforcement;
}

void GameEngine::checkWinner() {
	// tell the player if a winner has be decided.
	//??player????????winner?? 
	// if winner contain player 
	//cout << "The Winner is " << winnner << endl;
	//// if there is no winner yet 
	//cout << "There is no winner yet!";

	cout << "check winners" << endl;
	setState(GameState::win);
}

void GameEngine::replay() {
	cout << "A brand new game has started!" << endl;
	state = GameState::start;
}
