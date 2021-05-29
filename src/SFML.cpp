#include "../include/SFML.hpp"
#include <unistd.h>
#include <iostream>

SFML_Lib::SFML_Lib()
{
    _coord = {{350, 200}, {350, 350}, {350, 500}, {350, 650}, {350, 800}};
    if (!_background_t.loadFromFile("./assets/background.jpg"))
        exit(84);
    if (!_font.loadFromFile("./assets/aokay.ttf"))
        exit(84);
    _background_s.setTexture(_background_t);
    _state = false;
    _window.setFramerateLimit(60);
    _text.setCharacterSize(50);
    _text.setFont(_font);
    _pop.setSize(sf::Vector2f(64, 64));
}

void SFML_Lib::create_window()
{
    _window.create(sf::VideoMode(1920, 1080), "CovidEvolution",
                   sf::Style::Resize);
}

void SFML_Lib::destroy_window()
{
    _window.close();
}

void SFML_Lib::update()
{
    _window.display();
}

void SFML_Lib::clear()
{
    _window.clear(sf::Color::Black);
}

void SFML_Lib::draw_map(std::vector<std::string> map)
{    
    for (unsigned int i = 0; i != map.size(); i++) {
        for (unsigned int j = 0; j != map[i].length(); j++) {
            if (map[i][j] == 'N') {
                _pop.setPosition(j * 100 + 775, i * 100 + 200);
                _pop.setFillColor(sf::Color::Green);
                _window.draw(_pop);
            } else if (map[i][j] == 'X') {
                _pop.setPosition(j * 100 + 775, i * 100 + 200);
                _pop.setFillColor(sf::Color::Red);
                _window.draw(_pop);
            } else if (map[i][j] == 'D') {
                _pop.setPosition(j * 100 + 775, i * 100 + 200);
                _pop.setFillColor(sf::Color::Black);
                _window.draw(_pop);
            } else if (map[i][j] == 'V') {
                _pop.setPosition(j * 100 + 775, i * 100 + 200);
                _pop.setFillColor(sf::Color::Cyan);
                _window.draw(_pop);
            }
        }
    }
}

void SFML_Lib::draw_menu()
{
    _window.draw(_background_s);
}

int SFML_Lib::getInput()
{
    if (!_window.pollEvent(_event))
        return (0);
    if (_event.type == sf::Event::Closed)
        return (1);
    if (_event.type == sf::Event::KeyPressed)
    {
        switch (_event.key.code) {
        case sf::Keyboard::Enter:
            return (2);
        case sf::Keyboard::Left:
            return (3);
        case sf::Keyboard::Right:
            return (4);
        case sf::Keyboard::Up:
            return (5);
        case sf::Keyboard::Down:
            return (6);
        case sf::Keyboard::Escape:
            return (2);
        case sf::Keyboard::Space:
            return (7);
        case sf::Keyboard::O:
            return (8);
        case sf::Keyboard::P:
            return (9);
        default:
            return (0);
        }
    }
    return (0);
}

std::string SFML_Lib::type_text()
{
    /*
    while (_state == false)
    {
        clear();
        while (_window.pollEvent(_event))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
               _state = true;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace));
                //_player_name_entered = _player_name_entered.substr(0, _player_name_entered.length() - 1);
            else if (_event.type == sf::Event::TextEntered);
            {
                //_player_name_entered += _event.text.unicode;
            }
        }
        draw_menu();
        disp_text(750, 300, "ENTER YOU NAME :", "Red");
        //disp_text(850, 400, _player_name_entered, "Magenta");
        update();
    }
    if (_player_name_entered.empty() || _player_name_entered.size() == 1)
    {
        _player_name_entered = "guest";
    }
    return _player_name_entered;
    */
    return ("guest");
}

void SFML_Lib::disp_text(int x, int y, std::string content, std::string color)
{
    if (color == "RED")
        _text.setFillColor(sf::Color::Red);
    else if (color == "WHITE")
        _text.setFillColor(sf::Color::White);
    else if (color == "YELLOW")
        _text.setFillColor(sf::Color::Yellow);
    else if (color == "GREEN")
        _text.setFillColor(sf::Color::Green);
    else if (color == "CYAN")
        _text.setFillColor(sf::Color::Cyan);
    else
        _text.setFillColor(sf::Color::Black);
    _text.setPosition(x, y);
    _text.setString(content);
    _window.draw(_text);
}

int SFML_Lib::get_coord(int number, int fi_sec)
{
    if (fi_sec == 1)
        return (_coord[number].first);
    else
        return (_coord[number].second);
}

extern "C"
{
    SFML_Lib *init_glib()
    {
        return (new SFML_Lib());
    }
}
