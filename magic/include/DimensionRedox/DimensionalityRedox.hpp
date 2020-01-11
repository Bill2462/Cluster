#ifndef DIMENSIONALITY_REDOX_HPP_INCLUDED
#define DIMENSIONALITY_REDOX_HPP_INCLUDED

#include <vector>
#include <memory>
#include "Types.hpp"

namespace magic
{
    /**
     * @brief Dimensionality algorithm reducition type.
     */
    enum DimReductionAlgorithmType
    {
        MDS_ALGORITHM
    };
    
    /**
     * @brief Dimensionality reduction algorithm.
     */
    class DimReductionAlgorithm
    {
    public:
        static std::shared_ptr<DimReductionAlgorithm> build(DimReductionAlgorithmType type);
        virtual std::vector<FeatureVector> reduce(const std::vector<FeatureVector>& input, unsigned short outputDim) = 0;
    };
    
}

#endif
