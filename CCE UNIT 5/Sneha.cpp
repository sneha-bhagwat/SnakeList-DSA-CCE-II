
#include <iostream>
#include <string>
using namespace std;

const int N = 5;

// College buildings
string buildings[N] = {
    "Main Building",
    "Library",
    "Laboratory",
    "Canteen",
    "Auditorium"
};

// Adjacency matrix
int graph[N][N] = {0};

// Add a pathway between two buildings
void addPathway(int u, int v) {
    graph[u][v] = 1;
    graph[v][u] = 1;
}

// Display the adjacency matrix
void displayMatrix() {
    cout << "\nAdjacency Matrix:\n\n";

    cout << "        ";
    for (int i = 0; i < N; i++)
        cout << i << " ";
    cout << "\n";

    for (int i = 0; i < N; i++) {
        cout << i << "       ";
        for (int j = 0; j < N; j++)
            cout << graph[i][j] << " ";
        cout << "\n";
    }

    cout << "\nBuilding Index:\n";
    for (int i = 0; i < N; i++)
        cout << i << " - " << buildings[i] << "\n";
}

// Display all direct connections
void displayConnections() {
    cout << "\nCollege Building Connections:\n";

    bool found = false;

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (graph[i][j] == 1) {
                cout << buildings[i] << " <--> "
                     << buildings[j] << "\n";
                found = true;
            }
        }
    }

    if (!found)
        cout << "No pathways available.\n";
}

// Check a direct pathway
void checkPathway() {
    int u, v;

    cout << "\nEnter building indices (0 to "
         << N - 1 << "): ";
    cin >> u >> v;

    if (u < 0 || u >= N || v < 0 || v >= N) {
        cout << "Invalid building index!\n";
        return;
    }

    if (u == v) {
        cout << "Same building selected.\n";
    } else if (graph[u][v] == 1) {
        cout << "A direct pathway exists between "
             << buildings[u] << " and "
             << buildings[v] << ".\n";
    } else {
        cout << "No direct pathway exists between "
             << buildings[u] << " and "
             << buildings[v] << ".\n";
    }
}

int main() {
    int edges, u, v, choice;

    cout << "COLLEGE CAMPUS CONNECTIVITY\n";
    cout << "===========================\n";

    cout << "\nBuilding Index:\n";
    for (int i = 0; i < N; i++)
        cout << i << " - " << buildings[i] << "\n";

    cout << "\nEnter number of pathways (0 to 10): ";
    cin >> edges;

    if (cin.fail() || edges < 0 || edges > 10) {
        cout << "Invalid number of pathways!\n";
        return 1;
    }

    cout << "Enter the indices of connected buildings: \n";

    for (int i = 0; i < edges; i++) {
        cout << "Pathway " << i + 1 << ": ";
        cin >> u >> v;

        if (cin.fail() || u < 0 || u >= N ||
            v < 0 || v >= N || u == v) {
            cout << "Invalid input! Restart the program.\n";
            return 1;
        }

        addPathway(u, v);
    }

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Display Adjacency Matrix\n";
        cout << "2. Display Building Connections\n";
        cout << "3. Check Direct Pathway\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayMatrix();
                break;

            case 2:
                displayConnections();
                break;

            case 3:
                checkPathway();
                break;

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

