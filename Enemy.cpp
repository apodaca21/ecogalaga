// Enemy.cpp
#include "Enemy.h"
#include <cstdlib>

sf::Texture Enemy::sharedTexture;

Enemy::Enemy(float x, float y) {
    sprite.setTexture(sharedTexture);
    sprite.setPosition(x, y);
    sprite.setScale(0.55f, 0.55f);  // Escalar al 40%

    // Generar velocidades iniciales aleatorias
    speedX = ((rand() % 2 == 0 ? 1.0f : -1.0f) * (50 + rand() % 50) / 80.0f);
    speedY = ((50 + rand() % 50) / 90.0f);
}

void Enemy::update() {
    sf::Vector2f position = sprite.getPosition();

    // Cuadro delimitador para los enemigos
    float leftBound = 50.0f;
    float rightBound = 1230.0f;  // 1280 - margen
    float topBound = 50.0f;
    float bottomBound = 326.0f;  // 376 - margen

    // Movimiento horizontal
    if (position.x <= leftBound || position.x >= rightBound - sprite.getGlobalBounds().width) {
        speedX = -speedX;  // Cambiar dirección
    }

    // Movimiento vertical
    if (position.y <= topBound || position.y >= bottomBound - sprite.getGlobalBounds().height) {
        speedY = -speedY;  // Cambiar dirección
    }

    sprite.move(speedX, speedY);
}

void Enemy::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

void Enemy::move(const sf::Vector2f &movement) {
    sprite.move(movement);
}

sf::FloatRect Enemy::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Enemy::getPosition() const {
    return sprite.getPosition();
}

void Enemy::setSpeed(float multiplier) {
    speedX *= multiplier;
    speedY *= multiplier;
}

void Enemy::respawn(float x, float y, float speedMultiplier) {
    sprite.setPosition(x, y);
    setSpeed(speedMultiplier);
}

void Enemy::setSharedTexture(const std::string &texturePath) {
    if (!sharedTexture.loadFromFile(texturePath)) {
        throw std::runtime_error("Error cargando la textura compartida de los enemigos");
    }
}

std::vector<Enemy> Enemy::createEnemies(int count) {
    std::vector<Enemy> enemies;
    for (int i = 0; i < count; ++i) {
        float x = rand() % 1180 + 50;  // Limitar al área horizontal del cuadro
        float y = rand() % 176 + 50;   // Limitar al área vertical del cuadro
        enemies.emplace_back(x, y);
    }
    return enemies;
}
