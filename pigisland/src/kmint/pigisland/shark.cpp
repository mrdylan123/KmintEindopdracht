#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/aStar.h"
#include "kmint/pigisland/fsm/sharkWanderState.h"

namespace kmint {
namespace pigisland {

shark::shark(kmint::map::map_graph &g)
    : play::map_bound_actor{g, find_shark_resting_place(g)},
      drawable_{*this, shark_image()}, map_{&g}, resting_place_(&node())
{
	//shortest_path_ = aStar::run(g, *resting_place_, g[57]);

	currentState_.push(std::make_unique<sharkWanderState>(this));
}

void shark::act(delta_time dt) {
  t_since_move_ += dt;

  if (shortest_path_.empty()) {
	  node(*resting_place_);
	  t_since_move_ = from_seconds(0);
	  shortest_path_ = aStar::run(*map_, *resting_place_, (*map_)[57]);
  }

  if (to_seconds(t_since_move_) >= waiting_time(node())) {
    node(*shortest_path_.top());
	shortest_path_.pop();
    t_since_move_ = from_seconds(0);
  }
}

} // namespace pigisland
} // namespace kmint
