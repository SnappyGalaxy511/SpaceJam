#include "SpawnPlayer.h"
#include "WorldManager.h"
#include "Player.h"

SpawnPlayer::SpawnPlayer() {
	setType("spawn");
	registerInterest(df::STEP_EVENT);
}

int SpawnPlayer::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::STEP_EVENT) {
		if (WM.objectsOfType("player").isEmpty()) {
			new Player;
		}
	}

	return 0;
}