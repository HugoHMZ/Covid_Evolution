#include "../include/CovidEvolution.hpp"

CovidEvolution::CovidEvolution()
{
    _cities = {{"Paris", 2180000}, {"New Delhi", 16300000}, {"New York", 8600000}, {"Wuhan", 9000000}, {"Moscow", 5000000}};
    /* for (auto i = _cities.begin(); i != _cities.end(); ++i)
        std::cout << i->first << "  " << i->second << std::endl; */
    _current = 0;
}

CovidEvolution::~CovidEvolution()
{
}

void CovidEvolution::run()
{
    std::string input;

    std::cout << _cities[_current].first << "  " << _cities[_current].second << " residents selected" <<std::endl;
    while (std::getline(std::cin, input)) {
        if (input.empty() || input.length() != 1 || (input != "+" && input != "-"))
            continue;
        if (input == "+" && (long unsigned int) (_current + 1) <= _cities.size() - 1)
            _current++;
        else if (input == "-" && _current - 1 >= 0){
            _current--;
        }
        else {
            if (input == "+" && (long unsigned int) (_current + 1) > _cities.size() - 1)
                _current = 0;
            else if (input == "-" && _current - 1 == -1)
                _current = _cities.size() - 1;
        }
        std::cout << _cities[_current].first << "  " << _cities[_current].second << " residents selected" <<std::endl;
    }
}
