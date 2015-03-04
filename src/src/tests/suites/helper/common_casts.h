#ifndef __GENEIAL_TEST_COMMON_CASTS_H_
#define __GENEIAL_TEST_COMMON_CASTS_H_

#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>

#include <geneial/core/population/chromosome/BaseChromosome.h>
#include <geneial/core/population/chromosome/MultiValueChromosome.h>

namespace test_helper{

using namespace geneial::population::chromosome;

template <typename VALUE_TYPE, typename FITNESS_TYPE>
inline typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::ptr convertBaseChromosome(typename BaseChromosome<FITNESS_TYPE>::ptr ptr)
{
	typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::ptr myChrom
		= boost::dynamic_pointer_cast<MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE> >(ptr);
	BOOST_CHECK(myChrom);
	return myChrom;
}

} /* namespace test_helper */

#endif /* __GENEIAL_TEST_ */
