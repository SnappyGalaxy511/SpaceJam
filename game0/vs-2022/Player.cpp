#include "Player.h"

Player::Player() {
	setSprite("player");
	setType("player");
	setPosition(df::Vector(5, 20));
	setBox(df::Box(df::Vector(-1.5, -2), 3, 3.75));

	m_horizontal_velocity = 0;
	m_vertical_velocity = 0;
	m_step_countdown = 0; 
	m_step_countdown_current = 0;

	registerInterest(df::KEYBOARD_EVENT);
	registerInterest(df::STEP_EVENT);
}

int Player::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::KEYBOARD_EVENT) {
		keyboardHandler(dynamic_cast<const const df::EventKeyboard*>(p_e));
	}
	if (p_e->getType() == df::STEP_EVENT) {
		movePlayer(m_horizontal_velocity, m_vertical_velocity);
	}
	return 0; 
}

void Player::keyboardHandler(const df::EventKeyboard* p_e) {
	if (p_e->getKeyboardAction() == df::KEY_PRESSED) {
		switch (p_e->getKey()) {
			case df::Keyboard::A:
				m_horizontal_velocity -= 1; 
				m_a_activation = true; 
				break; 
			case df::Keyboard::D:
				m_horizontal_velocity += 1; 
				m_d_activation = true; 
				break; 
			case df::Keyboard::S:
				m_vertical_velocity += 1;
				m_s_activation = true; 
				break; 
			case df::Keyboard::W:
				m_vertical_velocity -= 1; 
				m_w_activation = true; 
		}
	}

	if (p_e->getKeyboardAction() == df::KEY_RELEASED) {
		switch (p_e->getKey()) {
		case df::Keyboard::A:
			if (m_a_activation) {
				m_horizontal_velocity += 1;
			}
			break;
		case df::Keyboard::D:
			if (m_d_activation) {
				m_horizontal_velocity -= 1;
			}
			break; 
		case df::Keyboard::S:
			if (m_s_activation) {
				m_vertical_velocity -= 1;
			}
			break; 
		case df::Keyboard::W:
			if (m_w_activation) {
				m_vertical_velocity += 1;
			}
		}
	}
}

void Player::movePlayer(float x_move, float y_move) {
	m_step_countdown_current--;
	
	if (m_step_countdown <= 0) {
		float new_x = getPosition().getX() + x_move;
		float new_y = getPosition().getY() + y_move / 2;

		if (new_x < 0 || new_x > WM.getBoundary().getHorizontal() || new_y < 0 || new_y > WM.getBoundary().getVertical() - 1) {
			return;
		}

		df::Vector new_pos(new_x, new_y);

		WM.moveObject(this, new_pos);

		m_step_countdown_current = m_step_countdown; 
	}
}