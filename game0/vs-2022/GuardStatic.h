#pragma once
#include "GuardBase.h"

class GuardStatic : public GuardBase {
    int m_swap_period_steps = 60;

public:
    GuardStatic(int swap_period_steps = 60,
        GuardDirection start = GuardDirection::East,
        int vision_length = 8, int vision_width = 1);

    int eventHandler(const df::Event* p_e) override;
};