#include <algorithm>
#include <unistd.h>
#include <cstdlib>
#include "../include/CovidEvolution.hpp"

CovidEvolution::CovidEvolution()
{
    _cities = {{"Paris", 2180000}, {"New Delhi", 16300000}, {"New York", 8600000}};
    _map = {"NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNVNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNXNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNXNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNXNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN"};
    _height = 25;
    _width = 80;
    _alive = _height * _width - 4;
    _current = 0;
}

CovidEvolution::~CovidEvolution()
{
}

std::pair<std::string, int> CovidEvolution::select_city(SFML_Lib *graphLib)
{
    int input;

    while (input != 2) {
        graphLib->draw_menu();
        input = graphLib->getInput();
        graphLib->disp_text(680, 30, "PLEASE CHOOSE A CITY :", "YELLOW");
        graphLib->disp_text(750, 100, "(CITY/POPULATION)", "YELLOW");
        for (int i = 0; i < (int)_cities.size(); i++) {
            if (_current == i) {
                graphLib->disp_text(graphLib->get_coord(i, 1), graphLib->get_coord(i, 2), _cities[i].first, "GREEN");
                graphLib->disp_text(graphLib->get_coord(i, 1) + 1000, graphLib->get_coord(i, 2), std::to_string(_cities[i].second), "GREEN");
            } else {
                graphLib->disp_text(graphLib->get_coord(i, 1), graphLib->get_coord(i, 2), _cities[i].first, "WHITE");
                graphLib->disp_text(graphLib->get_coord(i, 1) + 1000, graphLib->get_coord(i, 2), std::to_string(_cities[i].second), "WHITE");
            }
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
    std::pair<std::string, int> city;

    city = select_city(graphLib);
    while (graphLib->getInput() != 2) {
        graphLib->draw_menu();
        graphLib->draw_map(_map);
        simulate();
        graphLib->update();
        graphLib->clear();
        usleep(100000);
    }
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
    }
    return result;
}

void CovidEvolution::compute(std::vector<char> around, int y, int x)
{
    int pos = 0;
    int rd;

    if (_map[y][x] == 'X') {
        rd = rand() % 35;
        if (rd > 33) {
            _map[y][x] = 'D';
        }
        return;
    }
    if (_map[y][x] != 'N')
        return;
    pos = std::count(around.begin(), around.end(), 'X');
    for (int i = 0; i != pos; i++) {
        rd = rand() % 100 + 1;
        if (rd <= 3) {
            _alive--;
            _map[y][x] = 'X';
            return;
        }
    }
    around = getCircle(y, x);
    pos = std::count(around.begin(), around.end(), 'V');
    for (int i = 0; i != pos; i++) {
        rd = rand() % 100 + 1;
        if (rd <= 4) {
            _alive--;
            _map[y][x] = 'V';
            return;
        }
    }
    pos = std::count(around.begin(), around.end(), 'N');
    if (pos == 0) {
        _alive--;
        _map[y][x] = 'V';
    }
}

void CovidEvolution::simulate()
{
    std::vector<char> around;
    int nb_death = 0;

    for (long unsigned int y = 0; y < _map.size(); y++) {
        for (long unsigned int x = 0; x < _map[y].length(); x++) {
            around = getCircle(y, x);
            compute(around, y, x);
        }
    }
    if (_alive <= 0) {
        for (long unsigned int y = 0; y < _map.size(); y++) {
            for (long unsigned int x = 0; x < _map[y].length(); x++) {
                if (_map[y][x] == 'D')
                    nb_death++;
            }
        }
        std::cout << "In this simulation, " << nb_death << " people died" << std::endl;
        exit(0);
    }
}
