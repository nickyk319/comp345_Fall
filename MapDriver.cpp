#include <iostream>
#include "MapLoader.h"


int main() {
    mapLoader wml;
    wml.setMapFile("france.map");
    cout << wml.getMapFile() << endl;
    wml.readMap();
    wml.worldMap->displayContinents();
    wml.worldMap->displayTerritories();
    //print adjacent relation line by line
    //each line represent each territory's adjacent relation with other t in map
    for (int i = 0; i < wml.worldMap->getNumTerritory(); i++) {
        for (int j : wml.worldMap->territories[i]->adjTerritoryOnMap) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << "-------------------------continent set-----------------------------" << endl;
    for (int i = 0; i < wml.worldMap->getNumContinent(); i++) {
        for (int j : wml.worldMap->continents[i]->reachableForeignContinent) {
            cout << j << " ";
        }
        cout << endl;
    }
    wml.worldMap->validate();
    return 0;
}