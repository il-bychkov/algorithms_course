#include <iostream>
#include <vector>
#include <limits>

class Graph {
public:
    Graph(const int64_t& size) : num_vertices_(size) {}

    void addEdge(const int64_t& vertex1, const int64_t& vertex2, const int64_t& weight) {
        edges_.push_back({weight, {vertex1, vertex2}});
        edges_.push_back({weight, {vertex2, vertex1}});
    }

    void primMST() {
        std::vector<int64_t> parent(num_vertices_, 0);
        std::vector<int64_t> key(num_vertices_, std::numeric_limits<int64_t>::max());
        std::vector<bool> visited(num_vertices_, false);

        key[0] = 0;
        parent[0] = -1;

        for (int64_t count = 0; count < num_vertices_ - 1; count++) {
            
            // Pick the minimum key vertex from the
            // set of vertices not yet included in MST
            int64_t min_key_vertex = minKey(key, visited);

            visited[min_key_vertex] = true;

            // Update key value and parent index of
            // the adjacent vertices of the picked vertex.
            // Consider only those vertices which are not
            // yet included in MST
            for (int64_t i = 0; i < edges_.size(); i++) {
                
                int64_t vertex = -1;
                if (edges_[i].second.first == min_key_vertex)
                    vertex = edges_[i].second.second;
                else if (edges_[i].second.second == min_key_vertex)
                    vertex = edges_[i].second.first;

                // Vertex is not -1 only if min key vertex has adjacent vertex
                // Visited is false for vertices not yet included in MST
                // Update the key only if weight of edge is smaller than key[vertex]
                if (vertex != -1 && !visited[vertex] && edges_[i].first < key[vertex]) {
                    parent[vertex] = min_key_vertex;
                    key[vertex] = edges_[i].first;
                }
            }
        }

        // Output
        std::cout << "Prim’s algorithm" << std::endl;
        int64_t sum_mst = 0;
        std::cout << "Edge \tWeight\n";
        for (int64_t i = 1; i < num_vertices_; i++) {
            std::cout << parent[i] << " - " << i << " \t" << key[i] << std::endl;
            sum_mst += key[i];
        }
        std::cout << "Total weight: " << sum_mst << std::endl;
    }

private:
    int64_t num_vertices_;
    std::vector<std::pair<int64_t, std::pair<int64_t, int64_t>>> edges_;

    int64_t minKey(const std::vector<int64_t>& key, const std::vector<bool>& visited) {
        int64_t min = std::numeric_limits<int64_t>::max(), min_index;

        for (int64_t i = 0; i < num_vertices_; i++) {
            if (visited[i] == false && key[i] < min) {
                min = key[i];
                min_index = i;
            }
        }

        return min_index;
    }
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

	graph.primMST();

	return 0;
}
