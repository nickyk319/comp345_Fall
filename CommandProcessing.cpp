#include "CommandProcessing.h"
//runable version master


// ******************* Command ********************
Command::Command(string commandDesc): command(commandDesc), effect("") {
	type = CommandType::none;
	// initialize command type
	if (commandDesc.find("loadmap") != string::npos) {
		type = CommandType::loadmap;
	}
	else if (commandDesc.find("validatemap") != string::npos) {
		type = CommandType::validatemap;
	}
	else if (commandDesc.find("tournament") != string::npos) {
		type = CommandType::tournament;
	}
	else if (commandDesc.find("addplayer") != string::npos) {
		type = CommandType::addplayer;
	}
	else if (commandDesc.find("gamestart") != string::npos) {
		type = CommandType::gamestart;
	}
	else if (commandDesc.find("replay") != string::npos) {
		type = CommandType::replay;
	}
	else if (commandDesc.find("quit") != string::npos) {
		type = CommandType::quit;
	}
}

Command::~Command() {

}

void Command::saveEffect(string e) {
	effect = e;
	Notify(this);
}

string Command::stringToLog() {
	return "Command's Effect: " + effect;
}

// ******************* Command Processor **************
CommandProcessor::CommandProcessor() {
	// set initial state
	state = GameState::start;
}

CommandProcessor::~CommandProcessor() {

}


string CommandProcessor::readCommand() {
	string str;
	getline(cin, str);
	return str;
}


Command* CommandProcessor::getCommand() {
	Command* c = new Command(readCommand());
	saveCommand(c);
	return c;
}


bool CommandProcessor::validate(Command* c) {
	if (c->type == Command::CommandType::loadmap) {
		if (state == GameState::start || state == GameState::map_loaded) {
			return true;
		}
	}
	else if (c->type == Command::CommandType::validatemap) {
		if (state == GameState::map_loaded) {
			return true;
		}
	}
	else if (c->type == Command::CommandType::tournament) {
		if (state == GameState::start) {
			return true;
		}
	}
	else if (c->type == Command::CommandType::addplayer) {
		if (state == GameState::map_validated || state == GameState::players_added) {
			return true;
		}
	}
	else if (c->type == Command::CommandType::gamestart) {
		if (state == GameState::players_added) {
			return true;
		}
	}
	else if (c->type == Command::CommandType::replay) {
		if (state == GameState::win) {
			return true;
		}
	}
	else if (c->type == Command::CommandType::quit) {
		if (state == GameState::win) {
			return true;
		}
	}

	return false;
}

void CommandProcessor::saveCommand(Command* c) {
	savedCommands.push_back(c);
	Notify(this);
}

void CommandProcessor::setState(GameState s) {
	state = s;
}

GameState CommandProcessor::getState() {
	return state;
}

void CommandProcessor::printAllCommands() {
	for (Command* c : savedCommands) {
		cout << c->command << ": " << c->effect << endl;
	}
}

string CommandProcessor::stringToLog() {
	return "Command: " + savedCommands.at(savedCommands.size()-1)->command;
}

// ********************************************************
FileLineReader::FileLineReader(string filepath) {
	ifs.open(filepath);
	if (!ifs) {
		throw "file not found exception";
	}
}

FileLineReader::~FileLineReader() {
	ifs.close();
}

string FileLineReader::readlineFromFile() {
	if (!ifs.eof()) {
		string line;
		getline(ifs, line);
		return line;
	}

	else {
		throw "file end.";
	}
}

FileCommandProcessorAdapter::FileCommandProcessorAdapter(string filepath) {
	flr = new FileLineReader(filepath);
}

FileCommandProcessorAdapter::~FileCommandProcessorAdapter() {

}

string FileCommandProcessorAdapter::readCommand() {
	return flr->readlineFromFile();
}
