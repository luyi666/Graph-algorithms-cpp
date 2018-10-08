//
// Created by luyi on 2018/10/3 0003.
//
#include "Graph.h"
/** return number of vertices */
int Graph::V() { return _num_v; }

/** return number of edges */
int Graph::E() { return _num_e; }

/** check if x and y are connected */
bool Graph::adjacent(int x, int y) {
    // in adjacent matrix not connected is represented by -1 on initialization
    return _matrix[x][y] == -1;
}

/**
 * get neighbors of vertex x
 * @param x
 * @return vector of ints
 */
vector<int> Graph::neighbors(int x) {
    vector<int> connected;
    for (int j = 0; j < _matrix[x].size(); j++) {
        if (_matrix[x][j] > -1)
            connected.push_back(j);
    }
    return connected;
}

/**
 * add edge between x and y if there is no edge
 * @param x
 * @param y
 * @param value
 */
void Graph::add_edge(int x, int y, float value) {
    if (_matrix[x][y] == -1) {
        set_edge_value(x, y, value);
        // increment number of edges by 1
        _num_e++;
    }
}

/**
 * delete an edge between x and y if existing
 * @param x
 * @param y
 */
void Graph::del_edge(int x, int y) {
    if (_matrix[x][y] != -1) {
        set_edge_value(x, y, -1);
        _num_e--;
    }
}

/** get edge value */
float Graph::get_edge_value(int x, int y) {
    return _matrix[x][y];
}
/** set edge value */
void Graph::set_edge_value(int x, int y, float value) {
    _matrix[x][y] = value;
    _matrix[y][x] = value;
}

/**
 * random graph constructor
 * @param num_v number of vertices
 * @param density connection probability
 * @param min_cost min cost of an edge
 * @param max_cost max cost of an edge
 */
Graph::Graph(int num_v, float density, float min_cost, float max_cost) {
    _num_v = num_v;
    _density = density;
    // initialize the graph with -1
    _matrix = std::vector<std::vector<float>>(_num_v, std::vector<float>(_num_v, -1));
    _min_cost = min_cost;
    _max_cost = max_cost;
    // set density distribution and edge cost distribution
    uniform_real_distribution<float> density_dist(0, 1);
    uniform_real_distribution<float> cost_dist(_min_cost, _max_cost);
    for (int i = 0; i < _num_v; i++) {
        for (int j = i + 1; j < _num_v; j++) {
            if (density_dist(_eng) < _density) {
                add_edge(i, j, cost_dist(_eng));
            }
        }
    }
}

/**
 * overload << operator to print the graph details
 * @param os
 * @param g
 * @return ostream of message
 */
ostream &operator<<(ostream &os, Graph &g) {
    os << "Graph details: " << endl;
    os << "number of vertices: " << g.V() << endl;
    os << "number of edges: " << g.E() << endl;
    os << "connectivity matrix: " << endl;
    for (const auto &row: g._matrix) {
        for (float i : row) {
            os << i << "\t";
        }
        os << endl;
    }
    return os;
}

/**
 * check if two vertices are connected
 * @param i
 * @param j
 * @return boolean
 */
bool Graph::is_connected(int i, int j) {
    // create an open set and closed set
    vector<bool> open(_num_v, false);
    vector<bool> closed(_num_v, false);
    int closed_size = 0;
    int old_size = 0;
    // move the starting vertex to the open set
    open[i] = true;
    // if there is vertex that has not been closed move on
    while (closed_size < _num_v) {
        for (int i = 0; i < _num_v; i++) {
            old_size = closed_size;
            // if vertex i is open close it
            if (open[i] && !closed[i]) {
                closed[i] = true;
                open[i] = false;
                closed_size++;
            }
            // after vertex i is closed, we add new vertex j to open set from i to j
            for (int j = 0; j < _num_v; j++) {
                open[j] = _matrix[i][j] != -1 || open[j];
            }
        }
        // if the closed set size does not change, check if j is in the closed set
        if (old_size == closed_size) {
            return closed[j];
        }
    }
    // if all vertices are in closed set, then j must be connected
    return true;
}

/**
 * read a graph from an input file
 * @param filename
 */
Graph::Graph(string filename) {
    string line;
    ifstream myfile(filename);
    getline(myfile, line);
    _num_v = static_cast<unsigned int>(stoi(line));
    _matrix = std::vector<vector<float>>(_num_v, vector<float>(_num_v, -1));
    // use regexp to read digits
    const regex r("(\\d+)\\s+(\\d+)\\s+(\\d*\\.?\\d+)");
    match_results<string::iterator> sm;
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            if (regex_search(line.begin(), line.end(), sm, r)) {
                unsigned int src =  static_cast<unsigned int>(stoi(sm[1]));
                unsigned int dst =  static_cast<unsigned int>(stoi(sm[2]));
                float value =  stof(sm[3]);
                _matrix[src][dst] = value;
            }
        }
        myfile.close();
    }
    for (int i=0; i<_num_v; i++) {
        for (int j=i+1; j<_num_v; j++) {
            if (_matrix[i][j] != -1)
                _num_e++;
        }
    }
}