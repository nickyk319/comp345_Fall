#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

GameEngine::GameEngine() {
	state = GameState::start;
	ol = new OrdersList();
	deck = new Deck();
    hand = new Hand();
	numOfPlayers = 0;
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
    maploaded->setMapFile(inputMapFile);
    maploaded->readMap();
	cout << "The map has been successfully loaded! Now you can go to next step -- validateMap! " << endl;
	setState(GameState::map_loaded);
}

//To see if the map is valid or invaild
void GameEngine::validateMap() {
	// 1. use the Map.validate() function to validate map.
	if (worldMap.validate()) {
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
        cout << "Please enter the player name for player ID: " << i + 1 << " Player: " << endl;
        cin >> playerName;
        player_list.push_back(new Player(i, playerName));
    }
	// 2. players added successfully, print message.
	cout << "Valid number of players are created. Now you can go to next step -- assignCountries" << endl;
	setState(GameState::players_added);
}

void GameEngine::gameStart(){
    //assign territory to players in round-robin fashion
    cout << "\n The territories are assigned in the following order: " << endl;

    for (int i = 0; i < worldMap.territories.size(); i++) {
        worldMap.territories[i]->setTerritoryPlayer((player_list.at(i % numOfPlayers))->getName());
        string territoryPlayer = worldMap.territories[i]->getTerritoryPlayer();
        string territoryName = worldMap.territories[i]->getTName();

        cout << setw(12) << "Territory: " << territoryName << ", owned by " <<  territoryPlayer << endl;
    }
    //initialize 50 armies to each player
    for (int k = 0; k < numOfPlayers; k++) {
        (player_list.at(k))->setReinforcementPool(50);
    }

    //initialize a card deck
    cout << "\n<Initialize Deck>" << endl;
    cout << "\nThe size of deck now is " << endl;
    cout << deck->getCards().size() << endl;
    cout << "\nTake 2 cards from deck to hand:" << endl;
    for(int i = 0; i < numOfPlayers; i++){
        player_list[i]->handCard.push_back(deck->draw());
        player_list[i]->handCard.push_back(deck->draw());
    }

    for(int i = 0; i < numOfPlayers; i++){
        cout << *(player_list[i]) << endl;
    }
}

//Assign countries to player
void GameEngine::assignCountries() {
	cout << "Countries have been successfully assigned to each player. Now you can go to the next step -- issueOrder" << endl;
	setState(GameState::assign_reinforcement);
}

//
void GameEngine::mainGameLoop() {
    //Find order setup from gamestart()

}

void GameEngine::reinforcementPhase() {

    //Loop over all players
    for(auto i : player_list) {												//Need Player Order from part 2
        i->reinforcements = floor(i->territories.size() / 3);				//Initial reinforcement pool = floor(#territories / 3)

        //Does player own a continent?
        vector <int> numTerritoriesPerContinent = { 0 };					//Vector to hold count of # of territories per continent
        for(auto j : i->territories)
            numTerritoriesPerContinent[j->getCID()]+=1;						//Increment count at position CID

        int index = 1;
        for(auto j : worldMap.continents) {									//Compare map continent size with player count
            if (j->territoriesInContinent.size() == numTerritoriesPerContinent[index++]) {
                i->reinforcements += worldMap.continents[index-1]->getBonus();		//If player owns all territories in continent, add bonus to reinforcements
            }
            continue;
        }

        if (i->reinforcements < 3)
            i->reinforcements = 3;
    }
}

//Please uncomment this method when you finished
//void GameEngine::issueOrdersPhase() {
//    for(auto i : player_list) {
//        i->issueOrder();
//    }
//}

void GameEngine::executeOrdersPhase() {
    for(auto i : player_list) {

    }
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
