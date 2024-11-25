#ifndef BULLET_H
#define BULLET_H

#include <SFML/Graphics.hpp>
#include <string>

class Bullet {
public:
    Bullet(float x, float y, bool isEnemyBullet); // Constructor de la bala
    void update();                               // Actualizar posición de la bala
    void draw(sf::RenderWindow &window);         // Dibujar la bala en la ventana
    sf::FloatRect getBounds() const;            // Obtener los límites de la bala
    sf::Vector2f getPosition() const;           // Obtener la posición de la bala
    bool isOutOfBounds() const;                 // Comprobar si la bala está fuera de pantalla
    bool isEnemyBullet() const;                 // Saber si es una bala enemiga
    void setColor(const sf::Color &color);      // Cambiar color de la bala (solo para el jugador)

    static void setEnemyBulletTexture(const std::string &texturePath); // Configurar textura de balas enemigas

private:
    sf::Sprite sprite;            // Sprite para balas enemigas
    sf::RectangleShape shape;     // Forma para balas del jugador
    static sf::Texture enemyBulletTexture; // Textura compartida para las balas enemigas
    bool isEnemy;                 // Indica si la bala es enemiga o del jugador
};

#endif // BULLET_H
