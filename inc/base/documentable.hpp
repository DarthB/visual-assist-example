#pragma once

#include <string>
#include <vector>

namespace vae {
namespace base {

    /*!
     * \class Documentable
     *
     * \brief A toy example for multiple inhertiance
     *
     * \author Tim Janus
     * \date September 2022
     */
    class Documentable {
    public:
        virtual ~Documentable() = default;

        virtual std::string loc_get_name() const = 0;

        virtual std::string loc_get_description() const = 0;

        virtual std::vector<std::string> get_supported_parameters() const = 0;

        virtual std::string loc_get_parameter_description(
            const std::string& parameter_name) const = 0;

        virtual std::string loc_get_parameter_range(
            const std::string& parameter_name) const = 0;
    };

};
};