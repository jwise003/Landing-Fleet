/*
A Beach Landing
Author:  John Wiseman

This program creates a squadron of 5 - 7 ALCs (Amphibious Landing Craft)
and moves them to attack a beach.
*/


#include <iostream>
#include <cstdlib>

using namespace std;
#include "LandingFleet_Imp.cpp"

int main()
{
    int mapHeight = 0;      // height of map
    int mapWidth = 0;       // width of map
    int numBoats;       // size of fleet

    int minHeight;      // minimum map height
    int minWidth;       // minimum map width

    int maxStartH;      // highest possible start point for control craft
    int minStartH;      // lowest possible start point for control craft
    int maxStartW;      // furthest right possible start point for control craft
    int minStartW;      // furthest left possible start point for control craft

    int x;      // command ALC start x
    int y;      // command ALC start y


    createWorld(numBoats, minWidth, minHeight, mapWidth, mapHeight,
                minStartH, maxStartH, minStartW, maxStartW, x, y);

    return 0;
}

