#include "GuardPatrol.h"
#include "WorldManager.h"
#include "EventStep.h"
#include <cmath>

GuardPatrol::GuardPatrol(const std::vector<df::Vector>& waypoints,
    float speed_cells_per_step,
    GuardDirection start,
    int vision_length, int vision_width)
    : m_waypoints(waypoints), m_speed(speed_cells_per_step) {
    m_facing = start;
    setVision(vision_length, vision_width);
    setType("GuardPatrol");
    setSprite("enemy");
}

void GuardPatrol::updateFacingFromDelta(const df::Vector& delta) {
    if (fabs(delta.getX()) >= fabs(delta.getY()))
        m_facing = (delta.getX() >= 0) ? GuardDirection::East : GuardDirection::West;
    else
        m_facing = (delta.getY() >= 0) ? GuardDirection::South : GuardDirection::North;
}

int GuardPatrol::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::STEP_EVENT) {
        if (!m_waypoints.empty()) {
            df::Vector cur = getPosition();
            df::Vector target = m_waypoints[m_current_wp];
            df::Vector delta(target.getX() - cur.getX(), target.getY() - cur.getY());

            float dx = delta.getX();
            float dy = delta.getY();
            float dist = std::sqrt(dx * dx + dy * dy);
            if (dist < 0.001f) dist = 0.0f;

            if (dist <= m_speed || dist == 0.0f) {
                WM.moveObject(this, target);
                m_current_wp = (m_current_wp + 1) % m_waypoints.size();
            }
            else {
                df::Vector step(delta.getX() / dist * m_speed,
                    delta.getY() / dist * m_speed);
                updateFacingFromDelta(step);
                df::Vector next(cur.getX() + step.getX(), cur.getY() + step.getY());
                WM.moveObject(this, next);
            }
        }
        visionCheckAndReact();
    }
    return 0;
}