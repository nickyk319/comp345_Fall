#include <iostream>
#include "GameEngine.h"
#include "Map.h"


int main() {
	GameEngine* ge = new GameEngine();
    ge->startUpPhase();

	while (true) {
		cout << "---------- " << ge->stateToString() << " ------------" << endl;
		string command = "";
		cout << "$> ";
		cin >> command;
		if (command == "loadmap" &&
			(ge->getState() == GameState::start || ge->getState() == GameState::map_loaded)) {
			ge->loadMap();
		}
		else if (command == "validatemap" && ge->getState() == GameState::map_loaded) {
			ge->validateMap();
		}
		else if (command == "addplayer" && (ge->getState() == GameState::map_validated || ge->getState() == GameState::players_added)) {
			ge->addPlayer();
		}
		else if (command == "assigncountries" && ge->getState() == GameState::players_added) {
			ge->assignCountries();
		}
		else if (command == "issueorder" && (ge->getState() == GameState::assign_reinforcement || ge->getState() == GameState::issue_orders || ge->getState() == GameState::players_added)) {
			ge->mainGameLoop();
		}
		else if (command == "endissueorders" && ge->getState() == GameState::issue_orders) {
			ge->endIssueOrders();
		}
		else if (command == "executeorders" && ge->getState() == GameState::execute_orders) {
			ge->executeOrder();
		}
		else if (command == "endexecuteorders" && ge->getState() == GameState::execute_orders) {
			ge->endExecuteOrders();
		}
		else if (command == "checkwinner" && ge->getState() == GameState::execute_orders) {
			ge->checkWinner();
		}
		else if (command == "end" && ge->getState() == GameState::win) {
			ge->end();
		}
		else if (command == "play" && ge->getState() == GameState::win) {
			ge->replay();
		}
		else {
			cout << "invalid command!" << endl << endl;

		}


	}
}