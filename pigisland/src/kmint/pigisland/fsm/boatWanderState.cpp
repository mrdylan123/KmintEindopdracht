#include "../../../../include/kmint/pigisland/fsm/boatWanderState.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/fsm/boatRepairState.h"
#include "kmint/pigisland/pig.hpp"

kmint::pigisland::boatWanderState::boatWanderState(boat* boat) : boatState(boat)
{
}

void kmint::pigisland::boatWanderState::update(kmint::delta_time deltaTime)
{
	boatState::update(deltaTime);

	if (boat_->damage() >= 100)
	{
		boat_->pushState(std::make_unique<boatRepairState>(boat_));
		return;
	}

	boat_->handle_collisions([](play::actor& collidingActor)
	{
		// Cast from actor to pig
		if (typeid(collidingActor) == typeid(pig))
		{
			pig* pig = dynamic_cast<pigisland::pig*>(&collidingActor);
			pig->rescue();
		}
	});

	if (to_seconds(elapsedTime_) >= waiting_time(boat_->node()))
	{
		boat_->move(random_adjacent_node(boat_->node()));
		elapsedTime_ = from_seconds(0);
		boat_->incrementDamage();
	}
}
