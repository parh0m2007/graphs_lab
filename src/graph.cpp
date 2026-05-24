#include "graph.h"
#include <queue>
#include <QSet>

Graph::Graph() {}

void Graph::addVertex(int id, const QString& label) {
    if (!hasVertex(id)) {
        vertices.push_back(id);
        vertexLabels[id] = label;
        adjacencyList[id] = std::vector<std::pair<int, int>>();
    } else {
        vertexLabels[id] = label;
    }
}

void Graph::addEdge(int from, int to, int weight, bool directed) {
    if (hasVertex(from) && hasVertex(to)) {
        adjacencyList[from].push_back(std::make_pair(to, weight));
        if (!directed) {
            adjacencyList[to].push_back(std::make_pair(from, weight));
        }
    }
}

void Graph::removeVertex(int id) {
    if (hasVertex(id)) {
        // Remove from vertices list
        vertices.erase(std::remove(vertices.begin(), vertices.end(), id), vertices.end());
        
        // Remove from adjacency list
        adjacencyList.erase(id);
        
        // Remove edges pointing to this vertex
        for (auto& pair : adjacencyList) {
            auto& neighbors = pair.second;
            neighbors.erase(
                std::remove_if(neighbors.begin(), neighbors.end(),
                    [id](const std::pair<int, int>& p) { return p.first == id; }),
                neighbors.end()
            );
        }
        
        // Remove label
        vertexLabels.erase(id);
    }
}

void Graph::removeEdge(int from, int to) {
    if (hasVertex(from) && adjacencyList.count(from)) {
        auto& neighbors = adjacencyList[from];
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(),
                [to](const std::pair<int, int>& p) { return p.first == to; }),
            neighbors.end()
        );
    }
    
    // For undirected graph, remove reverse edge too
    if (hasVertex(to) && adjacencyList.count(to)) {
        auto& neighbors = adjacencyList[to];
        neighbors.erase(
            std::remove_if(neighbors.begin(), neighbors.end(),
                [from](const std::pair<int, int>& p) { return p.first == from; }),
            neighbors.end()
        );
    }
}

int Graph::getVerticesCount() const {
    return static_cast<int>(vertices.size());
}

int Graph::getEdgesCount() const {
    int count = 0;
    for (const auto& pair : adjacencyList) {
        count += static_cast<int>(pair.second.size());
    }
    // For undirected graph, each edge is counted twice
    return count / 2;
}

bool Graph::hasVertex(int id) const {
    return std::find(vertices.begin(), vertices.end(), id) != vertices.end();
}

bool Graph::hasEdge(int from, int to) const {
    if (!hasVertex(from) || !adjacencyList.count(from)) {
        return false;
    }
    for (const auto& neighbor : adjacencyList.at(from)) {
        if (neighbor.first == to) {
            return true;
        }
    }
    return false;
}

std::vector<int> Graph::getAllVertices() const {
    return vertices;
}

std::vector<std::pair<int, int>> Graph::getNeighbors(int vertexId) const {
    if (adjacencyList.count(vertexId)) {
        return adjacencyList.at(vertexId);
    }
    return std::vector<std::pair<int, int>>();
}

std::vector<int> Graph::bfs(int startVertex) const {
    std::vector<int> result;
    if (!hasVertex(startVertex)) {
        return result;
    }
    
    std::vector<bool> visited(1000, false); // Assuming vertex IDs are < 1000
    std::queue<int> queue;
    
    queue.push(startVertex);
    visited[startVertex] = true;
    
    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();
        result.push_back(current);
        
        if (adjacencyList.count(current)) {
            for (const auto& neighbor : adjacencyList.at(current)) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    queue.push(neighbor.first);
                }
            }
        }
    }
    
    return result;
}

void Graph::dfsHelper(int vertex, std::vector<int>& result, std::vector<bool>& visited) const {
    visited[vertex] = true;
    result.push_back(vertex);
    
    if (adjacencyList.count(vertex)) {
        for (const auto& neighbor : adjacencyList.at(vertex)) {
            if (!visited[neighbor.first]) {
                dfsHelper(neighbor.first, result, visited);
            }
        }
    }
}

std::vector<int> Graph::dfs(int startVertex) const {
    std::vector<int> result;
    if (!hasVertex(startVertex)) {
        return result;
    }
    
    std::vector<bool> visited(1000, false); // Assuming vertex IDs are < 1000
    dfsHelper(startVertex, result, visited);
    
    return result;
}

std::map<int, int> Graph::dijkstra(int startVertex) const {
    std::map<int, int> distances;
    if (!hasVertex(startVertex)) {
        return distances;
    }
    
    const int INF = std::numeric_limits<int>::max();
    
    // Initialize distances
    for (int vertex : vertices) {
        distances[vertex] = INF;
    }
    distances[startVertex] = 0;
    
    // Priority queue: (distance, vertex)
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, 
                        std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(0, startVertex));
    
    while (!pq.empty()) {
        int currentDist = pq.top().first;
        int currentVertex = pq.top().second;
        pq.pop();
        
        // Skip if we found a better path already
        if (currentDist > distances[currentVertex]) {
            continue;
        }
        
        // Explore neighbors
        if (adjacencyList.count(currentVertex)) {
            for (const auto& neighbor : adjacencyList.at(currentVertex)) {
                int nextVertex = neighbor.first;
                int weight = neighbor.second;
                int newDist = currentDist + weight;
                
                if (newDist < distances[nextVertex]) {
                    distances[nextVertex] = newDist;
                    pq.push(std::make_pair(newDist, nextVertex));
                }
            }
        }
    }
    
    return distances;
}

std::vector<std::vector<int>> Graph::floydWarshall() const {
    const int INF = std::numeric_limits<int>::max() / 2; // Avoid overflow
    int n = getVerticesCount();
    
    // Create distance matrix
    std::vector<std::vector<int>> dist(n, std::vector<int>(n, INF));
    
    // Map vertex ID to index
    std::map<int, int> vertexToIndex;
    std::map<int, int> indexToVertex;
    for (int i = 0; i < n; ++i) {
        vertexToIndex[vertices[i]] = i;
        indexToVertex[i] = vertices[i];
    }
    
    // Initialize diagonal
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
    }
    
    // Initialize with edge weights
    for (const auto& pair : adjacencyList) {
        int from = pair.first;
        for (const auto& neighbor : pair.second) {
            int to = neighbor.first;
            int weight = neighbor.second;
            dist[vertexToIndex[from]][vertexToIndex[to]] = weight;
        }
    }
    
    // Floyd-Warshall algorithm
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
    
    return dist;
}

void Graph::clear() {
    adjacencyList.clear();
    vertexLabels.clear();
    vertices.clear();
}
