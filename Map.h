#include <vector>
#include <set>
#include <string>

using namespace std;

class Territory
{
public:
    int tID;    //Territory ID
    int cID;    //Continent ID
    int pID;    //Player ID
    int numArmy;
    string tName;   //Territory Name
    string cName;   //Continent Name  
    bool isAdjacent;  //Connected Continent Check

    vector<int> adjTerritoryOnMap;  //List of Adjacent Territories on entire map
    vector<int> adjTerritoriesInContinent;    //List of Adjacent Territories in same continent
    vector<int> reachableForeignContinent;

    //Constructors
    Territory();
    Territory(string tName, string cName, int tID, int cID);

    //Getters
    int getTID();
    int getCID();
    int getPID();
    int getNumArmy();
    string getTName();
    string getCName();
    bool getAdjContinent();
    vector<int> getAdjTerritoryOnMap();
    vector<int> getAdjTerritoryInContinent();

    //Setters
    void setTID(int tID);
    void setTName(string tName);
    void setAdjContinent(bool canLeave);

    void printTerritory(vector<int> v);
};

class Continent
{
public:
    int cID;    //Continent ID
    string cName;   //Continent Name
    vector<Territory*> territoriesInContinent; //List of Territories in Continent
    set<int> connectedContinents;    //Adjacent Continents

    vector<int> reachableForeignContinent;

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

class Map
{
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
    void validate();
};
