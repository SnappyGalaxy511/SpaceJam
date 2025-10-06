#pragma once
#include <string>
#include "Object.h"
#include "StateMachine.h"
#include "Box.h"
#include "State.h"

namespace df { class State; }

class LaserOn;
class LaserOff;

class Laser : public df::Object {
public:
	enum class Orientation { Horizontal, Vertical };

	Laser(int on_steps = 45, int off_steps = 45,
		Orientation orient = Orientation::Horizontal, int length = 5);

	void setVictimType(const std::string& t) { m_victim_type = t; }

	void setOnSteps(int s) { m_on_steps = s; }
	void setOffSteps(int s) { m_off_steps = s; }
	void setOrientation(Orientation o);
	void setLength(int L);

	int eventHandler(const df::Event* p_e) override;
	int draw() override;

	bool isOn() const { return m_is_on; }

	//Helpers
	void setOn(bool on) { m_is_on = on; }
	int  getOnSteps() const { return m_on_steps; }
	int  getOffSteps() const { return m_off_steps; }
	void resetTimer(int steps) { m_timer = steps; }
	void tickTimer() { if (m_timer > 0) m_timer--; }
	bool timerElapsed() const { return m_timer <= 0; }

private:
	df::StateMachine m_fsm;

	LaserOn* m_on_ptr;
	LaserOff* m_off_ptr;
	LaserOn& onState();
	LaserOff& offState();

	LaserOn* m_on_storage;
	LaserOff* m_off_storage;

	int  m_on_steps;
	int  m_off_steps;
	int  m_timer = 0;
	bool m_is_on = false;
	std::string m_victim_type = "player";

	Orientation m_orient;
	int m_length;

	void updateBeamBox();
	void drawBeam() const;

	friend class LaserOn;
	friend class LaserOff;
};

//States
class LaserOn : public df::State {
public:
	void Enter(df::Object* p_obj) override;
	void Execute(df::Object* p_obj) override;
	void Exit(df::Object* p_obj) override;
};

class LaserOff : public df::State {
public:
	void Enter(df::Object* p_obj) override;
	void Execute(df::Object* p_obj) override;
	void Exit(df::Object* p_obj) override;
};