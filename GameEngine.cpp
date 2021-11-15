#include "GameEngine.h"
#include "Map.h"
#include "Player.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
Map Map::worldMap;

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
    
    //validateMap();
    //add players
 //  addPlayer();

}


//prompt the user to give a path for a map
void GameEngine::loadMap() {
    //promp user to enter the name of the map file
    cout << "Please enter the name of the map file you want to load(end with .map format):" << endl;
    cin >> inputMapFile;
    //load map to game engine
    MapLoader map;
    //testmap
    inputMapFile = "europe.map";
    map.setMapFile(inputMapFile);
    ifstream fin(inputMapFile);
    if (!fin) {
        cout << "The map name is invalid! Pls double-check the map name and restart ur game! " << endl;
        setState(GameState::finsihed);
        
    }
    else {
        cout << "The map has been successfully loaded! Now you can go to next step -- validateMap! " << endl;
        setState(GameState::map_loaded);
        
    }
    map.readMap(inputMapFile);
    Map::worldMap.displayContinents();
	
}

//To see if the map is valid or invaild
void GameEngine::validateMap() {
	// 1. use the Map.validate() function to validate map.
	if (Map::worldMap.validate()) {
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
    while (numOfPlayers < 2 || numOfPlayers>6) {
        cout << "Pls enter a valid number (2-6) ";
        cin >> numOfPlayers; // add input validation again
    }
    
    vector<Territory*> territory;
    vector<Card*> card;
    vector<Order*> order;
    for(int i = 0; i < numOfPlayers; i++){
        cout << "Please enter the player name for player ID: " << i + 1 << " Player: " << endl;
        cin >> playerName;
        player_list.push_back(new Player(i, playerName));
        //cout << player_list.at(i) << endl;
    }
	// 2. players added successfully, print message.
	cout << "Valid number of players are created. Now you can go to next step -- assignCountries" << endl;
	setState(GameState::players_added);
}

//determine randomly the order of play of the players in the game
void GameEngine::shufflePlayerList() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(player_list.begin(), player_list.end(), g);
}

void GameEngine::gameStart(){
    
    //assign territory to players in round-robin fashion
    cout << "\n The territories are assigned in the following order: " << endl;

    for (int i = 0; i < Map::worldMap.territories.size(); i++) {
        Map::worldMap.territories[i]->setTerritoryPlayer((player_list.at(i % numOfPlayers))->getName());
        string territoryPlayer = Map::worldMap.territories[i]->getTerritoryPlayer();
        string territoryName = Map::worldMap.territories[i]->getTName();

        cout << setw(12) << "Territory: " << territoryName << ", owned by " <<  territoryPlayer << endl;
    }
    //initialize 50 armies to each player
    for (int k = 0; k < numOfPlayers; k++) {
        (player_list.at(k))->setReinforcementPool(50);

    }
    cout << "Every player has 50 armies at beginning. Good Luck!";

    shufflePlayerList();

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
    cout << "reinforcementPhase"<<endl;
 GameEngine::reinforcementPhase();
 cout << "issueOrdersPhase" << endl;
    GameEngine::issueOrdersPhase();
    cout << "executeOrdersPhase" << endl;
    GameEngine::executeOrdersPhase();
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
        for(auto j : Map::worldMap.continents) {									//Compare map continent size with player count
            //if (j->territoriesInContinent.size() == numTerritoriesPerContinent[index++]) {
           //     i->reinforcements += Map::worldMap.continents[index-1]->getBonus();		//If player owns all territories in continent, add bonus to reinforcements
           // }
            continue;
        }

        if (i->reinforcements < 3)
            i->reinforcements = 3;
    }
}

//Please uncomment this method when you finished
void GameEngine::issueOrdersPhase() {
    for(auto i : player_list) {
        if (i->getReinforcementPool() > 0) {
            cout << "\nYou can place deploy orders now. " << endl;
            i->issueOrder();

            cout << "\n\n------------------issueorder complete!-------------------\n\n";
            cout << "You have " << i->getReinforcementPool()<< " armies now. " << endl;

            
            cout << "\n\n------------------test issueorder-------------------\n\n";
            cout << "\nWhich country do you want to defend?" << endl;
            cin >> defendNum;


            std::string input1 = defendNum;
            std::stringstream ss( defendNum);

            std::string word1;
            while (ss >> word1) {
                i->todefend(word1);

            }

            cout << "\nWhich country do you want to attack?" << endl;
            cin >> attackNum;


            std::string input = attackNum;
            std::stringstream bb(attackNum);

            std::string word;
            while (bb >> word) {
                i->toAttack(word);

            }
            cout << "\n\n------------------test issueorder complete-------------------\n\n";
        }
        else {
            cout << "You will enter the next step!!" << endl;
        }
    }
}


void GameEngine::executeOrdersPhase() {
    cout << "\n\n------------------execute order-------------------\n\n";
    for(auto i : player_list) {
        for (auto j : i->OrderList) {
            cout<<j.validate();
             j.execute();
        }
        if (i->lose() == true) {
            player_list.erase(player_list.begin());
        }
        if (i->win() == true) {
            break;
        }
    }
    cout << "\n\n------------------execute order complete-------------------\n\n";
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
