#include <array>                    // for std::array
#include <chrono>                   // for std::chrono
#include <iostream>                 // for std::cout
#include <boost/format.hpp>         // for boost::format
#include <boost/numeric/odeint.hpp> // for boost::numeric::odeint

using state_type = std::array<double, 2>;

void rhs(state_type const & y, state_type & dydx, double const x);

int main()
{
    using namespace std::chrono;
    using namespace boost::numeric::odeint;
    using stepper_type = boost::numeric::odeint::bulirsch_stoer<state_type>;
    
    auto const start = system_clock::now();

    auto const x1 = 0.00001;
    auto const xf = 11.0;
    auto const dx = 0.001;
    
    state_type y1 = { 0.99998416139571, -1.58175227379914 };

    integrate_const(
        stepper_type(1.0E-15, 1.0E-15),
        [](state_type const & y, state_type & dydx, double const x)
        {
	        dydx[0] = y[1];
	        dydx[1] = y[0] * std::sqrt(y[0] / x);
        },
        y1,
        x1,
        xf,
        dx);
    auto const end = system_clock::now();

    std::cout << boost::format("y[1] = %.14f, y[2] = %.14f\n") % y1[0] % y1[1];
    std::cout << boost::format("計算時間 = %.14f（秒）\n") % duration_cast< duration<double> >(end - start).count();
}
