#ifndef CONNECTION_H
#define CONNECTION_H

#include "node.h"

#include <vector>

class Node;

class Connection
{
    public:
        Connection(int index, Node* a, Node* b);
        ~Connection();

        int getIndex() {return m_index;};

        void addWeight(float w) {m_weights.push_back(w);};

    private:
        int m_index;

        Node* m_node_a;
        Node* m_node_b;

        std::vector<float> m_weights;

};

#endif // CONNECTION_H
