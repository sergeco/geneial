#pragma once

#include <geneial/utility/Printable.h>
#include <geneial/core/fitness/Fitness.h>
#include <geneial/core/fitness/FitnessEvaluator.h>

#include <iostream>
#include <memory>
#include <cassert>

namespace geneial
{
namespace population
{
namespace chromosome
{

using namespace geneial::utility;

/**
 * @brief Abstract superclass for any type of chromosome
 */
template<typename FITNESS_TYPE>
class BaseChromosome: public Printable, public std::enable_shared_from_this<BaseChromosome<FITNESS_TYPE> >
{
    template<typename T> class Optional
    {
        T mValue;
        bool mHasValue;

    public:

        Optional() :
                mHasValue(false)
        {
        }

        Optional(T &&v) :
                mValue(std::move(v)), mHasValue(true)
        {
        }

        inline void set(T const &&v)
        {
            mValue = std::move(v);
            mHasValue = true;
        }

        //Note this does not call the dtor right away
        inline void clear()
        {
            mHasValue = false;\
        }

        inline T const &get() const
        {
            return mValue;
        }

        inline bool is_initialized() const
        {
            return mHasValue;
        }
    };

public:
    static const int CHROMOSOME_AGE_UNITIALIZED = 0;

    using chromosome_age = unsigned int;
    using chromsome_hash = std::size_t;

    using ptr = std::shared_ptr<BaseChromosome<FITNESS_TYPE>>;
    using const_ptr =std::shared_ptr<const BaseChromosome<FITNESS_TYPE>>;

    ptr getPtr()
    {
        return this->shared_from_this();
    }

    const_ptr getConstPtr()
    {
        return this->shared_from_this();
    }

    /**
     *
     */
    explicit BaseChromosome(typename FitnessEvaluator<FITNESS_TYPE>::ptr fitnessEvaluator) :
            _fitness(), _fitnessEvaluator(fitnessEvaluator), _age(CHROMOSOME_AGE_UNITIALIZED)
    {
        assert(_fitnessEvaluator);
    }

    virtual ~BaseChromosome()
    {
    }

    virtual bool equals(const BaseChromosome<FITNESS_TYPE> &chromosome) const = 0;

    /**
     * Used to 'age' a chromosome. Increments the age of a chromosome by one
     * Returns the new age of the chromosome
     */
    chromosome_age doAge();

    /**
     * Returns the age of a chromosome
     */
    chromosome_age getAge() const;

    void setAge(const chromosome_age age);

    virtual void print(std::ostream& os) const = 0;

    bool inline hasFitness() const
    {
        //Note (bewo) cast to bool will yield to boost::optional evaluation
        return _fitness.is_initialized();
    }

    /**
     * Gets the fitness value of a Chromosome.
     * Calls the fitness evaluator, if chromosome has no fitness yet.
     */
    const Fitness<FITNESS_TYPE>& getFitness() const;

    /**
     * If the chromosome was modified from outside and it's "cached" fitness can no no longer be
     * guaranteed to be accurate, this should be invoked to trigger a new Fitness Evaluation
     *
     * Caution: this function only has an effect on the concrete chromosome object, but does not
     * alter any external datastructures outside of the object's context
     * (e.g., the fitness map of a population)
     */
    void invalidateFitness();

    /**
     * Sets fitness of a chromosome
     */
    void setFitness(typename std::unique_ptr<Fitness<FITNESS_TYPE>> fitness);

    const typename FitnessEvaluator<FITNESS_TYPE>::ptr getFitnessEvaluator() const;

    void setFitnessEvaluator(const typename FitnessEvaluator<FITNESS_TYPE>::ptr& fitnessEvaluator);

    virtual chromsome_hash getHash() const = 0;

protected:

    virtual bool hashEquals(const BaseChromosome<FITNESS_TYPE> &chromosome) const;

    virtual void printHash(std::ostream& os) const;

private:
    mutable Optional<typename std::unique_ptr<Fitness<FITNESS_TYPE>>>_fitness;

    typename FitnessEvaluator<FITNESS_TYPE>::ptr _fitnessEvaluator;

    chromosome_age _age;
};

}
/* namespace chromomsome */
} /* namespace population */
} /* namespace geneial */

#include <geneial/core/population/chromosome/BaseChromosome.hpp>

