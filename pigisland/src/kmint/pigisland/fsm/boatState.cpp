#include "../../../../include/kmint/pigisland/fsm/boatState.h"

kmint::pigisland::boatState::boatState(boat* boat)
{
	boat_ = boat;
}

void kmint::pigisland::boatState::update(kmint::delta_time deltaTime)
{
	state::update(deltaTime);
}
