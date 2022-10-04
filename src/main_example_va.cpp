#include "def/ObjectiveFunction.hpp"
#include "def/problem.hpp"

#include "om/OptimizationMethodBase.hpp"
#include "om/OptimizationMethodFactory.hpp"

#include <iostream>

using vae::def::ProblemBuilder;
using vae::def::VariableBuilder;

class objective_quadratic_2d
    : public vae::def::ObjectiveFunction {

public:
    gsl::owner<ObjectiveFunction*> clone() const override
    {
        throw std::logic_error("The method or operation is not implemented.");
    }

    double evaluate(const vae::def::Problem& pr) const override
    {
        auto x = pr.get_dof("x").get_value();
        auto y = pr.get_dof("y").get_value();

        return x * x + y * y; 
    }
};

// #review with perspective on usability for library users

/**
 *  @brief Generates an optimization problem for f(x,y) = x^2 + y^2
 */
vae::def::Problem generate_quadratic_function_problem()
{
    vae::def::ProblemBuilder pb;

    pb.add_dof("x", [](VariableBuilder& vb) { vb.min(-3.0).max(3.0); })
        .add_dof("y", [](VariableBuilder& vb) { vb.min(-3.0).max(3.0); });

    auto return_candidate = pb.build();
    return return_candidate.value();
}

/**
 *  @brief Generates an imaginary optimization problem for a reactor
 */
vae::def::Problem generate_reactor_problem_description()
{
    vae::def::ProblemBuilder pb;
    pb.add_dof("Volumen", [](VariableBuilder& vb) { vb.min(0.5).max(2.0); })
        .add_dof("Temperatur", [](VariableBuilder& vb) { vb.min(50.0).max(80.0); })
        .add_dof("Druck", [](VariableBuilder& vb) { vb.min(0.5).max(15.0); })
        .add_state_var("ProduktReinheit", [](VariableBuilder& vb) {
            vb.desc("Die Reinheit des Produkts in Prozent zwischen 0 und 1");
        })
        .add_state_var("ProduktMasse", [](VariableBuilder& vb) {
            vb.desc("Die Menge an produzierten Produkt in KG pro Stunde");
        });

    auto return_candidate = pb.build();
    return return_candidate.value();
}

int main(int argc, char** args)
{
    // #hack Example for Something hacky
    auto problem = generate_quadratic_function_problem();
    auto obj_function = objective_quadratic_2d();

    std::random_device dev;
    std::mt19937 random_twister(dev());

    auto optimization_method = factor_optimization_method(
        vae::om::EOptimizationMethod::OM_RANDOM_SEARCH,
        { { "max_iterations", "250" },
            { "max_step_size", "0.025" },
            { "objective_tolerance", "0.000001" } },
        random_twister);

    uint32_t counter = 1;
    auto output_lambda = 
        [&](vae::def::Problem& cur_p, double cur_val, vae::def::Problem& best_p, double best_val) {
        std::cout << counter << ". cur: ";
        std::cout << cur_p << " = " << cur_val << ", best: ";
        std::cout << best_p << " = " << best_val << std::endl;
        counter += 1;
        };

    optimization_method->set_substep_done_handler(output_lambda);
    auto [val, prob] = optimization_method->optimize(problem, obj_function);
    
    std::cout << std::endl
              << std::endl
              << "BEST: " << prob << " = " << val << std::endl;
    return 0;
}
