/* Graph.h 
contains definitions and implemenetations for graph
*/
#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
#include <optional>

template <class T, class D>
class Graph {
public:
    // default constructor
    Graph();

    // destructor
    ~Graph() = default;

    // create node
    void AddNode(T id, D data);

    // remove node
    std::optional<D> RemoveNode(T id);

    // add an edge from one node to another
    bool AddEdge(T fromId, T toId);

    // get node data
    std::optional<D> GetData(T id);

    // returns a vector of the neighbors of a node
    std::optional<std::vector<T>> GetNeighbors(T id);

    // get size
    std::size_t GetSize();

    // is empty
    bool IsEmpty();

    // print
    void Print();

private:
    struct Node {
        T m_id;
        D m_data;
        std::vector<Node*> m_neighbors; // directed edges only

        Node(T id, D data) : m_id(id), m_data(data) {}
    };

    std::size_t m_size;
    std::vector<std::unique_ptr<Node>> m_nodes;
    std::unordered_map<T, Node*> m_nodeLookup; // O(1) access time - raw* because 
};

// constructor
template<class T, class D>
Graph<T, D>::Graph() : m_size(0) {}


template <class T, class D>
void Graph<T, D>::AddNode(T id, D data) {
    std::unique_ptr<Node> newNode = std::make_unique<Node>(id, data);
    m_nodeLookup[id] = newNode.get(); // .get() returns a raw* to an object- m_nodeLookup stores Node*
    m_nodes.push_back(std::move(newNode)); // std::move to transfer ownership of the pointer
    m_size++;
}

template <class T, class D>
std::optional<D> Graph<T, D>::RemoveNode(T id) {
    auto it = m_nodeLookup.find(id);
    if(it == m_nodeLookup.end()) {
        return std::nullopt;
    }

    std::optional<D> data = GetData(id);
    m_nodeLookup.erase(it);

    for(std::size_t i = 0; i < m_nodes.size(); ++i) {
        std::vector<Node*>& neighbors = m_nodes.at(i)->m_neighbors;
        for(std::size_t j = 0; j < neighbors.size(); ++j) {
            if(neighbors.at(j)->m_id == id) {
                neighbors.erase(neighbors.begin() + j);
                --j; // prevent skipping
            }
        }

        if(m_nodes.at(i)->m_id == id) {
            m_nodes.erase(m_nodes.begin() + i);
            --i;
        }
    }

    m_size--;
    return data;
}

template <class T, class D>
bool Graph<T, D>::AddEdge(T fromId, T toId) {
    auto it1 = m_nodeLookup.find(fromId);
    auto it2 = m_nodeLookup.find(toId);

    if(it1 == m_nodeLookup.end() || it2 == m_nodeLookup.end() || m_size < 2) {
        return false;
    }

    Node* fromNode = it1->second;
    Node* toNode = it2->second;

    // prevent duplicate edges in the same direction
    for(std::size_t i = 0; i < fromNode->m_neighbors.size(); ++i) {
        if(fromNode->m_neighbors.at(i)->m_id == toId) {
            return false;
        }
    }
    fromNode->m_neighbors.push_back(toId);
    return true;
}

template <class T, class D>
std::optional<D> Graph<T, D>::GetData(T id) {
    auto it = m_nodeLookup.find(id);
    if(it == m_nodeLookup.end()) {
        return std::nullopt;
    }
    return it->second->m_data;
}

template <class T, class D>
std::optional<std::vector<T>> Graph<T, D>::GetNeighbors(T id) {
    std::vector<T> neighbors;
    auto it = m_nodeLookup.find(id);
    if(it == m_nodeLookup.end()) {
        return std::nullopt;
    }
    Node* node = it->second;
    for(std::size_t i = 0; i < node->m_neighbors.size(); ++i) {
        neighbors.push_back(node->m_neighbors.at(i)->m_id);
    }
    return neighbors;
}

template <class T, class D>
std::size_t Graph<T, D>::GetSize() {
    return m_nodes.size();
}

template <class T, class D>
bool Graph<T, D>::IsEmpty() {
    return m_nodes.empty();
}

template <class T, class D>
void Graph<T, D>::Print() {
    for(auto it = m_nodeLookup.begin(); it != m_nodeLookup.end(); ++it) {
        std::cout << it->first << " : " << it->second->m_data << std::endl;
    }
}

#endif