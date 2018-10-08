#include "PriorityQueue.h"
#include "Graph.h"
#include "ShortestPath.h"
#include "Prim.h"
#include <chrono>

/**
 * test for class PriorityQueue, Graph and ShortestPath
 */
void test() {
    // initialize an empty pq
    PriorityQueue<string> pq;
    pq.insert("a", 1);
    pq.insert("b", 0);
    pq.insert("c", 3);
    pq.chgPrioirity("b", 4);
    pq.insert("e", -1);
    cout << pq;
    vector<pair<string, float>> v = {{"a", 1},
                                     {"b", 0},
                                     {"c", 3},
                                     {"e", -1}};
    // initialize pq from an input vector
    PriorityQueue<string> pq2 = PriorityQueue<string>(v);
    pq2.chgPrioirity("b", 4);
    cout << pq2;

    // initialize a random graph by giving number of vertices and connection probability
    Graph g = Graph(10, 0.5);
    cout << g << endl;

    // initialize ShortestPath from a graph
    ShortestPath dijkstra(g);
    // get shortest path from vertex 0 to vertex 2
    cout << dijkstra.path(0, 2) << endl;
}

/**
 * calculate the average path cost from vertex 0 to other vertices in a given graph
 */
float avg_cost(Graph g) {
    float distance = 0;
    int num_path = 0;
    ShortestPath dijkstra(g);
    for (int i = 1; i < g.V(); i++) {
        // get path cost from vertex 0 to i
        float path_size_i = dijkstra.path_size(0, i);
        // take account only for vertices where the path exits, i.e. cost is greater than 0
        if (path_size_i > 0) {
            distance += path_size_i;
            num_path += 1;
        }
    }
    return distance / num_path;
}


int main() {
    // load test graph for dijkstra algorithm
    Graph test0 = Graph("./shortest_path_test_graph.txt");
    ShortestPath dijkstra_test(test0);
    cout << test0;
    // test case from 0 to 5. It should print 0->2->3->5 with path cost 26
    dijkstra_test.info(0, 5);

    // timing for efficiency
    auto t1 = std::chrono::high_resolution_clock::now();
    int num_v = 50;
    float density = 0.2;
    Graph g = Graph(num_v, density);
    cout << "number of nodes: " << num_v << " density: " << density << " avg cost: " << avg_cost(g) << endl;
    density = 0.4;
    Graph g2 = Graph(num_v, density);
    cout << "number of nodes: " << num_v << " density: " << density << " avg cost: " << avg_cost(g2) << endl;
    auto t2 = std::chrono::high_resolution_clock::now();
    // timing for speed
    cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " miliseconds elapsed..." << endl;
    Graph g3 = Graph("./mst_test_graph.txt");
    cout << g3;
    Prim MST(g3);
    cout << "MST cost for the test file is " << MST.mst() << endl;
}