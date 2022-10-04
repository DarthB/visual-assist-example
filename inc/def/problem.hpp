#pragma once

#include <functional>
#include <optional>
#include <string>
#include <vector>

#include "base/result.hpp"

#include "def/Variable.hpp"

namespace vae {
namespace def {

    /**
     *	@brief Signature for a function that calculates state variables based upon a number of
     *			degrees of freedom
     */
    using EvaluationFunction
        = std::function<std::vector<Variable>(
            const std::vector<Variable>&,
            const std::vector<Variable>&)>;

    /**
     *  @brief Error reasons when building an optimization problem.
     */
    enum class EProblemBuildError {
        NO_ERROR,

        MISSING_DOF,

        INVALID_VARIABLE_ADDED,

        AMBIGIOUS_VARIABLE
    };

    struct ProblemBuildError {
        /// the error code
        EProblemBuildError type;

        /// nested error type when variable building was wrong
        std::unordered_map<std::string, EVariableBuildError> nested_errors;

        /// implicit conversion to error enum where needed
        operator EProblemBuildError() const { return type; }
    };

    class Problem {
    public:
        const Variable& get_dof(const std::string& name) const;

        const Variable& get_state_var(const std::string& name) const;

        void foreach_dof(std::function<void(Variable&)>);

        void foreach_state_var(std::function<void(Variable&)>);

        const std::vector<Variable>& get_dofs() const { return m_dofs; }

        std::vector<Variable>& get_states() { return m_states; }

    private:
        std::vector<Variable> m_dofs;

        std::vector<Variable> m_states;

        friend class ProblemBuilder;
    };

    class ProblemBuilder {
    public:
        ProblemBuilder();

        ProblemBuilder& add_dof(
            std::string name,
            std::function<void(VariableBuilder&)> = [](VariableBuilder&) {});

        ProblemBuilder& add_state_var(
            std::string name,
            std::function<void(VariableBuilder&)> = [](VariableBuilder&) {});

        cpp::result<Problem, ProblemBuildError> build();

    private:
        Problem m_problem;
    };

    std::ostream& operator<<(std::ostream& out, Problem&);
}; // ns vae::def
}; // ns vae
