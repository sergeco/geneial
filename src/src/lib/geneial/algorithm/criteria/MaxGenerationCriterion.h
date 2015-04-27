#pragma once

#include <geneial/core/population/management/BaseManager.h>
#include <geneial/algorithm/criteria/BaseStoppingCriterion.h>
#include <geneial/core/population/Population.h>

namespace geneial
{
namespace algorithm
{
namespace stopping_criteria
{

using namespace geneial::population;
using namespace geneial::population::management;

template<typename FITNESS_TYPE>
class MaxGenerationCriterion: public BaseStoppingCriterion<FITNESS_TYPE>
{
private:
    const typename Population<FITNESS_TYPE>::population_age _max;

public:
    MaxGenerationCriterion(const long num_max_iterations) :
            _max(num_max_iterations)
    {
    }

    virtual ~MaxGenerationCriterion()
    {
    }

    virtual inline bool wasReached(BaseManager<FITNESS_TYPE> &manager)
    {
        return !(manager.getPopulation().getAge() < _max);
    }

    virtual void print(std::ostream& os) const
    {
        os << "MaxGenerationCriterion (" << _max << ")";
    }

};

} /* namespace stopping_criteria */
} /* namespace algorithm */
} /* namespace geneial */

