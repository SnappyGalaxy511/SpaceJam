#pragma once
#include "Event.h"

namespace game {
	inline const std::string KEYCARD_EVENT = "keycard-collected";
}

class EventKeycard : public df::Event {
public:
	EventKeycard() { setType(game::KEYCARD_EVENT); }
};