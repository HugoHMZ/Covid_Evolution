#include <iostream>
#include "../include/Exceptions.hpp"
#include "../include/CovidEvolution.hpp"
#include "../include/SFML.hpp"

int main(void)
{
    try {
        CovidEvolution planner;
        SFML_Lib *graphLib = new SFML_Lib;
        graphLib->create_window();
        //planner.run(graphLib);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return(84);
    }
    return 0;
}
