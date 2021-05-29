/*
** EPITECH PROJECT, 2021
** B-OOP-400-LIL-4-1-tekspice-hugo.humez
** File description:
** Exceptions
*/

#ifndef EXCEPTIONS_HPP_
#define EXCEPTIONS_HPP_

#include <string>
#include <exception>

class customException : public std::exception {
    public:
        customException(std::string const &s) noexcept
            : _message(s) {}
        const char *what() const noexcept override {
            return _message.c_str();
        }
    private:
        std::string _message;
};

#endif /* !EXCEPTIONS_HPP_ */
