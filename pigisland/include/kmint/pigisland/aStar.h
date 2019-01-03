#ifndef KMINTAPP_ASTAR_H
#define KMINTAPP_ASTAR_H

#include "kmint/map/map.hpp"
#include <stack>
#include "kmint/graph/graph.hpp"
#include <iostream>
#include <map>

#include <queue>
#include "distance.h"

class aStar
{
public:
    static int distanceBetween(kmint::math::vector2d vector1, kmint::math::vector2d vector2)
    {
        kmint::math::vector2d distanceVector = vector1 - vector2;

        int distance = (abs(distanceVector.x()) + abs(distanceVector.y())) / 32;

        return distance;
    }

    static std::stack<const kmint::graph::basic_node<kmint::map::map_node_info>*> run(
        kmint::map::map_graph& graph, kmint::graph::basic_graph<kmint::map::map_node_info>::node_type const& start,
        kmint::graph::basic_graph<kmint::map::map_node_info>::node_type const& end)
    {
	graph.untag_all();
        std::stack<const kmint::graph::basic_node<kmint::map::map_node_info>*> shortestPath = std::stack<const kmint::graph::basic_node<kmint::map::map_node_info>*>{};

        std::priority_queue<std::pair<int, const kmint::graph::basic_node<kmint::map::map_node_info>*>,
            std::vector<std::pair<int, const kmint::graph::basic_node<kmint::map::map_node_info>*>>,
            std::greater<std::pair<int, const kmint::graph::basic_node<kmint::map::map_node_info>*>>> priorityQueue;

        std::vector<const kmint::graph::basic_node<kmint::map::map_node_info>*> visitedNodes{};

        kmint::graph::basic_node<kmint::map::map_node_info>* startNode = nullptr;
        const kmint::graph::basic_node<kmint::map::map_node_info>* endNode = nullptr;

        std::map<const kmint::graph::basic_node<kmint::map::map_node_info>*, distance> distances{};

        for (std::size_t i = 0; i < graph.num_nodes(); ++i) {
            distance dist{};

            if (graph[i].node_id() == start.node_id())
            {
                startNode = &graph[i];
                dist.setShortestDistance(0);
            }

            distances.insert(std::pair<kmint::graph::basic_node<kmint::map::map_node_info>*, distance>(&graph[i], dist));
        }

        priorityQueue.push(std::make_pair(distances.at(startNode).shortestDistance(), startNode));

        int checks = 0;

        /* Looping till priority queue becomes empty (or all
          distances are not finalized) */
        while (!priorityQueue.empty())
        {
            checks++;

            // The first vertex in pair is the minimum distance 
            // vertex, extract it from priority queue. 
            // vertex label is stored in second of pair (it 
            // has to be done this way to keep the vertices 
            // sorted distance (distance must be first item 
            // in pair) 
            const kmint::graph::basic_node<kmint::map::map_node_info>* node = priorityQueue.top().second;

            if (node->node_id() == end.node_id())
            {
                endNode = node;
                break;
            }

            priorityQueue.pop();

            visitedNodes.emplace_back(node);

            // 'i' is used to get all adjacent vertices of a vertex 
            for (auto& vertex : *node)
            {
                const kmint::graph::basic_node<kmint::map::map_node_info>* oppositeNode;

                if (node == &vertex.from())
                {
                    oppositeNode = &vertex.to();
                }
                else
                {
                    oppositeNode = &vertex.from();
                }

                if (std::find(visitedNodes.begin(), visitedNodes.end(), oppositeNode) == visitedNodes.end())
                {
                    //  If there is shorted path to v through u. 
                    if (distances.at(oppositeNode).shortestDistance() > distances.at(node).shortestDistance() + vertex.weight() + distanceBetween(oppositeNode->location(), end.location()))
                    {
                        // Updating distance of v 
                        distances.at(oppositeNode).setShortestDistance(distances.at(node).shortestDistance() + vertex.weight() + distanceBetween(oppositeNode->location(), end.location()));
						distances.at(oppositeNode).setFromNode(node);
                        priorityQueue.push(std::make_pair(distances.at(oppositeNode).shortestDistance(), oppositeNode));
                    }
                }
            }
        }

        if (distances.at(endNode).fromNode() != nullptr || endNode->node_id() == start.node_id())
        {
            while (endNode != nullptr)
            {
                shortestPath.push(endNode);
				for (std::size_t i = 0; i < graph.num_nodes(); ++i) {

					if (graph[i].node_id() == endNode->node_id())
					{
						graph[i].tagged(true);
					}
				}
                endNode = distances.at(endNode).fromNode();
            }
        }

        return shortestPath;
    }
};
#endif
