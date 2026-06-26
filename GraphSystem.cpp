/* GraphSystem.cpp */
#include "GraphSystem.h"

void GraphSystem::AddNode(int id, std::string data) {
    m_graph.AddNode(id, data);
    std::cout << "Added node: " << id << " : " << data << std::endl;
}

std::optional<std::string> GraphSystem::RemoveNode(int id) {
    std::optional<std::string> data = m_graph.RemoveNode(id);
    if(data.has_value()) {
        std::cout << "Removed node: " << id << " : " << data.value() << std::endl;
        return data.value();
    }
    std::cout << "Error: could not remove node " << id << ", does not exist" << std::endl;
    return std::nullopt;
}

void GraphSystem::AddEdge(int fromId, int toId) {
    if(m_graph.AddEdge(fromId, toId)) {
        std::cout << "Added edge from node " << fromId << " to " << toId << std::endl;
    } else {
        std::cout << "Error: could not add edge from node " << fromId << " to " << toId << "." << std::endl;
        std::cout << "Not enough nodes or an edge in the same direction already exists" << std::endl;
    }
}

std::optional<std::string> GraphSystem::GetData(int id) {
    std::optional<std::string> data = m_graph.GetData(id);
    if(data.has_value()) {
        std::cout << id << " : " << data.value() << std::endl;
        return data.value();
    }
    std::cout << "Error: could not find node " << id << ", does not exist" << std::endl;
    return std::nullopt;
}

std::optional<std::vector<int>> GraphSystem::GetNeighbors(int id) {
    std::optional<std::vector<int>> neighbors = m_graph.GetNeighbors(id);
    if(neighbors.has_value() && !neighbors.value().empty()) {
        std::cout << "Neighbors to node " << id << ":" << std::endl;
        for(std::size_t i = 0; i < neighbors.value().size(); ++i) {
            std::cout << neighbors.value().at(i) << std::endl;
        }
        return neighbors.value();
    } else {
        std::cout << "Error: no neighbors for node " << id << " or node could not be found" << std::endl;
        return std::nullopt;
    }
}

std::size_t GraphSystem::GetSize() {
    return m_graph.GetSize();
}  

bool GraphSystem::IsEmpty() {
    return m_graph.IsEmpty();
}

void GraphSystem::Print() {
    std::cout << "Printing the whole graph: " << std::endl;
    m_graph.Print();
}

void GraphSystem::Run() {
    
}
