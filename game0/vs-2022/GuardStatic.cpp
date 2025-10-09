#include "GuardStatic.h"
#include "EventStep.h"

GuardStatic::GuardStatic(int swap_period_steps,
    GuardDirection start,
    int vision_length, int vision_width) {
    m_swap_period_steps = swap_period_steps;
    m_facing = start;
    setVision(vision_length, vision_width);
    setType("GuardStatic");
    setSprite("enemy");
}

int GuardStatic::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        m_tick++;
        if (m_tick % m_swap_period_steps == 0) {
            switch (m_facing) {
            case GuardDirection::East:  m_facing = GuardDirection::West; break;
            case GuardDirection::West:  m_facing = GuardDirection::East; break;
            case GuardDirection::North: m_facing = GuardDirection::South; break;
            case GuardDirection::South: m_facing = GuardDirection::North; break;
            }
        }
        visionCheckAndReact();
    }
    return 0;
}