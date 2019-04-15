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

        int getIndex() const {return m_index;};
        Node* getNodeA() const {return m_node_a;};
        Node* getNodeB() const {return m_node_b;};
        std::vector<float> getWeights() const {return m_weights;};

        void addWeight(float w) {m_weights.push_back(w);};

    private:
        int m_index;

        Node* m_node_a;
        Node* m_node_b;

        std::vector<float> m_weights;

};

#endif // CONNECTION_H
