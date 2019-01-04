#include "../../../include/kmint/pigisland/geneticAlgorithm.h"
#include <algorithm>
#include <map>
#include "kmint/random.hpp"
#include <numeric>

kmint::pigisland::geneticAlgorithm::geneticAlgorithm() : generationcount_{1}
{
}

void kmint::pigisland::geneticAlgorithm::addGenetics(genetics genetics)
{
	genetics_.emplace_back(genetics);
}

std::vector<kmint::pigisland::genetics> kmint::pigisland::geneticAlgorithm::generatePopulation(
	std::vector<std::pair<float, float>>& chromosomeRanges)
{
	generationcount_++;

	// Selection 
	std::vector<genetics*> parents{};

	float totalFitness = std::accumulate(genetics_.begin(), genetics_.end(), 0.0f,
	                                     [](float total, genetics& g) { return total + g.fitness(); });

	// Calculate chances and sort by chance
	for (genetics& genetics : genetics_)
		genetics.calculateChance(totalFitness);

	std::sort(genetics_.begin(), genetics_.end(), [](const genetics& g, const genetics& otherG)
	{
		return g.chance() < otherG.chance();
	});


	// Calculate the accumulated chances (chance + sum of previous chances)
	float accumulatedValue = 0;

	std::map<genetics*, float> accumulatedValues{};

	for (genetics& genetics : genetics_)
	{
		accumulatedValue += genetics.chance();

		accumulatedValues.insert(std::make_pair(&genetics, accumulatedValue));
	}

	const float maxChance = (--accumulatedValues.end())->second;
	const float minChance = accumulatedValues.begin()->second;

	while (parents.size() <= 1)
	{
		parents.clear();
		const float cutOffValue = random_scalar(0.0f, 1.0f);

		for (auto& genetics : accumulatedValues)
		{
			// If the normalized chance is greater or equal to the cutOffValue, this genetics becomes a parent
			if ((genetics.second - minChance) / (maxChance - minChance) >= cutOffValue)
				parents.emplace_back(&(*genetics.first));
		}
	}


	const int chromosomeCount = genetics_[0].chromosomes()->size();

	std::vector<genetics> resultGenetics{};

	// Crossover
	for (int i = 0; i < 100 - parents.size(); ++i)
	{
		// Randomly choose parents and chromosome divider index
		int divider = random_int(1, chromosomeCount - 1);

		const int firstParent = random_int(0, parents.size());
		int secondParent = random_int(0, parents.size());

		while (firstParent == secondParent && parents.size() != 1)
			secondParent = random_int(0, parents.size());

		std::pair<genetics, genetics> parentPair{*parents[firstParent], *parents[secondParent]};

		// Merge parent chromosomes into new offspring chromosome
		std::vector<float> newChromosomes{};

		for (size_t i = 0; i < divider; i++)
		{
			newChromosomes.emplace_back((*parentPair.first.chromosomes())[i]);
		}

		for (size_t i = divider; i < parentPair.first.chromosomes()->size(); i++)
		{
			newChromosomes.emplace_back((*parentPair.second.chromosomes())[i]);
		}

		resultGenetics.emplace_back(newChromosomes);
	}

	for (genetics* parent : parents)
	{
		resultGenetics.emplace_back(*parent);
	}

	// Mutation
	if (generationcount_ % 20 == 0)
	{
		for (genetics& genetics : resultGenetics)
		{
			int randomChromosomeToMutate = random_int(0, chromosomeCount);
			float newValue = random_scalar(chromosomeRanges[randomChromosomeToMutate].first,
			                               chromosomeRanges[randomChromosomeToMutate].second);

			(*genetics.chromosomes())[randomChromosomeToMutate] = newValue;
		}
	}

	genetics_.clear();

	return resultGenetics;
}
