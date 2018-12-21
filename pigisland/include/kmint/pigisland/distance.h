#include "kmint/map/map.hpp"

class distance
{
public:
    distance();

    int shortestDistance() const;
    kmint::graph::basic_node<kmint::map::map_node_info>* fromNode() const;
    void setShortestDistance(int shortestDistance);
    void setFromNode(kmint::graph::basic_node<kmint::map::map_node_info>* fromNode);

private:
    int shortestDistance_;
    kmint::graph::basic_node<kmint::map::map_node_info>* fromNode_;
};
