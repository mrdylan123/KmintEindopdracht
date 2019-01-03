#include <utility>
#include "../../../include/kmint/pigisland/genetics.h"
#include "kmint/random.hpp"

kmint::pigisland::genetics::genetics(int fitness, std::vector<float> chromosomes) : fitness_{ fitness }, chromosomes_{ std::move(chromosomes) }
{
}

float kmint::pigisland::genetics::calculateChance()
{
    chance_ = (fitness_ + 1) / (random_scalar(0.0f, 1.0f) * (fitness_ + 1));

    return chance_;
}

float kmint::pigisland::genetics::chance() const
{
    return chance_;
}
