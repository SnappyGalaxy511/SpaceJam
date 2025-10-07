#include "LevelManager.h"

LevelManager::LevelManager() {
	//First row
	for (int i = 0; i < 25; i++) {
		level_one_object_list[i] = LevelElement(new Tile(false), new df::Vector(i, 15));
	}

	//Second row
	for (int i = 25; i < 50; i++) {
		level_one_object_list[i] = LevelElement(new Tile(false), new df::Vector(i - 15, 10));
	}
	
	//First Collumn
	for (int i = 50; i < 65; i++) {
		level_one_object_list[i] = LevelElement(new Tile(true), new df::Vector(35, 74 - i));
	}

	//Second Collumn
	for (int i = 65; i < 80; i++) {
		level_one_object_list[i] = LevelElement(new Tile(true), new df::Vector(45, 89 - i));
	}

	//Lasers 
	level_one_object_list[80] = LevelElement(new Laser(20, 25, Laser::Orientation::Vertical, 16), new df::Vector(12, 0));
	level_one_object_list[81] = LevelElement(new Laser(30, 25, Laser::Orientation::Vertical, 16), new df::Vector(18, 0));

	//Keycard and Door
	level_one_object_list[82] = LevelElement(new Keycard(), new df::Vector(60, 20));
	level_one_object_list[83] = LevelElement(new Door(), new df::Vector(40, 10));

	//Load Level is currently broken from reasons far beyond me so I'm doing it like this. I'll fix it later
	for (int i = 0; i < 84; i++) {
		level_one_object_list[i].gameObject->setPosition(*level_one_object_list[i].position);
	}
}

LevelManager& LevelManager::getInstance() {
	LevelManager& level_manager = LevelManager(); 
	return level_manager;
}

int LevelManager::startUp() {
	//loadLevel(0);
	return 0; 
}

void LevelManager::shutDown() {

}

void LevelManager::loadLevel(int level_index) {
	for (int i = 0; i < 50; i++) {
		if (level_one_object_list[i].gameObject == nullptr) {
			break; 
		}
		level_one_object_list[i].gameObject->setPosition(*level_one_object_list[i].position);
	}
	printf("\nlevel loaded!\n");
}