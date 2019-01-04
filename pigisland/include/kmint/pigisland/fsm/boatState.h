#ifndef KMINT_PIGISLAND_BOATSTATE_HPP
#define KMINT_PIGISLAND_BOATSTATE_HPP
#include "state.h"
#include <memory>
#include <stack>

namespace kmint
{
	namespace pigisland
	{
		class boat;

		class boatState : public state
		{
		public:
			boatState(boat* boat);
			~boatState() = default;
			boatState(const boatState& other) = delete;
			boatState(boatState&& other) noexcept = delete;
			boatState& operator=(const boatState& other) = delete;
			boatState& operator=(boatState&& other) noexcept = delete;

			void update(kmint::delta_time deltaTime) override;
		protected:
			boat* boat_;
		};
	}
}
#endif
