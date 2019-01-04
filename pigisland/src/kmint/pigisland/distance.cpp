#include "../../../include/kmint/pigisland/distance.h"

distance::distance() : shortestDistance_{std::numeric_limits<int>::max()}, fromNode_{nullptr}
{
}

int distance::shortestDistance() const
{
	return shortestDistance_;
}

const kmint::graph::basic_node<kmint::map::map_node_info>* distance::fromNode() const
{
	return fromNode_;
}

void distance::setShortestDistance(int shortestDistance)
{
	shortestDistance_ = shortestDistance;
}

void distance::setFromNode(const kmint::graph::basic_node<kmint::map::map_node_info>* fromNode)
{
	fromNode_ = fromNode;
}
