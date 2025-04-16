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

std::vector<int> reconstruct_path(
    const std::unordered_map<int, int>& previous,
    int start,
    int target) {

    std::vector<int> path;
    int node = target;

    while (node != -1) {
        path.push_back(node);
        if (node == start) {
            break;
        }
        auto it = previous.find(node);
        if (it == previous.end()) {
            path.clear();
            return path;
        }
        node = it->second;
    }

    std::reverse(path.begin(), path.end());

    if (!path.empty() && path.front() == start) {
        return path;
    } else {
        return {};
    }
}

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

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;
        int source;
        int destination;
        double weight;

        if (!std::getline(ss, token, ',')) continue;
        source = std::stoi(token);

        if (!std::getline(ss, token, ',')) continue;
        destination = std::stoi(token);

        if (!std::getline(ss, token, ',')) continue;
        weight = std::stod(token);

        graph[source].push_back(std::make_pair(destination, weight));
    }

    file.close();
    return graph;
}

int main() {
    const std::string filename = "/Users/benjaminlang/Documents/School/Spring 25/DSA-Project-3---Nanjing-Navigator-3000-/Nanjing_distances.csv";
    auto graph = read_graph_from_csv(filename);

    std::chrono::duration<double, std::milli> total_time_ms{0.0};
    int num_calls = 0;

    for (int i = 1; i <= 10; ++i) {
        int source = i;
        auto t0 = std::chrono::high_resolution_clock::now();
        dijkstra(graph, source);
        auto t1 = std::chrono::high_resolution_clock::now();
        total_time_ms += (t1 - t0);
        ++num_calls;
    }

    double total_ms  = total_time_ms.count();
    double avg_ms    = total_ms / num_calls;
    double total_sec = total_ms / 1000.0;

    std::cout << "=== Performance Comparison ===\n"
              << "Dijkstra's Algorithm: " << num_calls << " calls\n"
              << std::fixed << std::setprecision(3)
              << "  Total time: "   << total_ms  << " ms (" << total_sec << " s)\n"
              << "  Average: "      << avg_ms    << " ms/call\n";

    // int startNode = 0;
    // auto t_start = std::chrono::high_resolution_clock::now();
    // auto result  = dijkstra(graph, startNode);
    // auto t_end   = std::chrono::high_resolution_clock::now();
    //
    // std::chrono::duration<double, std::milli> elapsed = t_end - t_start;
    // std::cout << "Dijkstra run time: " << elapsed.count() << " ms\n";
    //
    // auto distances = result.first;
    // auto previous  = result.second;
    //
    // int targetNode = 90089;
    // std::vector<int> shortestPath = reconstruct_path(previous, startNode, targetNode);
    //
    // std::cout << "The path is of length: " << (size(shortestPath)) << std::endl;
    //
    // if (!shortestPath.empty()) {
    //     std::cout << "Shortest path: ";
    //     for (int u : shortestPath) {
    //         std::cout << u << " ";
    //     }
    //     std::cout << "\n";
    // } else {
    //     std::cout << "No path from " << startNode << " to " << targetNode << "\n";
    // }
    return 0;
}
