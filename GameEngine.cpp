#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <cmath>

using namespace std;

GameEngine::GameEngine() {
	state = GameState::start;
	ol = new OrdersList();
	deck = new Deck();
	numOfPlayers = 0;
}

//promt the user to give a path for a map
void GameEngine::loadMap() {
	cout << "The map has been succesfullly loaded! Now you can go to next step -- validateMap! " << endl;
	setState(GameState::map_loaded);
}

//To see if the map is valid or invaild
void GameEngine::validateMap() {
	// 1. use the Map.validate() function to validate map.
	if (true) {
		cout << "The map you loaded is valide! Now you can go to next step -- addplayer!" << endl;
		setState(GameState::map_validated);
	}
	else {
		cout << "Invalid map" << endl;
	}

}

//help user add the player 
void GameEngine::addPlayer() {
	// 1. ask for user input for number of players
	cout << "Enter the number of players you have!(2-5): ";
	cin >> numOfPlayers; // add input validation

	// 2. players added successfully, print message.
	cout << "Valid number of players are created. Now you can go to next step -- assignCountries" << endl;
	setState(GameState::players_added);
}

//Assign countries to player
void GameEngine::assignCountries() {
	cout << "Countries have been sucessfully assigned to each player. Now you can go to the next step -- issueOrder" << endl;
	setState(GameState::assign_reinforcement);
}

//
void GameEngine::mainGameLoop() {
	//Find order setup from gamestart()

}

void GameEngine::reinforcementPhase() {

	//Loop over all players
	for(auto i : players) {
		i.reinforcements = floor(i.territories.size() / 3);				//Initial reinforcement pool = floor(#territories / 3)

		//Does player own a continent?
		vector <int> numTerritoriesPerContinent = { 0 };					//Vector to hold count of # of territories per continent
		for(auto j : i.territories)
			numTerritoriesPerContinent[j->getCID()]+=1;						//Increment count at position CID

		int index = 1;
		for(auto j : worldMap.continents) {									//Compare map continent size with player count
			if (j->territoriesInContinent.size() == numTerritoriesPerContinent[index++]) {
				i.reinforcements += worldMap.continents[index-1]->getBonus();		//If player owns all territories in continent, add bonus to reinforcements
			}
		continue;
		}

		if (i.reinforcements < 3)
			i.reinforcements = 3;
	}
}

void GameEngine::issueOrdersPhase() {
	for(auto i : players) {
		i.issueOrder();
	}
}

void GameEngine::executeOrdersPhase() {
	for(auto i : players) {
	
	}
}

//issue the order
void GameEngine::issueOrder() {
	cout << "Orders have been issued secessfully. If you finished making orders, now you can go the the next step -- endIssueOrders" << endl;
	setState(GameState::issue_orders);
}

//finish issuing order
void GameEngine::endIssueOrders() {
	cout << "Now you can not issue orders anymore. You can go te the next step -- executeOrders" << endl;
	state = GameState::execute_orders;
}

//execute order for players 
void GameEngine::executeOrder() {
	cout << "Orders have been executed succesfully. If you finished executing orders, now you can go to next step -- endExecuteOrders or cheakwinner" << endl;
	setState(GameState::execute_orders);
}

//finish execute orders 
void GameEngine::endExecuteOrders() {
	cout << "Now you can not execute orders anymore. You can go te the next step -- checkwinner" << endl;
	state = GameState::assign_reinforcement;
}

//cheak if there is a winner 
void GameEngine::checkWinner() {
	cout << "check winners" << endl;
	setState(GameState::win);
}

//If the users want to replay 
void GameEngine::replay() {
	cout << "A brand new game has started!" << endl;
	state = GameState::start;
}
