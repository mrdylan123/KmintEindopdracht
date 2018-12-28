#include "kmint/pigisland/fsm/sharkWanderState.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/random.hpp"

namespace kmint {
	namespace pigisland {
		sharkWanderState::sharkWanderState(shark * shark) : sharkState(shark)
		{
		}

		void sharkWanderState::update(kmint::delta_time deltaTime)
		{
			state::update(deltaTime);

			if (to_seconds(elapsedTime_) >= waiting_time(shark_->node())) {
				// pick random edge
				int next_index = kmint::random_int(0, shark_->node().num_edges());
				shark_->node(shark_->node()[next_index].to());
				elapsedTime_ = kmint::from_seconds(0);
			}
		}
	}
}