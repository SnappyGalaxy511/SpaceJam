// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "ResourceManager.h"
#include "WorldManager.h"

//Game includes
#include "vs-2022/SpawnPlayer.h"
#include "vs-2022/LevelManager.h"

void loadResources(void);
void populateWorld(void);

int main(int argc, char *argv[]) {

  // Start up game manager.
  if (GM.startUp())  {
    LM.writeLog("Error starting game manager!");
    GM.shutDown();
    return 1;
  }

  // Set flush of logfile during development (when done, make false).
  LM.setFlush(true);

  // Show splash screen.
  df::splash();

  for (int i = 0; i < 1; i++) {
      printf("AHHHHHH");
  }

  //Prepare the game world
  loadResources();
  populateWorld();

  //Start game loop
  GM.run();
  
  // Shut everything down.
  GM.shutDown();
  return 0;
}

void loadResources(void) {
    RM.loadSprite("sprites/saucer-spr.txt", "player");
}

void populateWorld(void) {
    LevelManager& level_manager = LevelManager::getInstance();
    level_manager.startUp();

    new SpawnPlayer();
    level_manager.loadLevel(1);
}


