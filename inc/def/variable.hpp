#pragma once

#include <string>

#include "base/result.hpp"

/**
 *	@brief Enumeration of the errors that may occur when building a variable
 */
enum EVariableBuildError {
    /// The default value indicates no error
    NO_ERROR,

    /// The name is ill formed, e.g. empty string
    ILLFORMED_NAME,

    /// The min, max values don't make sense
    INVALID_MINMAX,

    /// The value is not in bound with min and max
    VALUE_OUT_OF_BOUNDS,

    /// The build method got called twice
    CALLED_BUILD_TWICE
};

namespace vae {
namespace def {
    /**
     *	@brief	The type of a variable in an optimization problem
     */
    enum class VariableType {
        /// variable is a state variable
        VT_State,

        /// variable is a degree of freedom
        VT_DOF,
    };

    enum class EBoundsStrategy {
        /// the strategy when overshooting the bound is clamping
        VDT_CLAMP,

        /// the strategy when overshooting the bound is reflecting at the boundary
        VDT_REFLECT,
    };

    enum class EVariableValueError {
        /// No error occured (default value)
        NO_ERROR,

        /// The given value is out of bounds
        OUT_OF_BOUNDS,
    };

    /**
     *	@brief A Variable consists of a name, bounds, a value and optional a description
     *
     */
    class Variable {
    public:
        Variable(const Variable&) = default;
        Variable& operator=(const Variable&) = default;
        Variable(Variable&&) = default;
        Variable& operator=(Variable&&) = default;

        // #todo 1.2 Implement the missing method
        cpp::result<void, EVariableValueError> set_value(double value);

        double get_value() const { return m_value; }

        const std::string& get_name() const { return m_name; }

        // #todo 1.4 extract methods delta_clamp and delta_reflect
        void delta(double delta, EBoundsStrategy strategy);

    private:
        /**
         *	A variable should be generated via a @ref VariableBuilder
         */
        Variable()
            : m_min(0.0)
            , m_max(1.0)
            , m_value(0.5)
        {
        }

        double m_value;
        double m_min;
        double m_max;

        std::string m_name;

        std::string m_description;

        friend class VariableBuilder;
    };

    /**
     * @brief Builder to ensure construction of a valid @ref Variable object
     */
    class VariableBuilder {
    public:
        VariableBuilder(std::string name)
            : m_done(false)
        {
            m_variable.m_name = name;
        }

        // #todo 1.1 Move the implementations into the source file
        VariableBuilder& name(std::string name)
        {
            this->m_variable.m_name = name;
            return *this;
        }

        VariableBuilder& desc(std::string desc)
        {
            this->m_variable.m_description = desc;
            return *this;
        }

        VariableBuilder& value(double value)
        {
            this->m_variable.m_value = value;
            return *this;
        }

        VariableBuilder& min(double min)
        {
            this->m_variable.m_min = min;
            return *this;
        }

        VariableBuilder& max(double max)
        {
            this->m_variable.m_max = max;
            return *this;
        }

        //
        cpp::result<Variable, EVariableBuildError> build();

    private:
        bool m_done;

        Variable m_variable;
    };

}; // ns vae::def
}; // ns vae
