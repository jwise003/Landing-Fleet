
/*
A Beach Landing
Author:  John Wiseman

This program creates a squadron of 5 - 7 ALCs (Amphibious Landing Craft)
and moves them to attack a beach.
*/
#include "LandingFleet.h"


ALC::ALC()
{

}
ALC::~ALC()
{

}
void ALC::setx(int i)     // set boat's x coord
{
    x = i;
}
int ALC::getx()     // get boat's x coord
{
    return x;
}
void ALC::sety(int i)     // set boat's y coord
{
    y = i;
}
int ALC::gety()     // get boat's y coord
{
    return y;
}
void ALC::setHead(ALC* i)   // set boat's head
{
    head = i;
}
ALC* ALC::getHead()   // get boat's head
{
    return head;
}
void ALC::setNext(ALC* i)   // set boat's next
{
    next = i;
}
ALC* ALC::getNext()   // get boat's next
{
    return next;
}




ALC* createFleet(int i, int x, int y)     // Creates a 'V' formation fleet of ALCs of 'i' size
{
    ALC* head = new ALC;        //create the command ALC
    ALC* curr = head;           // set the current
    ALC* temp = NULL;           // placeholder for creating and setting new ALCs

    head->setx(x);              //assign the starting x/y coords to the command ALC
    head->sety(y);
    head->setHead(head);        //set itself as head
    head->setNext(NULL);        //set head's next to NULL

    int x1 = x;            //create alternative x's for the fleet v-split
    int x2 = x;

    for(int n = 1; n < i; n++)  //Loop to create rest of fleet
    {
        if(n%2 == 1)    // if this results in 1, it is a new row of 2 boats.  Adjust y down, and spread the x's one further in each direction.
        {
            y--;        //move y towards beach
            x1 = x1 - 1;     //move x west one
            x2 = x2 + 1;     //move another x east one
        }
        temp = new ALC;             //temp is a new ALC
        curr->setNext(temp);        //setting the next in the current ALC to the ALC in temp
        curr = curr->getNext();     //move forward in LL
        curr->setHead(head);        //tell the new ALC where the head is located
        curr->setNext(NULL);        // set its Next to NULL

        curr->sety(y);              //set new ALCs y
        if(n%2 == 1)                // if 1, new ALC is west-most ALC on row, else it is east-most ALC on row.
            curr->setx(x1);
        else
            curr->setx(x2);
    }
    return head;        //return the head of the LL to main function
}





void printFleet(int height, int width, ALC* boat, ALC* shore, int number)       // Print's the world with fleet
{

    int big = ((width - 1) / 5);     //will allow us to quick fill chunks with ____| or ----+
    int little = ((width-1) % 5);     // let's us fill in the remainder
    system("cls");                      //clear the screen up
    for(int h = height; h > 0; h--)     //starting from the top, one row at a time.
    {
        if(boat == NULL || h != boat->gety())           //if there are no boats in this row (common case is first)
        {
            if(h%5 != 0)                //if it isn't a Grid row (4/5 times, common case is fist)
            {
                cout << "|";            //draw the left border
                for(int w = 0; w < big; w++)    //fill the middle
                    cout << "    |";
//              for(int w = 0; w < little; w++) //fill remainder   (this piece is not necessary, but I include it for symmetry, because OCD)
//                  cout << " ";
            }
            else  // if it IS a Grid row
            {
                cout << "+";                //draw the left border
                for(int w = 0; w < big; w++)    //fill middle
                    cout << "----+";
                for(int w = 0; w < little; w++) //fill rest
                    cout << "-";
            }
            cout << endl;               // next row!
        }
        else            // if there ARE boat(s) in this row
        {
            int numberBoats = number;
            int vessels = 1;             //number of ALCs in row
            int nowX = boat->getx();        //current boat's x
            int nextX = 0;              // holder for next ALC's x coord.

            if(boat->getNext() != NULL)
            {
                if(h == boat->getNext()->gety()) // see if next boat is in this row
                {
                    nextX = boat->getNext()->getx(); //get that boat's x coord
                    vessels = 2;                    // 2 boats, if 2 in row.
                }
            }

            int wid = 0;            // current position on width
            while((vessels > 0) || (wid < width))  //while there are boats left, or map to draw
            {
                while((wid != nowX) && (wid < width))  //while it's not a boat, and is map
                {
                    if(h%5 != 0)            //if row is not Grid
                    {
                        if(wid%5)           //if column is not Grid
                            cout << " ";     //print a blank space
                        else                //if it is a grid
                            cout << "|";    //print a grid line
                        wid++;               //iterate position in row
                    }
                    else                    //if row IS Grid
                    {
                        if(wid%5 != 0)        //if Column is not Grid
                            cout << "-";           //print longitude line
                        else                    //if Column IS Grid
                            cout << "+";           //Make an intersection
                        wid++;
                    }
                }                   //out of while loop 2
                if(wid < width)  //if not at end of row, then...
                {
                    if(h == 1)
                        cout << "L";    //print ALC landing
                    else
                        cout << "V";     //print an ALC
                    wid++;            //iterate through width
                    nowX = nextX;   //set next boat's x coord to break while
                    boat = boat->getNext(); //move to next boat in LL
                    vessels--;      //deincrement vessel count
                    numberBoats--;
                }
            }
            cout << endl;
        }
    }
}





string attack(int height, int width, ALC* attackers,ALC* shore, int number)           // Maneuvers the squadron towards the beach at Y = 0;
{
    ALC* head = attackers;
    ALC* curr = attackers;
    ALC* deleter;

    if(curr->gety()== 1)
    {
        while(curr!=NULL)
        {
            deleter = curr;
            curr = curr->getNext();
            delete deleter;
        }
        if(curr == NULL)
        {
            delete curr;
            return "EXIT";
        }

    }
    while(curr != NULL)
        {
            curr->sety((curr->gety() - 1));    //Iterate the nodes down Y until they land
            curr = curr->getNext();
        }

    printFleet(height, width, attackers, shore, number);          //print the fleet
    return "b";
}




void createWorld(int numBoats, int minWidth, int minHeight, int mapWidth, int mapHeight,
                 int minStartH, int maxStartH, int minStartW, int maxStartW, int x, int y)
{
        cout << "Select a size for a fleet of ALCs.  Your choice should be between 5 and 7. ";
    cin >> numBoats;                        // how many boats will there be?
    while(numBoats > 7 || numBoats < 5)
    {
        cout << "Your selection should be between 5 and 7." << endl;
        cout << "Please select again. ";
        cin >> numBoats;
    }

    minWidth = numBoats;                    // minimum map width, based on fleet size.
    minHeight = ((numBoats / 2) + 1);       // minimum map height, based on fleet size.
    ///cout statement to tell user what these are
    cout << "Based on the fleet size you have selected, your minimum map size" << endl;
    cout << "is " << minHeight << " tall by " << minWidth << " wide.  Please select values for map size." << endl;

    cout << "Enter a value for map width." << endl;
    while(mapWidth <= minWidth || mapWidth >= 40) //set mapWidth between the min and max limit.
    {
        cout << "Enter a map width greater than " << minWidth << ", and less than 40. ";
        cin >> mapWidth;
    }

    cout << "Enter a value for map height." << endl;
    while(mapHeight <= minHeight || mapHeight >= 50)  // set mapHeight between the min and max limit.
    {
        cout << "Enter a map height greater than " << minHeight << ", and less than 50. ";
        cin >> mapHeight;
    }

    maxStartH = mapHeight;         //max start height of command ALC
    minStartH = ((numBoats / 2) + 2);       // min start height of command ALC
    maxStartW = (mapWidth - ((numBoats) / 2)-1);     //max start width of command ALC
    minStartW = (numBoats / 2);        //min start width of command ALC

    cout << "Place your command ship between y " << minStartH << " and y " << maxStartH << "," << endl; //Instructions for entering boat starting location
    cout << "and x " << minStartW << " and x " << maxStartW << "." << endl;
    cout << "Enter Y: ";        //Get Y
    cin >> y;
    cout << "Enter X: ";        //Get X
    cin >> x;

    if(x < minStartW || x > maxStartW || y < minStartH || y > maxStartH)        // check to see if X and Y are within parameters
    {

        while(y < minStartH || y > maxStartH)
        {
            cout << "Y must be between y " << minStartH << " and y " << maxStartH << "." << endl;
            cout << "Enter Y. ";
            cin >> y;
        }
        while(x < minStartW || x > maxStartW)           // if they aren't do it again until they're right.
        {
            cout << "X must be between x " << minStartW << " and x " << maxStartW << "." << endl;
            cout << "Enter X. ";
            cin >> x;
        }

    }
    ALC* commander = createFleet(numBoats, x, y);   //Run the function to create a fleet of a at coordinate x,y
    printFleet(mapHeight, mapWidth, commander, commander, numBoats);

    string choice = "b";
    while(choice != "EXIT")
    {
        cout << "Press 'a' to attack, type EXIT to leave the program, commander.";
        cin >> choice;
        if(choice == "a")
            choice = attack(mapHeight, mapWidth, commander, commander, numBoats);
    }
    cout << "Your final ship has landed on the beach!  Exiting simulation, Commander.";
}
