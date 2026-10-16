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

Graph::~Graph()
{
    for (int i = 0; i < nodeCount; i++)
    {
        Edge* current = nodes[i]->firstEdge;

        while (current != nullptr)
        {
            Edge* temp = current;
            current = current->next;
            delete temp;
        }

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

    for (int i = 0; i < nodeCount; i++) // 检查节点编号是否已存在
    {
        if (nodes[i]->id == id)
        {
            cout << "Node ID already exists!" << endl;
            return;
        }
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

void Graph::displayMatrix()
{
    cout << "    ";
    for (int i = 0; i < nodeCount; i++)
    {
        cout << nodes[i]->id << " ";
    }
    cout << endl;

    for (int i = 0; i < nodeCount; i++)
    {
        cout << nodes[i]->id << " ";

        for (int j = 0; j < nodeCount; j++)
        {
            bool connected = false;

            Edge* current = nodes[i]->firstEdge;
            while (current != nullptr)
            {
                if (current->to == nodes[j]->id)
                {
                    connected = true;
                    break;
                }
                current = current->next;
            }

            cout << (connected ? 1 : 0) << " ";
        }

        cout << endl;
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

void Graph::deleteEdge(int from, int to)
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

    Edge* current = fromNode->firstEdge;
    Edge* prev = nullptr;

    while (current != nullptr)
    {
        if (current->to == to) // 找到要删除的边
        {
            if (prev == nullptr) // 删除的是第一个边
            {
                fromNode->firstEdge = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current; // 释放内存
            cout << "Edge from " << from << " to " << to << " deleted." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Edge from " << from << " to " << to << " does not exist!" << endl;
}

void Graph::deleteNode(int id)
{
    int index = -1;

    // 查找要删除的节点
    for (int i = 0; i < nodeCount; i++)
    {
        if (nodes[i]->id == id)
        {
            index = i;
            break;
        }
    }

    // 节点不存在
    if (index == -1)
    {
        cout << "Node does not exist!" << endl;
        return;
    }
    // 删除其他节点中指向该节点的边
    for (int i = 0; i < nodeCount; i++)
    {
        if (i == index)
        {
            continue;
        }

        Edge* current = nodes[i]->firstEdge;
        Edge* previous = nullptr;

        while (current != nullptr)
        {
            if (current->to == id)
            {
                Edge* temp = current;

                if (previous == nullptr)
                {
                    nodes[i]->firstEdge = current->next;
                }
                else
                {
                    previous->next = current->next;
                }

                current = current->next;
                delete temp;
            }
            else
            {
                previous = current;
                current = current->next;
            }
        }
    }
    // 删除该节点自己的所有出边
    Edge* current = nodes[index]->firstEdge;

    while (current != nullptr)
    {
        Edge* temp = current;
        current = current->next;
        delete temp;
    }

    nodes[index]->firstEdge = nullptr;

    // 删除节点本身
    delete nodes[index];

    // 后面的节点依次向前移动
    for (int i = index; i < nodeCount - 1; i++)
    {
        nodes[i] = nodes[i + 1];
    }

    nodeCount--;

    nodes[nodeCount] = nullptr;

    cout << "Node deleted successfully!" << endl;
}
