#include "CommandProcessing.h"


void executeCommand(Command* c, CommandProcessor* cp) {
	// validate command
	if (cp->validate(c)) {
		if (c->type == Command::CommandType::loadmap) {
			cp->setState(GameState::map_loaded);
			c->saveEffect("Map " + c->command.substr(c->command.find("<")) + " has been loaded.");
		}
		else if(c->type == Command::CommandType::validatemap){
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
	else{
		c->saveEffect("Invalid command was not executed");
	}
}


int main(int argc, char* argv[]) {


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

		// print state
		cout << (int)cp->state << endl;
		// print all commands
		cp->printAllCommands();

		Command* command = cp->getCommand();

		// execute the command 
		executeCommand(command, cp);

		system("cls");
	}

}