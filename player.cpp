#include "Player.h"
#include <stdexcept>

Player::Player(const std::string &texturePath) : speed(5.0f) {
    if (!texture.loadFromFile(texturePath)) {
        throw std::runtime_error("Error cargando la textura del jugador");
        sprite.setPosition(600.0f, 600.0f); // Aparecer en el centro inferior de la pantalla //falta arreglarse por que no aparece
    }
    sprite.setTexture(texture);
    sprite.setScale(0.12f, 0.12f); // Escalar al 25%
}

void Player::handleInput() {
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) movement.x += speed;

    sprite.move(movement);
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::FloatRect Player::getBounds() const {
    return sprite.getGlobalBounds();
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

void Player::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}
