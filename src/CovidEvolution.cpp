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

std::pair<std::string, int> CovidEvolution::select_country(SFML_Lib *graphLib)
{
    int input;

    while (input != 2) {
        graphLib->draw_menu();
        input = graphLib->getInput();
        for (int i = 0; i < (int)_cities.size(); i++) {
            if (_current == i)
                graphLib->disp_text(graphLib->get_coord(i, 1), graphLib->get_coord(i, 2), _cities[i].first, "RED");
            else
                graphLib->disp_text(graphLib->get_coord(i, 1), graphLib->get_coord(i, 2), _cities[i].first, "WHITE");
        }
        if (input == 5 && _current >= 1)
            _current--;
        else if (input == 6 && _current < 4)
            _current++;
        else if (input == 5 && _current == 4)
            _current = 0;
        else if (input == 6 && _current - 1 == -1)
            _current = _cities.size() - 1;
        else
            _current = _current;
        graphLib->update();
        graphLib->clear();
    }
    return (_cities[_current]);
}

void CovidEvolution::run(SFML_Lib *graphLib)
{
    std::pair<std::string, int> country;

    country = select_country(graphLib);
    std::cout << country.first << std::endl;
}
