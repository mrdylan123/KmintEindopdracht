#include "kmint/pigisland/fsm/boatRepairState.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/aStar.h"
#include "kmint/random.hpp"

kmint::pigisland::boatRepairState::boatRepairState(boat* boat) : boatState(boat)
{
    const auto shortestPath = aStar::run(*boat->map(), boat->node(), find_random_mooring_place(*boat->map()));

    boat->setShortestPath(shortestPath);
}

void kmint::pigisland::boatRepairState::update(delta_time deltaTime)
{
    boatState::update(deltaTime);

    if (boat_->shortestPath()->empty())
    {
	switch (boat_->node().node_info().kind)
	{
	case '1': boat_->repair(random_int(30, 50)); break;
	case '2': boat_->repair(random_int(20, 100)); break;
	case '3': boat_->repair(50); break;
	}

	boat_->popState();
	return;
    }

    if (to_seconds(elapsedTime_) >= waiting_time(boat_->node())) {
	boat_->moveAlongShortestPath();
	elapsedTime_ = from_seconds(0);
    }
}
