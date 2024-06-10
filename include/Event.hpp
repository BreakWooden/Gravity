#ifndef EVENT_HPP
#define EVENT_HPP

#include <SFML/Graphics.hpp>
#include "Particle.hpp"
#include <vector>

class Event {
public:
    Event(sf::RenderWindow& window, std::vector<Particle>& particles);

    void handleEvents();
    bool isLeftMouseButtonPressed() const;
    sf::Vector2f getMousePressPosition() const;
    sf::Vector2f getCurrentMousePosition() const;

    sf::Vector2f getAcceleration();

private:
    sf::RenderWindow& window;
    std::vector<Particle>& particles;
    bool isLeftMousePressed;
    bool isRightMousePressed;
    sf::Vector2f mousePressPosition;
    sf::Vector2f currentMousePosition;

    sf::Vector2f acceleration;
};

#endif // EVENT_HPP
