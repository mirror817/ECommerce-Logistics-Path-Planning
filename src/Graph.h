#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Node.h"

class Graph
{
private:
    Node** nodes;  // 节点数组
    int nodeCount; // 当前节点数量
    int capacity;  // 最大容量

public:
    Graph(int maxSize = 100);
    ~Graph();

    void addNode(int id, string name, NodeType type);
    void addEdge(int from, int to, double time, double distance, double cost);
    void displayNodes();
};

#endif