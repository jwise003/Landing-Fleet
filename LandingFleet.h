
/*
A Beach Landing
Author:  John Wiseman

This program creates a squadron of 5 - 7 ALCs (Amphibious Landing Craft)
and moves them to attack a beach.
*/
#ifndef LANDINGFLEET_H
#define LANDINGFLEET_H




class ALC       //Class for Amphibious Landing Craft squadron
{
public:
    ALC();
    ~ALC();
    void setx(int i);     // set boat's x coord
    int getx();     // get boat's x coord
    void sety(int i);     // set boat's y coord
    int gety();     // get boat's y coord
    void setHead(ALC* i);   // set boat's head
    ALC* getHead();   // get boat's head
    void setNext(ALC* i);   // set boat's next
    ALC* getNext();   // get boat's next
private:
    int x = 0;      // x coord
    int y = 0;      // y coord
    ALC* head;  // head of LL of ALCs
    ALC* next;  // next ALC in the list
};


ALC* createFleet(int i, int x, int y);     // Creates a 'V' formation fleet of ALCs of 'i' size
void printFleet(int height, int width, ALC* boat, ALC* shore, int number);       // Print's the world with fleet
string attack(int height, int width, ALC* attackers, ALC* shore, int number);     //Moves the squadron towards the beach at Y = 0
void createWorld(int numBoats, int minWidth, int minHeight, int mapWidth, int mapHeight,    //creates the map
                 int minStartH, int maxStartH, int minStartW, int maxStartW, int x, int y);
#endif
