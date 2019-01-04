#ifndef KMINT_PIGISLAND_GENETICALGORITHM_HPP
#define KMINT_PIGISLAND_GENETICALGORITHM_HPP

#include <vector>
#include "genetics.h"

namespace kmint
{
	namespace pigisland
	{
		class geneticAlgorithm
		{
		public:
			geneticAlgorithm();
			~geneticAlgorithm() = default;
			geneticAlgorithm(const geneticAlgorithm& other) = default;
			geneticAlgorithm(geneticAlgorithm&& other) noexcept = default;
			geneticAlgorithm& operator=(const geneticAlgorithm& other) = default;
			geneticAlgorithm& operator=(geneticAlgorithm&& other) noexcept = default;

			void addGenetics(genetics genetics);
			std::vector<genetics> generatePopulation(std::vector<std::pair<float, float>>& chromosomeRanges);
		private:
			std::vector<genetics> genetics_;
			int generationcount_;
		};
	} // namespace pigisland
} // namespace kmint

#endif /* KMINT_PIGISLAND_GENETICALGORITHM_HPP_HPP */
