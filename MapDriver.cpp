#include <iostream>
#include "Map.h"
#include "Map.cpp"
int main() {
    MapLoader map = new MapLoader();
    map.readMap();

    return 0;
}