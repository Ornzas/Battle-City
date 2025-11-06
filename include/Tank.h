#pragma once
#include <SFML/Graphics.hpp>
#include "Constants.h"

// Предварительное объявление, чтобы использовать ссылку на Map
class Map;

class Tank {
public:
    Tank();
    void handleInput(float deltaTime, const Map& map);
    sf::Sprite& getSprite();

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float speed = 100.0f;          // пикселей в секунду
    float animationTimer = 0.0f;   // накопленное время
    int currentFrame = 0;          // текущий кадр анимации
    int direction = 0;             // 0-вверх,1-вправо,2-вниз,3-влево
    int tankSize = 28;
    void updateAnimation(float deltaTime, bool moving);
};