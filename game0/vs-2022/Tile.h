#pragma once

#include "Object.h"

class Tile : public df::Object {
private:
	bool m_is_vertical;

public:
	Tile();
	Tile(bool is_vertical);

	int eventHandler(const df::Event* p_e) override;
	int draw() override;
};
