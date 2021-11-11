#pragma once

#include <string>
#include "Cards.h"
#include "Map.h"
#include "Order.h"
#include "Player.h"


enum class GameState {
	start, map_loaded, map_validated, players_added, assign_reinforcement, issue_orders, execute_orders, win, finsihed
};

class GameEngine {

private:
	GameState state;
    MapLoader *maploaded;
	OrdersList* ol;
	Deck* deck;
    Hand *hand;
	int numOfPlayers;
    const int MAX_NUM_PLAYER = 6;
    string playerName;
    string inputMapFile;
    
    vector<Territory *> territory_list;


public:
	GameEngine();
	vector<Player*> player_list;
    int convert_name_to_id();
    void initializePlayers();
    void shufflePlayerList();
    void startUpPhase();
    void gameStart();

	string stateToString() {
		switch (state) {
		case GameState::start:
			return "start";
		case GameState::map_loaded:
			return "map_loaded";
		case GameState::map_validated:
			return "map_validated";
		case GameState::players_added:
			return "players_added";
		case GameState::assign_reinforcement:
			return "assign_reinforcement";
		case GameState::issue_orders:
			return "issue_orders";
		case GameState::execute_orders:
			return "execute_orders";
		case GameState::win:
			return "win";
		}
	}

	GameState getState() {
		return state;
	}

	void setState(GameState s) {
		state = s;
	}

	/* the following functions represents the transition functions(edges) */

	// startup phase
	void loadMap();
	// 1. ask for player input for a map file path
	// 2. create a maploader instance
	// 3. pass the file path to maploader
	// 4. load map(MapLoader.readMap()), and make your game engine store the map that was loaded
	// 5. if load fails(file path not found or other error), repeat 1-4
	// 6. if load succeed, print message to console.

	void validateMap();
	// 1. use the Map.validate() function to validate map. 
	// 2. if map not valid, return false.
	// if valid, print message to console.


	void addPlayer();
	// 1. ask for user input for number of players
	// 2. use loop to create players and put them into a playerlist
	// players added successfully, print message. 


	void assignCountries();
	// Assign every country in the map to all players in round robin fashion.

    void mainGameLoop();
    //

    void reinforcementPhase();
    //

    void issueOrdersPhase();
    //

    void executeOrdersPhase();
    //

	void issueOrder();
	// call the issue order function of each player
	// issue order frunction should return an order pointer.
	// store the returned order into order list (ol).


	void endIssueOrders();

	void executeOrder();
	// loop over order list (ol), and call the validate() and execute() function of each order
	// once an order is done executing, delete it from the order list. 


	void endExecuteOrders();

	void checkWinner();
	// tell the player if a winner has be decided.

	void replay();

	void end() {
		exit(0);
	}

};
