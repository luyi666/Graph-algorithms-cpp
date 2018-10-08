//
// Created by luyi on 2018/10/2 0002.
//
#include "PriorityQueue.h"

template<class T>
/**
 * changes the priority of the node and update its position if necessary
 * @tparam T node type
 * @param node
 * @param priority
 */
void PriorityQueue<T>::chgPrioirity(T node, float priority) {
    _dict.at(node) = priority;
    for (int i = 0; i < size(); i++) {
        if (_queue.at(i).first == node) {
            auto old_priority = _queue.at(i).second;
            _queue.at(i).second = priority;
            // if the new priority is lower, go up (as a min heap)
            if (old_priority > priority) {
                bubble_up(i);
            }
                // if the new priority is higher, go down
            else {
                bubble_down(i);
            }
        }
    }
}

template<class T>
/**
 * if the heap contains an element
 * @tparam T
 * @param node
 * @return boolean
 */
bool PriorityQueue<T>::contains(T node) {
    return _dict.find(node) != _dict.end();
}

template<class T>
/**
 * get priority of a given node
 * @tparam T
 * @param node
 * @return priority
 */
float PriorityQueue<T>::get_value(T node) {
    return _dict.at(node);
}

template<class T>
/**
 * insert a new node to the tree
 * @tparam T
 * @param node
 * @param priority
 */
void PriorityQueue<T>::insert(T node, float priority) {
    _dict.insert({node, priority});
    _queue.push_back(make_pair(node, priority));
    // call bubble up to maintain heap structure
    bubble_up(size() - 1);
}

template<class T>
/**
 * retrieve the top element
 * @tparam T
 * @return top element with min priority
 */
pair<T, float> PriorityQueue<T>::top() {
    auto ele = _queue.at(0);
    _queue.at(0) = _queue.at(size() - 1);
    _queue.pop_back();
    _dict.erase(ele.first);
    bubble_down(0);
    return ele;
}

template<class T>
/**
 *
 * @tparam T
 * @return size of the queue
 */
int PriorityQueue<T>::size() {
    return _queue.size();
}

template<class T>
/** default constructor */
PriorityQueue<T>::PriorityQueue() {
}

template<class T>
/**
 * construct from a given vector
 * @tparam T
 * @param queue
 */
PriorityQueue<T>::PriorityQueue(vector<pair<T, float>> &queue) : _queue(queue) {
    // bubble down all the nodes except the leaf nodes
    for (int i = static_cast<int> (size() / 2); i >= 0; i--) {
        bubble_down(i);
    }
    // maintain a fast accessible dict
    for (const auto &x: _queue) {
        _dict.insert({x.first, x.second});
    }
}

template<class T>
/**
 * swap position of i and j
 * @tparam T
 * @param i
 * @param j
 */
void PriorityQueue<T>::swap(int i, int j) {
    auto temp = _queue.at(i);
    _queue.at(i) = _queue.at(j);
    _queue.at(j) = temp;
}

template<class T>
/**
 * bubble down node i
 * @tparam T
 * @param i index of node
 */
void PriorityQueue<T>::bubble_down(int i) {
    int min_id = i;
    int left_id = i * 2 + 1;
    int right_id = i * 2 + 2;
    // compare node i with its children
    if (left_id < size() && _queue.at(left_id).second < _queue.at(min_id).second) {
        min_id = left_id;
    }
    if (right_id < size() && _queue.at(right_id).second < _queue.at(min_id).second) {
        min_id = right_id;
    }
    // swap with one of the children with lower priority
    if (min_id != i) {
        swap(i, min_id);
        // recursively bubble it down
        bubble_down(min_id);
    }
}

template<class T>
/**
 * bubble up node i
 * @tparam T
 * @param i index of node
 */
void PriorityQueue<T>::bubble_up(int i) {
    // return if it is already on the top
    if (i == 0)
        return;
    // get parent index of node i
    int p_id = static_cast<int> (i - 1) / 2;
    // if a parent priority is greater, then bubble i up to maintain a min heap
    if (_queue.at(i).second < _queue.at(p_id).second) {
        // swap bubble i with its parent
        swap(i, p_id);
        // recursively the original bubble i up
        bubble_up(p_id);
    }
}

template<class T>
/**
 * clear the queue
 * @tparam T
 */
void PriorityQueue<T>::clear() {
    _queue.clear();
    _dict.clear();
}

// predefine some useful tempalte class
template
class PriorityQueue<int>;

template
class PriorityQueue<string>;
