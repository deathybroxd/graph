/* GraphSystem.cpp */
#include "GraphSystem.h"

void GraphSystem::AddNode(const std::string& id, const std::string& data) {
    m_graph.AddNode(id, data);
    std::cout << "Added node: " << id << " : " << data << std::endl;
}

void GraphSystem::RemoveNode(const std::string& id) {
    std::optional<std::string> data = m_graph.RemoveNode(id);
    if(data.has_value()) {
        std::cout << "Removed node: " << id << " : " << data.value() << std::endl;
    }
    std::cout << "Error: could not remove node " << id << ", does not exist" << std::endl;
}

void GraphSystem::AddEdge(const std::string& fromId, const std::string& toId) {
    if(m_graph.AddEdge(fromId, toId)) {
        std::cout << "Added edge from node " << fromId << " to " << toId << std::endl;
    } else {
        std::cout << "Error: could not add edge from node " << fromId << " to " << toId << "." << std::endl;
        std::cout << "Not enough nodes or an edge in the same direction already exists" << std::endl;
    }
}

void GraphSystem::GetData(const std::string& id) {
    std::optional<std::string> data = m_graph.GetData(id);
    if(data.has_value()) {
        std::cout << id << " : " << data.value() << std::endl;
    } else {
        std::cout << "Error: could not find node " << id << ", does not exist" << std::endl;
    }
}

void GraphSystem::GetNeighbors(const std::string& id) {
    std::optional<std::vector<std::string>> neighbors = m_graph.GetNeighbors(id);
    if(neighbors.has_value() && !neighbors.value().empty()) {
        std::cout << "Neighbors to node " << id << ":" << std::endl;
        for(std::size_t i = 0; i < neighbors.value().size(); ++i) {
            std::cout << neighbors.value().at(i) << std::endl;
        }
    } else {
        std::cout << "Error: no neighbors for node " << id << " or node could not be found" << std::endl;
    }
}

void GraphSystem::BFS(const std::string& startId) {
    std::optional<std::vector<std::string>> searchedList = m_graph.BFS(startId);
    if(searchedList.has_value()) {
        std::cout << "Breadth-First-Search starting from " << startId << ":" << std::endl;
        for(std::size_t i = 0; i < searchedList.value().size(); ++i) {
            std::cout << searchedList.value().at(i) << "->";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Error: node " << startId << " could not be found " << std::endl;
    }
}

void GraphSystem::DFS(const std::string& startId) {
    std::optional<std::vector<std::string>> searchedList = m_graph.DFS(startId);
    if(searchedList.has_value()) {
        std::cout << "Depth-First-Search starting from " << startId << ":" << std::endl;
        for(std::size_t i = 0; i < searchedList.value().size(); ++i) {
            std::cout << searchedList.value().at(i) << "->";
        }
        std::cout << std::endl;
    } else {
        std::cout << "Error: node " << startId << " could not be found " << std::endl;
    }
}



void GraphSystem::Size() {
    std::cout << "Current graph size: " << m_graph.GetSize() << std::endl;
}  

void GraphSystem::IsEmpty() {
    if(m_graph.IsEmpty()) {
        std::cout << "Graph is currently empty" << std::endl;
    } else {
        std::cout << "Graph is not currently empty " << std::endl;
    }
}

void GraphSystem::Print() {
    std::cout << "Printing the whole graph: " << std::endl;
    if(!m_graph.IsEmpty()) {
        m_graph.Print();
    } else {
        std::cout << "Graph is currently empty" << std::endl;
    }
}

void GraphSystem::HelpMenu() {
    std::cout << "===== COMMANDS =====" << std::endl;
    std::cout << "ADD <id #> <data> - Adds a node" << std::endl;
    std::cout << "REMOVE <id #> - Removes a node" << std::endl;
    std::cout << "ADD_EDGE <fromId #> <toId #> - Adds an edge from one node to another" << std::endl;
    std::cout << "GET <id #> - Gets data from a node" << std::endl;
    std::cout << "GET_NEIGHBORS <id #> - Gets all neighbors of a node" << std::endl;
    std::cout << "BFS <id #> - Breadth-first-search on an a node id " << std::endl;
    std::cout << "DFS <id #> - Depth-first-search on a node id " << std::endl;
    std::cout << "SIZE - Gets the size of the whole graph" << std::endl;
    std::cout << "IS_EMPTY - Checks if the graph is empty" << std::endl;
    std::cout << "PRINT - Prints the whole graph" << std::endl;
    std::cout << "HELP - Reprints the help menu" << std::endl;
    std::cout << "QUIT - Exit the program " << std::endl;
    std::cout << "====================" << std::endl;
}


void GraphSystem::Run() {
    std::string line;
    HelpMenu();
    while(getline(std::cin, line)) {   
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        switch (ParseCommand(command)) {
            case Command::ADD: {
                std::string id, data;
                if(iss >> id >> data) {
                    m_graph.AddNode(id, data);
                }
                break;
            }

            case Command::REMOVE: {
                std::string id;
                if(iss >> id) {
                    RemoveNode(id);
                }
                break;
            }

            case Command::ADD_EDGE: {
                std::string fromId, toId;
                if(iss >> fromId >> toId) {
                    AddEdge(fromId, toId);
                }
                break;
            }

            case Command::GET: {
                std::string id;
                if(iss >> id) {
                    GetData(id);
                }
                break;
            }

            case Command::GET_NEIGHBORS: {
                std::string id;
                if(iss >> id) {
                    GetNeighbors(id);
                }
                break;
            }

            case Command::BFS: {
                std::string id;
                if(iss >> id) {
                    BFS(id);
                }
                break;
            }

            case Command::DFS: {
                std::string id;
                if(iss >> id) {
                    DFS(id);
                }
                break;
            }

            case Command::SIZE:
                Size();
                break;

            case Command::IS_EMPTY: 
                IsEmpty();
                break;

            case Command::PRINT:
                Print();
                break;

            case Command::HELP:
                HelpMenu();
                break;

            case Command::QUIT:
                return;

            default:
                std::cout << "Error: Unknown command" << std::endl;
                break;
        }
        // reprint menu each time
        HelpMenu();
    }
}

// PRIVATE FUNCTIONS vvvvv

GraphSystem::Command GraphSystem::ParseCommand(const std::string& str) {
    static const std::unordered_map<std::string, Command> lookupTable {
        {"ADD", Command::ADD},
        {"REMOVE", Command::REMOVE},
        {"ADD_EDGE", Command::ADD_EDGE},
        {"GET", Command::GET},
        {"GET_NEIGHBORS", Command::GET_NEIGHBORS},
        {"BFS", Command::BFS},
        {"DFS", Command::DFS},
        {"SIZE", Command::SIZE},
        {"IS_EMPTY", Command::IS_EMPTY},
        {"PRINT", Command::PRINT},
        {"HELP", Command::HELP},
        {"QUIT", Command::QUIT},
        {"UNKNOWN", Command::UNKNOWN}
    };

    auto it = lookupTable.find(str);
    if (it != lookupTable.end()) {
        return it->second;
    } else {
        return Command::UNKNOWN;
    }
}