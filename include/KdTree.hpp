#ifndef KDTREE_HPP
#define KDTREE_HPP

#include <vector>
#include "Particle.hpp"

class KdTree {
public:
    struct Node {
        Particle* particle;
        int axis;
        Node* left;
        Node* right;
        Node(Particle* particle, int axis) : particle(particle), axis(axis), left(nullptr), right(nullptr) {}
    };

    KdTree(std::vector<Particle*>& particles);
    ~KdTree();

    void rangeSearch(Particle& target, float range, std::vector<Particle*>& result);

private:
    Node* buildKdTree(std::vector<Particle*>& particles, int depth);
    void destroyKdTree(Node* node);
    void rangeSearch(Node* node, Particle& target, float range, std::vector<Particle*>& result);

    Node* root;
};

#endif // KDTREE_HPP
