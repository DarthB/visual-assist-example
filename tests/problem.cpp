#include <gtest/gtest.h>

#include "def/problem.hpp"

using namespace vae::def;

TEST(ProblemBuilderTest, MissingDOFs)
{
    ProblemBuilder pb;
    auto res = pb.build();
    
    // #review is first expect needed when we test on enum?
    EXPECT_EQ(res.has_error(), true);
    EXPECT_EQ(res.error(), EProblemBuildError::MISSING_DOF);
}

TEST(ProblemBuilderTest, AmbigiousVariables)
{
    ProblemBuilder pb;
    pb.add_dof("Temperature").add_state_var("Temperature");
    auto res = pb.build();

    EXPECT_EQ(res.has_error(), true);
    EXPECT_EQ(res.error(), EProblemBuildError::AMBIGIOUS_VARIABLE);
}