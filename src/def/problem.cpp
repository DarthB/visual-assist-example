#include "def/Problem.hpp"
#include "def/Variable.hpp"

#include <iostream>

namespace vae {
namespace def {

    ProblemBuilder::ProblemBuilder()
    {
    }

    vae::def::ProblemBuilder& ProblemBuilder::add_dof(
        std::string name,
        std::function<void(VariableBuilder&)> adaptor /*= [](VariableBuilder&) {}*/)
    {
        VariableBuilder vb(name);
        adaptor(vb);
        auto res = vb.build();
        if (res.has_error()) {
            // #todo 2.1 handle all error cases
            EVariableBuildError ec = res.error();
            switch (ec) {
            case NO_ERROR:
                // we do nothing here
                break;
            }
        }
        auto dof = res.value();
        m_problem.m_dofs.push_back(dof);
        return *this;
    }

    vae::def::ProblemBuilder& ProblemBuilder::add_state_var(
        std::string name,
        std::function<void(VariableBuilder&)> adaptor /*= [](VariableBuilder&) {}*/)
    {
        VariableBuilder vb(name);
        adaptor(vb);
        auto res = vb.build();
        auto state_var = res.value();
        m_problem.m_states.push_back(state_var);
        return *this;
    }

    cpp::result<vae::def::Problem, vae::def::ProblemBuildError> ProblemBuilder::build()
    {
        return m_problem;
    }

    const vae::def::Variable& Problem::get_dof(const std::string& name) const
    {
        auto f = std::find_if(m_dofs.begin(), m_dofs.end(), [&name](const auto& dof) {
            return dof.get_name() == name;
        });

        if (f == m_dofs.end()) {
            throw std::exception("DOF not found");
        }

        return *f;
    }

    const vae::def::Variable& Problem::get_state_var(const std::string& name) const
    {
        auto f = std::find_if(m_states.begin(), m_states.end(), [&name](const auto& state_var) {
            return state_var.get_name() == name;
        });

        if (f == m_states.end()) {
            throw std::exception("State variable not found");
        }

        return *f;
    }

    void Problem::foreach_dof(std::function<void(Variable&)> ftor)
    {
        for (auto& dof : m_dofs) {
            ftor(dof);
        }
    }

    void Problem::foreach_state_var(std::function<void(Variable&)> ftor)
    {
        for (auto& state_var : m_states) {
            ftor(state_var);
        }
    }

    std::ostream& operator<<(std::ostream& out, Problem& problem)
    {
        out << "f(";
        bool first = true;
        problem.foreach_dof([&first, &out](auto& dof) {
            if (!first) {
                out << ",";
            }
            out << dof.get_value();
            first = false;
        });
        out << ")";
        return out;
    }

}; // ns vae::def
}; // ns vae
