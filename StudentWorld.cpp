#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
    lastWhiteY = 0;
}

GhostRacer* StudentWorld::getGR() {
    return gr;
}
int StudentWorld::init()
{
    
    gr = new GhostRacer(0, 128, 32, this, 10, 0, 100);
    int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH / 2;
    int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH / 2;
    int n = VIEW_HEIGHT / SPRITE_HEIGHT;
    int m = VIEW_HEIGHT / (4 * SPRITE_HEIGHT);
    for(int i = 0; i < n; i++) //yellow border lines
    {
        for (int j = 0; j <= n - 1; j++) {
            actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, j * SPRITE_HEIGHT, this, 0, -4));

            actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, j * SPRITE_HEIGHT, this, 0, -4));
            
        }
  
    }

    for (int i = 0; i < m; i++) // white border lines
    {
        for (int j = 0; j <= n - 1; j++) {
            actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH / 3, j *
                (4 * SPRITE_HEIGHT), this, 0, -4));

            actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH / 3, j *
                (4 * SPRITE_HEIGHT), this, 0, -4));
        }
        if (i == m - 1) {
            lastWhiteY = actors[i]->getY();
        }

    }
 
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
   
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    gr->doSomething();
    for (int i = 0; i < actors.size(); i++) {
        if (actors[i]->getAlive()) {
            actors[i]->doSomething();
            if (gr->gethp() <= 0) {
                decLives();
                return GWSTATUS_PLAYER_DIED;
            }
            if (actors[i] == gr) { //and Ghost Racer completed currentLevel
                //add bonus points to the score
                // return GWSTATUS_FINISHED_LEVEL;
            }
        }
    }
    // Remove newly-dead actors after each tick
    for (vector<Actor*>::iterator it = actors.begin(); it != actors.end();) {
        if ((*it)->getAlive() == false) {
            

            delete* it;
            it = actors.erase(it);
        }
        else {
            it++;
        }
    }

        

    
     // Potentially add new actors to the game
 // (e.g., oil slicks or goodies or border lines) 
    
   
        int new_border_y = VIEW_HEIGHT - SPRITE_HEIGHT;
        lastWhiteY += ((-4) - gr->getVertSpeed());
        int delta_y = new_border_y - lastWhiteY;

        int LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH / 2;
        int RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH / 2;
        int n = VIEW_HEIGHT / SPRITE_HEIGHT;
        int m = VIEW_HEIGHT / (4 * SPRITE_HEIGHT);



        
        
        if (delta_y >= SPRITE_HEIGHT) {
            actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE, new_border_y, this, 0, -4));

            actors.push_back(new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE, new_border_y, this, 0, -4));


        }
        if (delta_y >= 4 * SPRITE_HEIGHT) {
           
            actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH / 3, new_border_y, this, 0, -4));
            
            actors.push_back(new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH / 3, new_border_y, this, 0, -4));
           
            lastWhiteY = new_border_y;
        }
        
       
      
   
  
    // Update the Game Status Line

    // the player hasn’t completed the current level and hasn’t died, so
 // continue playing the current level
    return GWSTATUS_CONTINUE_GAME;

}

void StudentWorld::cleanUp()
{
    
    for (int i = 0; i < actors.size(); i++) {
        Actor* act = actors[i];
        actors.erase(actors.begin() + i);
        delete act;

    }
    delete gr;
    //destroy GhostRacer
    
} 

/*void StudentWorld::cleanUp()
{
    for (vector<Actor*>::iterator i = actors.begin(); i != actors.end(); i++) {
        delete* i;
    }
    //destroy GhostRacer
    delete gr;
}*/

StudentWorld::~StudentWorld() {
    cleanUp();
}
