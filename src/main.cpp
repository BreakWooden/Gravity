#include "Particle.hpp"
#include "CollisionManager.hpp"
#include "Event.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

int main() {
    float width = 1920 * 1.1;
    float height = 1080 * 1.1;
    sf::RenderWindow window(sf::VideoMode(width, height), "Gravity Simulation");
    window.setFramerateLimit(260);
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timePerFrame = sf::seconds(1.f / 60.f);

    std::vector<Particle> particles;
    CollisionManager collisionManager(width, height);
    
    Event eventManager(window, particles);

    sf::Vector2f acceleration;

    // Initialisation des polices et du texte
    sf::Font font;
    if (!font.loadFromFile("include/fonts/Roboto-Black.ttf")) {
        // Gérer l'erreur de chargement de la police
        return -1;
    }
    sf::Text particleCount;
    particleCount.setFont(font);
    particleCount.setCharacterSize(24); // Taille du texte
    particleCount.setFillColor(sf::Color::White); // Couleur du texte

    sf::Text fpsCount;
    fpsCount.setFont(font);
    fpsCount.setCharacterSize(24); // Taille du texte
    fpsCount.setFillColor(sf::Color::White); // Couleur du texte

    // Variables pour le calcul des FPS
    float fps = 0.0f;
    int frameCount = 0;
    sf::Time fpsUpdateTime = sf::Time::Zero;
    const sf::Time fpsUpdateInterval = sf::seconds(1.0f);

    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        fpsUpdateTime += elapsedTime;
        frameCount++;

        if (fpsUpdateTime >= fpsUpdateInterval) {
            fps = static_cast<float>(frameCount) / fpsUpdateTime.asSeconds();
            frameCount = 0;
            fpsUpdateTime -= fpsUpdateInterval;
        }

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;

            eventManager.handleEvents();
            acceleration = eventManager.getAcceleration();

            collisionManager.checkAllCollisions(particles, timePerFrame.asSeconds());

            for (Particle& particle : particles) { // Mise à jour des particules
                particle.setAcceleration(acceleration);
            }
        }

        window.clear(); // Clear the screen before drawing

        for (Particle& particle : particles) { // Drawing particles
            window.draw(particle.getShape());
        }

        // Draw the line if the left mouse button is pressed
        if (eventManager.isLeftMouseButtonPressed()) {
            sf::Vertex line[] = {
                sf::Vertex(eventManager.getMousePressPosition(), sf::Color::Red),
                sf::Vertex(eventManager.getCurrentMousePosition(), sf::Color::Red)
            };
            window.draw(line, 2, sf::Lines);
        }

        // Mise à jour et affichage du nombre de particules
        particleCount.setString("Particles: " + std::to_string(particles.size()));
        particleCount.setPosition(width - particleCount.getGlobalBounds().width - 10, 40); // Position en haut à droite, sous les FPS
        window.draw(particleCount);

        // Affichage des FPS
        std::ostringstream fpsStream;
        fpsStream << std::fixed << std::setprecision(1) << fps;
        fpsCount.setString("FPS: " + fpsStream.str());
        fpsCount.setPosition(width - fpsCount.getGlobalBounds().width - 10, 10); // Position en haut à droite
        window.draw(fpsCount);

        window.display(); // Display the window content
    }

    return 0;
}
