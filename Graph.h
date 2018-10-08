//
// Created by luyi on 2018/10/3 0003.
//
#include <vector>
#include <random>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;
#ifndef DIJKSTRA_GRAPH_H
#define DIJKSTRA_GRAPH_H

/**
 * Graph class to represent a random graph
 */
class Graph {
private:
    unsigned int _num_v = 0;    // number of vertices
    unsigned int _num_e = 0;    // number of edges
    float _density = -1;    // density
    float _min_cost;    // min cost of an edge
    float _max_cost;    // max cost of an edge
    mt19937 _eng;   // random generator
    vector<vector<float>> _matrix;  // adjacent matrix representation

public:
    /** return _num_v */
    int V();

    /** return _num_e */
    int E();

    /** is vertex x connected to y */
    bool adjacent(int x, int y);

    /** list neighbors of vertex x */
    vector<int> neighbors(int x);

    /** add an edge with cost value from x to y */
    void add_edge(int x, int y, float value);

    /** delete edge from x to y */
    void del_edge(int x, int y);

    /** get edge value from x to y */
    float get_edge_value(int x, int y);

    /** set edge value from x to y */
    void set_edge_value(int x, int y, float value);

    /** initialize graph by number of vertices and connection probability, edge cost initialization is optional */
    Graph(int num_v, float density, float min_cost = 1.0, float max_cost = 10.0);

    /** load a graph from a given file */
    Graph(string filename);

    /** print a graph by friend funtion */
    friend ostream &operator<<(ostream &os, Graph &g);

    /** check if there is a path from i to j which connects them */
    bool is_connected(int i, int j);
};

#endif //DIJKSTRA_GRAPH_H
