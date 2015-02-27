#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE contiuous_mvc

#include <boost/test/unit_test.hpp>
#include <cstdlib>
#include <set>
#include <vector>

#include <geneial/core/population/chromosome/MultiValueChromosome.h>
#include <geneial/core/population/chromosome/BaseChromosome.h>

#include <geneial/core/population/builder/ContinousMultiIntValueChromosomeFactory.h>
#include <geneial/core/population/builder/ContinousMultiValueBuilderSettings.h>

#include "mocks/MockFitnessEvaluator.h"

#include "helper/common_casts.h"

using namespace GeneticLibrary::Population::Chromosome;

BOOST_AUTO_TEST_SUITE( ContinousMultiValueChromosome )



template <typename VALUE_TYPE, typename FITNESS_TYPE>
inline void checkContinuity(typename BaseChromosome<FITNESS_TYPE>::ptr chromosomeToCheck,VALUE_TYPE maxDeriv )
{
	typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::ptr mvcPtr = TestHelper::convertBaseChromosome<VALUE_TYPE,FITNESS_TYPE>(chromosomeToCheck);

	VALUE_TYPE lastVal = *(mvcPtr->getContainer().begin());
	for(typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::const_it it = mvcPtr->getContainer().begin();
			it != mvcPtr->getContainer().end();++it){
		VALUE_TYPE val = std::abs(lastVal-*it);
		BOOST_CHECK(val <= maxDeriv);
		lastVal = *it;
	}
}


template <typename VALUE_TYPE, typename FITNESS_TYPE>
inline void checkLimits(typename BaseChromosome<FITNESS_TYPE>::ptr chromosomeToCheck,VALUE_TYPE lower, VALUE_TYPE upper)
{
	typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::ptr mvcPtr = TestHelper::convertBaseChromosome<VALUE_TYPE,FITNESS_TYPE>(chromosomeToCheck);

	for(typename MultiValueChromosome<VALUE_TYPE,FITNESS_TYPE>::const_it it = mvcPtr->getContainer().begin();
			it != mvcPtr->getContainer().end();++it){
		BOOST_CHECK(*it >= lower);
		BOOST_CHECK(*it <= upper);
	}
}


#define CONTINUITY_FACTORY_SIGNIFICANCE (100);
BOOST_AUTO_TEST_CASE( Continuity_Factory )
{
	const MockDoubleFitnessEvaluator::ptr evaluator(new MockDoubleFitnessEvaluator);

	int i = CONTINUITY_FACTORY_SIGNIFICANCE;
	while(i--)
	{
		BOOST_MESSAGE("130-0,20,5");
		ContinousMultiValueBuilderSettings<int,double> *builderSettings1 = new ContinousMultiValueBuilderSettings<int,double>(evaluator,2,130,0,true,20,5);
		ContinousMultiIntValueChromosomeFactory<double> *chromosomeFactory1 = new ContinousMultiIntValueChromosomeFactory<double>(builderSettings1);
		BaseChromosome<double>::ptr testCandidate11 = chromosomeFactory1->createChromosome();
		checkContinuity<int,double>(testCandidate11,5);
		checkLimits<int,double>(testCandidate11,0,130);

		BaseChromosome<double>::ptr testCandidate12 = chromosomeFactory1->createChromosome();
		checkContinuity<int,double>(testCandidate12,5);
		checkLimits<int,double>(testCandidate12,0,130);

		BOOST_MESSAGE("130-0,20,1");
		ContinousMultiValueBuilderSettings<int,double> *builderSettings2 = new ContinousMultiValueBuilderSettings<int,double>(evaluator,1,130,0,true,20,1);
		ContinousMultiIntValueChromosomeFactory<double> *chromosomeFactory2 = new ContinousMultiIntValueChromosomeFactory<double>(builderSettings2);
		BaseChromosome<double>::ptr testCandidate2 = chromosomeFactory2->createChromosome();
		checkContinuity<int,double>(testCandidate2,1);
		checkLimits<int,double>(testCandidate2,0,130);

		BOOST_MESSAGE("130-0,0,5");
		ContinousMultiValueBuilderSettings<int,double> *builderSettings3 = new ContinousMultiValueBuilderSettings<int,double>(evaluator,1,130,0,false,0,5);
		ContinousMultiIntValueChromosomeFactory<double> *chromosomeFactory3 = new ContinousMultiIntValueChromosomeFactory<double>(builderSettings3);
		BaseChromosome<double>::ptr testCandidate3 = chromosomeFactory3->createChromosome();
		checkContinuity<int,double>(testCandidate3,5);
		checkLimits<int,double>(testCandidate3,0,130);

		BOOST_MESSAGE("-130-0,0,5");
		ContinousMultiValueBuilderSettings<int,double> *builderSettings4 = new ContinousMultiValueBuilderSettings<int,double>(evaluator,1,0,-130,false,0,5);
		ContinousMultiIntValueChromosomeFactory<double> *chromosomeFactory4 = new ContinousMultiIntValueChromosomeFactory<double>(builderSettings4);
		BaseChromosome<double>::ptr testCandidate4 = chromosomeFactory4->createChromosome();
		checkContinuity<int,double>(testCandidate4,5);
		checkLimits<int,double>(testCandidate4,-130,0);

		BOOST_MESSAGE("-130-130,0,5");
		ContinousMultiValueBuilderSettings<int,double> *builderSettings5 = new ContinousMultiValueBuilderSettings<int,double>(evaluator,1,130,-130,false,0,5);
		ContinousMultiIntValueChromosomeFactory<double> *chromosomeFactory5 = new ContinousMultiIntValueChromosomeFactory<double>(builderSettings5);
		BaseChromosome<double>::ptr testCandidate5 = chromosomeFactory5->createChromosome();
		checkContinuity<int,double>(testCandidate5,5);
		checkLimits<int,double>(testCandidate5,-130,130);

		BOOST_MESSAGE("130-0,0,5");
		ContinousMultiValueBuilderSettings<int,double> *builderSettings6 = new ContinousMultiValueBuilderSettings<int,double>(evaluator,1,130,0,false,0,130);
		ContinousMultiIntValueChromosomeFactory<double> *chromosomeFactory6 = new ContinousMultiIntValueChromosomeFactory<double>(builderSettings6);
		BaseChromosome<double>::ptr testCandidate6 = chromosomeFactory6->createChromosome();
		checkContinuity<int,double>(testCandidate6,130);
		checkLimits<int,double>(testCandidate6,-130,130);
	}
}


BOOST_AUTO_TEST_SUITE_END()
