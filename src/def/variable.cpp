#include "def/Variable.hpp"

#include <algorithm>

namespace vae {
namespace def {

    void Variable::set_value(double value)
    {
        m_value = value;
        
    }

    void delta_reflect(double delta, double& value, double m_max, double m_min)
    {
        value += delta;

        // determine if we are in bounds
        int32_t out_of_bounds
            = static_cast<int32_t>(value > m_max)
            - static_cast<int32_t>(value < m_min);

        if (out_of_bounds != 0) {
            
        }
    }

    void Variable::delta(double delta, EBoundsStrategy strategy)
    {
        if (strategy == EBoundsStrategy::VDT_CLAMP) {
            delta_clamp(delta);
        } else if (strategy == EBoundsStrategy::VDT_REFLECT) {
            delta_reflect(delta, m_value, m_max, m_min);
        }
    }

    void Variable::delta_clamp(double delta)
    {
        m_value = std::clamp(m_value + delta, m_min, m_max);
    }

    VariableBuilder::VariableBuilder(std::string name)
        : m_done(false)
    {
        m_variable.m_name = name;
    }

    vae::def::VariableBuilder& VariableBuilder::name(std::string name)
    {
        this->m_variable.m_name = name;
        return *this;
    }

    vae::def::VariableBuilder& VariableBuilder::desc(std::string desc)
    {
        this->m_variable.m_description = desc;
        return *this;
    }

    vae::def::VariableBuilder& VariableBuilder::value(double value)
    {
        this->m_variable.m_value = value;
        return *this;
    }

    vae::def::VariableBuilder& VariableBuilder::min(double min)
    {
        this->m_variable.m_min = min;
        return *this;
    }

    vae::def::VariableBuilder& VariableBuilder::max(double max)
    {
        this->m_variable.m_max = max;
        return *this;
    }

    cpp::result<vae::def::Variable, EVariableBuildError> VariableBuilder::build()
    {
        if (m_done) {
            return cpp::fail(EVariableBuildError::CALLED_BUILD_TWICE);
        }

        if (m_variable.m_name.empty()) {
            return cpp::fail(EVariableBuildError::ILLFORMED_NAME);
        }

        if (m_variable.m_value < m_variable.m_min || m_variable.m_value > m_variable.m_max) {
            return cpp::fail(EVariableBuildError::VALUE_OUT_OF_BOUNDS);
        }

        if (m_variable.m_min >= m_variable.m_max) {
            return cpp::fail(EVariableBuildError::INVALID_MINMAX);
        }

        m_done = true;
        return std::move(m_variable);
    }

}; // ns vae::def
}; // ns vae