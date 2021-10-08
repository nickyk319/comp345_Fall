#include "MapLoader.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


void mapLoader::readMap()
{
    bool checkMap = false;
    bool checkContinent = false;
    bool checkTerritory = false;
    bool checkAdjacent = false;
    int continentNum = 0;
    int territoryNum = 0;
    int adjacentRow = 0;
    string textContent;

    // stream from reading
    ifstream MyReadFile(this->mapRoutinue);

    // to read all the text in the txt by lines
    while (getline(MyReadFile, textContent)) {

        //map validate check
        if (textContent == "[files]") {
            checkMap = true;
            continue;
        }
        //check whether the file is map & read all the lines in map
        if (checkMap) {
            vector<string> line;
            cout << textContent << endl;
            line = tokenizeString(textContent);
            if (line.size() != 3) {
                cout << "The file is wrong pls check it again" << endl;
                break;
            }
            this->worldMap = new Map(line[0], stoi(line[1]), stoi(line[2]));
            checkMap = false;
            //cout<<worldMap->getNumOfAllTerritory()<<endl;
        }

        //continent validate check
        if (textContent == "[continents]") {
            checkContinent = true;
            continue;
        }
        //check whether the file is continent & read all the lines in continent
        if (checkContinent) {
            continentNum++;
            vector<string> line;
            cout << textContent << endl;
            line = tokenizeString(textContent);
            if (line.size() != 2) {
                cout << "The file is wrong pls check it again" << endl;
                break;
            }
            worldMap->continents.push_back(new Continent(line[0], stoi(line[1])));
            if (continentNum == worldMap->getNumContinent()) {
                checkContinent = false;
            }
        }

        //territory validate check
        if (textContent == "[countries]") {
            checkTerritory = true;
            continue;
        }
        //check whether the file is territory & read all the lines in territory
        if (checkTerritory) {
            territoryNum++;
            vector<string> line;
            cout << textContent << endl;
            line = tokenizeString(textContent);
            if (line.size() != 4) {
                cout << "The file is wrong pls check it again" << endl;
                break;
            }
            worldMap->territories.push_back(new Territory(line[0], line[1], stoi(line[2]), stoi(line[3])));
            if (territoryNum == worldMap->getNumTerritory()) {
                checkTerritory = false;
            }
        }

        //validate check
        if (textContent == "Adjacent status:") {
            checkAdjacent = true;
            continue;
        }
        //check whether the text is adjacent & read all the lines in adjacent
        if (checkAdjacent) {
            vector<string> line;
            line = tokenizeString(textContent);
            if (line.size() > worldMap->getNumTerritory()) {
                cout << "The file is wrong pls check it again" << endl;
                break;
            }
            for (auto& i : line) {
                worldMap->territories[adjacentRow]->adjTerritoryOnMap.push_back(stoi(i));
                int currentContinent = worldMap->territories[adjacentRow]->getCID();
                if (adjacentRow != stoi(i) && currentContinent == worldMap->territories[stoi(i)]->getCID()) {
                    worldMap->territories[adjacentRow]->adjTerritoriesInContinent.push_back(stoi(i));
                }
                if (adjacentRow != stoi(i) && currentContinent != worldMap->territories[stoi(i)]->getCID()) {
                    worldMap->continents[currentContinent]->connectedContinents.insert(worldMap->territories[stoi(i)]->getCID());
                }
            }
            adjacentRow++;
            if (adjacentRow == worldMap->getNumTerritory()) {
                checkTerritory = false;
            }
        }

    }
    // stream close
    MyReadFile.close();
    }