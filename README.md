# A* Pathfinding Algorithm Visualization

This project demonstrates how A* efficiently finds the shortest path between two points while avoiding obstacles.

![Project Demo](https://i.imgur.com/QcV2MCn.png)

## Features

- **Interactive Grid System**: Click to place/remove walls and obstacles
- **Real-time Pathfinding**: Path automatically recalculates when obstacles are placed
- **Visual Feedback**: 
  - Blue Square: Start position
  - Red Square: Target position
  - Black Squares: Walls
  - Green Squares: Calculated shortest path

## Dependencies

- C++ 17 or higher
- SFML 2.5.1 or higher
- CMake 3.10 or higher (for building)

## Building and Running

1. Clone the repository
```bash
git clone https://github.com/yourusername/astar-visualization.git
cd astar-visualization
```

2. Build the project
```bash
mkdir build
cd build
cmake ..
make
```

3. Run the executable
```bash
./pathfinding
```

## Usage

- **Left Click**: Place walls/obstacles
- **Starting Position**: Blue square (preset)
- **Target Position**: Red square (preset)
- The path will automatically update whenever obstacles are placed

## Algorithm Complexity

- **Time Complexity**: O(n log n) where n is the number of nodes
- **Space Complexity**: O(n) for storing nodes in the open and closed sets

## Contributing

Feel free to open issues or submit pull requests with improvements. Please read CONTRIBUTING.md for details on the code of conduct and the process for submitting pull requests.

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Acknowledgments

- Inspired by various pathfinding visualizers and educational resources
- Built using SFML (Simple and Fast Multimedia Library)

## Contact

Project Link: [https://github.com/yourusername/astar-visualization](https://github.com/voIuminous/cpp-pathfinding)
