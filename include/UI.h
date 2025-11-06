#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Constants.h"

class UI {
public:
    UI();
    void draw(sf::RenderWindow& window);
    void setLives(int value);
    void setLevel(int value);

private:
    sf::Font font;
    sf::Text livesText;
    sf::Text levelText;
};