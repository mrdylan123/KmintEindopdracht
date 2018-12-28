#include "kmint/pigisland/pig.hpp"
#include "kmint/math/angle.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include <cmath>

namespace kmint {
    namespace pigisland {

        namespace {

            math::vector2d random_vector() {
                auto x = random_scalar(100, 924);
                auto y = random_scalar(50, 728);
                return { x, y };
            }
        } // namespace

        pig::pig(math::vector2d location)
            : free_roaming_actor{ random_vector() },
            drawable_{ *this, pig_image() }, sharkAttraction_{ random_scalar(-1.0f, 1.0f) },
            boatAttraction_{ random_scalar(-1.0f, 1.0f) }, cohesion_{ random_scalar(0.0f, 1.0f) },
            separation_{ random_scalar(0.0f, 1.0f) }, alignment_{ random_scalar(0.0f, 1.0f) } {}


        void pig::act(delta_time dt) {
            free_roaming_actor::act(dt);
        }
    } // namespace pigisland

} // namespace kmint
