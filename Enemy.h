// Enemy.h
#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Enemy {
public:
    Enemy(float x, float y);

    void update();
    void draw(sf::RenderWindow &window);
    void move(const sf::Vector2f &movement);  // Método para mover al enemigo
    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;

    void setSpeed(float multiplier);  // Método para ajustar la velocidad
    void respawn(float x, float y, float speedMultiplier);  // Método para reaparecer el enemigo

    static void setSharedTexture(const std::string &texturePath);
    static std::vector<Enemy> createEnemies(int count);

private:
    sf::Sprite sprite;
    static sf::Texture sharedTexture;  // Textura compartida entre todos los enemigos
    float speedX;
    float speedY;
};

#endif // ENEMY_H
