#include <iostream>
#include "GameEngine.h"
#include "Map.h"
#include "CommandProcessing.h"
//runable version master
void executeCommand(Command* c, CommandProcessor* cp) {
	// validate command
	if (cp->validate(c)) {
		if (c->type == Command::CommandType::loadmap) {
			cp->setState(GameState::map_loaded);
			c->saveEffect("Map " + c->command.substr(c->command.find("<")) + " has been loaded.");
		}
		else if (c->type == Command::CommandType::tournament) {
			cp->setState(GameState::tournament_mode);
			c->saveEffect("tournament_mode.");
			
		}
		else if (c->type == Command::CommandType::m) {
			cp->setState(GameState::tournament_mode);
			c->saveEffect("<listofmapfiles>");
			GameEngine* tor = new GameEngine();
			tor->GameEngine::tournamentmode_m();
		}
		else if (c->type == Command::CommandType::p) {
			cp->setState(GameState::tournament_mode);
			c->saveEffect("<listofplayerstrategies>");

		}
		else if (c->type == Command::CommandType::g) {
			cp->setState(GameState::tournament_mode);
			c->saveEffect("<numberofgames>");

		}
		else if (c->type == Command::CommandType::d) {
			cp->setState(GameState::tournament_mode);
			c->saveEffect("<maxnumberofturns>");

		}
		else if (c->type == Command::CommandType::validatemap) {
			cp->setState(GameState::map_validated);
			c->saveEffect("Map under validation.");
		}
		else if (c->type == Command::CommandType::addplayer) {
			cp->setState(GameState::players_added);
			c->saveEffect("Player " + c->command.substr(c->command.find("<")) + " has been added.");
		}
		else if (c->type == Command::CommandType::gamestart) {
			cp->setState(GameState::assign_reinforcement);
			c->saveEffect("Game started.");
		}
		else if (c->type == Command::CommandType::replay) {
			cp->setState(GameState::start);
			c->saveEffect("Game restarted.");
		}
		else if (c->type == Command::CommandType::quit) {
			cp->setState(GameState::quit);
			c->saveEffect("Game quited.");
		}
	}
	else {
		cout<<("Invalid command was not executed")<<endl;
		system("pause");
	}
}
int main(int argc, char* argv[]) {
	GameEngine* ge = new GameEngine();
    ge->startUpPhase();

	CommandProcessor* cp = nullptr;

	if (argc > 1) {
		if (strcmp(argv[1], "-console") == 0) {
			cp = new CommandProcessor();
		}
		else if (argc > 2 && strcmp(argv[1], "-file") == 0) {
			cp = new FileCommandProcessorAdapter(argv[2]);
		}
		else {
			cp = new CommandProcessor();
		}
	}
	else {
		cp = new CommandProcessor();
	}

	while (true) {
		system("cls");
		// print state
		cout << "-----------------commandProcssing-----------------" << endl;
		cout << "gamestate: "<<(int)cp->getState() << endl;
		// print all commands
		cp->printAllCommands();

		Command* command = cp->getCommand();

		// execute the command 
		executeCommand(command, cp);

		
	}

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