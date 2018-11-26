////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Learning Library (ELL)
//  File:     MeanPoolingFunction.tcc (neural)
//  Authors:  Byron Changuion
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>

namespace ell
{
namespace predictors
{
    namespace neural
    {
        template <typename ElementType>
        MeanPoolingFunction<ElementType>::MeanPoolingFunction() :
            _sum(0),
            _numValues(0)
        {
        }

        template <typename ElementType>
        void MeanPoolingFunction<ElementType>::Accumulate(ElementType input)
        {
            _sum += input;
            _numValues++;
        }

        template <typename ElementType>
        ElementType MeanPoolingFunction<ElementType>::GetValue() const
        {
            return (_sum / (ElementType)_numValues);
        }
    } // namespace neural
} // namespace predictors
} // namespace ell
