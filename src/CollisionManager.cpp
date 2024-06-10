#include "CollisionManager.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

CollisionManager::CollisionManager(float windowWidth, float windowHeight) 
    : windowWidth(windowWidth), windowHeight(windowHeight) {}

void CollisionManager::handleBoxCollision(Particle& particle, float deltaTime) {
    sf::Vector2f position = particle.getPosition();
    sf::Vector2f velocity = particle.getVelocity();
    float radius = particle.getRadius();

    float left = position.x - radius;
    float right = position.x + radius;
    float top = position.y - radius;
    float bottom = position.y + radius;

    bool collisionDetected = false;

    if (left <= 0) {
        position.x = radius;
        velocity.x = -velocity.x * (friction/1.2); // Reflect velocity
        collisionDetected = true;
    } else if (right >= windowWidth) {
        position.x = windowWidth - radius;
        velocity.x = -velocity.x * (friction/1.2); // Reflect velocity
        collisionDetected = true;
    }

    if (top <= 0) {
        position.y = radius;
        velocity.y = -velocity.y * (friction/1.2); // Reflect velocity
        collisionDetected = true;
    } else if (bottom >= windowHeight) {
        position.y = windowHeight - radius;
        velocity.y = -velocity.y * (friction/1.2); // Reflect velocity
        collisionDetected = true;
    }

    if (collisionDetected) {
        particle.setPosition(position);
        particle.setVelocity(velocity);
    }
}

void CollisionManager::checkCollisionBetweenParticles(Particle& part_i, Particle& part_j) {
    sf::Vector2f position_i = part_i.getPosition();
    sf::Vector2f velocity_i = part_i.getVelocity();
    float radius_i = part_i.getRadius();

    sf::Vector2f position_j = part_j.getPosition();
    sf::Vector2f velocity_j = part_j.getVelocity();
    float radius_j = part_j.getRadius();

    sf::Vector2f distanceVec = position_i - position_j;
    float distance = std::sqrt(distanceVec.x * distanceVec.x + distanceVec.y * distanceVec.y);

    if (distance < radius_i + radius_j) {
        sf::Vector2f normal = distanceVec / distance;

        sf::Vector2f relativeVelocity = velocity_i - velocity_j;

        float dotProduct = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

        if (dotProduct < 0) {
            float impulse = 2 * dotProduct / (part_i.getMass() + part_j.getMass());

            sf::Vector2f newVelocity_i = velocity_i - impulse * part_j.getMass() * normal;
            sf::Vector2f newVelocity_j = velocity_j + impulse * part_i.getMass() * normal;

            part_i.setVelocity(newVelocity_i * friction);
            part_j.setVelocity(newVelocity_j * friction);
        }

        float overlap = radius_i + radius_j - distance;
        sf::Vector2f separation = (overlap / 2.0f) * normal;
        part_i.setPosition(position_i + separation);
        part_j.setPosition(position_j - separation);
    }
}

void CollisionManager::interpolatePosition(Particle& particle, float interpolationFactor) {
    sf::Vector2f position = particle.getPosition();
    sf::Vector2f velocity = particle.getVelocity();
    position += velocity * interpolationFactor;
    particle.setPosition(position);
}

void CollisionManager::checkAllCollisions(std::vector<Particle>& particles, float deltaTime) {
    const float step = 0.01f;
    int subSteps = static_cast<int>(std::ceil(deltaTime / step));

    std::vector<Particle*> particlePointers;
    for (auto& particle : particles) {
        particlePointers.push_back(&particle);
    }

    KdTree kdTree(particlePointers);

    for (int i = 0; i < subSteps; ++i) {
        float interpolationFactor = (i + 1) * step;

        for (auto& particle : particles) {
            interpolatePosition(particle, interpolationFactor);
            handleBoxCollision(particle, step);

            std::vector<Particle*> potentialCollisions;
            kdTree.rangeSearch(particle, particle.getRadius() * 2, potentialCollisions);

            for (auto& otherParticle : potentialCollisions) {
                if (&particle != otherParticle) {
                    checkCollisionBetweenParticles(particle, *otherParticle);
                }
            }
        }
    }

    for (auto& particle : particles) {
        particle.updateParticle(deltaTime);
        applyDamping(particle);
    }
}

void CollisionManager::applyDamping(Particle& particle) {
    sf::Vector2f velocity = particle.getVelocity();
    float dampingFactor = 1.0f; // Ajustez ce facteur selon vos besoins
    particle.setVelocity(velocity * dampingFactor);
}