#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "fsm/state.h"
#include <stack>

namespace kmint {
    namespace pigisland {

	class boat : public play::map_bound_actor {
	public:
	    boat(kmint::map::map_graph &g);
	    ui::drawable const &drawable() const override { return drawable_; }
	    bool incorporeal() const override { return false; }
	    scalar radius() const override { return 16.0; }
	    void act(delta_time dt) override;

	    map::map_graph* map() const { return map_; }
	    int damage() const { return damage_; }
	    void incrementDamage();
	    void repair(int amount);
	    const std::stack<const graph::basic_node<map::map_node_info>*>* shortestPath() const { return &shortest_path_; }
	    void setShortestPath(const std::stack<const graph::basic_node<map::map_node_info>*>& shortestPath) { shortest_path_ = shortestPath; }

	    void pushState(std::unique_ptr<state> state);
	    void popState();

	    void move(node_type const& nextNode);
	    void moveAlongShortestPath();

	private:
	    play::image_drawable drawable_;
	    map::map_graph *map_;
	    delta_time t_since_move_{};

	    int damage_;
	    std::stack<std::unique_ptr<state>> currentState_;
	    std::stack<const graph::basic_node<map::map_node_info>*> shortest_path_;
	};

    } // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
