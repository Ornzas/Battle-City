#include "Game.h"
#include "Resources.h"
#include "PlayerTank.h"
#include "EnemyTank.h"
#include <iostream>

Game::Game()
    : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Battle City Clone")
{
    window.setFramerateLimit(60);

    if (!Resources::load()) {
        std::cerr << "Failed to load resources\n";
    }
    // фон — прямоугольник или часть атласа
    backgroundSprite.setTexture(Resources::atlas);
    backgroundSprite.setTextureRect(sf::IntRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT));

    map.setAtlasTexture(Resources::atlas);
    if (!map.loadFromFile("assets/maps/level00.txt")) {
        std::cerr << "Не удалось загрузить карту!\n";
    }

    // создаём игрока
    player = std::make_unique<PlayerTank>();
    player->setAtlasTexture(Resources::atlas);
    player->setTextureRect(sf::IntRect(0, 672, 32, 32)); // поправь координаты

    // враги
    for (int i = 0; i < 3; ++i) {
        auto e = std::make_unique<EnemyTank>();
        e->setAtlasTexture(Resources::atlas);
        e->setTextureRect(sf::IntRect(32, 672, 32, 32)); // поправь
        enemies.push_back(std::move(e));
    }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event ev;
    while (window.pollEvent(ev)) {
        if (ev.type == sf::Event::Closed) window.close();
    }
}

void Game::update(float dt) {
    // Обновляем игрока с передачей карты для проверки коллизий
    // PlayerTank::handleInput принимает map — реализуй как раньше
    player->handleInput(dt, map);

    for (auto& e : enemies) e->update(dt);
}

void Game::render() {
    window.clear();
    window.draw(backgroundSprite);
    map.draw(window, mapOffset);

    // рисуем танков со смещением
    sf::Sprite tmp = player->getSprite();
    tmp.setPosition(tmp.getPosition() + mapOffset);
    window.draw(tmp);

    for (auto& e : enemies) {
        sf::Sprite s = e->getSprite();
        s.setPosition(s.getPosition() + mapOffset);
        window.draw(s);
    }

    window.display();
}
