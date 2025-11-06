#include "UI.h"

UI::UI() {
    font.loadFromFile("assets/fonts/arial.ttf");

    livesText.setFont(font);
    livesText.setCharacterSize(18);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition(13 * 32 + 20, 50); // справа от карты

    levelText.setFont(font);
    levelText.setCharacterSize(18);
    levelText.setFillColor(sf::Color::Yellow);
    levelText.setPosition(13 * 32 + 20, 100);
}

void UI::setLives(int value) {
    livesText.setString("Lives: " + std::to_string(value));
}

void UI::setLevel(int value) {
    levelText.setString("Level: " + std::to_string(value));
}

void UI::draw(sf::RenderWindow& window) {
    window.draw(livesText);
    window.draw(levelText);
}