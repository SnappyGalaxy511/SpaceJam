#include "Tile.h"
#include "DisplayManager.h"

Tile::Tile() {
	m_is_vertical = false;
}

Tile::Tile(bool is_vertical) {
	m_is_vertical = is_vertical;
}

int Tile::draw() {
	df::DisplayManager& disp = df::DisplayManager::getInstance();
	const df::Vector p = getPosition();

	if (m_is_vertical == false) {
		disp.drawCh(df::Vector(p.getX(), p.getY()), '-', df::Color::BLUE);
	}
	else {
		disp.drawCh(df::Vector(p.getX(), p.getY()), '|', df::Color::BLUE);
	}

	return 0; 
}

int Tile::eventHandler(const df::Event* p_e) {
	return 0; 
}