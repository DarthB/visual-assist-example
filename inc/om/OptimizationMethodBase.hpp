#pragma once

#include <functional>
#include <random>
#include <stdint.h>

namespace vae {
namespace def {
    class ObjectiveFunction;
}
}
namespace vae {
namespace def {
    class Problem;
}
}

namespace vae {
namespace om {

    // #todo: 3.1 Show documentation snippets here
    // #todo: 0.1 Rename to OptimizationMethodParameters
    struct OptimizationMethodParameters {
        OptimizationMethodParameters();

        uint32_t max_iterations;

        double objective_tolerance;

        double max_step_size;
    };

    /**
     *	@brief	A base class for optimization methods. It prvoides a optimize method that must be implemented by sub
     *          classes and works on a Problem and a ObjectiveFunction
     *	@author Tim Janus
     */
    class OptimizationMethodBase {
    public:
        /// The signature for a inform function that transports one TIndiviual instance to the
        /// listener
        typedef std::function<void(vae::def::Problem&, double, vae::def::Problem&, double)> substep_done_ftor;

        /**
         *	@brief	Default-Ctor, post-condition: default substep done method is set
         *
         */
        OptimizationMethodBase(std::mt19937& rand);

        /** @brief Default-Dtor */
        virtual ~OptimizationMethodBase() = default;

        /**
         *  Initializes the optimization algorithm based on a parameter map.
         *  @param[in]      parameters A map containing parameters to adapt the behavior of this
         *                  optimization algorithm. Hereby every algorithm shall at least support
         *                  max iterations and the objective tolerance.
         */
        virtual void initialize(std::unordered_map<std::string, std::string> parameters);

        /**
         *	@brief	Optimize the given individual
         *	@param[in]	    start_point	The start point in the search stpace
         *					optimization method and also acts as output of the optimization.
         *  @param[in]      The objective function that evaluates the optimization problem
         */
        virtual std::pair<double, vae::def::Problem> optimize(
            vae::def::Problem start_point,
            const vae::def::ObjectiveFunction& objective)
            = 0;

        void set_substep_done_handler(substep_done_ftor handler)
        {
            m_substep_done_handler = handler;
        }

    protected:
        std::mt19937& m_rand;

        /// A function object that is invoked every time when the local-optimization has finished
        /// a sub step.
        substep_done_ftor m_substep_done_handler;

        OptimizationMethodParameters m_params;
    };

}; // ns vae::om
}; // ns vae
