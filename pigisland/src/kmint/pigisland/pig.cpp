#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>
#include "kmint/pigisland/shark.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/genetics.h"

namespace kmint
{
	namespace pigisland
	{
		namespace
		{
			math::vector2d random_vector()
			{
				auto x = random_scalar(100, 924);
				auto y = random_scalar(50, 728);
				return {x, y};
			}
		} // namespace

		pig::pig(math::vector2d location, shark* shark, boat* boat)
			: free_roaming_actor{random_vector()},
			  drawable_{*this, pig_image()}, sharkAttraction_{random_scalar(-1.0f, 1.0f)},
			  boatAttraction_{random_scalar(-1.0f, 1.0f)}, cohesion_{random_scalar(0.0f, 1.0f)},
			  separation_{random_scalar(0.0f, 1.0f)}, alignment_{random_scalar(0.0f, 1.0f)},
			  shark_{shark}, boat_{boat}, maxVelocity_{30}, isDead_{false}, rescued_{false}
		{
		}

		pig::pig(math::vector2d location, shark* shark, boat* boat, pigisland::genetics& genetics)
			: free_roaming_actor{random_vector()},
			  drawable_{*this, pig_image()}, sharkAttraction_{(*genetics.chromosomes())[0]},
			  boatAttraction_{(*genetics.chromosomes())[1]}, cohesion_{(*genetics.chromosomes())[2]},
			  separation_{(*genetics.chromosomes())[3]}, alignment_{(*genetics.chromosomes())[4]},
			  shark_{shark}, boat_{boat}, maxVelocity_{30}, isDead_{false}, rescued_{false}
		{
		}

		math::vector2d pig::getVelocity()
		{
			return velocity_;
		}

		genetics pig::genetics() const
		{
			int fitness = 0;

			if (!isDead_)
				fitness++;

			if (rescued_)
				fitness += 10;

			return pigisland::genetics{
				fitness, std::vector<float>{{sharkAttraction_, boatAttraction_, cohesion_, separation_, alignment_}}
			};
		}

		void pig::act(delta_time dt)
		{
			if (rescued_) return;

			free_roaming_actor::act(dt);

			math::vector2d sharkVector = shark_->location() - location();
			math::vector2d boatVector = boat_->location() - location();
			math::vector2d nearbyVector = math::vector2d{0, 0};
			math::vector2d alignmentVector = math::vector2d{0, 0};
			math::vector2d islandVector = math::vector2d{0, 0};

			for (size_t i = 0; i < num_perceived_actors(); i++)
			{
				actor* perceivedActor = &perceived_actor(i);

				// Cast from actor to pig
				if (typeid(*perceivedActor) == typeid(pig))
				{
					pig* pig = static_cast<kmint::pigisland::pig*>(perceivedActor);
					nearbyVector += pig->location() - location();
					alignmentVector += pig->velocity_;
				}
			}

			// Pigs cannot go on the grass islands
			for (rectangle& island : grassIslands())
			{
				if (island.overlaps(location().x(), location().y(), 1, 1))
				{
					const math::vector2d islandLocation = math::vector2d{
						static_cast<float>((island.x() + island.w()) / 2),
						static_cast<float>((island.y() + island.h()) / 2)
					};

					islandVector = (islandLocation - location()) * 999;
				}
			}

			// Sum all vectors to get a final vector to apply the force with
			applyForce(sharkVector * sharkAttraction_
			           + boatVector * boatAttraction_
			           + nearbyVector * -separation_
			           + nearbyVector * cohesion_
			           + alignmentVector * alignment_
			           + islandVector, dt);
		}

		void pig::die()
		{
			isDead_ = true;
		}

		void pig::rescue()
		{
			rescued_ = true;
			location(math::vector2d{512, 384});
		}

		void pig::applyForce(math::vector2d force, delta_time dt)
		{
			float dtSeconds = to_seconds(dt);

			// Calculate new velocity
			const float accelerationX = force.x() / mass_;
			const float accelerationY = force.y() / mass_;

			velocity_.x(velocity_.x() + accelerationX * dtSeconds);
			velocity_.y(velocity_.y() + accelerationY * dtSeconds);

			// Limit velocity
			if (velocity_.x() > maxVelocity_)
				velocity_.x(maxVelocity_);

			if (velocity_.x() < -maxVelocity_)
				velocity_.x(-maxVelocity_);

			if (velocity_.y() > maxVelocity_)
				velocity_.y(maxVelocity_);

			if (velocity_.y() < -maxVelocity_)
				velocity_.y(-maxVelocity_);

			// Restrict pigs from going offscreen
			float locX = location().x() + velocity_.x() * dtSeconds;
			float locY = location().y() + velocity_.y() * dtSeconds;

			if (locX < 10)
				locX = 10;
			if (locX > 1014)
				locX = 1014;
			if (locY < 10)
				locY = 10;
			if (locY > 758)
				locY = 758;

			location(math::vector2d{locX, locY});
		}
	} // namespace pigisland
} // namespace kmint
