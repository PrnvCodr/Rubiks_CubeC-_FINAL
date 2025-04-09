# Rubik's Cube Cracker

A high-performance, OpenGL-rendered Rubik’s Cube simulator and solver written in C++. This application features both a **fast solver** (Thistlethwaite's algorithm) and an **optimal solver** (Korf’s algorithm) capable of finding minimal move solutions (20 moves or fewer). Built from the ground up with custom rendering and solving logic, it's a complete virtual cube experience for enthusiasts and speedcubers alike.

---

## 🔄 Controls & Shortcuts

- **Face Rotations:**  
  Use `U`, `D`, `L`, `R`, `F`, `B` for clockwise twists of the Up, Down, Left, Right, Front, and Back faces respectively.  
  - Hold `Shift` for counter-clockwise  
  - Hold `Alt` for 180° twists

- **Cube Rotation (View):**  
  - Arrow Keys for rotating the cube around X and Y axes  
  - `Z` to rotate around Z-axis (`Shift + Z` for inverse)

- **Slice Moves:**  
  - `M`, `E`, `S` for respective middle layer slices

- **Solving & Scrambling:**  
  - `F1`: Fast solve using Thistlethwaite's algorithm  
  - `F2`: Optimal solve using Korf's algorithm  
  - `F5`: Apply a 100-move scramble

---

## 🧊 Rendering Engine

- **OpenGL-Based**: Custom renderer with handcrafted visuals and animations.
- **SLERP Animations**: Face rotations are interpolated using quaternions for smooth transitions.
- **Dynamic Lighting**: Implements a Phong-style shading model with specular highlights and simulated imperfections on stickers.
- **Visual Effects**: Floating animation for added visual flair.

---

## 🧠 Optimal Solver (Korf’s Algorithm)

The optimal solver is based on **Richard Korf's IDA*** (Iterative Deepening A*) algorithm, a classic AI approach used to find **the shortest possible solution** for the Rubik’s Cube—guaranteed to be 20 moves or fewer.

### How It Works:

1. **State Encoding**: The cube state is encoded using a compact representation with permutation and orientation data.
2. **Heuristic Lookup**: Heuristics are generated from **precomputed pattern databases**, which give the estimated distance (in moves) to the solved state.
3. **IDA* Search**: A depth-limited DFS is run iteratively, expanding the search only if the heuristic plus the current path cost is within a threshold. The threshold increases gradually.
4. **Optimality**: The heuristic is **admissible and consistent**, ensuring that the solution found is always the shortest possible.

### Pattern Databases Used:

- **Corners Database**: Stores positions and orientations of all 8 corners.
- **Two Edge Databases**: Each stores states for a 7-edge subset for efficiency.
- **Full Edge Permutations**: Captures all permutations of the 12 edge pieces.

### Memory Footprint:

- Total DB size: ~758MB
- Extremely fast due to perfect hashing with **Lehmer codes**, ensuring fast cube state lookups with zero collisions.

---

## ⚡ Fast Solver (Thistlethwaite’s Algorithm)

Thistlethwaite’s algorithm provides a **fast and practical solution** by reducing the problem into progressively simpler stages using group theory.

### How It Works:

1. The Rubik’s Cube is viewed as a mathematical group with defined states and allowable moves.
2. Instead of solving the entire cube in one go, the algorithm **moves the cube through a series of subgroups**, each with stricter constraints on allowable moves.
3. At each stage, only a subset of moves is permitted, reducing complexity and allowing **efficient lookup and pruning**.
4. Once the cube enters the final group (where only half-turns are allowed), it's only a few moves away from solved.

### Why It’s Fast:

- By limiting the search space at each stage, the algorithm avoids checking irrelevant moves.
- Uses **breadth-first searches with precomputed lookup tables** to determine the shortest path to the next group.
- Often solves the cube in **30–45 moves**, and does so in a fraction of a second.

Unlike Korf’s algorithm, Thistlethwaite does not guarantee the shortest solution, but it is significantly faster and ideal for interactive use.

---

## ⚙️ Building & Running

- Supported Platforms: Linux (g++), Windows (MinGW 64-bit)
- Refer to the `BUILDING.md` file for detailed build instructions.
- Requires OpenGL-compatible GPU and C++17 support.

---

## 🧮 Algorithm Highlights

- **Iterative Deepening A\***: Combines DFS’s low memory usage with the power of A* search.
- **Perfect Hashing with Lehmer Codes**: Compact and fast cube state indexing.
- **Custom Pattern Database Generator**: Generates all heuristic databases offline for blazing fast runtime performance.

---

## 🧪 Performance Showcase

Sample metrics from test scrambles (100 random moves each):

| Scramble # | Optimal Moves | Time (s) |
|------------|---------------|----------|
| 1          | 19            | 1.42     |
| 2          | 20            | 1.89     |
| 3          | 18            | 1.27     |
| ...        | ...           | ...      |

*Benchmarking on older-generation quad-core CPU*

---

## 🌟 Final Thoughts

This project showcases how algorithmic theory meets visual design. Whether you're here to study cube-solving AI or just to enjoy spinning faces with buttery-smooth visuals, Rubik’s Cube Cracker delivers both speed and depth.

Feel free to explore, tweak, and expand upon it. Happy solving! 🧩
