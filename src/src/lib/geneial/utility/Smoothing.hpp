#pragma once

#include <geneial/utility/Smoothing.h>

geneial_private_namespace(geneial)
{
geneial_private_namespace(utility)
{
using ::geneial::population::chromosome::MultiValueChromosome;
geneial_export_namespace
{

template<typename VALUE_TYPE, typename FITNESS_TYPE>
void Smoothing::restoreSmoothness(typename MultiValueChromosome<VALUE_TYPE, FITNESS_TYPE>::ptr chromosome,
        VALUE_TYPE maxAbsElevation, VALUE_TYPE min, VALUE_TYPE max)
{
    VALUE_TYPE lastVal = *(chromosome->getContainer().begin());

    for (auto& it: chromosome->getContainer())
    {
        const VALUE_TYPE currentValue = it;

        if (std::abs(currentValue-lastVal) < maxAbsElevation)
        {
            //We are within the boundaries of the allowed elevation..
            //Not much to do here...
            lastVal = currentValue;
        }
        else
        {
            //We have exceeded the boundaries of the allowed elevation
            if (currentValue < lastVal)
            {
                //Case descending
                it = std::max(lastVal - maxAbsElevation, min);
                lastVal = it;
            }
            else
            {
                //Case ascending
                it = std::min(lastVal + maxAbsElevation, max);
                lastVal = it;
            }

        }
    }

}

template<typename VALUE_TYPE, typename FITNESS_TYPE>
void Smoothing::peakAt(unsigned int pos, unsigned int epsLeft, unsigned int epsRight, VALUE_TYPE elevation,
        typename MultiValueChromosome<VALUE_TYPE, FITNESS_TYPE>::ptr chromosome)
{
    const unsigned int chromSize = chromosome->getSize();

    assert(pos < chromSize);
    assert(0 <= pos);

    //Look at all the value to the LEFT of pos
    //Determine target left position (avoid underflow)
    unsigned int leftEpsPos = pos - epsLeft;
    if (pos < epsLeft)
    {
        leftEpsPos = 0;
    }
    assert(leftEpsPos >= 0);
    assert(leftEpsPos <= chromSize - 1);

    for (int i = pos; i >= static_cast<int>(leftEpsPos); i--)
    {
        assert(i >= 0);
        assert(i <= static_cast<signed>(chromSize - 1));
        //How many pct have we advanced to the left?
        double pctElevated;
        if (leftEpsPos != 0)
        {
            pctElevated = 1.0 - (static_cast<double>(i - leftEpsPos)) / static_cast<double>(leftEpsPos);
        }
        else
        {
            pctElevated = 1.0;
        }
        const VALUE_TYPE toModify = static_cast<VALUE_TYPE>(static_cast<double>(pctElevated) * elevation);

        chromosome->getContainer()[i] += toModify;
    }

    //Look at all the values to the RIGHT of pos
    //avoid overflow.
    unsigned int rightEpsPos = std::min(pos + epsRight, chromSize - 1);
    assert(rightEpsPos >= 0);
    assert(rightEpsPos <= chromSize - 1);

    for (unsigned int i = pos + 1; i < rightEpsPos; i++)
    {
        assert(i >= 0);
        assert(i <= chromSize - 1);
        //How many pct have we advanced to the right?
        double pctElevated;
        if (rightEpsPos != 0)
        {
            pctElevated = (static_cast<double>(i)) / static_cast<double>(rightEpsPos);
        }
        else
        {
            pctElevated = 0;
        }
        const VALUE_TYPE toModify = static_cast<VALUE_TYPE>((1.0 - static_cast<double>(pctElevated)) * elevation);

        chromosome->getContainer()[i] += toModify;
    }

}

} /* geneial_export_namespace */
} /* private namespace utility */
} /* private namespace geneial */

