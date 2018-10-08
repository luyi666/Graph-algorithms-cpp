//
// Created by luyi on 2018/10/2 0002.
//
#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;
#ifndef DIJKSTRA_PRIORITYQUEUE_H
#define DIJKSTRA_PRIORITYQUEUE_H

/**
 * class representing a min heap
 * @tparam T class of vertex type (e.g. string, int...)
 */
template<class T>
class PriorityQueue {
private:
    vector<pair<T, float>> _queue;  // queue element with its content and value as a pair
    unordered_map<T, float> _dict;  // return queue element by element content
    void swap(int i, int j);    // swap node in the tree
    void bubble_up(int i);      // call bubble up when a new element is added
    void bubble_down(int i);    // call bubble down when an element is retrieved from the top
public:
    /** initialing from a vector of key value pair */
    PriorityQueue(vector<pair<T, float>> &queue);

    /** default initializer */
    PriorityQueue();

    /** change priority of a particular node */
    void chgPrioirity(T node, float priority);

    /** check if a node is in the queue */
    bool contains(T node);

    /** get value of a node */
    float get_value(T node);

    /** insert a new node with its priority */
    void insert(T node, float priority);

    /** retrieve a node from top of the tree */
    pair<T, float> top();

    /** return the size of the heap */
    int size();

    /** print the queue with its detailed info */
    friend ostream &operator<<(ostream &os, PriorityQueue<T> &pq) {
        os << "print the priority queue in order: ";
        while (pq.size() > 0) {
            auto x = pq.top();
            os << x.first << " " << x.second << " ";
        }
        os << endl;
        return os;
    }

    /** clear the queue */
    void clear();
};

#endif //DIJKSTRA_PRIORITYQUEUE_H
