#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

class Edge;

enum NodeType
{
    WAREHOUSE,
    DELIVERY_POINT,
    TRANSFER_STATION
};

class Node
{
public:
    int id;        // 节点编号
    string name;   // 名称
    NodeType type; // 类型

    Edge* firstEdge; // 指向这个节点的第一条道路

    Node(int i, string n, NodeType t)
    {
        id = i;
        name = n;
        type = t;
        firstEdge = nullptr;
    }
};

#endif
