/* GraphSystem.h
graph system is a user interface to use the graph data structure.
*/
#ifndef GRAPHSYSTEM_H
#define GRAPHSYSTEM_H
#include "Graph.h"
#include <string>
#include <sstream>

class GraphSystem {
public:
    GraphSystem() = default;
    ~GraphSystem() = default;

    // add node
    void AddNode(const std::string& id, const std::string& data);

    // remove node
    std::optional<std::string> RemoveNode(const std::string& id);

    // add edge
    void AddEdge(const std::string& fromId, const std::string& toId);

    // get data from node
    std::optional<std::string> GetData(const std::string& id);

    // get neighbors
    std::optional<std::vector<std::string>> GetNeighbors(const std::string& id);

    // get size
    std::size_t GetSize();

    // check if empty
    bool IsEmpty();

    // print the graph
    void Print();

    // help menu
    void HelpMenu();

    // run the menu
    void Run();
    

private:
    enum class Command {ADD, REMOVE, ADD_EDGE, GET, GET_NEIGHBORS, SIZE, IS_EMPTY, PRINT, HELP, QUIT, UNKNOWN};

    Command ParseCommand(const std::string& str);

    Graph<std::string, std::string> m_graph;
};

#endif