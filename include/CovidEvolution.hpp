/*
** EPITECH PROJECT, 2021
** Hackathon
** File description:
** CovidEvolution
*/

#ifndef COVIDEVOLUTION_HPP_
#define COVIDEVOLUTION_HPP_

#include <vector>
#include <iostream>
#include <string>
#include "SFML.hpp"

class CovidEvolution {
    public:
        CovidEvolution();
        ~CovidEvolution();
        void run(SFML_Lib *);
        std::pair<std::string, int> select_country(SFML_Lib *);
        void simulate();
        void compute(std::vector<char>, int, int);
        std::vector<char> getCircle(int y, int x);
        bool in_range(int, int, int);

    protected:
    private:
        std::vector<std::pair<std::string, int>> _cities;
        int _current;
        std::vector<std::string> _map;

        int _height;
        int _width;
        int _alive;
};

#endif /* !COVIDEVOLUTION_HPP_ */
