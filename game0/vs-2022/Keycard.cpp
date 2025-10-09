#include "Keycard.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "LevelManager.h"
#include "DisplayManager.h"
#include "EventKeycard.h"

using namespace df;

Keycard::Keycard() {
	setType("Keycard");
	setSprite("keycard");
	setSolidness(SOFT);
	registerInterest(df::COLLISION_EVENT);
}

int Keycard::eventHandler(const Event* p_e) {
    if (p_e->getType() == COLLISION_EVENT) {
        auto* ec = dynamic_cast<const EventCollision*>(p_e);
        if (!ec) return 0;

        Object* a = ec->getObject1();
        Object* b = ec->getObject2();
        Object* other = (a == this) ? b : a;

        if (other && other->getType() == collector_type_) {
            // Notify the world that the keycard was collected.
            EventKeycard ev;
            WorldManager::getInstance().onEvent(&ev);

            // Remove the keycard safely at end of frame.
            WorldManager::getInstance().markForDelete(this);

            //Testing LevelManager functionality
            LevelManager::getInstance().clearLevel();
            LevelManager::getInstance().loadLevel(LevelManager::getInstance().getCurrentLevel() + 1);
            return 1;
        }
    }
    return 0;
}

int Keycard::draw() {
    df::DisplayManager& disp = df::DisplayManager::getInstance();
    const df::Vector p = getPosition();

    disp.drawCh(df::Vector(p.getX(), p.getY()), drawChar, df::Color::YELLOW);

    return 0;
}