//
// Created by luyi on 2018/10/3 0003.
//
#include "ShortestPath.h"

/**
 * add or update openset by expanding a closed vertex
 * @param s vertex to be expanded
 * @param cost_2_s  min cost to node s
 */
void ShortestPath::expand(int s, float cost_2_s) {
    vector<int> neigh = _g.neighbors(s);
    // expand by neighbors of s
    for (auto x: neigh) {
        // if this neighbor is in the closed set then done
        if (_cost.find(x) != _cost.end()) {
            continue;
        }
        // total cost equals path cost from s to x + current cost to s
        float path_cost = _g.get_edge_value(s, x) + cost_2_s;
        // if neighbor not in openset add it
        if (!_openset.contains(x)) {
            _openset.insert(x, path_cost);
            _traceback[x] = s;
        }
            // if neighbor in openset and has less cost by expanding current vertex s, update it
        else {
            if (_openset.get_value(x) > path_cost) {
                _openset.chgPrioirity(x, path_cost);
                _traceback[x] = s;
            }
        }
    }
}

/**
 * do dijkstra algorithm from s to d
 *
 * @param s source vertex
 * @param d destination vertex
 */
void ShortestPath::get_path(int s, int d) {
    // clear cached result from last evaluation
    _traceback.clear();
    _cost.clear();
    _openset.clear();

    // start from s with min cost s->s=0
    expand(s, 0);

    while (_openset.size() > 0) {
        // retrieve edge with min cost
        auto ele = _openset.top();
        _cost[ele.first] = ele.second;
        // return if d is retrieved and happens to have min cost
        if (ele.first == d) {
            return;
        }
        // start next iteration from the retrieved vertex
        s = ele.first;
        expand(s, ele.second);
    }
}

/**
 * get path size from s to d
 * @param s source vertex
 * @param d destination vertex
 * @return shortest path
 */
float ShortestPath::path_size(int s, int d) {
    get_path(s, d);
    return get_cost(s, d);
}

/**
 * get path trace from s to d
 * @param s source vertex
 * @param d destination vertex
 * @return trace of shortest path
 */
string ShortestPath::path(int s, int d) {
    get_path(s, d);
    return get_trace(s, d);
}

/**
 * helper function to get shortest path trace
 * @param s source vertex
 * @param d destination vertex
 * @return trace of shortest path
 */
string ShortestPath::get_trace(int s, int d) {
    vector<int> path;
    int temp = d;
    // path exists only if s and d are connected
    if (_cost.find(d) != _cost.end()) {
        // trace back
        while (temp != s) {
            path.push_back(temp);
            temp = _traceback[temp];
        }
        path.push_back(s);
        reverse(path.begin(), path.end());
        string result;
        for (auto x: path) {
            if (x == d)
                result += to_string(x);
            else
                result += to_string(x) + "->";
        }
        return result;
    }
    // return "not connected" if d is reachable from s
    return "not connected";
}

/**
 *
 * @param s source vertex
 * @param d destination vertex
 * @return shortest path cost from s to d, if s and d are not connected return -1
 */
float ShortestPath::get_cost(int s, int d) {
    if (_cost.find(d) != _cost.end()) {
        return _cost[d];
    }
    return -1;
}

/**
 * path info from s to d for testing purpose
 * @param s source vertex
 * @param d destination vertex
 */
void ShortestPath::info(int s, int d) {
    get_path(s, d);
    cout << "the shortest path from " << s << " to " << d << " is " << get_cost(s, d) << endl;
    cout << "path trace as: " << get_trace(s, d) << endl;
}

/**
 * algorithm initializer
 * @param g input graph g
 */
ShortestPath::ShortestPath(Graph g) : _g(g) {}