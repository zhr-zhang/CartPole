#include "Env.h"
Observation Env::reset() const
{
    //Observation a;
    //a = make_tuple(0,0,0,0);
    //get<0>(a) = randomDouble(-0.05, 0.05);
    get<0>(observation) = randomDouble(-0.05, 0.05);
    get<1>(observation) = randomDouble(-0.05, 0.05);
    get<2>(observation) = randomDouble(-0.05, 0.05);
    get<3>(observation) = randomDouble(-0.05, 0.05);
    return observation;
}

tuple<Observation, double, bool, bool> Env::step(const bool& action) const
{
    double x, x_dot, theta, theta_dot;
    tie(x, x_dot, theta, theta_dot) = observation;
    double force = action ? force_mag : -force_mag;
    double costheta = cos(theta);
    double sintheta = sin(theta);
    // https://coneural.org/florian/papers/05_cart_pole.pdf
    double temp = (
        force + polemass_length * theta_dot * theta_dot * sintheta
        ) / total_mass;
    double thetaacc = (gravity * sintheta - costheta * temp) / (
        length * (4.0 / 3.0 - masspole * costheta * costheta / total_mass)
        );
    double xacc = temp - polemass_length * thetaacc * costheta / total_mass;
    if (kinematics_integrator == "euler")
    {
        x = x + tau * x_dot;
        x_dot = x_dot + tau * xacc;
        theta = theta + tau * theta_dot;
        theta_dot = theta_dot + tau * thetaacc;
    }
    else {
        x_dot = x_dot + tau * xacc;
        x = x + tau * x_dot;
        theta_dot = theta_dot + tau * thetaacc;
        theta = theta + tau * theta_dot;
    }
    observation = make_tuple(x, x_dot, theta, theta_dot);
    terminated = (x < -x_threshold ||
        x > x_threshold ||
        theta < -theta_threshold_radians ||
        theta > theta_threshold_radians) ?
        true : false;
    double reward;
    if (!terminated) {
        reward = 1.0;
    }
    else {
        reward = 0.0;
    }
    return make_tuple(observation, reward, terminated, false);
}
