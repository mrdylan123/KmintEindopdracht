#include "../../../../include/kmint/pigisland/fsm/sharkScaredState.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/random.hpp"

kmint::pigisland::sharkScaredState::sharkScaredState(shark* shark) : sharkState(shark), numberOfSteps_{ 0 }
{
    shark->setIsHungry(false);
}

void kmint::pigisland::sharkScaredState::update(kmint::delta_time deltaTime)
{
    sharkState::update(deltaTime);

    if (numberOfSteps_ >= 10)
    {
	shark_->setIsScared(false);
	shark_->setIsHungry(true);
	shark_->popState();
	return;
    }

    if (to_seconds(elapsedTime_) >= waiting_time(shark_->node()))
    {
	// pick random edge
	int next_index = random_int(0, shark_->node().num_edges());
	shark_->move(shark_->node()[next_index].to());
	elapsedTime_ = from_seconds(0);
	numberOfSteps_++;
    }
}