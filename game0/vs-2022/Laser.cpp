#include "Laser.h"
#include <algorithm>
#include "Event.h"
#include "EventStep.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "DisplayManager.h"
#include "Color.h"
#include "Player.h"

using namespace df;

Laser::Laser(int on_steps, int off_steps, Orientation orient, int length)
	: m_on_steps(on_steps)
	, m_off_steps(off_steps)
	, m_orient(orient)
	, m_length(std::max(1, length)) {

	setType("Laser");
	setAltitude(MAX_ALTITUDE - 1);     // draw above most things

	registerInterest(STEP_EVENT);
	registerInterest(COLLISION_EVENT);

	m_on_storage = new LaserOn();
	m_off_storage = new LaserOff();
	m_on_ptr = m_on_storage;
	m_off_ptr = m_off_storage;

	m_fsm.setOwner(this);
	m_fsm.setState(m_off_ptr);         // start OFF
	// Ensure OFF-look even if StateMachine doesn't call Enter() on setState.
	setOn(false);
	setSolidness(SPECTRAL);
	setVisible(false);
	resetTimer(m_off_steps);
	// Make the beam's collision box a skinny strip.
	updateBeamBox();
}

void Laser::setOrientation(Orientation o) {
	m_orient = o;
	updateBeamBox();
}

void Laser::setLength(int L) {
	m_length = std::max(1, L);
	updateBeamBox();
}

void Laser::updateBeamBox() {
	const float w = (m_orient == Orientation::Horizontal) ? m_length - 0.5 : 0.5;
	const float h = (m_orient == Orientation::Vertical) ? m_length - 0.5 : 0.5;
	setBox(df::Box(df::Vector(0, 0), w, h));
}

int Laser::eventHandler(const Event* p_e) {
	if (p_e->getType() == STEP_EVENT) {

		if (WM.objectsOfType("player").isEmpty()) {
			new Player;
		}

		m_fsm.Update();      // Let current state tick once per frame.
		return 1;
	}

	if (p_e->getType() == COLLISION_EVENT) {
		if (m_is_on) {       // lethal only while ON
			auto* col = static_cast<const EventCollision*>(p_e);
			Object* a = col->getObject1();
			Object* b = col->getObject2();

			if (a && a->getType() == m_victim_type) {
				WM.markForDelete(a);
			}
			if (b && b->getType() == m_victim_type) {
				WM.markForDelete(b);
			}
		}
		return 1;
	}

	return 0;
}

int Laser::draw() {
	if (!m_is_on) return 0;  // invisible when OFF
	drawBeam();
	return 0;
}

void Laser::drawBeam() const {
	df::DisplayManager& disp = df::DisplayManager::getInstance();
	const df::Vector p = getPosition();

	if (m_orient == Orientation::Horizontal) {
		for (int i = 0; i < m_length; ++i) {
			disp.drawCh(df::Vector(p.getX() + i, p.getY()), '-', df::Color::RED);
		}
	}
	else {
		for (int i = 0; i < m_length; ++i) {
			disp.drawCh(df::Vector(p.getX(), p.getY() + i), '|', df::Color::RED);
		}
	}
}
LaserOn& Laser::onState() { return *m_on_ptr; }
LaserOff& Laser::offState() { return *m_off_ptr; }


// Laser ON state

void LaserOn::Enter(Object* p_obj) {
	auto* L = static_cast<Laser*>(p_obj);
	L->setOn(true);
	L->setSolidness(SOFT);      // collide but don't block
	L->setVisible(true);
	L->resetTimer(L->getOnSteps());
}

void LaserOn::Execute(Object* p_obj) {
	auto* L = static_cast<Laser*>(p_obj);
	L->tickTimer();
	if (L->timerElapsed()) {
		// Flip to OFF.
		L->m_fsm.changeState(L->m_off_ptr);
	}
}

void LaserOn::Exit(Object* p_obj) {
	(void)p_obj;
}


// Laser OFF state

void LaserOff::Enter(Object* p_obj) {
	auto* L = static_cast<Laser*>(p_obj);
	L->setOn(false);
	L->setSolidness(SPECTRAL);  // no collisions when off
	L->setVisible(false);
	L->resetTimer(L->getOffSteps());
}

void LaserOff::Execute(Object* p_obj) {
	auto* L = static_cast<Laser*>(p_obj);
	L->tickTimer();
	if (L->timerElapsed()) {
		// Flip to ON.
		L->m_fsm.changeState(L->m_on_ptr);
	}
}

void LaserOff::Exit(Object* p_obj) {
	(void)p_obj;
}