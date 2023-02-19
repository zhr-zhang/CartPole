#pragma once
#include <Math.h>
#include "Global.h"
class Env
{
private:
    mutable Observation observation = make_tuple(0, 0, 0, 0);
    const double gravity = 9.8;
    const double masscart = 1.0;
    const double masspole = 0.1;
    const double total_mass = masspole + masscart;
    const double length = 0.5;  // actually half the pole's length
    const double polemass_length = masspole * length;
    const double force_mag = 10.0;
    const double tau = 0.02;  // seconds between state updates
    const char* kinematics_integrator = "euler";

    // Angle at which to fail the episode
    const double theta_threshold_radians = 12 * 2 * PI / 360;
    const double x_threshold = 2.4;

    mutable bool terminated = false;
public:
    Observation reset()const;
    tuple<Observation, double, bool, bool> step(const bool& action)const;
};

