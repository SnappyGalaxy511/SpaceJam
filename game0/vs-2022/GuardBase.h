#pragma once
#include "Object.h"
#include "WorldManager.h"
#include "EventStep.h"
#include "Box.h"
#include "Player.h"
#include "GuardDirection.h"
#include <vector>
#include <cmath>

class GuardBase : public df::Object {
protected:
	GuardDirection m_facing = GuardDirection::East;
	int m_vision_length = 8;
	int m_vision_width = 1;
	int m_tick = 0;
	bool m_debug_draw = false;


	df::Box makeVisionBox() const;

	bool isBlockingObject(const df::Object* o) const;
	df::Box pointProbe(const df::Vector& pt) const;
	bool pointHitsBlocker(const df::Vector& pt) const;
	bool hasUnobstructedLOSTo(const Player* player) const;
	bool canSeePlayer();


	virtual void onPlayerSpotted();

public:
	GuardBase();

	virtual int eventHandler(const df::Event* p_e) override { return 0; }
	void visionCheckAndReact();

	void setFacing(GuardDirection dir) { m_facing = dir; }
	GuardDirection getFacing() const { return m_facing; }
	void setVision(int length, int width) { m_vision_length = length; m_vision_width = width; }
	void setDebugDraw(bool enabled) { m_debug_draw = enabled; }
};