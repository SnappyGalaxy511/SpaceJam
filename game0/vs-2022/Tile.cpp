#include "Tile.h"
#include "DisplayManager.h"

Tile::Tile() {
	m_is_vertical = false;
	setBox(df::Box(df::Vector(0, 0), 0.4, 0.4));

}

Tile::Tile(bool is_vertical) {
	m_is_vertical = is_vertical;

	if (is_vertical) {
		setBox(df::Box(df::Vector(0.125/2, -1.75/2), 0.125, 1.75));
	}
	else {
		setBox(df::Box(df::Vector(-1, -0.125/2), 2, 0.125));
	}
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