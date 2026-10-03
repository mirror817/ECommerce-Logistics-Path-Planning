#include "Graph.h"
#include <iostream>

using namespace std;

int main()
{
    Graph graph;

    graph.addNode(1, "Beijing Warehouse", WAREHOUSE);
    graph.addNode(2, "Delivery Point 1", DELIVERY_POINT);
    graph.addNode(3, "Transfer Station 1", TRANSFER_STATION);

    graph.addEdge(1, 2, 8.0, 5.0, 8.0);
    graph.addEdge(1, 99, 12.0, 8.0, 12.0);

    graph.displayNodes();

    return 0;
}