#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LoggingObserver.h"
using namespace std;
//runable version master
enum class GameState {
	start, map_loaded, map_validated, players_added, assign_reinforcement, issue_orders, execute_orders, win, quit
};

// single command
class Command : public ILoggable, Subject{
public:
	enum class CommandType {loadmap, validatemap, addplayer, gamestart, replay, quit, none};

	// constructor
	Command(string commandDesc);
	//destructor 
	~Command();
	void saveEffect(string e);

	// forced implementation of ILoggable interface's function
	string stringToLog();

	string command;
	string effect;
	CommandType type;
};


class CommandProcessor: public ILoggable, Subject {
public:

	// constructor
	CommandProcessor();
	//destructor 
	~CommandProcessor();
	virtual string readCommand();

	// call read command function
	// create a command instance with the name returned from readCommand()
	// use saveCommand() to store the command into the list
	Command* getCommand();

	// 
	bool validate(Command* c);

	// might be private
	vector<Command*> savedCommands;

	// current game statesdf
	GameState state;
	// getter and setter
	void setState(GameState s);
	GameState getState();

	// forced implementation of ILoggable interface's function
	string stringToLog();

	void printAllCommands();

private:
	void saveCommand(Command* c);
};


class FileLineReader {
public:
	// constructor 
	FileLineReader(string filepath);
	//destructor 
	~FileLineReader();
	string readlineFromFile();

private:
	ifstream ifs;
};

class FileCommandProcessorAdapter : public CommandProcessor {
public:
	// constructor
	FileCommandProcessorAdapter(string filepath);
	//destructor 
	~FileCommandProcessorAdapter();
	virtual string readCommand();

private:
	FileLineReader* flr;
};
