#pragma once
#pragma once
#include "Object.h"
#include "EventCollision.h"
#include "Player.h"

class Goal : public df::Object {
public:
	Goal();

	void setNextLevel(int level_index);

	int eventHandler(const df::Event* p_e) override;

private:
	int m_next_level = -1; // -1 means use LevelManager.getcurrentLevel()+1
	bool isPlayer(const df::Object* o) const;
	void advanceLevel();
};