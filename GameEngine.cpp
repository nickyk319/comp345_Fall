#include "GameEngine.h"
#include <iostream>
#include <iomanip>

GameEngine::GameEngine() {
	state = GameState::start;
	ol = new OrdersList();
	deck = new Deck();
	numOfPlayers = 0;
    player_list ;
}

void GameEngine::startUpPhase(){
    //load map
    loadMap();
    //validate map
    validateMap();
    //add players
    addPlayer();

}

//prompt the user to give a path for a map
void GameEngine::loadMap() {
    //promp user to enter the name of the map file
    cout << "Please enter the name of the map file you want to load(end with .map format):" << endl;
    cin >> inputMapFile;
    //load map to game engine
    mapLoaded->setMapFile(inputMapFile);
    mapLoaded->readMap();
	cout << "The map has been successfully loaded! Now you can go to next step -- validateMap! " << endl;
	setState(GameState::map_loaded);
}

//To see if the map is valid or invaild
void GameEngine::validateMap() {
	// 1. use the Map.validate() function to validate map.
	if (mapLoaded->worldMap.validate()) {
		cout << "The map you loaded is valid! Now you can go to next step -- add players!" << endl;
		setState(GameState::map_validated);
	}
	else {
		cout << "Invalid map" << endl;
	}

}

//help user add the player 
void GameEngine::addPlayer() {
	// 1. ask for user input for number of players
	cout << "Enter the number of players you want to have (2-6): ";
	cin >> numOfPlayers; // add input validation
    vector<Territory*> territory;
    vector<Card*> card;
    vector<Order*> order;
    for(int i = 0; i < numOfPlayers; i++){
        cout << "Please enter the player name for " << i + 1 << " Player: " << endl;
        cin >> playerName;
        player_list.push_back(new Player(playerName));
    }
	// 2. players added successfully, print message.
	cout << "Valid number of players are created. Now you can go to next step -- assignCountries" << endl;
	setState(GameState::players_added);
}

void GameEngine::gameStart(){
    //assign territory to players in round-robin fashion
    cout << "\n The territories are assigned in the following order: " << endl;

    for (int i = 0; i < mapLoaded->worldMap.territories.size(); i++) {
        mapLoaded->worldMap.territories[i]->setTerritoryPlayer((player_list.at(i % numOfPlayers))->getName());
        string territoryPlayer = mapLoaded->worldMap.territories[i]->getTerritoryPlayer();
        string territoryName = mapLoaded->worldMap.territories[i]->getTName();

        cout << setw(12) << "Territory: " << territoryName << " owned by " <<  territoryPlayer << endl;
    }


}

//Assign countries to player
void GameEngine::assignCountries() {
	cout << "Countries have been successfully assigned to each player. Now you can go to the next step -- issueOrder" << endl;
	setState(GameState::assign_reinforcement);
}

//issue the order
void GameEngine::issueOrder() {
	cout << "Orders have been issued successfully. If you finished making orders, now you can go the the next step -- endIssueOrders" << endl;
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
