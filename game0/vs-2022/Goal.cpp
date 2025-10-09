#include "Goal.h"
#include "Event.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "DisplayManager.h"
#include "GameManager.h"
#include "LevelManager.h"
#include "Color.h"

Goal::Goal() {
	setType("Goal");
	setSolidness(df::SPECTRAL);     
	setAltitude(df::MAX_ALTITUDE); 
	registerInterest(df::COLLISION_EVENT);
	setSprite("goal");
}

void Goal::setNextLevel(int level_index) {
	m_next_level = level_index;
}

bool Goal::isPlayer(const df::Object* o) const {
	if (!o) return false;
	if (o->getType() == "Player") return true;
	return dynamic_cast<const Player*>(o) != nullptr;
}

void Goal::advanceLevel() {
	LevelManager& lm = LevelManager::getInstance();

	int current = lm.getCurrentLevel();
	int target = (m_next_level >= 0) ? m_next_level : (current + 1);

	lm.loadLevel(target);
}

int Goal::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::COLLISION_EVENT) {
		auto* col = static_cast<const df::EventCollision*>(p_e);
		df::Object* a = col->getObject1();
		df::Object* b = col->getObject2();

		// If either colliding object is the player, trigger level advance
		if (isPlayer(a) || isPlayer(b)) {
			advanceLevel();
			return 1;
		}
	}
	return 0;
}