#pragma once

#include "Object.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "EventKeyboard.h"

class Player : public df::Object {
private:
	float m_horizontal_velocity; 
	float m_vertical_velocity; 

	bool m_w_activation = false;
	bool m_a_activation = false;
	bool m_s_activation = false;
	bool m_d_activation = false;

	int m_step_countdown; 
	int m_step_countdown_current; 

public:
	Player();
	int eventHandler(const df::Event* p_e) override;
	void keyboardHandler(const df::EventKeyboard* p_e);
	void movePlayer(float x_move, float y_move);
};
