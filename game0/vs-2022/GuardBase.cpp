#include "GuardBase.h"
#include "WorldManager.h"
#include "GameManager.h"
#include "Box.h"
#include <cmath>


static df::Box worldBoxOf(const df::Object* o) {
	if (!o) return df::Box(df::Vector(), 0, 0);

	df::Box lb = o->getBox();
	df::Vector pos = o->getPosition();

	df::Vector world_corner(pos.getX() + lb.getCorner().getX(),
		pos.getY() + lb.getCorner().getY());
	return df::Box(world_corner, lb.getHorizontal(), lb.getVertical());
}

// Axis-aligned box overlap 
static bool boxesOverlap(const df::Box& A, const df::Box& B) {
	float a_left = A.getCorner().getX();
	float a_top = A.getCorner().getY();
	float a_right = a_left + A.getHorizontal();
	float a_bottom = a_top + A.getVertical();

	float b_left = B.getCorner().getX();
	float b_top = B.getCorner().getY();
	float b_right = b_left + B.getHorizontal();
	float b_bottom = b_top + B.getVertical();

	if (a_right <= b_left)   return false;
	if (b_right <= a_left)   return false;
	if (a_bottom <= b_top)    return false;
	if (b_bottom <= a_top)    return false;
	return true;
}

// Make a 1x1 probe box at a given world position.
static df::Box probeAt(const df::Vector& pt) {
	return df::Box(df::Vector(pt.getX(), pt.getY()), 1.0f, 1.0f);
}

GuardBase::GuardBase() {
	setSolidness(df::HARD);
	registerInterest(df::STEP_EVENT);
}

//vision box
df::Box GuardBase::makeVisionBox() const {
	df::Vector p = getPosition();
	switch (m_facing) {
		case GuardDirection::East:
			return df::Box(df::Vector(p.getX() + 1, p.getY() - m_vision_width / 2.0f), m_vision_length, m_vision_width);
		case GuardDirection::West:
			return df::Box(df::Vector(p.getX() - m_vision_length, p.getY() - m_vision_width / 2.0f), m_vision_length, m_vision_width);
		case GuardDirection::North:
			return df::Box(df::Vector(p.getX() - m_vision_width / 2.0f, p.getY() - m_vision_length), m_vision_width, m_vision_length);
		case GuardDirection::South:
			return df::Box(df::Vector(p.getX() - m_vision_width / 2.0f, p.getY() + 1), m_vision_width, m_vision_length);	
	}
	return df::Box(p, 0, 0);
}

//Line of sight helpers
bool GuardBase::isBlockingObject(const df::Object* o) const {
	if (!o) return false; 
	if (o == this) return false;
	if (dynamic_cast<const Player*>(o)) return false; 
	return (o->getSolidness() == df::HARD);
}

df::Box GuardBase::pointProbe(const df::Vector& pt) const {
	return probeAt(pt);
}

bool GuardBase::pointHitsBlocker(const df::Vector& pt) const {
	df::WorldManager& wm = WM;
	df::ObjectList all = wm.getAllObjects();
	df::Box probe = pointProbe(pt);

	for (int i =0; i < all.getCount(); i++) {
		df::Object* o = all[i];
		if (!isBlockingObject(o)) continue;
		if(boxesOverlap(probe, worldBoxOf(o))) {
			return true; 
		}
	}
	return false;
}

bool GuardBase::hasUnobstructedLOSTo(const Player* player) const {
	if (!player) return false;

	df::Vector g = getPosition();
	df::Box pb = worldBoxOf(player);
	df::Vector pc(pb.getCorner().getX() + pb.getHorizontal() * 0.5f, pb.getCorner().getY() + pb.getVertical() * 0.5f);

	float dx = pc.getX() - g.getX();
	float dy = pc.getY() - g.getY();
	float dist = std::sqrt(dx * dx + dy * dy);
	if (dist <= 0.0001f) return true;

	const float step = 0.5f;
	int samples = (int)std::ceil(dist / step);

	//walk toward player but avoid sampling at t==0 (self) and t==1 (player center)
	for(int i = 1; i<samples; i++) {
		float t = (i * step) / dist;
		if (t >= 1.0f) break;
		df::Vector p(g.getX() + dx * t, g.getY() + dy * t);

		if (boxesOverlap(probeAt(p), worldBoxOf(this))) continue;
		if (pointHitsBlocker(p)) {
			return false;
		}
	}
	return true;
}

bool GuardBase::canSeePlayer() {
	df::WorldManager& wm = WM;
	df::ObjectList all = wm.getAllObjects();
	df::Box vis = makeVisionBox();

	Player* player = nullptr;
	for (int i = 0; i < all.getCount(); ++i) {
		if ((player = dynamic_cast<Player*>(all[i]))) break;
	}
	if (!player) return false;

	if (!boxesOverlap(worldBoxOf(player), vis)) return false;

	return hasUnobstructedLOSTo(player);
}

void GuardBase::onPlayerSpotted() {
	WM.markForDelete(WM.objectsOfType("player"));
}

void GuardBase::visionCheckAndReact() {
	if (canSeePlayer()) {
		onPlayerSpotted();
	}
}