#include "kmint/pigisland/fsm/boatRepairState.h"
#include "kmint/pigisland/node_algorithm.hpp"
#include "kmint/pigisland/boat.hpp"
#include "kmint/pigisland/aStar.h"
#include "kmint/random.hpp"

kmint::pigisland::boatRepairState::boatRepairState(boat* boat) : boatState(boat)
{
	map::map_node const* chosenMooringPlace = nullptr;

	// Choose a mooring place based on the weights
	auto weights = std::vector<std::pair<int, map::map_node const&>>{
		{boat->repairChance1(), find_node_of_kind(*boat->map(), '1')},
		{boat->repairChance2(), find_node_of_kind(*boat->map(), '2')},
		{boat->repairChance3(), find_node_of_kind(*boat->map(), '3')},
	};

	int totalWeight = 0;

	for (auto& weight : weights)
	{
		totalWeight += weight.first;
	}

	int morringPlaceChance = rand() % totalWeight;

	for (auto& weight : weights)
	{
		if (morringPlaceChance < weight.first)
		{
			chosenMooringPlace = &weight.second;
			break;
		}

		morringPlaceChance -= weight.first;
	}

	const auto shortestPath = aStar::run(*boat->map(), boat->node(), *chosenMooringPlace);

	boat->setShortestPath(shortestPath);
}

void kmint::pigisland::boatRepairState::update(delta_time deltaTime)
{
	boatState::update(deltaTime);

	if (boat_->shortestPath()->empty())
	{
		int repairedAmount;
		switch (boat_->node().node_info().kind)
		{
		case '1':
			repairedAmount = random_int(30, 50);
			boat_->setRepairChance1(repairedAmount);
			boat_->repair(repairedAmount);
			break;
		case '2':
			repairedAmount = random_int(20, 100);
			boat_->setRepairChance2(repairedAmount);
			boat_->repair(repairedAmount);
			break;
		case '3':
			repairedAmount = 50;
			boat_->setRepairChance3(repairedAmount);
			boat_->repair(repairedAmount);
			break;
		}

		boat_->popState();
		return;
	}

	if (to_seconds(elapsedTime_) >= waiting_time(boat_->node()))
	{
		boat_->moveAlongShortestPath();
		elapsedTime_ = from_seconds(0);
	}
}
