#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include <chrono>

std::pair<std::unordered_map<int, double>, std::unordered_map<int, int>> dijkstra(
    const std::unordered_map<int, std::vector<std::pair<int, double>>>& graph,
    int start) {

    double INF = std::numeric_limits<double>::infinity();

    std::unordered_map<int, double> distances;
    std::unordered_map<int, int> previous;
    for (const auto& entry : graph) {
        distances[entry.first] = INF;
        previous[entry.first]  = -1;
    }
    distances[start] = 0.0;

    std::priority_queue<
        std::pair<double, int>,
        std::vector<std::pair<double, int>>,
        std::greater<std::pair<double, int>>> heap;
    heap.emplace(0.0, start);

    while (!heap.empty()) {
        auto [dist_u, u] = heap.top();
        heap.pop();

        if (dist_u > distances[u]) {
            continue;
        }

        for (const auto& edge : graph.at(u)) {
            int v        = edge.first;
            double w     = edge.second;
            double alt   = dist_u + w;
            if (alt < distances[v]) {
                distances[v] = alt;
                previous[v]  = u;
                heap.emplace(alt, v);
            }
        }
    }

    return {distances, previous};
}

// Reconstructs the shortest path from start to target using the 'previous' map.
// 'previous' maps each node to its predecessor (or -1 if none).
// Returns a vector of nodes from start to target, or empty if no path exists.
std::vector<int> reconstruct_path(
    const std::unordered_map<int, int>& previous,
    int start,
    int target) {

    std::vector<int> path;
    int node = target;

    // Walk backwards from target to start
    while (node != -1) {
        path.push_back(node);
        if (node == start) {
            break;
        }
        auto it = previous.find(node);
        if (it == previous.end()) {
            // No predecessor information, abort
            path.clear();
            return path;
        }
        node = it->second;
    }

    // Reverse to get path from start → target
    std::reverse(path.begin(), path.end());

    // Verify that path actually begins with start
    if (!path.empty() && path.front() == start) {
        return path;
    } else {
        return {};  // no valid path
    }
}

// Reads a CSV file with columns: Source,Destination,Weight
// and builds an adjacency‑list graph.
// If you need an undirected graph, uncomment the second push_back.
std::unordered_map<int, std::vector<std::pair<int, double>>>
read_graph_from_csv(const std::string& filename) {
    std::unordered_map<int, std::vector<std::pair<int, double>>> graph;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << filename << "\n";
        return graph;
    }

    std::string line;
    // Read and discard header
    if (!std::getline(file, line)) {
        std::cerr << "Error: file is empty\n";
        return graph;
    }

    // Each subsequent line: Source,Destination,Weight
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        int source;
        int destination;
        double weight;

        // Parse Source
        if (!std::getline(ss, token, ',')) continue;
        source = std::stoi(token);

        // Parse Destination
        if (!std::getline(ss, token, ',')) continue;
        destination = std::stoi(token);

        // Parse Weight
        if (!std::getline(ss, token, ',')) continue;
        weight = std::stod(token);

        // Add the directed edge source → destination
        graph[source].push_back(std::make_pair(destination, weight));
    }

    file.close();
    return graph;
}

int main() {
    const std::string filename = "/Users/benjaminlang/Documents/School/Spring 25/DSA-Project-3---Nanjing-Navigator-3000-/Nanjing_distances.csv";
    auto graph = read_graph_from_csv(filename);

    int startNode = 0;
    auto t_start = std::chrono::high_resolution_clock::now();
    auto result  = dijkstra(graph, startNode);
    auto t_end   = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = t_end - t_start;
    std::cout << "Dijkstra run time: " << elapsed.count() << " ms\n";

    auto distances = result.first;
    auto previous  = result.second;

    int targetNode = 90089;
    std::vector<int> shortestPath = reconstruct_path(previous, startNode, targetNode);

    std::cout << "The path is of length: " << (size(shortestPath)) << std::endl;

    if (!shortestPath.empty()) {
        std::cout << "Shortest path: ";
        for (int u : shortestPath) {
            std::cout << u << " ";
        }
        std::cout << "\n";
    } else {
        std::cout << "No path from " << startNode << " to " << targetNode << "\n";
    }
    return 0;
}
