#include "LevelManager.h"
#include "WorldManager.h"
#include "Laser.h"
#include "Tile.h"
#include "Keycard.h"
#include "Door.h"
#include "Goal.h"
#include "GuardPatrol.h"
#include "Win.h"

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
	level_one_object_list[85] = LevelElement(new Laser(30, 25, Laser::Orientation::Horizontal, 32), new df::Vector(46, 16));

	//Keycard and Door
	level_one_object_list[82] = LevelElement(new Keycard(), new df::Vector(60, 20));
	level_one_object_list[83] = LevelElement(new Door(), new df::Vector(40, 10));

	//Objective
	level_one_object_list[84] = LevelElement(new Goal(), new df::Vector(40, 22));

	for (int i = 0; i < 86; i++) {
		level_one_object_list[i].gameObject->setPosition(*level_one_object_list[i].position);
	}
}

void LevelManager::loadLevelTwo() {
	LevelElement bottom_half[100];
	LevelElement top_half[100];
	LevelElement lasers[10];
	LevelElement other_stuff[10];

//BOTTOM HALF OF LEVEL
	//First Box
	for (int i = 0; i < 10; i++) {
		bottom_half[i] = LevelElement(new Tile(true), new df::Vector(15, 24 - i));
	}

	for (int i = 10; i < 20; i++) {
		bottom_half[i] = LevelElement(new Tile(true), new df::Vector(25, 24 - i + 10));
	}

	for (int i = 20; i < 29; i++) {
		bottom_half[i] = LevelElement(new Tile(false), new df::Vector(i - 4, 14));
	}


	//Second Box
	for (int i = 29; i < 39; i++) {
		bottom_half[i] = LevelElement(new Tile(false), new df::Vector(10.5 + i, 14));
	}

	for (int i = 39; i < 49; i++) {
		bottom_half[i] = LevelElement(new Tile(false), new df::Vector(0.5 + i, 18));
	}

	for (int i = 49; i < 52; i++) {
		bottom_half[i] = LevelElement(new Tile(true), new df::Vector(39, 15 + i - 49));
	}

	for (int i = 52; i < 55; i++) {
		bottom_half[i] = LevelElement(new Tile(true), new df::Vector(49, 15 + i - 52));
	}

	//Third Box
	for (int i = 55; i < 65; i++) {
		bottom_half[i] = LevelElement(new Tile(false), new df::Vector(5.5 + i, 14));
	}

	for (int i = 65; i < 75; i++) {
		bottom_half[i] = LevelElement(new Tile(true), new df::Vector(60, 15 + i - 65));
	}

	for (int i = 75; i < 85; i++) {
		bottom_half[i] = LevelElement(new Tile(true), new df::Vector(70, 15 + i - 75));
	}

//TOP HALF OF LEVEL
	//Fourth Box
	for (int i = 0; i < 8; i++) {
		top_half[i] = LevelElement(new Tile(true), new df::Vector(15, i));
	}

	for (int i = 8; i < 16; i++) {
		top_half[i] = LevelElement(new Tile(true), new df::Vector(25, i - 8));
	}

	for (int i = 16; i < 25; i++) {
		top_half[i] = LevelElement(new Tile(false), new df::Vector(i, 8));
	}

	//Fifth Box
	for (int i = 25; i < 35; i++) {
		top_half[i] = LevelElement(new Tile(false), new df::Vector(14.5 + i, 8));
	}

	for (int i = 35; i < 45; i++) {
		top_half[i] = LevelElement(new Tile(false), new df::Vector(4.5 + i, 4));
	}

	for (int i = 45; i < 48; i++) {
		top_half[i] = LevelElement(new Tile(true), new df::Vector(39, 6 + i - 46));
	}

	for (int i = 48; i < 51; i++) {
		top_half[i] = LevelElement(new Tile(true), new df::Vector(49, 6 + i - 49));
	}

	//Sixth Box
	for (int i = 51; i < 71; i++) {
		top_half[i] = LevelElement(new Tile(false), new df::Vector(9.5 + i, 8));
	}

	for (int i = 71; i < 91; i++) {
		top_half[i] = LevelElement(new Tile(false), new df::Vector(9.5 + i - 20, 4));
	}

	for (int i = 91; i < 94; i++) {
		top_half[i] = LevelElement(new Tile(true), new df::Vector(60, 5 + i - 91));
	}

//LASERS 
	lasers[0] = LevelElement(new Laser(30, 30, Laser::Orientation::Horizontal, 14), new df::Vector(0, 15));

	lasers[1] = LevelElement(new Laser(20, 25, Laser::Orientation::Horizontal, 13), new df::Vector(26, 15));
	lasers[2] = LevelElement(new Laser(20, 25, Laser::Orientation::Horizontal, 10), new df::Vector(50, 15));
	lasers[3] = LevelElement(new Laser(20, 25, Laser::Orientation::Horizontal, 13), new df::Vector(26, 6));
	lasers[4] = LevelElement(new Laser(20, 25, Laser::Orientation::Horizontal, 10), new df::Vector(50, 6));

	lasers[5] = LevelElement(new Laser(35, 15, Laser::Orientation::Vertical, 4), new df::Vector(44, 0.25));
	lasers[6] = LevelElement(new Laser(35, 15, Laser::Orientation::Vertical, 5), new df::Vector(44, 19));

//GUARD
	
	std::vector<df::Vector> waypoints = {df::Vector(18, 11), df::Vector(54, 11)};
	LevelElement guard = LevelElement(new GuardPatrol(waypoints), new df::Vector(18, 11));

	guard.gameObject->setPosition(*guard.position);

//OTHER STUFF
	other_stuff[0] = LevelElement(new Keycard(), new df::Vector(75, 1));
	other_stuff[1] = LevelElement(new Door(), new df::Vector(77, 14));
	other_stuff[2] = LevelElement(new Goal(), new df::Vector(75, 21));

	//level_one_object_list[25] = LevelElement(new GuardStatic(60, GuardDirection::East, 2, 20), new df::Vector(10, 10));

	for (int i = 0; i < 85; i++) {
		bottom_half[i].gameObject->setPosition(*bottom_half[i].position);
	}

	for (int i = 0; i < 94; i++) {
		top_half[i].gameObject->setPosition(*top_half[i].position);
	}

	for (int i = 0; i < 7; i++) {
		lasers[i].gameObject->setPosition(*lasers[i].position);
	}

	for (int i = 0; i < 3; i++) {
		other_stuff[i].gameObject->setPosition(*other_stuff[i].position);
	}
}

void LevelManager::loadLevelThree() {
	LevelElement first_wall[24];

	for (int i = 0; i < 20; i++) {
		first_wall[i] = LevelElement(new Tile(true), new df::Vector(12, 24 - i));
		first_wall[i].gameObject->setPosition(*first_wall[i].position);
	}


	LevelElement cove_wall[24];

	for (int i = 0; i < 7; i++) {
		cove_wall[i] = LevelElement(new Tile(true), new df::Vector(24, 11 + i));
		cove_wall[i].gameObject->setPosition(*cove_wall[i].position);
	}

	
	LevelElement cove_floor1[24];
	LevelElement cove_floor2[24];

	for (int i = 0; i < 21; i++) {
		cove_floor1[i] = LevelElement(new Tile(false), new df::Vector(25 + i, 10.5));
		cove_floor2[i] = LevelElement(new Tile(false), new df::Vector(25 + i, 17.5));

		cove_floor1[i].gameObject->setPosition(*cove_floor1[i].position);
		cove_floor2[i].gameObject->setPosition(*cove_floor2[i].position);
	}


	LevelElement second_cove[48];

	for (int i = 0; i < 6; i++) {
		second_cove[i] = LevelElement(new Tile(true), new df::Vector(24, i));
		second_cove[i].gameObject->setPosition(*second_cove[i].position);
	}

	for (int i = 6; i < 12; i++) {
		second_cove[i] = LevelElement(new Tile(true), new df::Vector(46, i - 6));
		second_cove[i].gameObject->setPosition(*second_cove[i].position);
	}

	for (int i = 12; i < 33; i++) {
		second_cove[i] = LevelElement(new Tile(false), new df::Vector(i + 24 - 11, 5.5));
		second_cove[i].gameObject->setPosition(*second_cove[i].position);
	}


	LevelElement tower1[24];
	LevelElement tower2[24];
	LevelElement tower_cap[24];

	for (int i = 0; i < 20; i++) {
		tower1[i] = LevelElement(new Tile(true), new df::Vector(60, 24 - i));
		tower2[i] = LevelElement(new Tile(true), new df::Vector(70, 24 - i));

		tower1[i].gameObject->setPosition(*tower1[i].position);
		tower2[i].gameObject->setPosition(*tower2[i].position);
	}

	for (int i = 0; i < 9; i++) {
		tower_cap[i] = LevelElement(new Tile(false), new df::Vector(61 + i, 4));

		tower_cap[i].gameObject->setPosition(*tower_cap[i].position);
	}


	LevelElement lasers[12];

	lasers[0] = LevelElement(new Laser(20, 25, Laser::Orientation::Horizontal, 12), new df::Vector(0, 12));
	lasers[1] = LevelElement(new Laser(15, 30, Laser::Orientation::Horizontal, 12), new df::Vector(0, 7));

	lasers[2] = LevelElement(new Laser(20, 25, Laser::Orientation::Vertical, 6), new df::Vector(30, 18));
	lasers[3] = LevelElement(new Laser(15, 30, Laser::Orientation::Vertical, 6), new df::Vector(40, 18));

	lasers[4] = LevelElement(new Laser(15, 30, Laser::Orientation::Vertical, 4), new df::Vector(65, 0));

	for (int i = 0; i < 5; i++) {
		lasers[i].gameObject->setPosition(*lasers[i].position);
	}


	LevelElement guards[2];

	std::vector<df::Vector> waypoints1 = { df::Vector(50, 8), df::Vector(18, 8) };
	std::vector<df::Vector> waypoints2 = { df::Vector(50, 8), df::Vector(50, 20) };

	guards[0] = LevelElement(new GuardPatrol(waypoints1), new df::Vector(18, 8));
	guards[1] = LevelElement(new GuardPatrol(waypoints2, 0.2f, GuardDirection::North), new df::Vector(50, 20));

	guards[0].gameObject->setPosition(*guards[0].position);
	guards[1].gameObject->setPosition(*guards[01].position);


	LevelElement other_stuff[12];

	other_stuff[0] = LevelElement(new Keycard(), new df::Vector(32, 14));
	other_stuff[1] = LevelElement(new Door(), new df::Vector(77, 4.5));
	other_stuff[2] = LevelElement(new Goal(), new df::Vector(75, 20));

	for (int i = 0; i < 3; i++) {
		other_stuff[i].gameObject->setPosition(*other_stuff[i].position);
	}
}

void LevelManager::loadLevelVictory() {
	LevelElement win = LevelElement(new Win(), new df::Vector(40, 12));
	win.gameObject->setPosition(*win.position);
}

void LevelManager::loadLevel(int level) {
	clearLevel();

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