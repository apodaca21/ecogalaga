#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Game.h"

int main() {
    const int windowWidth = 1283;
    const int windowHeight = 752;

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "ECOGALAGA");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:\\Users\\migue\\CLionProjects\\SFML\\fondojuegoespacio.png")) {
        throw std::runtime_error("Error cargando la textura del fondo del menú");
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
            static_cast<float>(windowWidth) / backgroundTexture.getSize().x,
            static_cast<float>(windowHeight) / backgroundTexture.getSize().y
    );

    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("C:\\Users\\migue\\CLionProjects\\SFML\\sonidofondo.ogg")) {
        throw std::runtime_error("Error cargando la música de fondo");
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.setVolume(30);
    backgroundMusic.play();

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        throw std::runtime_error("Error cargando la fuente");
    }

    sf::Text title("ECOGALAGA", font, 90);
    title.setPosition(420, 50);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(7);

    sf::Text menu[2];
    std::string options[2] = {"JUGAR", "SALIR"};
    int selectedIndex = 0;

    for (int i = 0; i < 2; ++i) {
        menu[i].setFont(font);
        menu[i].setString(options[i]);
        menu[i].setCharacterSize(50);
        menu[i].setFillColor(i == 0 ? sf::Color::Yellow : sf::Color::White);
        menu[i].setOutlineColor(sf::Color::Black);
        menu[i].setOutlineThickness(5);
        menu[i].setPosition(540, 300 + i * 80);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                    menu[selectedIndex].setFillColor(sf::Color::White);
                    selectedIndex = (selectedIndex + 1) % 2;
                    menu[selectedIndex].setFillColor(sf::Color::Yellow);
                }

                if (event.key.code == sf::Keyboard::Enter) {
                    if (selectedIndex == 0) {
                        backgroundMusic.stop();
                        runGame(window);
                        backgroundMusic.play();
                    } else if (selectedIndex == 1) {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        window.draw(backgroundSprite);
        window.draw(title);
        for (int i = 0; i < 2; ++i) {
            window.draw(menu[i]);
        }
        window.display();
    }

    return 0;
}

