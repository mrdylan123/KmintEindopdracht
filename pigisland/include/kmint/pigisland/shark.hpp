#ifndef KMINT_PIGISLAND_SHARK_HPP
#define KMINT_PIGISLAND_SHARK_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include <stack>

namespace kmint
{
    namespace pigisland
    {
	class state;

	class shark : public play::map_bound_actor
	{
	public:
	    shark(map::map_graph& g);
	    ~shark() = default;
	    ui::drawable const& drawable() const override { return drawable_; }
	    bool perceptive() const override { return true; }
	    scalar radius() const override { return 16.0; }
	    bool incorporeal() const override { return false; }
	    scalar range_of_perception() const override { return 100.0f; }
	    void act(delta_time dt) override;
	    int totalSteps() const { return totalSteps_; }
	    void setTotalSteps(int totalSteps) { totalSteps_ = totalSteps; }
	    bool isResting() const { return isResting_; }
	    void setIsResting(bool isResting) { isResting_ = isResting; }
	    bool isScared() const { return isScared_; }
	    void setIsScared(bool isHungry) { isScared_ = isHungry; }
	    bool isHungry() const { return isHungry_; }
	    void setIsHungry(bool isHungry) { isHungry_ = isHungry; }
	    map::map_graph* map() const { return map_; }
	    map::map_node const* restingPlace() const { return resting_place_; }
	    const std::stack<const graph::basic_node<map::map_node_info>*>* shortestPath() const { return &shortest_path_; }
	    void setShortestPath(const std::stack<const graph::basic_node<map::map_node_info>*>& shortestPath) { shortest_path_ = shortestPath; }
	    void pushState(std::unique_ptr<state> state);
	    void popState();

	    void move(node_type const& nextNode);
	    void moveToRestingPlace();
	    void moveAlongShortestPath();

	private:
	    play::image_drawable drawable_;
	    map::map_graph* map_;
	    map::map_node const* resting_place_;
	    delta_time t_since_move_{};
	    std::stack<const graph::basic_node<map::map_node_info>*> shortest_path_;
	    int totalSteps_;
	    bool isResting_;
	    bool isScared_;
	    bool isHungry_;

	    std::stack<std::unique_ptr<state>> currentState_;
	};
    } // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_SHARK_HPP */
