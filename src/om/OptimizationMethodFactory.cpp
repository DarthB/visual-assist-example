
#include "om/OptimizationMethodFactory.hpp"
#include "om/OptimizationMethodBase.hpp"
#include "om/OptimizationMethodRandomSearch.hpp"

std::unique_ptr<vae::om::OptimizationMethodBase> vae::om::factor_optimization_method(
    EOptimizationMethod method,
    const std::unordered_map<std::string, std::string>& params,
    std::mt19937& rng)
{
    std::unique_ptr<vae::om::OptimizationMethodBase> reval;

    switch (method) {

    default:
        return nullptr;
    case EOptimizationMethod::OM_NONE:
        return nullptr;
    case EOptimizationMethod::OM_RANDOM_SEARCH:
        reval = std::make_unique<vae::om::OptimizationMethodRandomSearch>(rng);
    case EOptimizationMethod::OM_NEWTON_METHOD:
        break;
    }

    reval->initialize(params);
    return reval;
}
