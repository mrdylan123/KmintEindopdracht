#include "../../../../include/kmint/pigisland/fsm/sharkRestState.h"
#include "kmint/pigisland/aStar.h"
#include "kmint/pigisland/node_algorithm.hpp"

kmint::pigisland::sharkRestState::sharkRestState(shark* shark) : sharkState(shark)
{
    shark_->setIsHungry(false);
    shark_->setShortestPath(aStar::run(*shark_->map(), shark_->node(), *shark_->restingPlace()));
    shark_->setTotalSteps(0);
}

void kmint::pigisland::sharkRestState::update(kmint::delta_time deltaTime)
{
    sharkState::update(deltaTime);

    if (shark_->shortestPath()->empty()) {
	shark_->setIsResting(true);
	shark_->popState();
    }

    else if (to_seconds(elapsedTime_) >= waiting_time(shark_->node())) {
	shark_->moveToRestingPlace();
	elapsedTime_ = from_seconds(0);
    }
}
