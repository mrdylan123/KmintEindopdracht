#include "kmint/pigisland/fsm/sharkWanderState.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/fsm/sharkPursuitState.h"

namespace kmint
{
    namespace pigisland
    {
	sharkWanderState::sharkWanderState(shark* shark) : sharkState(shark)
	{
	}

	void sharkWanderState::update(delta_time deltaTime)
	{
	    sharkState::update(deltaTime);

	    if (shark_->num_perceived_actors() != 0)
	    {
		pig* closestPig = nullptr;
		float closestDistance = std::numeric_limits<float>::max();

		for (size_t i = 0; i < shark_->num_perceived_actors(); i++) {
		    play::actor* perceivedActor = &shark_->perceived_actor(i);

		    // Cast from actor to pig
		    if (typeid(*perceivedActor) == typeid(pig)) {
			pig* pig = dynamic_cast<pigisland::pig*>(perceivedActor);

			float dist = distance2(shark_->location(), pig->location());

			if (dist < closestDistance)
			{
			    closestPig = pig;
			    closestDistance = dist;
			}
		    }
		}

		if (closestPig)
		    shark_->pushState(std::make_unique<sharkPursuitState>(shark_, closestPig));
	    }

	    if (to_seconds(elapsedTime_) >= waiting_time(shark_->node()))
	    {
		// pick random edge
		int next_index = random_int(0, shark_->node().num_edges());
		shark_->move(shark_->node()[next_index].to());
		elapsedTime_ = from_seconds(0);
	    }


	}
    }
}
