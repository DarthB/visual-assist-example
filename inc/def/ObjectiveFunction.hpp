#pragma once

#include <gsl/gsl>

#include <string>
#include <vector>

namespace vae { namespace def { class Variable; } }

// forward declaration added via Visual Assist
namespace vae { namespace def { class Problem; } }


namespace vae {
namespace def {

    class ObjectiveFunction {
    public:
        ObjectiveFunction()=default;
        virtual ~ObjectiveFunction() = default;
        ObjectiveFunction(const ObjectiveFunction& other) = delete;
        ObjectiveFunction& operator=(const ObjectiveFunction& other) = delete;
        ObjectiveFunction(ObjectiveFunction&& other) = default;
        ObjectiveFunction& operator=(ObjectiveFunction&& other) = default;

        /**
         *  Clones a objective function
         *  
         * 
         *  @see https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rh-copy
         */
        virtual gsl::owner < ObjectiveFunction* > clone() const = 0;

        virtual double evaluate(
            const vae::def::Problem& pr) const = 0;
    };


};
};