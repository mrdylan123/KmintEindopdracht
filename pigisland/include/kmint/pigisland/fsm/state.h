#ifndef KMINT_PIGISLAND_STATE_HPP
#define KMINT_PIGISLAND_STATE_HPP

#include "kmint/primitives.hpp"

namespace kmint
{
	namespace pigisland
	{
		class state
		{
		public:
			state();
			virtual ~state() = default;
			state(const state& other) = delete;
			state(state&& other) noexcept = delete;
			state& operator=(const state& other) = delete;
			state& operator=(state&& other) noexcept = delete;

			virtual void update(kmint::delta_time deltaTime);

		protected:
			kmint::delta_time elapsedTime_;
		};
	}
}
#endif
