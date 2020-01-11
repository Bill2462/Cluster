#ifndef MDS_HPP_INCLUDED
#define MDS_HPP_INCLUDED

#include <eigen3/Eigen/Core>
#include "DimensionalityRedox.hpp"

namespace magic
{
    /**
     * @brief Multidimensional scaling (MDS) algorithm.
     */
    class MDS : public magic::DimReductionAlgorithm
    {
    public:
        std::vector<FeatureVector> reduce(const std::vector<FeatureVector>& input, unsigned short outputDim) override;
        
    private:
        void computeDistanceMatrix(const std::vector<FeatureVector>& points);
        
        Eigen::MatrixXd distanceMatrix; /** @brief Distance matrix. */
    };
}

#endif
