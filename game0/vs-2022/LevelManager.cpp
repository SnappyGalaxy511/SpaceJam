#include "LevelManager.h"
#include "WorldManager.h"

LevelManager::LevelManager() {

}

LevelManager& LevelManager::getInstance() {
	static LevelManager level_manager;
	return level_manager;
}

int LevelManager::startUp() {
	clearLevel();

	return 0; 
}

void LevelManager::shutDown() {

}

void LevelManager::clearLevel() {
	df::ObjectList all_objects = WM.getAllObjects();

	for (int i = 1; i < all_objects.getCount(); i++) {
		WM.markForDelete(all_objects[i]);
	}
}

void LevelManager::loadLevelOne() {
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
	level_one_object_list[80] = LevelElement(new Laser(20, 25, Laser::Orientation::Vertical, 15), new df::Vector(12, 0));
	level_one_object_list[81] = LevelElement(new Laser(30, 25, Laser::Orientation::Vertical, 15), new df::Vector(18, 0));

	//Keycard and Door
	level_one_object_list[82] = LevelElement(new Keycard(), new df::Vector(60, 20));
	level_one_object_list[83] = LevelElement(new Door(), new df::Vector(40, 10));

	for (int i = 0; i < 84; i++) {
		level_one_object_list[i].gameObject->setPosition(*level_one_object_list[i].position);
	}
}

void LevelManager::loadLevelTwo() {
	//First row
	for (int i = 0; i < 25; i++) {
		level_one_object_list[i] = LevelElement(new Tile(false), new df::Vector(i, 15));
	}

	for (int i = 0; i < 25; i++) {
		level_one_object_list[i].gameObject->setPosition(*level_one_object_list[i].position);
	}
}

void LevelManager::loadLevelThree() {

}

void LevelManager::loadLevelVictory() {

}

void LevelManager::loadLevel(int level) {
	switch (level) {
	case 1:
		loadLevelOne();
		break; 
	case 2:
		loadLevelTwo();
		m_current_level = 2;
		break;
	case 3:
		loadLevelThree();
		m_current_level = 3; 
		break;
	default:
		loadLevelVictory();
	}
}

int LevelManager::getCurrentLevel() {
	return m_current_level;
}