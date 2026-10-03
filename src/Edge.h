#ifndef EDGE_H
#define EDGE_H

class Edge
{
public:
    int from;
    int to;

    double time;

    double distance; // 距离
    double cost;     // 费用

    Edge* next; // 指向下一条道路

    Edge(int f, int t, double tm, double d, double c)
    {
        from = f;
        to = t;
        time = tm;
        distance = d;
        cost = c;
        next = nullptr;
    }
};

#endif
