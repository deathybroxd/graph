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
    Graph() = default;
    ~Graph() = default;

    // create node
    void AddNode(T id, D data);

    // remove node
    std::optional<D> RemoveNode(T id);

    // add an edge from one node to another
    void AddEdge(T fromId, T toId);

    // get node data
    std::optional<D> GetData(T id);

    // returns a vector of the neighbors of a node
    std::optional<std::vector<T>> GetNeighbors(T id);

private:
    struct Node {
        T m_id;
        D m_data;
        std::vector<Node*> m_neighbors; // directed edges only

        Node(T id, D data) : m_id(id), m_data(data) {}
    };

    std::vector<std::unique_ptr<Node>> m_nodes;
    std::unordered_map<T, Node*> m_nodeLookup; // O(1) access time - raw* because 
};

template <class T, class D>
void Graph<T, D>::AddNode(T id, D data) {
    std::unique_ptr<Node> newNode = std::make_unique<Node>(id, data);
    m_nodeLookup[id] = newNode.get(); // .get() returns a raw* to an object- m_nodeLookup stores Node*4
    m_nodes.push_back(std::move(newNode)); // std::move to transfer ownership
}



#endif