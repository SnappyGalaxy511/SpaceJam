#pragma once

#include "Object.h"
#include "Event.h"
#include "EventStep.h"

class SpawnPlayer : public df::Object {
public:
	SpawnPlayer();
	int eventHandler(const df::Event* p_e) override;
};
