#include <iostream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Graph {
private:
    struct Node {
        int id;
        list<int> neighbors;
    };

    vector<Node> vertices;

    bool hasEulerianCycle() const {
        for (const auto& vertex : vertices) {
            if (vertex.neighbors.size() % 2 != 0) {
                return false;
            }
        }
        return true;
    }

    bool findHamiltonianCycle(int current, int depth, vector<int>& path, vector<bool>& visited) {
        if (depth == vertices.size()) {
            return path.front() == path.back();
        }

        for (int neighbor : vertices[current].neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                path[depth] = neighbor;
                if (findHamiltonianCycle(neighbor, depth + 1, path, visited)) {
                    return true;
                }
                visited[neighbor] = false;
            }
        }
        return false;
    }

public:
    void addVertex(int id) {
        vertices.push_back({ id, {} });
    }

    void addEdge(int start, int end) {
        vertices[start].neighbors.push_back(end);
        vertices[end].neighbors.push_back(start);
    }

    void displayGraph() const {
        for (const auto& vertex : vertices) {
            cout << "Node " << vertex.id << ": ";
            for (int neighbor : vertex.neighbors) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> getEulerianCycle() {
        vector<int> cycle;
        if (!hasEulerianCycle()) return cycle;

        vector<bool> visited(vertices.size(), false);
        list<int> stack;
        stack.push_back(0);

        while (!stack.empty()) {
            int current = stack.back();
            if (!vertices[current].neighbors.empty()) {
                int next = vertices[current].neighbors.front();
                stack.push_back(next);
                vertices[current].neighbors.remove(next);
                vertices[next].neighbors.remove(current);
            } else {
                cycle.push_back(current);
                stack.pop_back();
            }
        }
        return cycle;
    }

    vector<int> getHamiltonianCycle() {
        vector<int> path(vertices.size(), -1);
        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        path[0] = 0;

        if (findHamiltonianCycle(0, 1, path, visited)) {
            return path;
        }
        return {};
    }

    Graph createSpanningTree() const {
        Graph spanningTree;
        for (int i = 0; i < vertices.size(); ++i) {
            spanningTree.addVertex(i);
        }

        vector<bool> visited(vertices.size(), false);
        visited[0] = true;
        queue<int> queue;
        queue.push(0);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();

            for (int neighbor : vertices[current].neighbors) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    spanningTree.addEdge(current, neighbor);
                    queue.push(neighbor);
                }
            }
        }
        return spanningTree;
    }
};

int main() {
    setlocale(LC_ALL, "RUSSIAN");
    Graph g;

    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);

    cout << "Структура графа:\n";
    g.displayGraph();

    vector<int> eulerianCycle = g.getEulerianCycle();
    if (!eulerianCycle.empty()) {
        cout << "Эйлеров цикл: ";
        for (int node : eulerianCycle) {
            cout << node << " ";
        }