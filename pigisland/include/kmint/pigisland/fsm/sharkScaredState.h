#ifndef KMINT_PIGISLAND_SHARKSCAREDSTATE_HPP
#define KMINT_PIGISLAND_SHARKSCAREDSTATE_HPP
#include "sharkState.h"

namespace kmint
{
	namespace pigisland
	{
		class sharkScaredState : public sharkState
		{
		public:
			sharkScaredState(shark* shark);
			~sharkScaredState() = default;
			sharkScaredState(const sharkScaredState& other) = delete;
			sharkScaredState(sharkScaredState&& other) noexcept = delete;
			sharkScaredState& operator=(const sharkScaredState& other) = delete;
			sharkScaredState& operator=(sharkScaredState&& other) noexcept = delete;

			void update(kmint::delta_time deltaTime) override;

		private:
			int numberOfSteps_;
		};
	}
}

#endif
