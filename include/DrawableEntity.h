#pragma once
#include <SFML/Graphics.hpp>

class DrawableEntity {
protected:
    sf::Sprite sprite;
public:
    virtual ~DrawableEntity() = default;
    virtual void draw(sf::RenderWindow& window) { window.draw(sprite); }
    sf::Sprite& getSprite() { return sprite; }
    const sf::Sprite& getSprite() const { return sprite; }
};
