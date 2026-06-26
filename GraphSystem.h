/* GraphSystem.h
graph system is a user interface to use the graph data structure.
*/
#ifndef GRAPHSYSTEM_H
#define GRAPHSYSTEM_H
#include "Graph.h"
#include <string>

class GraphSystem {
public:
    GraphSystem() = default;
    ~GraphSystem() = default;

    // add node
    void AddNode(int id, std::string data);

    // remove node
    std::optional<std::string> RemoveNode(int id);

    // add edge
    void AddEdge(int fromId, int toId);

    // get data from node
    std::optional<std::string> GetData(int id);

    // get neighbors
    std::optional<std::vector<int>> GetNeighbors(int id);

    // get size
    std::size_t GetSize();

    // check if empty
    bool IsEmpty();

    // print the graph
    void Print();

    // run the menu
    void Run();

private:
    Graph<int, std::string> m_graph;
};

#endif;