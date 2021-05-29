#include <iostream>
#include "../include/Exceptions.hpp"
#include "../include/CovidEvolution.hpp"

int main(void)
{
    try {
        CovidEvolution planner;
        //planner.run();
        planner.simulate();
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return(84);
    }
    return 0;
}
