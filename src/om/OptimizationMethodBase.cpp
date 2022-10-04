#include "om/OptimizationMethodBase.hpp"
#include <algorithm>
#include <locale>
#include <string>

vae::om::optimization_method_parameters::optimization_method_parameters()
    : max_iterations(100)
    , objective_tolerance(0.0001)
    , max_step_size(0.1)
{
}

vae::om::OptimizationMethodBase::OptimizationMethodBase(std::mt19937& rand)
    : m_rand(rand)
{
}

void vae::om::OptimizationMethodBase::initialize(
    std::unordered_map<std::string, std::string> parameters)
{
    for (const auto& [varname, value] : parameters) {
        std::string lower_varname;
        std::transform(
            varname.begin(), varname.end(),
            std::back_inserter(lower_varname),
            [](char c) { return std::tolower(c); });

        if (lower_varname.compare("max_iterations") == 0) {
            m_params.max_iterations = stoi(value);
        } else if (lower_varname.compare("objective_tolerance") == 0) {
            m_params.objective_tolerance = stod(value);
        } else if (lower_varname.compare("max_step_size") == 0) {
            m_params.max_step_size = stod(value);
        } else {
        }
    }
}
