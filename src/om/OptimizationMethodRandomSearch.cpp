#include "om/OptimizationMethodRandomSearch.hpp"

#include "def/ObjectiveFunction.hpp"
#include "def/Variable.hpp"
#include "def/problem.hpp"

vae::om::OptimizationMethodRandomSearch::OptimizationMethodRandomSearch(
    std::mt19937& rand)
    : super(rand)
{
}

std::pair<double, vae::def::Problem> 
    vae::om::OptimizationMethodRandomSearch::optimize(
    vae::def::Problem best_known,
    const vae::def::ObjectiveFunction& objective)
{
    // evaluate the start point
    double best_known_val = objective.evaluate(best_known);

    uint32_t finished_iterations = 0;
    std::uniform_real_distribution distrib(
        -m_params.max_step_size,
        m_params.max_step_size);

    while (finished_iterations < m_params.max_iterations) {
        auto next_point = best_known;
        next_point.foreach_dof([&](auto& dof) {
            auto range = distrib(m_rand);
            dof.delta(range, vae::def::EBoundsStrategy::VDT_CLAMP);
        });

        double next_val = objective.evaluate(next_point);

        if (next_val < best_known_val) {
            best_known = next_point;
            best_known_val = next_val;
        }

        finished_iterations += 1;
        m_substep_done_handler(next_point, next_val, best_known, best_known_val);

        if (best_known_val < m_params.objective_tolerance) {
            break;
        }
    }

    return std::make_pair(best_known_val, best_known);
}
