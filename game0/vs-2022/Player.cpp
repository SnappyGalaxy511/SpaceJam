#include "Player.h"

Player::Player() {
	setSprite("player");
	setType("player");
	setPosition(df::Vector(5, 20));

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
				break; 
			case df::Keyboard::D:
				m_horizontal_velocity += 1; 
				break; 
			case df::Keyboard::S:
				m_vertical_velocity += 1;
				break; 
			case df::Keyboard::W:
				m_vertical_velocity -= 1; 
		}
	}

	if (p_e->getKeyboardAction() == df::KEY_RELEASED) {
		switch (p_e->getKey()) {
		case df::Keyboard::A:
			m_horizontal_velocity += 1;
			break;
		case df::Keyboard::D:
			m_horizontal_velocity -= 1;
			break; 
		case df::Keyboard::S:
			m_vertical_velocity -= 1;
			break; 
		case df::Keyboard::W:
			m_vertical_velocity += 1;
		}
	}
}

void Player::movePlayer(int x_move, int y_move) {
	m_step_countdown_current--;
	

	if (m_step_countdown <= 0) {
		df::Vector new_pos(getPosition().getX() + x_move, getPosition().getY() + y_move);
		WM.moveObject(this, new_pos);

		m_step_countdown_current = m_step_countdown; 
	}
}