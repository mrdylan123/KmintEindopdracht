#ifndef KMINT_PIGISLAND_BOATWANDERSTATE_HPP
#define KMINT_PIGISLAND_BOATWANDERSTATE_HPP
#include "boatState.h"

namespace kmint
{
	namespace pigisland
	{
		class boatWanderState : public boatState
		{
		public:
			boatWanderState(boat* boat);
			~boatWanderState() = default;
			boatWanderState(const boatWanderState& other) = delete;
			boatWanderState(boatWanderState&& other) noexcept = delete;
			boatWanderState& operator=(const boatWanderState& other) = delete;
			boatWanderState& operator=(boatWanderState&& other) noexcept = delete;

			void update(kmint::delta_time deltaTime) override;
		};
	}
}
#endif
