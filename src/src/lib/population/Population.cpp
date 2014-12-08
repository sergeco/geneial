/*
 * Population.cpp
 *
 *  Created on: Nov 26, 2014
 *      Author: bewo
 */

#include "Population.h"
#include "Config.h"
#include <vector>

namespace GeneticLibrary {
namespace Population {

/**
 * Creates a vector containing ONE chromosome, the population needs to be build with replenishPopulation
 * @see replenishPopulation
 */
Population::Population() {
	//put one Chromosome into the population to create a starting point
	chromosomes.push_back(GeneticLibrary::Population::Chromosome::BasicChromosome());
}

Population::~Population() {
}

void Population::print(std::ostream& os) const {
	os << "Population: ";
}

/**
 * Returns a Vector of Chromosomes, each Chromosome contains a set of Values and a fitness value
 * @return A vector of chromosomes
 */
std::vector<GeneticLibrary::Population::Chromosome::BasicChromosome> Population::getChromosomes(){
	return this->chromosomes;
}


/**
	 * @return The amount of chomosones wich are part of the population.
	 */
int Population::size(){
	return this-> chromosomes.size();
}

} /* namespace Population */
} /* namespace GeneticLibrary */
