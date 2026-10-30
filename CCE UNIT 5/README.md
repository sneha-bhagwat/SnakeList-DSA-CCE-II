
# College Campus Connectivity Using Graphs

## 📌 Project Overview

This project represents college buildings as vertices and the pathways connecting them as edges using a graph.

An adjacency matrix is used to store and display the connectivity between different college buildings.

The project is implemented in C++ and demonstrates the practical application of graph data structures in campus navigation.

## 🎯 Objectives

- To understand graph representation using an adjacency matrix.
- To represent college buildings as vertices.
- To represent connecting pathways as edges.
- To display the connectivity between buildings.
- To check whether a direct pathway exists between two buildings.

## 🏫 Real-Life Application

A college campus contains different buildings connected by walking pathways.

This project models the campus as an undirected graph, where:

- **Vertices:** Main Building, Library, Laboratory, Canteen, Auditorium.
- **Edges:** Pathways connecting the buildings.
- **Adjacency Matrix:** A two-dimensional array that stores the connections.

## 🛠️ Technologies Used

- Programming Language: C++
- Header Files: `<iostream>` and `<string>`
- Data Structure: Graph
- Graph Representation: Adjacency Matrix

## 📂 Project Structure

```text
College-Campus-Connectivity/
│
├── main.cpp
└── README.md
```

## ⚙️ How It Works

1. The program defines five college buildings.
2. Each building is assigned an index from 0 to 4.
3. The user enters the number of pathways and the connected building indices.
4. The `addPathway()` function updates the adjacency matrix.
5. The user can display the matrix, list direct connections, or check a pathway.

## 📊 Understanding the Adjacency Matrix

The adjacency matrix is a two-dimensional array.

- `1` means a direct pathway exists between two buildings.
- `0` means no direct pathway exists.
- The diagonal elements are `0` because a building is not connected to itself by a pathway in this model.

Example:

```text
    0 1 2 3 4
0   0 1 1 0 0
1   1 0 0 1 0
2   1 0 0 0 1
3   0 1 0 0 1
4   0 0 1 1 0
```

## ▶️ How to Run the Program

### Step 1: Compile

Using GCC or MinGW:

```bash
g++ main.cpp -o campus
```

### Step 2: Execute

On Windows:

```bash
campus.exe
```

On Linux or macOS:

```bash
./campus
```

You can also run the program in Code::Blocks, Visual Studio Code, or another C++ IDE.

## 📋 Program Features

1. Display the adjacency matrix.
2. Display direct connections between buildings.
3. Check whether a direct pathway exists.
4. Use a menu-driven interface.

## ⏱️ Time and Space Complexity

Let `V` represent the number of vertices (buildings).

- **Space Complexity:** O(V²), because the adjacency matrix stores V × V entries.
- **Adding a pathway:** O(1).
- **Displaying the adjacency matrix:** O(V²).
- **Checking a direct pathway:** O(1).
- **Displaying all connections:** O(V²).

## 📚 Data Structures Concepts Used

- Graphs
- Vertices and edges
- Adjacency matrix
- Two-dimensional arrays
- Functions
- Loops and conditional statements
- Menu-driven programming

## 🔮 Future Enhancements

- Add more college buildings.
- Allow users to add and remove pathways.
- Find a route between two buildings using BFS.
- Display a graphical map of the campus.

## ✅ Conclusion

This project demonstrates how a graph can represent a real-world college campus.

The adjacency matrix provides a simple way to store, display, and check direct connections between buildings. It helps in understanding graph representation and its practical applications.

---

**Project:** College Campus Connectivity Using Graphs  
**Language:** C++  
**Topic:** Graph Representation Using Adjacency Matrix

