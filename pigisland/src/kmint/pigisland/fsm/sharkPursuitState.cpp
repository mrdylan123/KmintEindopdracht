#include "../../../../include/kmint/pigisland/fsm/sharkPursuitState.h"
#include "../../../../include/kmint/pigisland/aStar.h"
#include "../../../../include/kmint/pigisland/pig.hpp"
#include "../../../../include/kmint/pigisland/node_algorithm.hpp"

kmint::pigisland::sharkPursuitState::sharkPursuitState(shark* shark, pig* pig) : sharkState(shark)
{
    graph::basic_node<map::map_node_info>* closestNode = nullptr;
    float closestDistance = std::numeric_limits<float>::max();

    for (graph::basic_node<map::map_node_info>& node : *shark_->map())
    {
	float dist = distance2(node.location(), pig->location());

	if (dist < closestDistance)
	{
	    closestNode = &node;
	    closestDistance = dist;
	}
    }

    shark_->setShortestPath(aStar::run(*shark_->map(), shark_->node(), *closestNode));
}

void kmint::pigisland::sharkPursuitState::update(kmint::delta_time deltaTime)
{
    sharkState::update(deltaTime);

    if (shark_->shortestPath()->empty()) {
	shark_->popState();
    }
    else if (to_seconds(elapsedTime_) >= waiting_time(shark_->node())) {
	shark_->moveAlongShortestPath();
	elapsedTime_ = from_seconds(0);
    }
}
