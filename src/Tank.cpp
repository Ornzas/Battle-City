#include "Tank.h"
#include <iostream>
#include "Map.h"

Tank::Tank() {
    if (!texture.loadFromFile("assets/images/sprites.png")) {
        std::cerr << "Ошибка: не удалось загрузить спрайт sprites.png\n";
    }
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(3, 3, tankSize, tankSize));
    sprite.setPosition(80, 80);
}

void Tank::setAtlas(sf::Texture& texture) {
    sprite.setTexture(texture);
}

void Tank::handleInput(float deltaTime, const Map& map) {
    bool moving = false;
    float distance = speed * deltaTime; // движение в пикселях за кадр
    sf::Vector2f moveDir(0, 0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        moveDir.y -= distance;;
        direction = 0; moving = true;
        //sprite.setTextureRect(sf::IntRect(3, 3, 40, 40)); // вверх
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        moveDir.y += distance;
        direction = 2; moving = true;
        //sprite.setTextureRect(sf::IntRect(184, 3, 40, 40)); // вниз
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        moveDir.x -= distance;
        direction = 1; moving = true;
        //sprite.setTextureRect(sf::IntRect(96, 3, 40, 40)); // влево
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        moveDir.x += distance;
        direction = 3; moving = true;
        //sprite.setTextureRect(sf::IntRect(276, 3, 40, 40)); // вправо
    }

    // Проверяем коллизию перед движением
    sf::FloatRect nextPos = sprite.getGlobalBounds();
    nextPos.left += moveDir.x;
    nextPos.top += moveDir.y;

    if (!map.isBlocked(nextPos)) {
        sprite.move(moveDir);
    }
    
    updateAnimation(deltaTime, moving);
}

void Tank::updateAnimation(float deltaTime, bool moving) {
    if (!moving) {
        currentFrame = 0; // первый кадр — "покой"
        sprite.setTextureRect(sf::IntRect(direction * 64, 3, tankSize, tankSize));
        return;
    }

    animationTimer += deltaTime;

    if (animationTimer >= 0.15f) { // скорость анимации (0.15с на кадр)
        animationTimer = 0.0f;
        currentFrame = (currentFrame + 1) % 2; // 2 кадра
        //currentFrame = 0; // 2 кадра
    }

    sprite.setTextureRect(sf::IntRect(currentFrame * 32 + direction * 64 , 3, tankSize, tankSize));
}

sf::Sprite& Tank::getSprite() {
    return sprite;
}
