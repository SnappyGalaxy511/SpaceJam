#pragma once
#include "GuardBase.h"

class GuardPatrol : public GuardBase {
    std::vector<df::Vector> m_waypoints;
    int m_current_wp = 0;
    float m_speed = 0.5f;

    void updateFacingFromDelta(const df::Vector& delta);

public:
    GuardPatrol(const std::vector<df::Vector>& waypoints,
        float speed_cells_per_step = 0.5f,
        GuardDirection start = GuardDirection::East,
        int vision_length = 12, int vision_width = 1);

    int eventHandler(const df::Event* p_e) override;
};