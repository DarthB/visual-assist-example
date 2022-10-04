#include "def/Variable.hpp"

#include <algorithm>

namespace vae {
namespace def {

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

    // #todo 1.3 Rearrange the variable methods before the VariableBuilder methods
    void Variable::delta(double delta, EBoundsStrategy strategy)
    {
        if (strategy == EBoundsStrategy::VDT_CLAMP) {
            m_value = std::clamp(m_value + delta, m_min, m_max);

            
        } else if (strategy == EBoundsStrategy::VDT_REFLECT) {
            this->m_value += delta;
            
            // determine if we are in bounds
            int32_t out_of_bounds
                = static_cast<int32_t>(m_value > m_max)
                - static_cast<int32_t>(m_value < m_min);
            
        }
    }


}; // ns vae::def
}; // ns vae