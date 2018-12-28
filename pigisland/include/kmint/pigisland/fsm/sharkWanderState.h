#ifndef KMINT_PIGISLAND_SHARKWANDERSTATE_HPP
#define KMINT_PIGISLAND_SHARKWANDERSTATE_HPP
#include "sharkState.h"

namespace kmint {
	namespace pigisland {
		class sharkWanderState : public sharkState {
		public:
			sharkWanderState(shark* shark);
			void update(kmint::delta_time deltaTime) override;
		};
	}
}
#endif