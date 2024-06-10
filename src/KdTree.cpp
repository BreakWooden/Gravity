#include "KdTree.hpp"
#include <algorithm>
#include <cmath>

KdTree::KdTree(std::vector<Particle*>& particles) {
    root = buildKdTree(particles, 0);
}

KdTree::~KdTree() {
    destroyKdTree(root);
}

KdTree::Node* KdTree::buildKdTree(std::vector<Particle*>& particles, int depth) {
    if (particles.empty()) {
        return nullptr;
    }

    int axis = depth % 2; // 0 for x-axis, 1 for y-axis

    std::sort(particles.begin(), particles.end(), [axis](Particle* a, Particle* b) {
        return axis == 0 ? a->getPosition().x < b->getPosition().x : a->getPosition().y < b->getPosition().y;
    });

    size_t medianIndex = particles.size() / 2;
    Particle* medianParticle = particles[medianIndex];

    std::vector<Particle*> leftParticles(particles.begin(), particles.begin() + medianIndex);
    std::vector<Particle*> rightParticles(particles.begin() + medianIndex + 1, particles.end());

    Node* node = new Node(medianParticle, axis);
    node->left = buildKdTree(leftParticles, depth + 1);
    node->right = buildKdTree(rightParticles, depth + 1);

    return node;
}

void KdTree::destroyKdTree(Node* node) {
    if (!node) {
        return;
    }
    destroyKdTree(node->left);
    destroyKdTree(node->right);
    delete node;
}

void KdTree::rangeSearch(Particle& target, float range, std::vector<Particle*>& result) {
    rangeSearch(root, target, range, result);
}

void KdTree::rangeSearch(Node* node, Particle& target, float range, std::vector<Particle*>& result) {
    if (!node) {
        return;
    }

    sf::Vector2f targetPos = target.getPosition();
    sf::Vector2f nodePos = node->particle->getPosition();

    float distance = std::sqrt(std::pow(targetPos.x - nodePos.x, 2) + std::pow(targetPos.y - nodePos.y, 2));

    if (distance < range) {
        result.push_back(node->particle);
    }

    int axis = node->axis;
    float diff = axis == 0 ? targetPos.x - nodePos.x : targetPos.y - nodePos.y;

    if (diff < 0) {
        rangeSearch(node->left, target, range, result);
        if (std::abs(diff) < range) {
            rangeSearch(node->right, target, range, result);
        }
    } else {
        rangeSearch(node->right, target, range, result);
        if (std::abs(diff) < range) {
            rangeSearch(node->left, target, range, result);
        }
    }
}
