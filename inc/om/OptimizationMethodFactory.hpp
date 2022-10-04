#pragma once

#include <random>

#include <gsl/gsl>

namespace vae { namespace om { class OptimizationMethodBase; } }

namespace vae {
namespace om {

    enum class EOptimizationMethod {
        OM_NONE,
        OM_RANDOM_SEARCH,
        OM_NEWTON_METHOD,
    };

    std::unique_ptr<vae::om::OptimizationMethodBase>
    factor_optimization_method(
        EOptimizationMethod method,
        const std::unordered_map<std::string, std::string>& params,
        std::mt19937& rng);

};
};
