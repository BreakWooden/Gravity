#include "Particle.hpp"
#include <cmath>
#include <iostream>
#include <algorithm> // Include this header for std::min

// Constructor
Particle::Particle(float x, float y, float mass) : position(x, y), mass(mass) {
    radius = mass * 10;
    particle.setRadius(radius);
    
    // Définir l'origine au centre du cercle
    particle.setOrigin(radius, radius);
    
    // Mettre à jour la position après avoir défini l'origine
    particle.setPosition(position);
    
    acceleration.x = 0;
    acceleration.y = 0;
    velocity.x = 0;
    velocity.y = 0;
}

// Method
void Particle::updateVelocity(const float& deltatime) {
    velocity += acceleration * deltatime; // V = V0 + A*t
}

void Particle::updatePosition(const float& deltatime) {
    position += velocity * deltatime; // P = P0 + V*t
    particle.setPosition(position); // Use setPosition instead of move
}

#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

void Particle::updateParticle(const float& deltatime) {
    // Calculer la norme de la vitesse
    float speedNorm = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);
    
    // Limiter la vitesse maximale à 100.0f
    float factor = std::min(speedNorm, 100.0f);
    
    // Normaliser la vitesse entre 0 et 1
    float normalizedSpeed = factor / 100.0f;
    
    // Initialiser les composantes de couleur (bleu -> vert -> rouge)
    sf::Color color;
    
    if (normalizedSpeed <= 0.5f) {
        // Interpolation entre bleu (0, 0, 255) et vert (0, 255, 0)
        float t = normalizedSpeed * 2.0f;
        color.r = 0;
        color.g = static_cast<sf::Uint8>(255 * t);
        color.b = static_cast<sf::Uint8>(255 * (1.0f - t));
    } else {
        // Interpolation entre vert (0, 255, 0) et rouge (255, 0, 0)
        float t = (normalizedSpeed - 0.5f) * 2.0f;
        color.r = static_cast<sf::Uint8>(255 * t);
        color.g = static_cast<sf::Uint8>(255 * (1.0f - t));
        color.b = 0;
    }
    
    // Appliquer la couleur à la particule
    particle.setFillColor(color);
    
    // Mettre à jour la vélocité et la position
    updateVelocity(deltatime);
    updatePosition(deltatime);
}

// Getter
sf::Vector2f Particle::getPosition() const {
    return position;
}

sf::Vector2f Particle::getVelocity() const {
    return velocity;
}

sf::Vector2f Particle::getAcceleration() const {
    return acceleration;
}

sf::CircleShape Particle::getShape() const {
    return particle;
}

float Particle::getMass() const {
    return mass;
}

float Particle::getRadius() const {
    return radius;
}


// Setter
void Particle::setVelocity(const sf::Vector2f& newVelocity) {
    velocity = newVelocity;
}

void Particle::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
    particle.setPosition(newPosition);
}

void Particle::setAcceleration(sf::Vector2f& acc) {
    acceleration = acc;
}