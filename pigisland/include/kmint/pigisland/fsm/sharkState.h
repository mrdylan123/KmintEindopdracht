#ifndef KMINT_PIGISLAND_SHARKSTATE_HPP
#define KMINT_PIGISLAND_SHARKSTATE_HPP
#include "state.h"
#include "../shark.hpp"

namespace kmint {
	namespace pigisland {
		class sharkState : public state {
		public:
			sharkState(shark* shark);
		protected:
			shark* shark_;
		};
	}
}
#endif