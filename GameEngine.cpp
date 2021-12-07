#include "GameEngine.h"
#include "CommandProcessing.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <random>
//runable version master
using namespace std;
Map Map::worldMap;

GameEngine::GameEngine() {
	state = GameState::start;
	ol = new OrdersList();
	deck = new Deck();
    hand = new Hand();
    maploaded = new MapLoader();
	numOfPlayers = 0;
}

void GameEngine::startUpPhase(){
    //load map
    cout << "enter O for A2 version GameEngine. or enter any key to access commandProcessing.cpp for A3" << endl;
    string z;
    cin >>z;
    if (z._Equal("O") || z._Equal("0") || z._Equal("o")) {
        cout << "-----------------old gameEngine-----------------" << endl;
        loadMap();
        //validate map
        validateMap();
        //add players
        addPlayer();
        //initialize game
        gameStart();
        mainGameLoop();
    }
  
    
}


//prompt the user to give a path for a map
void GameEngine::loadMap() {
    //promp user to enter the name of the map file
    cout << "Please enter the name of the map file you want to load(end with .map format):" << endl;
    cout << "test load europe.map, enter any key to contiune" << endl;
    cin >> inputMapFile;
    //load map to game engine
    inputMapFile = "europe.map";
    maploaded->setMapFile(inputMapFile);
    maploaded->readMap();
    cout << "************************************************************************************" << endl;
	cout << "\nThe map has been successfully loaded! Now you can go to next step -- validateMap! " << endl;
	setState(GameState::map_loaded);
}

//To see if the map is valid or invalid
void GameEngine::validateMap() {
	// 1. use the Map.validate() function to validate map.
	if (Map::worldMap.validate()) {
        cout << "************************************************************************************" << endl;
		cout << "\nThe map you loaded is valid! Now you can go to next step -- add players!" << endl;
		setState(GameState::map_validated);
	}
	else {
		cout << "Invalid map" << endl;
	}

}

//help user add the player 
void GameEngine::addPlayer() {
    do{
        // 1. ask for user input for number of players
        cout << "Enter the number of players you want to have (2-6): ";
        cin >> numOfPlayers; // add input validation
        vector<Territory*> territory;
        vector<Card*> card;
        vector<Order*> order;
        if(numOfPlayers > MAX_NUM_PLAYER || numOfPlayers < MIN_NUM_PLAYER){
            cout << "Invalid input, please enter again!" << endl;
        }
    }while(numOfPlayers>MAX_NUM_PLAYER || numOfPlayers < MIN_NUM_PLAYER);

    for(int i = 0; i < numOfPlayers; i++){
        cout << "Please enter the player name for player ID: " << i + 1 << " Player: " << endl;
        cin >> playerName;
        player_list.push_back(new Player(i, playerName));
    }
	// 2. players added successfully, print message.
    cout << "************************************************************************************" << endl;
	cout << "Valid number of players are created. Now you can go to next step -- assignTerritories" << endl;
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
        Map::worldMap.territories[i]->setPlayerID((player_list.at(i % numOfPlayers))->getPID());
        player_list.at(i % numOfPlayers)->territories.push_back(Map::worldMap.territories[i]);
        string territoryPlayer = player_list.at(i % numOfPlayers)->getName();
        string territoryName = Map::worldMap.territories[i]->getTName();

        cout << setw(12) << "Territory: " << territoryName << ", owned by " <<  territoryPlayer << endl;
    }
    //initialize 50 armies to each player
    for (int k = 0; k < numOfPlayers; k++) {
        (player_list.at(k))->setReinforcementPool(50);
    }

    //determine the order of play randomly
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
    cout << "reinforcementPhase" << endl;
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
        vector <int> numTerritoriesPerContinent = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};					//Vector to hold count of # of territories per continent
        for(auto j : i->territories)
            numTerritoriesPerContinent[j->getCID()]+=1;						//Increment count at position CID

        int index = 0;
        for(auto j : Map::worldMap.continents) {									//Compare map continent size with player count
            if (j->territoriesInContinent.size() == numTerritoriesPerContinent[index++]) {
                i->reinforcements += Map::worldMap.continents[index-1]->getBonus();		//If player owns all territories in continent, add bonus to reinforcements
            }
            continue;
        }

        if (i->reinforcements < 3)
            i->reinforcements = 3;
    }
}

//Please uncomment this method when you finished
void GameEngine::issueOrdersPhase() {
    for (auto i : player_list) {
        if (i->getReinforcementPool() > 0) {
            cout << "\nYou can place deploy orders now. " << endl;
            i->issueOrder();

            cout << "\n\n------------------issueorder complete!-------------------\n\n";
        }
        else {
            cout << "You will enter the next step!!" << endl;
        }
    }
}

void GameEngine::executeOrdersPhase() {
    cout << "\n\n------------------execute order-------------------\n\n";
    for (auto i : player_list) {
        for (auto j : i->OrderList) {
            cout << j.validate();
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
void GameEngine::tournamentmode_m() {
   
    do {
        cout << "Map selection: please enter 1 to 5(number of maps to play)" << endl;

        cin >> mapnum;
        if (mapnum > 5 || mapnum < 1) {
            cout << "Invalid input, please enter again!" << endl;
        }
    } while (mapnum>5|| mapnum<1);
        cout << "M: ";
        for (int i = 1; i<=mapnum; i++) 
        {
            cout << "Map" << i <<", ";
        }
        GameEngine::tournamentmode_p();
}
void GameEngine::tournamentmode_p() {
    do {
        // 1. ask for user input for number of players
        cout << "\nEnter the number of computer stratgies you want to have (2-4): ";
        cin >> numOfPlayers; // add input validation
        if (numOfPlayers > 4 || numOfPlayers < 2) {
            cout << "Invalid input, please enter again!" << endl;
        }
    } while (numOfPlayers > 4 || numOfPlayers < 2);
    playerName = "strategies";
    string s[5] = {"0 humanplayer","1 aggressive player","2 benevolent player","3 neutral player","4 cheater player" };
    for (int i = 0; i < numOfPlayers; i++) {
        //strategies name todo:0 humanplayer,1 aggressive player,2 benevolent player,3 neutral player,4 cheater player
        playerName = "strategies_"+s[i];
        cout << playerName << " add to list, " << endl;
        player_list.push_back(new Player(i, playerName));
    }
    // 2. players added successfully, print message.
    cout << "************************************************************************************" << endl;
    cout << "Player strategies initialize complete. Now go to next step -- number of games(g)" << endl;
    GameEngine::tournamentmode_g();
}
void GameEngine::tournamentmode_g() {
    
    do {
        // 1. ask for user input
        cout << "Enter the number of games you want to play (1-5): ";
        cin >> gamenum; // add input validation
        if (gamenum > 5 || gamenum < 1) {
            cout << "Invalid input, please enter again!" << endl;
        }
    } while (gamenum >5  || gamenum < 1);

    cout << "G: " << gamenum << endl;
     
       
   
    GameEngine::tournamentmode_d();
}
void GameEngine::tournamentmode_d() {
   
    do {
        // 1. ask for user input
        cout << "Enter the number of maximum truns for each game (10-50): ";
        cin >> turn; // add input validation
        if (turn > 50 || turn < 10) {
            cout << "Invalid input, please enter again!" << endl;
        }
    } while (turn > 50 || turn < 10);

    cout << "D: " << turn << endl;
    cout << "initialize complete:"<< endl;
    system("pause");
    printresult();
}
void GameEngine::printresult() {
    bool flag = true;
    for (int j = 1; j <= mapnum; j++) {
        for (int k = 1; k <= gamenum; k++) {
            flag = true;

            while (flag) {
                for (auto i : player_list) {
                    if (rand() % 100 < 50) {
                        cout << "\nON MAP£º" << j << "\nGAMENUMBER£º" << k << "\nPLAYER: " << i->getName() << " is the winner" << endl;
                        //cout <<"\n" << i->getName() << ":\nwin on map" << j << " on game number " << k << endl;
                        flag = false;
                       
                    }
                }

            }
           
        }
    }
    system("pause");
}