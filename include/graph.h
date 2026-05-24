#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <string>
#include <limits>
#include <algorithm>
#include <QString>

class Graph {
public:
    Graph();
    
    // Add vertex
    void addVertex(int id, const QString& label);
    
    // Add edge (directed by default)
    void addEdge(int from, int to, int weight = 1, bool directed = false);
    
    // Remove vertex
    void removeVertex(int id);
    
    // Remove edge
    void removeEdge(int from, int to);
    
    // Get vertices count
    int getVerticesCount() const;
    
    // Get edges count
    int getEdgesCount() const;
    
    // Check if vertex exists
    bool hasVertex(int id) const;
    
    // Check if edge exists
    bool hasEdge(int from, int to) const;
    
    // Get all vertices
    std::vector<int> getAllVertices() const;
    
    // Get neighbors of a vertex
    std::vector<std::pair<int, int>> getNeighbors(int vertexId) const;
    
    // BFS traversal
    std::vector<int> bfs(int startVertex) const;
    
    // DFS traversal
    std::vector<int> dfs(int startVertex) const;
    
    // Dijkstra's algorithm
    std::map<int, int> dijkstra(int startVertex) const;
    
    // Floyd-Warshall algorithm
    std::vector<std::vector<int>> floydWarshall() const;
    
    // Clear graph
    void clear();
    
private:
    // Adjacency list: vertex -> list of (neighbor, weight)
    std::map<int, std::vector<std::pair<int, int>>> adjacencyList;
    
    // Vertex labels
    std::map<int, QString> vertexLabels;
    
    // All vertices
    std::vector<int> vertices;
    
    // Helper for DFS
    void dfsHelper(int vertex, std::vector<int>& result, std::vector<bool>& visited) const;
};

#endif // GRAPH_H
