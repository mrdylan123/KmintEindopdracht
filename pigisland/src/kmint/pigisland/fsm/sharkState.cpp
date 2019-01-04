#include "kmint/pigisland/fsm/sharkState.h"
#include "kmint/random.hpp"
#include "kmint/pigisland/fsm/sharkRestState.h"
#include "kmint/pigisland/pig.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/fsm/sharkScaredState.h"


namespace kmint
{
	namespace pigisland
	{
		sharkState::sharkState(shark* shark) : shark_{shark}
		{
		}

		void sharkState::update(kmint::delta_time deltaTime)
		{
			state::update(deltaTime);

			if (shark_->isHungry())
			{
				shark_->handle_collisions([](play::actor& collidingActor)
				{
					// Cast from actor to pig
					if (typeid(collidingActor) == typeid(pig))
					{
						pig* pig = dynamic_cast<pigisland::pig*>(&collidingActor);
						pig->die();
					}
				});
			}

			if (shark_->num_perceived_actors() != 0 && !shark_->isScared())
			{
				for (size_t i = 0; i < shark_->num_perceived_actors(); i++)
				{
					play::actor* perceivedActor = &shark_->perceived_actor(i);

					// Cast from actor to boat
					if (typeid(*perceivedActor) == typeid(boat))
					{
						boat* boat = dynamic_cast<pigisland::boat*>(perceivedActor);

						// Check if the boat is within 50 pixels
						const float dist = distance(shark_->location(), boat->location());
						if (dist <= 50)
						{
							shark_->setIsScared(true);
							shark_->pushState(std::make_unique<sharkScaredState>(shark_));
							return;
						}
					}
				}
			}

			if (shark_->totalSteps() == 100)
				shark_->pushState(std::make_unique<sharkRestState>(shark_));
		}
	}
}
