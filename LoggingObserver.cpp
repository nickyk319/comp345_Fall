#include "LoggingObserver.h"
#include <fstream>

Subject::Subject() {
	new LogObserver(this);
}

void Subject::Attach(Observer* o) {
	_observers.push_back(o);
}

void Subject::Detach(Observer* o) {
	_observers.remove(o);
}

void Subject::Notify(ILoggable* l) {
	for (Observer* o : _observers) {
		o->Update(l);
	}
}


LogObserver::LogObserver(Subject* s) : _subject(s) {
	_subject->Attach(this);
}

LogObserver::~LogObserver() {
	_subject->Detach(this);
}

void LogObserver::Update(ILoggable * l) {

	ofstream ofs;
	ofs.open("gameLog.txt", ofstream::app);
	ofs << l->stringToLog() << endl;
	ofs.close();
}