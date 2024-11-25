#include "Bullet.h"

sf::Texture Bullet::enemyBulletTexture;

Bullet::Bullet(float x, float y, bool isEnemyBullet) : isEnemy(isEnemyBullet) {
    if (isEnemy) {
        // Configurar sprite para balas enemigas
        sprite.setTexture(enemyBulletTexture);
        sprite.setPosition(x, y);
        sprite.setScale(0.29f, 0.29f); // Escalar la textura de la botella
    } else {
        // Configurar forma para balas del jugador
        shape.setSize(sf::Vector2f(15.0f, 23.0f)); // Tamaño del rectángulo
        shape.setFillColor(sf::Color::Green); // Color inicial (rojo)
        shape.setPosition(x, y);
    }
}

void Bullet::update() {
    // Velocidad de la bala: positiva para el jugador, negativa para enemigos
    float speed = isEnemy ? 3.0f : -5.0f;

    if (isEnemy) {
        sprite.move(0, speed);
    } else {
        shape.move(0, speed);
    }
}

void Bullet::draw(sf::RenderWindow &window) {
    if (isEnemy) {
        window.draw(sprite);
    } else {
        window.draw(shape);
    }
}

sf::FloatRect Bullet::getBounds() const {
    return isEnemy ? sprite.getGlobalBounds() : shape.getGlobalBounds();
}

sf::Vector2f Bullet::getPosition() const {
    return isEnemy ? sprite.getPosition() : shape.getPosition();
}

bool Bullet::isOutOfBounds() const {
    float y = getPosition().y;
    return y < 0 || y > 752; // Fuera de la pantalla
}

bool Bullet::isEnemyBullet() const {
    return isEnemy;
}

void Bullet::setColor(const sf::Color &color) {
    if (!isEnemy) {
        shape.setFillColor(color);
    }
}

void Bullet::setEnemyBulletTexture(const std::string &texturePath) {
    if (!enemyBulletTexture.loadFromFile(texturePath)) {
        throw std::runtime_error("Error cargando la textura de la bala enemiga");
    }
}
