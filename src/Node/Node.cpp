#include "Node.h"

Node::Node(int x, int y) : x(x), y(y) {
    f_cost = 0.0f;
    g_cost = 0.0f;
    h_cost = 0.0f;
    parent = nullptr;
}

float Node::calculateHeuristic(Node* target) {
    return static_cast<float>(abs(x - target->x) + abs(y - target->y));
}

float Node::calculateEuclideanHeuristic(Node* target) {
    float dx = static_cast<float>(x - target->x);
    float dy = static_cast<float>(y - target->y);
    return sqrt(dx * dx + dy * dy);
}

void Node::updateCosts(float new_g_cost, float new_h_cost) {
    g_cost = new_g_cost;
    h_cost = new_h_cost;
    f_cost = g_cost + h_cost;
}

bool Node::operator<(const Node& other) const {
    if (f_cost == other.f_cost) {
        if (g_cost == other.g_cost) {
            if (x == other.x) return y > other.y;
            return x > other.x;
        }
        return g_cost > other.g_cost;
    }
    return f_cost > other.f_cost;
}

bool Node::operator==(const Node& other) const {
    return x == other.x && y == other.y;
}

std::pair<int, int> Node::getPosition() const {
    return std::make_pair(x, y);
}

std::vector<std::pair<int, int>> Node::getNeighbors() const {
    std::vector<std::pair<int, int>> neighbors;
    const int dx[] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    const int dy[] = { -1, -1, -1, 0, 0, 1, 1, 1 };

    for (int i = 0; i < 8; ++i) {
        neighbors.push_back(std::make_pair(x + dx[i], y + dy[i]));
    }

    return neighbors;
}

std::vector<std::pair<int, int>> Node::getCardinalNeighbors() const {
    std::vector<std::pair<int, int>> neighbors;
    const int dx[] = { 0, 1, 0, -1 };
    const int dy[] = { -1, 0, 1, 0 };

    for (int i = 0; i < 4; ++i) {
        neighbors.push_back(std::make_pair(x + dx[i], y + dy[i]));
    }

    return neighbors;
}
