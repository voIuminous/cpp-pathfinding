#include "SystemState.h"

// PRIVATE FUNCTIONS
void SystemState::initVariables()
{
	this->window = nullptr;

    updateWalls();
}

void SystemState::updateWalls()
{
	this->walls.clear();
	for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++)
	{
		for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++)
		{
			switch (map[i][j]) {
			case 0:
				this->walls.push_back(Wall(sf::Vector2f(63, 59), sf::Color::White, sf::Vector2f(j * 64.0f, i * 60.0f)));
				break;
			case 1:
				this->walls.push_back(Wall(sf::Vector2f(63, 59), sf::Color::Red, sf::Vector2f(j * 64.0f, i * 60.0f)));
				break;
			case 2:
				this->walls.push_back(Wall(sf::Vector2f(63, 59), sf::Color::Black, sf::Vector2f(j * 64.0f, i * 60.0f)));
				break;
			case 3:
				this->walls.push_back(Wall(sf::Vector2f(63, 59), sf::Color::Blue, sf::Vector2f(j * 64.0f, i * 60.0f)));
				break;
            case 4:
                this->walls.push_back(Wall(sf::Vector2f(63, 59), sf::Color::Green, sf::Vector2f(j * 64.0f, i * 60.0f)));
                break;
			}
		}
	}
}

std::pair<int, int> SystemState::getStartPosition() {
    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
        for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
            if (map[i][j] == 3) return { i, j };
        }
    }
    return { -1, -1 };
}

std::pair<int, int> SystemState::getEndPosition() {
    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
        for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
            if (map[i][j] == 1) return { i, j };
        }
    }
    return { -1, -1 };
}

bool SystemState::isValidMove(int x, int y) {
    if (x < 0 || x >= sizeof(map) / sizeof(map[0]) ||
        y < 0 || y >= sizeof(map[0]) / sizeof(map[0][0]))
        return false;
    return map[x][y] != 2;
}

std::vector<std::pair<int, int>> SystemState::reconstructPath(Node* endNode) {
    std::vector<std::pair<int, int>> path;
    Node* current = endNode;

    while (current != nullptr) {
        path.push_back({ current->x, current->y });
        current = current->parent;
    }

    return path;
}

void SystemState::getFastestPath() {
    for (int i = 0; i < sizeof(map) / sizeof(map[0]); i++) {
        for (int j = 0; j < sizeof(map[0]) / sizeof(map[0][0]); j++) {
            if (map[i][j] != 1 && map[i][j] != 2 && map[i][j] != 3) {
                map[i][j] = 0;
            }
        }
    }

    auto start = getStartPosition();
    auto end = getEndPosition();

    if (start.first == -1 || end.first == -1) return;

    Node* startNode = new Node(start.first, start.second);
    Node* endNode = new Node(end.first, end.second);

    std::priority_queue<Node*> openSet;
    std::unordered_set<std::string> closedSet;
    std::unordered_map<std::string, Node*> openSetMap;

    startNode->updateCosts(0.0f, startNode->calculateHeuristic(endNode));
    openSet.push(startNode);
    openSetMap[std::to_string(startNode->x) + "," + std::to_string(startNode->y)] = startNode;

    while (!openSet.empty()) {
        Node* current = openSet.top();
        openSet.pop();

        if (current->x == endNode->x && current->y == endNode->y) {
            auto path = reconstructPath(current);
            for (const auto& pos : path) {
                if (map[pos.first][pos.second] != 1 && map[pos.first][pos.second] != 3) {
                    map[pos.first][pos.second] = 4;
                }
            }
            delete endNode;
            while (!openSet.empty()) {
                Node* node = openSet.top();
                openSet.pop();
                if (node != current) delete node;
            }
            delete current;
            return;
        }

        std::string currentKey = std::to_string(current->x) + "," + std::to_string(current->y);
        openSetMap.erase(currentKey);
        closedSet.insert(currentKey);

        for (const auto& neighbor : current->getCardinalNeighbors()) {
            if (!isValidMove(neighbor.first, neighbor.second)) continue;

            std::string neighborKey = std::to_string(neighbor.first) + "," + std::to_string(neighbor.second);
            if (closedSet.find(neighborKey) != closedSet.end()) continue;

            float newGCost = current->g_cost + 1.0f;

            Node* neighborNode;
            bool inOpenSet = openSetMap.find(neighborKey) != openSetMap.end();

            if (!inOpenSet) {
                neighborNode = new Node(neighbor.first, neighbor.second);
                neighborNode->parent = current;
            }
            else {
                neighborNode = openSetMap[neighborKey];
                if (newGCost >= neighborNode->g_cost) continue;
                neighborNode->parent = current;
            }

            neighborNode->updateCosts(newGCost, neighborNode->calculateHeuristic(endNode));

            if (!inOpenSet) {
                openSet.push(neighborNode);
                openSetMap[neighborKey] = neighborNode;
            }
        }
    }

    delete endNode;
    return;
}

// INITIALIZE WINDOW
void SystemState::initWindow()
{
	this->videoMode.height = 720;
	this->videoMode.width = 1024;
	this->window.reset(new sf::RenderWindow(this->videoMode, "A* Pathfinding Visualization"));
}

// CONSTRUCTORS - DESTRUCTORS
SystemState::SystemState()
{
	this->initVariables();
	this->initWindow();
}

// ACCESSORS
const bool SystemState::running() const
{
	return this->window->isOpen();
}

// PUBLIC FUNCTIONS
void SystemState::pollEvents() {
	while (this->window->pollEvent(ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		}
	}
}

void SystemState::update()
{
	this->pollEvents();

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition();
		sf::Vector2i windowPos = window->getPosition();

		int gridX = (mousePos.x - windowPos.x) / 64;
		int gridY = (mousePos.y - windowPos.y - 30) / 60;

		if (gridX >= 0 && gridX < sizeof(map[0]) / sizeof(map[0][0]) &&
			gridY >= 0 && gridY < sizeof(map) / sizeof(map[0]))
		{
			map[gridY][gridX] = 2;
			updateWalls();
		}
	}

    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        getFastestPath();
        updateWalls();
    }

	this->window->setFramerateLimit(144);
}

void SystemState::render()
{
	this->window->clear(sf::Color::Black);
	
	for (auto& wall : walls)
	{
		wall.render(*window);
	}

	this->window->display();
}
