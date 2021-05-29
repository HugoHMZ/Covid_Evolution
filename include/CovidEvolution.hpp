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

class CovidEvolution {
    public:
        CovidEvolution();
        ~CovidEvolution();
        void run();

    protected:
    private:
        std::vector<std::pair<std::string, int>> _cities;
        int _current;
};

#endif /* !COVIDEVOLUTION_HPP_ */
