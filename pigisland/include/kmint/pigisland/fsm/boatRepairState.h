#ifndef KMINT_PIGISLAND_BOATREPAIRSTATE_HPP
#define KMINT_PIGISLAND_BOATREPAIRSTATE_HPP
#include "boatState.h"

namespace kmint
{
	namespace pigisland
	{
		class boatRepairState : public boatState
		{
		public:
			boatRepairState(boat* boat);
			~boatRepairState() = default;
			boatRepairState(const boatRepairState& other) = delete;
			boatRepairState(boatRepairState&& other) noexcept = delete;
			boatRepairState& operator=(const boatRepairState& other) = delete;
			boatRepairState& operator=(boatRepairState&& other) noexcept = delete;

			void update(kmint::delta_time deltaTime) override;
		};
	}
}
#endif
