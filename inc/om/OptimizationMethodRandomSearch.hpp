#pragma once

#include "base/Documentable.hpp"

#include "om/OptimizationMethodBase.hpp"

namespace vae {
namespace om {


    // #todo 0.2 Rename to OptimationMethodDFORandomSearch
    // #todo 2.2 implement interfaces
    class OptimizationMethodRandomSearch
        : public OptimizationMethodBase
//        , public vae::base::Documentable 
    {

    public:
        using super = OptimizationMethodBase;

        OptimizationMethodRandomSearch(std::mt19937& rand);

        std::pair<double, vae::def::Problem> optimize(
            vae::def::Problem start_point,
             const vae::def::ObjectiveFunction& objective) override;

    };

};
};
