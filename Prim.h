//
// Created by luyi on 2018/10/4 0004.
//
#include "PriorityQueue.h"
#include "Graph.h"
#include <set>
#ifndef DIJKSTRA_PRIM_H
#define DIJKSTRA_PRIM_H
using namespace std;
/**
 * class doing Prim's algorithm
 */
class Prim {
private:
    Graph _g;
    PriorityQueue<int> _openset;    // vertex with its edges stored in a min heap
    set<int> _closedset;    // vertices that have been chosen
    void expand(int s); // expand a vertex s by adding its outgoing edges to openset

public:
    /** get mininum spanning tree cost */
    float mst();
    /** initialize by graph g */
    Prim(Graph g);
};
#endif //DIJKSTRA_PRIM_H
