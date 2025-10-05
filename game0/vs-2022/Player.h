#pragma once

#include "Object.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventKeyboard.h"

class Player : public df::Object {
private:
	int m_horizontal_velocity; 
	int m_vertical_velocity; 
	int m_step_countdown; 
	int m_step_countdown_current; 

public:
	Player();
	int eventHandler(const df::Event* p_e) override;
	void keyboardHandler(const df::EventKeyboard* p_e);
	void movePlayer(int x_move, int y_move);
};
