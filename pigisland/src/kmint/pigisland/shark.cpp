#include "kmint/pigisland/shark.hpp"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/resources.hpp"
#include "kmint/random.hpp"
#include "kmint/pigisland/aStar.h"

namespace kmint {
namespace pigisland {

shark::shark(kmint::map::map_graph &g)
    : play::map_bound_actor{g, find_shark_resting_place(g)},
      drawable_{*this, shark_image()}, map_{&g}, resting_place_(&node())
{
    //graph::basic_graph<map::map_node_info>& asdf = map_[10];
    //shortest_path_ = aStar::run(*map_, *resting_place_, *map_[10]);
}

void shark::act(delta_time dt) {
  t_since_move_ += dt;
  if (to_seconds(t_since_move_) >= waiting_time(node())) {
    node(random_adjacent_node(node()));
    t_since_move_ = from_seconds(0);
  }
}

} // namespace pigisland
} // namespace kmint
