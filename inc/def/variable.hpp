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

using cpp::result;

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

        void set_value(double value);

        double get_value() const { return m_value; }

        const std::string& get_name() const { return m_name; }

        void delta(double delta, EBoundsStrategy strategy);

        void delta_clamp(double delta);

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
        VariableBuilder(std::string name);

        VariableBuilder& name(std::string name);

        VariableBuilder& desc(std::string desc);

        VariableBuilder& value(double value);

        VariableBuilder& min(double min);

        VariableBuilder& max(double max);

        //
        cpp::result<Variable, EVariableBuildError> build();

    private:
        bool m_done;

        Variable m_variable;
    };

}; // ns vae::def
}; // ns vae
