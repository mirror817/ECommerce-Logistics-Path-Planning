#include "Graph.h"
#include <iostream>

using namespace std;

Graph::Graph(int maxSize)
{
    capacity = maxSize;
    nodeCount = 0;

    nodes = new Node*[capacity]; // 指针数组

    for (int i = 0; i < capacity; i++)
    {
        nodes[i] = nullptr;
    }
}

Graph::~Graph() // 析构函数，释放节点内存
{
    for (int i = 0; i < nodeCount; i++)
    {
        delete nodes[i];
    }

    delete[] nodes;
}

void Graph::addNode(int id, string name, NodeType type) // 添加节点
{
    if (nodeCount >= capacity)
    {
        cout << "Graph is full!" << endl;
        return;
    }

    nodes[nodeCount] = new Node(id, name, type); // 创建新节点
    nodeCount++;
}

void Graph::displayNodes() // 显示所有节点
{
    for (int i = 0; i < nodeCount; i++)
    {
        cout << "ID: " << nodes[i]->id << ", Name: " << nodes[i]->name << endl;

        // 显示与该节点相连的边
        Edge* current = nodes[i]->firstEdge;
        while (current != nullptr)
        {
            cout << "  -> To: " << current->to << ", Distance: " << current->distance
                 << ", Time: " << current->time << ", Cost: " << current->cost << endl;
            current = current->next;
        }
    }
}

void Graph::addEdge(int from, int to, double time, double distance, double cost)
{
    Node* fromNode = nullptr; // 起点节点

    // 找到起点节点
    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i]->id == from)
        {
            fromNode = nodes[i];
            break;
        }
    }

    // 起点不存在
    if (fromNode == nullptr)
    {
        cout << "From node does not exist!" << endl;
        return;
    }

    Node* toNode = nullptr; // 终点节点

    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i]->id == to)
        {
            toNode = nodes[i];
            break;
        }
    }

    // 终点不存在
    if (toNode == nullptr)
    {
        cout << "To node does not exist!" << endl;
        return;
    }

    // 创建新的边
    Edge* newEdge = new Edge(from, to, time, distance, cost);

    // 插入邻接表头部
    newEdge->next = fromNode->firstEdge; // 新边指向当前节点的第一个边
    fromNode->firstEdge = newEdge;       // 第一个边指向新边
}