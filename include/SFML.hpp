#ifndef SFML_H
#define SFML_H

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

class SFML_Lib {
public:
    SFML_Lib();
    ~SFML_Lib() { _window.close(); };

    void create_window();
    void draw_map(std::vector<std::string> map);
    void draw_menu();
    void disp_text(int, int, std::string, std::string color);
    int getInput();
    std::string type_text();
    void destroy_window();
    void clear();
    void update();
    int get_coord(int, int);
protected:
private:
    std::vector<std::pair<int, int>> _coord;
    bool _state;
    sf::RenderWindow _window;
    sf::Text _text;
    sf::Font _font;
    sf::Texture _background_t;
    sf::Sprite _background_s;
    sf::Event _event;
    sf::RectangleShape _pop;
};

#endif /* !SFML_H */