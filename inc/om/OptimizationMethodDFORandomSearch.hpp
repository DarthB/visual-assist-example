#pragma once

#include "base/Documentable.hpp"

#include "om/OptimizationMethodBase.hpp"

namespace vae {
namespace om {

    /*!
     * \class classname
     *
     * \brief 
     *
     * \author smtmjanu
     * \date October 2022
     */
    class OptimizationMethodDFORandomSearch
        : public OptimizationMethodBase,
          public vae::base::Documentable {

    public:
        using super = OptimizationMethodBase;

        OptimizationMethodDFORandomSearch(std::mt19937& rand);

        std::pair<double, vae::def::Problem> optimize(
            vae::def::Problem start_point,
            const vae::def::ObjectiveFunction& objective) override;

        void initialize(std::unordered_map<std::string, std::string> parameters) override;

        std::string loc_get_name() const override;

        std::string loc_get_description() const override;

        std::vector<std::string> get_supported_parameters() const override;

        std::string loc_get_parameter_description(const std::string& parameter_name) const override;

        std::string loc_get_parameter_range(const std::string& parameter_name) const override;
    };

};
};
