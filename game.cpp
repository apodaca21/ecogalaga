// game.cpp
#include "Game.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>  // Para inicializar srand() con el tiempo actual

// Declaración global de la música
sf::Music backgroundMusic;
sf::SoundBuffer gameOverBuffer;
sf::Sound gameOverSound;

void initializeMusic() {
    static bool isInitialized = false;
    if (!isInitialized) {
        if (!backgroundMusic.openFromFile("C:\\Users\\migue\\CLionProjects\\SFML\\sonidofondo.ogg")) {
            throw std::runtime_error("Error cargando la música de fondo");
        }
        backgroundMusic.setLoop(true);
        backgroundMusic.setVolume(100);
        backgroundMusic.play();

        if (!gameOverBuffer.loadFromFile("C:\\Users\\migue\\CLionProjects\\SFML\\sonidogameover.ogg")) {
            throw std::runtime_error("Error cargando el sonido de game over");
        }
        gameOverSound.setBuffer(gameOverBuffer);

        isInitialized = true;
    }
}

std::string getRandomGameOverMessage() {
    static std::vector<std::string> messages = {
            "Si no reciclas, reusa.\nSi no reusas, reduce.",
            "Cuida el medio ambiente.\nNo hay un planeta B.",
            "Se parte de la solucion,\nNo de la contaminacion."
    };
    static sf::Clock messageClock;
    static int selectedMessageIndex = rand() % messages.size();

    if (messageClock.getElapsedTime().asSeconds() > 4) {
        selectedMessageIndex = rand() % messages.size();
        messageClock.restart();
    }

    return messages[selectedMessageIndex];
}

void runGame(sf::RenderWindow &window) {
    initializeMusic();

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:\\Users\\migue\\CLionProjects\\SFML\\fondoparajuego.png")) {
        throw std::runtime_error("Error cargando la textura del fondo del juego");
    }
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale(
            static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
            static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    sf::Texture gameOverTexture;
    if (!gameOverTexture.loadFromFile("C:\\Users\\migue\\CLionProjects\\SFML\\GAMEOVER.png")) {
        throw std::runtime_error("Error cargando la textura de game over");
    }
    sf::Sprite gameOverSprite(gameOverTexture);
    gameOverSprite.setScale(
            static_cast<float>(window.getSize().x) / gameOverTexture.getSize().x,
            static_cast<float>(window.getSize().y) / gameOverTexture.getSize().y
    );
    gameOverSprite.setPosition(0, 0);

    Player player("C:\\Users\\migue\\CLionProjects\\SFML\\personajeverde.png");
    player.setPosition(window.getSize().x / 2, window.getSize().y - 100);  // Colocar al jugador en el centro inferior
    Enemy::setSharedTexture("C:\\Users\\migue\\CLionProjects\\SFML\\enemigorojo.png");
    std::vector<Enemy> enemies = Enemy::createEnemies(7);
    Bullet::setEnemyBulletTexture("C:\\Users\\migue\\CLionProjects\\SFML\\botellamala.png");
    std::vector<Bullet> bullets;

    sf::SoundBuffer shootBuffer;
    if (!shootBuffer.loadFromFile("C:\\Users\\migue\\CLionProjects\\SFML\\sonidodisparo.ogg")) {
        throw std::runtime_error("Error cargando el sonido de disparo");
    }
    sf::Sound shootSound(shootBuffer);

    sf::Font font;
    if (!font.loadFromFile("Roboto-Regular.ttf")) {
        throw std::runtime_error("Error cargando la fuente");
    }
    sf::Text killsText("Kills: 0", font, 20);
    sf::Text timeText("Tiempo: 0", font, 20);
    killsText.setPosition(10, 10);
    timeText.setPosition(10, 40);

    sf::Clock gameClock; // Reloj para el tiempo de juego
    int kills = 0;
    float enemySpeedMultiplier = 0.3f;  // Reducir la velocidad de los enemigos
    bool isGameOver = false;
    sf::Time finalTime;
    sf::Clock timerClock; // Reloj para controlar el tiempo de partida

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return;
            }
            if (isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                // Regresar al menú principal
                return;
            }
            if (!isGameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                // Disparar cada vez que se presione espacio sin esperar
                bullets.emplace_back(player.getPosition().x + 20, player.getPosition().y, false);
                shootSound.play();
            }
        }

        if (!isGameOver) {
            player.handleInput();
            for (auto &enemy : enemies) {
                sf::Vector2f movement((rand() % 3 - 1) * 0.3f * enemySpeedMultiplier, (rand() % 3 - 1) * 0.3f * enemySpeedMultiplier);
                enemy.update();
                if (rand() % 100 < 50) {  // Probabilidad de cambiar de dirección
                    movement.x = (rand() % 3 - 1) * 0.2f * enemySpeedMultiplier;
                    movement.y = (rand() % 3 - 1) * 0.3f * enemySpeedMultiplier;
                }
                enemy.move(movement);

                sf::Vector2f enemyPos = enemy.getPosition();
                if (enemyPos.x < 0 || enemyPos.x > window.getSize().x - enemy.getBounds().width) {
                    movement.x = -movement.x;
                }
                if (enemyPos.y < 0 || enemyPos.y > 376 - enemy.getBounds().height) {
                    movement.y = -movement.y;
                }
                enemy.update();

                if (gameClock.getElapsedTime().asSeconds() > 1.3f) {
                    for (auto &enemy : enemies) {
                        bullets.emplace_back(enemy.getPosition().x + 20, enemy.getPosition().y + 40, true);
                    }
                    gameClock.restart();
                }
            }

            for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
                bulletIt->update();

                if (bulletIt->isEnemyBullet() && bulletIt->getBounds().intersects(player.getBounds())) {
                    isGameOver = true;
                    gameOverSound.play();
                    finalTime = timerClock.getElapsedTime();
                    break;
                }

                bool bulletErased = false;
                if (!bulletIt->isEnemyBullet()) {
                    for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
                        if (bulletIt->getBounds().intersects(enemyIt->getBounds())) {
                            enemies.erase(enemyIt);
                            bulletIt = bullets.erase(bulletIt);
                            bulletErased = true;
                            kills++;

                            enemies.emplace_back(rand() % 1280, rand() % 376);
                            enemies.back().setSpeed(0.5f + (enemySpeedMultiplier * 0.05f));
                            enemySpeedMultiplier += 0.05f;
                            break;
                        } else {
                            ++enemyIt;
                        }
                    }
                }

                if (!bulletErased && bulletIt->isOutOfBounds()) {
                    bulletIt = bullets.erase(bulletIt);
                } else if (!bulletErased) {
                    ++bulletIt;
                }
            }
        }

        if (!isGameOver) {
            killsText.setString("Kills: " + std::to_string(kills));
            timeText.setString("Tiempo: " + std::to_string(static_cast<int>(timerClock.getElapsedTime().asSeconds())));
        }

        window.clear();
        window.draw(backgroundSprite);
        player.draw(window);
        for (auto &enemy : enemies) enemy.draw(window);
        for (auto &bullet : bullets) bullet.draw(window);

        window.draw(killsText);
        window.draw(timeText);

        if (isGameOver) {
            window.draw(gameOverSprite);
            sf::Text finalKillsText("Total Kills: " + std::to_string(kills), font, 30);
            sf::Text finalTimeText("Total Tiempo: " + std::to_string(static_cast<int>(finalTime.asSeconds())), font, 30);
            finalKillsText.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 + 100);
            finalTimeText.setPosition(window.getSize().x / 2 - 100, window.getSize().y / 2 + 150);
            finalKillsText.setOutlineColor(sf::Color::Black);
            finalKillsText.setOutlineThickness(2);
            window.draw(finalKillsText);
            finalTimeText.setOutlineColor(sf::Color::Black);
            finalTimeText.setOutlineThickness(2);
            window.draw(finalTimeText);

            // Obtener un mensaje aleatorio de Game Over y dibujarlo
            std::string gameOverMessage = getRandomGameOverMessage();
            sf::Text messageText(gameOverMessage, font, 25);
            messageText.setPosition(window.getSize().x / 2 - 150, window.getSize().y / 2 + 250);
            messageText.setFillColor(sf::Color::White);
            messageText.setOutlineColor(sf::Color::Black);
            messageText.setOutlineThickness(2.5);
            window.draw(messageText);
        }

        window.display();
    }
}
