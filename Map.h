#ifndef _MAP_H
#define _MAP_H

#include <vector>
#include <set>
#include <string>

using namespace std;

class Territory {
public:
    int tID;    //Territory ID
    int cID;    //Continent ID
    int pID;    //Player ID
    int numArmy;
    string tName;   //Territory Name
    string cName;   //Continent Name
    string territoryPlayer;
    bool isAdjacent;  //Connected Continent Check

    vector<int> adjTerritoryOnMap;  //List of Adjacent Territories on entire map
    vector<int> adjTerritoriesInContinent;    //List of Adjacent Territories in same continent

    //Constructors
    Territory();
    Territory(int tID, int cID, string tName, string cName);

    //Getters
    int getTID();
    int getCID();
    int getPID();
    string getTerritoryPlayer();
    int getNumArmy();
    int getBelongedContinentID();
    string getTName();
    string getCName();
    bool getAdjContinent();
    vector<int> getAdjTerritoryOnMap(); //change to double
    vector<int> getAdjTerritoryInContinent();

    //Setters
    void setTID(int tID);
    void setTName(string tName);
    void setTerritoryPlayer(string);
    void setAdjContinent(bool canLeave);

    void displayBorders();
};
class Continent {
public:
    int cID;    //Continent ID
    string cName;   //Continent Name
    vector<Territory*> territoriesInContinent; //List of Territories in Continent
    set<int> connectedContinents;    //Adjacent Continents

    //Constructors
    Continent();
    Continent(string cName, int cID);

    //Getters
    int getCID();
    string getCName();
    vector<Territory*> getTerritoriesInContinent();
    set<int> getConnectedContinent();
    bool isConnected();
};
class Map {
public:
    string mName;   //Map Name
    int numContinent;   //# of all Continents
    int numTerritory;   //# of all Territories
    vector<Continent*> continents;  //Continents Vector
    vector<Territory*> territories; //Territories Vector

    //Constructors
    Map();
    Map(string mName, int numTerritory, int numContinent);

    //Getters
    string getMName();
    int getNumContinent();
    int getNumTerritory();
    vector<Territory*> getTerritories();

    //Setters
    void setMName(string mName);

    void displayTerritories();
    void displayContinents();
    void dfs(int i, vector<bool>& visited);
    void ccs(vector<bool>& visited);
    bool validate();
    bool connected();
    bool subgraphs();
    bool oneContinent();

};

class MapLoader {
public:
    Map worldMap;
    string mFile;

    MapLoader();

    string getMapFile();
    void setMapFile(const string& mf);
    vector<string> parseString(const string& s);
    vector<int> parseStringBorder(const string& s);
    void readMap();
};

//Global Functions
ostream& operator << (ostream& out, const Continent& c);
ostream& operator << (ostream& out, const Territory& t);
#endif