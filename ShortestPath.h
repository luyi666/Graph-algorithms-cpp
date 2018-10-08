//
// Created by luyi on 2018/10/3 0003.
//

#ifndef DIJKSTRA_SHORTESTPATH_H
#define DIJKSTRA_SHORTESTPATH_H

#include <unordered_map>
#include "Graph.h"
#include "PriorityQueue.h"

/**
 * class doing dijkstra algorithm
 */
class ShortestPath {
private:
    Graph _g;   // graph
    PriorityQueue<int> _openset;    // openset is a min heap
    unordered_map<int, int> _traceback; // traceback to show every step from source to destination
    unordered_map<int, float> _cost;    // path cost
    void expand(int s, float cost_2_s); // expand from a closed vertex and add new vertices to openset
    void get_path(int s, int d);    // run dijkstra from s to d
    string get_trace(int s, int d); // show trace from s to d
    float get_cost(int s, int d);   // show cost from s to d

public:
    /** shortest path trace from s to d */
    string path(int s, int d);

    /** shortest path cost from s to d */
    float path_size(int s, int d);

    /** show shortest path cost with its trace from s to d*/
    void info(int s, int d);

    /** initialize dijkstra on a graph g */
    ShortestPath(Graph g);
};

#endif //DIJKSTRA_SHORTESTPATH_H
