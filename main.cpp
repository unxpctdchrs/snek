#include "Game.h"

int main(){
    //Initialize game object
    Game game;
    
    //Game loop
    while(game.running()){
        game.update();

        game.render();
        
    }

    //end of application
    return 0;
}