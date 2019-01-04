#ifndef KMINT_PIGISLAND_GENETICS_HPP
#define KMINT_PIGISLAND_GENETICS_HPP

#include <vector>

namespace kmint
{
	namespace pigisland
	{
		class genetics
		{
		public:
			genetics(int fitness, std::vector<float> chromosomes);
			genetics(std::vector<float> chromosomes);
			~genetics() = default;
			genetics(const genetics& other) = default;
			genetics(genetics&& other) noexcept = default;
			genetics& operator=(const genetics& other) = default;
			genetics& operator=(genetics&& other) noexcept = default;

			int fitness() const { return fitness_; }
			std::vector<float>* chromosomes() { return &chromosomes_; }

			float calculateChance(float totalFitness);
			float chance() const;
		private:
			int fitness_;
			std::vector<float> chromosomes_;
			float chance_;
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_KMINT_PIGISLAND_GENETICS_HPP_HPP */
