#include <iostream>
#include <vector>

class DSU {
 public:
    DSU(const int64_t& size) : parent_(size, -1), rank_(size, 0) {}

    int64_t find(const int64_t& v) {
        if (parent_[v] == -1) return v;
        return parent_[v] = find(parent_[v]);
    }

    void Union(const int64_t& x, const int64_t& y) {
        int64_t s1 = find(x);
        int64_t s2 = find(y);

        if (s1 != s2) {
            if (rank_[s1] < rank_[s2]) {
                parent_[s1] = s2;
            }
            else if (rank_[s1] > rank_[s2]) {
                parent_[s2] = s1;
            }
            else {
                parent_[s2] = s1;
                rank_[s1] += 1;
            }
        }
    }

 private:
    std::vector<int64_t> parent_;
    std::vector<int64_t> rank_;
};

class Graph {
 public:
    Graph(const int64_t& size) : num_vertices_(size) {}

    void addEdge(const int64_t& vertex1, const int64_t& vertex2, const int64_t& weight) {
        edges_.push_back({weight, {vertex1, vertex2}});
    }

    void kruskalMST() {
        DSU dsu(num_vertices_);
        int64_t cost = 0;

        // Sort all edges 
        std::sort(edges_.begin(), edges_.end());

        std::cout << "Kruskal’s algorithm" << std::endl;
        for (const auto& edge : edges_) {
            int64_t weight = edge.first;
            int64_t vertex_from = edge.second.first;
            int64_t vertex_to = edge.second.second;
            
            // Take this edge in MST if it does 
            // not forms a cycle
            if (dsu.find(vertex_from) != dsu.find(vertex_to)) {
                std::cout << vertex_from << " - " << vertex_to << " \t" << weight << std::endl;
                dsu.Union(vertex_from, vertex_to);
                cost += weight;
            }
        }
        // Output the total weight of MST
        std::cout << "Total weight: " << cost << std::endl;
    }

 private:
    int64_t num_vertices_;
    std::vector<std::pair<int64_t, std::pair<int64_t, int64_t>>> edges_;
};

int main() {
    Graph graph(6);

    graph.addEdge(0, 1, 7);
    graph.addEdge(0, 2, 8);
    graph.addEdge(1, 2, 11);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 3, 6);
    graph.addEdge(2, 4, 9);
    graph.addEdge(3, 4, 11);
    graph.addEdge(3, 5, 9);
    graph.addEdge(4, 5, 10);

    graph.kruskalMST();

    return 0;
}
