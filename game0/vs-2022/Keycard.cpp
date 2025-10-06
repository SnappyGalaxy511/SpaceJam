#include "Keycard.h"
#include "EventCollision.h"
#include "WorldManager.h"
#include "EventKeycard.h"

using namespace df;

Keycard::Keycard() {
	setType("Keycard");
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
            return 1;
        }
    }
    return 0;
}