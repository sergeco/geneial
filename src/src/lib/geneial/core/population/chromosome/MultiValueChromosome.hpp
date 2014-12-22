/*
 * MultiValueChromosome.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: bewo
 */

#ifndef MULTIVALUECHROMOSOME_HPP_
#define MULTIVALUECHROMOSOME_HPP_

#include <geneial/core/population/chromosome/MultiValueChromosome.h>
#include <iterator>
#include <algorithm>

namespace GeneticLibrary {
namespace Population {
namespace Chromosome {

template <typename VALUE_TYPE, typename FITNESS_TYPE>
bool MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::equals(typename BaseChromosome<FITNESS_TYPE>::const_ptr chromosome) const{

	typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::const_ptr mvc = boost::dynamic_pointer_cast<const MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE> >(chromosome);
	if(mvc){
		return std::equal(_container.begin(),_container.end(),mvc->getConstIt());
	}else{
		return false;
	}
}


template <typename VALUE_TYPE, typename FITNESS_TYPE>
unsigned int MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getSize() const{
	return _container.size();
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::value_container& MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getContainer(){
	return _container;
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
void MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::setValueContainer(value_container container){
	_container = container;
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::const_it MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getConstIt() const{
	return _container.begin();
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::it MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getIt() const{
	return _container.begin();
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::it MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getMax() const{
	    return max_element(_container.begin(),_container.end());
}
template <typename VALUE_TYPE, typename FITNESS_TYPE>
typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::it MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getMin() const{
	   return min_element(_container.begin(),_container.end());
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
VALUE_TYPE MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getAverage() const{
	const VALUE_TYPE sum = std::accumulate(_container.begin(),_container.end(),0);
	const unsigned int size = getSize();

	if(size == 0){
		return 0;
	}else{
		assert(size>0);
		return sum/size;
	}
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
VALUE_TYPE MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getRange() const{
	MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::const_it max = getMax();
	MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::const_it min = getMin();
	assert(max>=min);
	return *max - *min;
}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
VALUE_TYPE MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::getSum() const{
	VALUE_TYPE sum = std::accumulate(_container.begin(),_container.end(),0);
	return sum;

}

template <typename VALUE_TYPE, typename FITNESS_TYPE>
void MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::print(std::ostream& os) const{
	os << "Fitness: ";
	if(this->hasFitness()){
		os << *this->getFitness();
	}else{
		os << "N/A";
	}
	os << ", ";
	os << "Age: " << this->getAge() << ", ";


	os << "Values: " << std::endl;
	std::ostream_iterator<VALUE_TYPE> out_it(os, "; ");
	std::copy ( _container.begin(), _container.end(), out_it );
	os << std::endl;
}

} /* namespace Chromosome */
} /* namespace Population */
} /* namespace GeneticLibrary */


#endif /* MULTIVALUECHROMOSOME_HPP_ */
