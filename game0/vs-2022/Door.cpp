#include "Door.h"
#include "DisplayManager.h"
#include "Event.h"
#include "EventKeycard.h"

using namespace df;

Door::Door() {
    setType("Door");
    registerInterest(game::KEYCARD_EVENT);

    fsm_.setOwner(this);
    fsm_.setState(&st_closed_);

    // starts closed
    setSolidness(HARD);
    setVisible(true);
}

int Door::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == game::KEYCARD_EVENT) {
        fsm_.changeState(&st_open_);
        return 1;
    }
    return 0;
}

int Door::draw() {
    df::DisplayManager& disp = df::DisplayManager::getInstance();
    const df::Vector p = getPosition();

    disp.drawCh(df::Vector(p.getX(), p.getY()), '?', df::Color::YELLOW);
    return 0; 
}

//States 
void Door::StateClosed::Enter(Object* owner) {
    auto* d = static_cast<Door*>(owner);
    d->setSolidness(HARD);
    d->setVisible(true);
}
void Door::StateClosed::Execute(Object* owner) { (void)owner; }
void Door::StateClosed::Exit(Object* owner) { (void)owner; }

void Door::StateOpen::Enter(Object* owner) {
    auto* d = static_cast<Door*>(owner);
    d->setSolidness(SPECTRAL);
    d->setVisible(false);
}
void Door::StateOpen::Execute(Object* owner) { (void)owner; }
void Door::StateOpen::Exit(Object* owner) { (void)owner; }
