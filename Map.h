#pragma once
#include <vector>
#include <set>
#include <string>
//runable version master
using namespace std;

class Territory {
public:
    int tID;    //Territory ID
    int cID;    //Continent ID
    int pID;    //Player ID
    int numArmy;
    string territoryPlayer = "default player";
    string tName;   //Territory Name
    string cName;   //Continent Name
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
    void setPlayerID(int);
    void setAdjContinent(bool canLeave);

    void displayBorders();
};

class Continent {
public:
    int cID;    //Continent ID
    int bonus;
    string cName;   //Continent Name
    vector<Territory*> territoriesInContinent; //List of Territories in Continent
    set<int> connectedContinents;    //Adjacent Continents

    //Constructors
    Continent();
    Continent(string cName, int cID, int bonus);

    //Getters
    int getCID();
    int getBonus();
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
    int getCountryIndex(int ID);
    vector<Territory*> getTerritories();
    void dfs(int i, set <bool>& visited);

    //Setters
    void setMName(string mName);

    void displayTerritories();
    void displayContinents();
    void dfs(int i, vector<bool>& visited,int leng);
    void ccs(vector<bool>& visited);
    bool validate();
    bool connected();
    bool subgraphs();
    bool oneContinent();
    bool belong_Onecontinent();
    bool continentMatched(int continentID);

    static Map worldMap;
};

class MapLoader {

public:
    string mFile;
    MapLoader();
    string getMapFile();
    void setMapFile(const string& mf);
    vector<string> parseString(const string& s);
    void readMap();
};

//Global Functions
ostream& operator << (ostream& out, const Continent& c);
ostream& operator << (ostream& out, const Territory& t);
vector<int> parseStringToInt(const string& s);


//Global Variables
//static Map worldMap;