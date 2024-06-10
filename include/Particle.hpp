#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <SFML/Graphics.hpp>

class Particle {
public:
    // Constructor
    Particle(float x, float y, float mass);

    // Method
    void updateParticle(const float& deltatime);

    // Getter
    sf::Vector2f getPosition() const;
    sf::Vector2f getVelocity() const;
    sf::Vector2f getAcceleration() const;
    sf::CircleShape getShape() const;
    float getMass() const;
    float getRadius() const;

    // Setter
    void setVelocity(const sf::Vector2f& velocity);
    void setPosition(const sf::Vector2f& position);
    void setAcceleration(sf::Vector2f& acc);

private:
    // Variable
    sf::CircleShape particle;
    sf::Vector2f position;
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Color color;
    float mass;
    float radius;

    const float MAX_VELOCITY = 1000.0f; // Maximum speed for a particle

    // Method
    void updateVelocity(const float& deltatime);
    void updatePosition(const float& deltatime);
};

#endif // PARTICLE_HPP
