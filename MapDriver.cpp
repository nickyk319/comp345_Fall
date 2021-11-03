#include "Map.h"
#include <iostream>

using namespace std;

int main() {
    MapLoader map;
    map.setMapFile("europe.map");
    map.readMap();
    map.worldMap.validate();

    return 0;
}