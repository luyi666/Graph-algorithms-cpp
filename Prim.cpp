//
// Created by luyi on 2018/10/4 0004.
//
#include "Prim.h"

/**
 * add or update outgoing edges from s to its neighbors
 * @param s vertex s to expand
 */
void Prim::expand(int s) {
    vector<int> neigh = _g.neighbors(s);
    // iterate neighbors of vertex s
    for (auto x: neigh) {
        // if this neighbor is in the closed set then done
        if (_closedset.find(x) != _closedset.end()) {
            continue;
        }
        float local_cost = _g.get_edge_value(s, x);
        // if neighbor not in openset add it
        if (!_openset.contains(x)) {
            _openset.insert(x, local_cost);
        } else {
            // if this neighbor is in openset but has less cost update it
            if (_openset.contains(x) && _openset.get_value(x) > local_cost) {
                _openset.chgPrioirity(x, local_cost);
            }
        }
    }
}

/**
 *
 * @return cost of minimum spanning tree
 */
float Prim::mst() {
    // clear cached results
    _closedset.clear();
    _openset.clear();
    float cost = 0;
    // assume we start from node 0
    int s = 0;
    // starting point is already included in the closed set
    _closedset.insert(s);
    // add vertices originating from vertex 0
    expand(s);
    while (_openset.size() > 0) {
        // get the edge with least cost
        auto to_close = _openset.top();
        s = to_close.first;
        // add the new vertex s to the closed set
        _closedset.insert(s);
        // update MST cost
        cost += to_close.second;
        //expand the new vertex
        expand(s);
    }
    return cost;
}

/**
 * initializer for prim's algorithm
 * @param g input graph
 */
Prim::Prim(Graph g) : _g(g) {}