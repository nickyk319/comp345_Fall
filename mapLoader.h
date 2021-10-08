#ifndef PART2_MAPLOADER_H
#define PART2_MAPLOADER_H


#include "Map.h"

class mapLoader {
public:
    Map* worldMap;
    string mapRoutinue;

    mapLoader();

    string getMapFile();
    void setMapFile(const string& mf);
    vector<string> tokenizeString(const string& s);
    void readMap();
    void validate();

};


#endif 
#pragma once
