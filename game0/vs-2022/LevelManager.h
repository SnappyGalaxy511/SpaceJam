#pragma once

#include "Manager.h"
#include "Laser.h"
#include "Tile.h"
#include "Keycard.h"
#include "Door.h"

struct LevelElement {
	df::Object *gameObject; 
	df::Vector *position;

	LevelElement(df::Object *object, df::Vector *vector) {
		gameObject = object;
		position = vector;
	}

	LevelElement() {
		gameObject = nullptr;
		position = nullptr;
	}
};

class LevelManager : public df::Manager {

private:
	LevelManager();
	LevelManager(const LevelManager&) = delete;
	LevelManager& operator=(const LevelManager&) = delete;

	LevelElement level_one_object_list[255];

	int m_current_level = 1;

public:
	static LevelManager& getInstance();
	int startUp() override;
	void shutDown() override;

	void clearLevel();
	void loadLevelOne();
	void loadLevelTwo();
	void loadLevelThree();
	void loadLevelVictory();
	void loadLevel(int level);

	int getCurrentLevel();


};
