#ifndef NODE_H
#define NODE_H

#include <utility>
#include <vector>
#include <cmath>

class Node {
public:
    // VARIABLES ARE PUBLIC FOR QUICK ACCESS
    int x;
    int y;

    float f_cost;
    float g_cost;
    float h_cost;

    Node* parent;
    Node(int x, int y);

    float calculateHeuristic(Node* target);
    float calculateEuclideanHeuristic(Node* target);

    void updateCosts(float new_g_cost, float new_h_cost);

    bool operator<(const Node& other) const;
    bool operator==(const Node& other) const;

    std::pair<int, int> getPosition() const;

    std::vector<std::pair<int, int>> getNeighbors() const;
    std::vector<std::pair<int, int>> getCardinalNeighbors() const;
};

#endif
