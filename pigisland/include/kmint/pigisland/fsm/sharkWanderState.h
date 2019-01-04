#ifndef KMINT_PIGISLAND_SHARKWANDERSTATE_HPP
#define KMINT_PIGISLAND_SHARKWANDERSTATE_HPP
#include "sharkState.h"

namespace kmint
{
	namespace pigisland
	{
		class sharkWanderState : public sharkState
		{
		public:
			sharkWanderState(shark* shark);
			~sharkWanderState() = default;
			sharkWanderState(const sharkWanderState& other) = delete;
			sharkWanderState(sharkWanderState&& other) noexcept = delete;
			sharkWanderState& operator=(const sharkWanderState& other) = delete;
			sharkWanderState& operator=(sharkWanderState&& other) noexcept = delete;

			void update(kmint::delta_time deltaTime) override;
		};
	}
}
#endif
