#include "Event.hpp"
#include <iostream>

Event::Event(sf::RenderWindow& window, std::vector<Particle>& particles)
    : window(window), particles(particles), isLeftMousePressed(false), isRightMousePressed(false) {}

void Event::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                isLeftMousePressed = true;
                mousePressPosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                currentMousePosition = mousePressPosition;  // Ensure it starts from the same position
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMousePressed = true;
            }
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && isLeftMousePressed) {
                isLeftMousePressed = false;
                sf::Vector2f mouseReleasePosition = sf::Vector2f(event.mouseButton.x, event.mouseButton.y);
                sf::Vector2f velocity = mouseReleasePosition - mousePressPosition;

                Particle newParticle(mousePressPosition.x, mousePressPosition.y, 1);
                newParticle.setVelocity(-velocity);
                particles.push_back(newParticle);
            } else if (event.mouseButton.button == sf::Mouse::Right) {
                isRightMousePressed = false;
            }
        }
        if (event.type == sf::Event::MouseMoved) {
            if (isLeftMousePressed) {
                currentMousePosition = sf::Vector2f(event.mouseMove.x, event.mouseMove.y);
            }
        }
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::C){
                particles.clear();
            }
            if (event.key.code == 55) {
                acceleration.y += 25;
            }
            if (event.key.code == 56) {
                acceleration.y -= 25;
            }
        }
    }

    if (isRightMousePressed) {
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        Particle newParticle(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y), 0.75);
        newParticle.setVelocity(sf::Vector2f(0, 0)); // Particles added with no initial velocity
        particles.push_back(newParticle);
    }
}

bool Event::isLeftMouseButtonPressed() const {
    return isLeftMousePressed;
}

sf::Vector2f Event::getMousePressPosition() const {
    return mousePressPosition;
}

sf::Vector2f Event::getCurrentMousePosition() const {
    return currentMousePosition;
}

sf::Vector2f Event::getAcceleration() {
    return acceleration;
}
