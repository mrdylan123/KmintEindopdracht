#include "kmint/pigisland/fsm/state.h"


namespace kmint
{
	namespace pigisland
	{
		state::state() : elapsedTime_{0}
		{
		}

		void state::update(kmint::delta_time deltaTime)
		{
			elapsedTime_ += deltaTime;
		}
	}
}
