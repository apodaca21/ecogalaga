#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
    explicit Player(const std::string &texturePath);

    void handleInput();
    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y);

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed;
};

#endif // PLAYER_H
