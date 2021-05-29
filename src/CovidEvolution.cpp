#include <algorithm>
#include "../include/CovidEvolution.hpp"

CovidEvolution::CovidEvolution()
{
    _cities = {{"Paris", 2180000}, {"New Delhi", 16300000}, {"New York", 8600000}, {"Wuhan", 9000000}, {"Moscow", 5000000}};
    /* for (auto i = _cities.begin(); i != _cities.end(); ++i)
        std::cout << i->first << "  " << i->second << std::endl; */
    _map = {"NNNNN", "NNNNN", "NNXNN","NNNNN", "NNNNN"};
    /* for (auto i = _map.begin(); i != _map.end(); ++i)
        std::cout << *i << std::endl; */
    _height = 5;
    _width = 5;
    _alive = _height * _width - 1;
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

bool CovidEvolution::in_range(int y, int x, int line)
{
    (void)line;
    if (y < 0 || y > _height - 1)
        return false;
    if (x < 0 || x > _width - 1)
        return false;
    return true;
}

std::vector<char> CovidEvolution::getCircle(int y, int x)
{
    std::vector<char> result(8);
    int offset_y = 0;
    int offset_x = 0;

    for (int i = 0; i != 8; i++) {
        if (i == 0 || i == 1 || i == 2)
            offset_y = -1;
        else if (i == 3 || i == 4)
            offset_y = 0;
        else if (i == 5 || i == 6 || i == 7)
            offset_y = 1;

        if (i == 0 || i == 3 || i == 5)
            offset_x = -1;
        else if (i == 1 || i == 6)
            offset_x = 0;
        else if (i == 2 || i == 4 || i == 7)
            offset_x = 1;
        if (offset_x == 0 && offset_y == 0)
            continue;


        if (in_range(y + offset_y, x + offset_x, y)) {
            result[i] = _map[y + offset_y][x + offset_x];
        } else {
            result[i] = 'U';
        }
        //std::cout << result[i] << std::endl;
    }
    return result;
}

void CovidEvolution::compute(std::vector<char> around, int y, int x)
{
    int pos = 0;
    int rd;

    if (_map[y][x] != 'N')
        return;
    pos = std::count(around.begin(), around.end(), 'X');
    for (int i = 0; i != pos; i++) {
        rd = rand() % 100;
        if (rd <= 3) {
            _alive--;
            _map[y][x] = 'X';
            return;
        }
    }
    around = getCircle(y, x);
    pos = std::count(around.begin(), around.end(), 'N');
    for (int i = 0; i != pos; i++) {
        rd = rand() % 100;
        if (rd <= 2) {
            _alive--;
            _map[y][x] = 'V';
            return;
        }
    }
    
}

void CovidEvolution::simulate()
{
    std::vector<char> around;
    srand(time(NULL));

    while (1) {
        for (long unsigned int y = 0; y < _map.size(); y++) {
            for (long unsigned int x = 0; x < _map[y].length(); x++) {
                around = getCircle(y, x);
                compute(around, y, x);

                /* std::cout << around[0] << " " << around[1] << " " << around[2] << std::endl;
                std::cout << around[3] << " " << _map[y][x] << " " << around[4] << std::endl;
                std::cout << around[5] << " " << around[6] << " " << around[7] << std::endl;
                std::cout << std::endl; */
            }
        }
        if (_alive == 0)
            break;
    }
    for (auto i = _map.begin(); i != _map.end(); ++i)
        std::cout << *i << std::endl;
}
