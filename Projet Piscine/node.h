#ifndef NODE_H
#define NODE_H

#include "connection.h"

#include <vector>

class Connection;

class Node
{
    public:
        Node(int index, float x, float y);
        ~Node();

        int getIndex() {return m_index;};

    private:
        int m_index;

        float m_x;
        float m_y;

        std::vector<Connection*> m_connections;
        std::vector<Node*> m_nodes;
};

#endif // NODE_H
