#include "../../../include/kmint/pigisland/geneticAlgorithm.h"
#include <algorithm>
#include <map>
#include "kmint/random.hpp"

kmint::pigisland::geneticAlgorithm::geneticAlgorithm()
{
}

void kmint::pigisland::geneticAlgorithm::addGenetics(genetics genetics)
{
    genetics_.emplace_back(genetics);
}

void kmint::pigisland::geneticAlgorithm::generatePopulation()
{
    std::vector<genetics*> parents{};

    for (genetics& genetics : genetics_)
	genetics.calculateChance();

    std::sort(genetics_.rbegin(), genetics_.rend(), [](const genetics& g, const genetics& otherG) 
    {
	    return g.chance() < otherG.chance();
    });

    float maxChance = genetics_.back().calculateChance();
    float minChance = genetics_.front().calculateChance();

    float cutOffValue = random_scalar(0.0f, 1.0f);

    for (genetics& genetics : genetics_)
    {
	if ((genetics.chance() - minChance) / (maxChance - minChance) < cutOffValue)
	    break;

	parents.emplace_back(&genetics);
    }
}
