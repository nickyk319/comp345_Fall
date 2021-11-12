#pragma once
#include <list>
#include <string>


using namespace std;

class ILoggable {
public:
	virtual string stringToLog() = 0;
};

// generic observer
class Observer {
public:
	virtual void Update(ILoggable * l) = 0;
};

// generic subject
class Subject {
public:
	Subject();
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(ILoggable * l);
private:
	list<Observer*> _observers;
};


// concrete observer
class LogObserver : public Observer {
public:
	// write the string returned by l->stringToLog() into gameLog.txt
	void Update(ILoggable* l);

	LogObserver(Subject* s);
	~LogObserver();

private:
	Subject* _subject;
};