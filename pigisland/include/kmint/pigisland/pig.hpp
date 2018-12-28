#ifndef KMINT_PIGISLAND_PIG_HPP
#define KMINT_PIGISLAND_PIG_HPP

#include "kmint/play.hpp"
#include "kmint/math/vector2d.hpp"

namespace kmint {
	namespace pigisland {
		class shark;
		class boat;

		class pig : public play::free_roaming_actor {
		public:
			explicit pig(math::vector2d location, shark* shark, boat* boat);
			const ui::drawable &drawable() const override { return drawable_; }
			void move(math::vector2d delta) { location(location() + delta); }
			void act(delta_time dt) override;
			bool perceptive() const override { return true; }
			scalar range_of_perception() const override { return 30.0f; }

			void applyForce(math::vector2d force, delta_time dt);
			math::vector2d getVelocity();

		private:
			play::image_drawable drawable_;
			float sharkAttraction_;
			float boatAttraction_;
			
			// Flocking
			float cohesion_;
			float separation_;
			float alignment_;

			math::vector2d velocity_;
			float maxVelocity_;
			int mass_ = 1;

			shark* shark_;
			boat* boat_;
		};

	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_PIG_HPP */
