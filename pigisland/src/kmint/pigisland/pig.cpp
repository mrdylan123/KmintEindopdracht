#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>
#include "kmint/pigisland/shark.hpp"
#include "kmint/primitives.hpp"
#include "kmint/pigisland/boat.hpp"

namespace kmint {
    namespace pigisland {

        namespace {

            math::vector2d random_vector() {
                auto x = random_scalar(100, 924);
                auto y = random_scalar(50, 728);
                return { x, y };
            }
        } // namespace

		pig::pig(math::vector2d location, shark* shark, boat* boat)
            : free_roaming_actor{ random_vector() },
            drawable_{ *this, pig_image() }, sharkAttraction_{ random_scalar(-1.0f, 1.0f) },
            boatAttraction_{ random_scalar(-1.0f, 1.0f) }, cohesion_{ random_scalar(0.0f, 1.0f) },
			separation_{ random_scalar(0.0f, 1.0f) }, alignment_{ random_scalar(0.0f, 1.0f) }, shark_{ shark }, boat_{ boat }, maxVelocity_ {
			30
		} {}

		math::vector2d pig::getVelocity() {
			return velocity_;
		}

        void pig::act(delta_time dt) {
            free_roaming_actor::act(dt);

			math::vector2d sharkVector = shark_->location() - location();
			math::vector2d boatVector = boat_->location() - location();
			math::vector2d nearbyVector = math::vector2d{ 0, 0 };
			math::vector2d alignmentVector = math::vector2d{ 0, 0 };

			for (size_t i = 0; i < num_perceived_actors(); i++) {
				actor* perceivedActor = &perceived_actor(i);

				// Cast from actor to pig
				if (typeid(*perceivedActor) == typeid(pig)) {
					pig* pig = static_cast<kmint::pigisland::pig*>(perceivedActor);
					nearbyVector += pig->location() - location();
					alignmentVector += pig->velocity_;
				}
			}

			applyForce(sharkVector * sharkAttraction_ + boatVector * boatAttraction_ + nearbyVector * -separation_ + nearbyVector * cohesion_ + alignmentVector * alignment_, dt);
        }

	    void pig::applyForce(math::vector2d force, delta_time dt)
	    {
			float dtSeconds = to_seconds(dt);

			const float accelerationX = force.x() / mass_;
			const float accelerationY = force.y() / mass_;

			velocity_.x(velocity_.x() + accelerationX * dtSeconds);
			velocity_.y(velocity_.y() + accelerationY * dtSeconds);

			if (velocity_.x() > maxVelocity_)
				velocity_.x(maxVelocity_);

			if (velocity_.x() < -maxVelocity_)
				velocity_.x(-maxVelocity_);

			if (velocity_.y() > maxVelocity_)
				velocity_.y(maxVelocity_);

			if (velocity_.y() < -maxVelocity_)
				velocity_.y(-maxVelocity_);

			float locX = location().x() + velocity_.x() * dtSeconds;
			float locY = location().y() + velocity_.y() * dtSeconds;
			if (locX < 100)
				locX = 100;
			if (locX > 924)
				locX = 924;
			if (locY < 50)
				locY = 50;
			if (locY > 728)
				locY = 728;
			location(math::vector2d{ locX, locY });
	    }
    } // namespace pigisland

} // namespace kmint
