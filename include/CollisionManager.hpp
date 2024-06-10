#ifndef COLLISIONMANAGER_HPP
#define COLLISIONMANAGER_HPP

#include <vector>
#include "Particle.hpp"
#include "KdTree.hpp"

class CollisionManager {
public:
    CollisionManager(float windowWidth, float windowHeight);
    void handleBoxCollision(Particle& particle, float deltaTime);
    void checkCollisionBetweenParticles(Particle& part_i, Particle& part_j);
    void interpolatePosition(Particle& particle, float interpolationFactor);
    void checkAllCollisions(std::vector<Particle>& particles, float deltaTime);
    void applyDamping(Particle& particle);

private:
    float windowWidth;
    float windowHeight;
    float friction = 0.92f;
};

#endif // COLLISIONMANAGER_HPP
