#include "DimensionRedox/MDS.hpp"
#include <exception>

using namespace magic;

/**
 * @brief Dimensionality reductor factory.
 * @param type Type of the dimensionality reduction algorithm. 
 * @return Returns a shared pointer to the dimensionality reduction algorithm.
 * @throw std::runtime_error If the type of the algorithm is invalid.
 */
std::shared_ptr<DimReductionAlgorithm> magic::DimReductionAlgorithm::build(DimReductionAlgorithmType type)
{
    switch(type)
    {
        case MDS_ALGORITHM:
            return std::shared_ptr<DimReductionAlgorithm>(new MDS);
    };
    
    throw(std::runtime_error("Invalid dimensionality reduction algorithm type"));
    
    return std::shared_ptr<DimReductionAlgorithm>(nullptr);
}
