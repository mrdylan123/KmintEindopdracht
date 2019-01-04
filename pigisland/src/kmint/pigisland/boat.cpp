#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/fsm/boatWanderState.h"
#include <iostream>

namespace kmint
{
	namespace pigisland
	{
		boat::boat(kmint::map::map_graph& g)
			: play::map_bound_actor{g, find_random_mooring_place(g)},
			  drawable_{*this, boat_image()}, map_{&g}, damage_{0}, repairChance1_{33}, repairChance2_{33},
			  repairChance3_{33}
		{
			currentState_.push(std::make_unique<boatWanderState>(this));
			std::cout << "Porcus Vincit state: " << typeid(*currentState_.top()).name() << std::endl;
		}

		void boat::act(delta_time dt)
		{
			currentState_.top()->update(dt);
		}

		void boat::incrementDamage()
		{
			damage_++;
		}

		void boat::repair(int amount)
		{
			damage_ -= amount;
		}

		void boat::pushState(std::unique_ptr<state> state)
		{
			if (currentState_.top() != state)
				currentState_.push(std::move(state));
			std::cout << "Porcus Vincit state: " << typeid(*currentState_.top()).name() << std::endl;
		}

		void boat::popState()
		{
			currentState_.pop();
			std::cout << "Porcus Vincit state: " << typeid(*currentState_.top()).name() << std::endl;
		}

		void boat::move(node_type const& nextNode)
		{
			node(nextNode);
		}

		void boat::moveAlongShortestPath()
		{
			move(*shortest_path_.top());
			shortest_path_.pop();
		}
	} // namespace pigisland
} // namespace kmint
