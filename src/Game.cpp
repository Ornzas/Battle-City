#include "Game.h"
#include "Constants.h"
#include <iostream> // <-- обязательно для std::cerr

Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Battle City Clone") {
        window.setFramerateLimit(60);

        if (!map.loadFromFile("assets/maps/level00.txt")) {
            std::cerr << "Не удалось загрузить карту!\n";
        }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); // время между кадрами
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(float deltaTime) {
    player.handleInput(deltaTime, map);
}

void Game::render() {
    window.clear();
    map.draw(window);
    window.draw(player.getSprite());
    window.display();
}
