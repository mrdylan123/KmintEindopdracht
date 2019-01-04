#ifndef KMINT_PIGISLAND_BOAT_HPP
#define KMINT_PIGISLAND_BOAT_HPP

#include "kmint/map/map.hpp"
#include "kmint/play.hpp"
#include "kmint/primitives.hpp"
#include "fsm/state.h"
#include <stack>

namespace kmint
{
	namespace pigisland
	{
		class boat : public play::map_bound_actor
		{
		public:
			boat(kmint::map::map_graph& g);
			ui::drawable const& drawable() const override { return drawable_; }
			bool incorporeal() const override { return false; }
			scalar radius() const override { return 24.0; }
			void act(delta_time dt) override;

			map::map_graph* map() const { return map_; }
			int damage() const { return damage_; }
			void incrementDamage();
			void repair(int amount);

			const std::stack<const graph::basic_node<map::map_node_info>*>* shortestPath() const
			{
				return &shortest_path_;
			}

			void setShortestPath(const std::stack<const graph::basic_node<map::map_node_info>*>& shortestPath)
			{
				shortest_path_ = shortestPath;
			}

			void pushState(std::unique_ptr<state> state);
			void popState();

			float repairChance1() const { return repairChance1_; }
			void setRepairChance1(float repairChance1) { repairChance1_ = repairChance1; }
			float repairChance2() const { return repairChance2_; }
			void setRepairChance2(float repairChance2) { repairChance2_ = repairChance2; }
			float repairChance3() const { return repairChance3_; }
			void setRepairChance3(float repairChance3) { repairChance3_ = repairChance3; }

			void move(node_type const& nextNode);
			void moveAlongShortestPath();

		private:
			play::image_drawable drawable_;
			map::map_graph* map_;
			delta_time t_since_move_{};

			int damage_;
			std::stack<std::unique_ptr<state>> currentState_;
			std::stack<const graph::basic_node<map::map_node_info>*> shortest_path_;

			float repairChance1_;
			float repairChance2_;
			float repairChance3_;
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_BOAT_HPP */
