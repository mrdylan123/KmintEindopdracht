#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/pigisland/aStar.h"
#include "kmint/pigisland/fsm/sharkWanderState.h"

namespace kmint {
    namespace pigisland {

	shark::shark(kmint::map::map_graph &g)
	    : play::map_bound_actor{ g, find_shark_resting_place(g) },
	    drawable_{ *this, shark_image() }, map_{ &g }, resting_place_(&node()), totalSteps_{ 0 }, isResting_{ false }, isScared_{ false }, isHungry_{ true }
	{
	    //shortest_path_ = aStar::run(g, *resting_place_, g[57]);

	    currentState_.push(std::make_unique<sharkWanderState>(this));
	}

	void shark::act(delta_time dt) {
	    currentState_.top()->update(dt);
	}

	void shark::pushState(std::unique_ptr<state> state)
	{
	    if (currentState_.top() != state)
		currentState_.push(std::move(state));
	}

	void shark::popState()
	{
	    currentState_.pop();
	}

	void shark::move(node_type const& nextNode)
	{
	    node(nextNode);
	    totalSteps_++;
	}

	void shark::moveToRestingPlace()
	{
	    node(*shortest_path_.top());
	    shortest_path_.pop();
	}

	void shark::moveAlongShortestPath()
	{
	    move(*shortest_path_.top());
	    shortest_path_.pop();
	}
    } // namespace pigisland
} // namespace kmint
