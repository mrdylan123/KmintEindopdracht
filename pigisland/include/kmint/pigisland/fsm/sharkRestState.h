#ifndef KMINT_PIGISLAND_SHARKRESTSTATE_HPP
#define KMINT_PIGISLAND_SHARKRESTSTATE_HPP
#include "sharkState.h"

namespace kmint
{
	namespace pigisland
	{
		class sharkRestState : public sharkState
		{
		public:
			sharkRestState(shark* shark);
			~sharkRestState() = default;
			sharkRestState(const sharkRestState& other) = delete;
			sharkRestState(sharkRestState&& other) noexcept = delete;
			sharkRestState& operator=(const sharkRestState& other) = delete;
			sharkRestState& operator=(sharkRestState&& other) noexcept = delete;


			void update(kmint::delta_time deltaTime) override;
		};
	}
}

#endif
