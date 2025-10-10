#pragma once
#include "Object.h"
#include <string>

class Keycard : public df::Object {
public:
	char drawChar = 'O';

	Keycard();

	void setCollectorType(const std::string& t) { collector_type_ = t; }
	const std::string& getCollectorType() const { return collector_type_; }

	int eventHandler(const df::Event* p_e) override;

private:
	std::string collector_type_ = "player";
};
