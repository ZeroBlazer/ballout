#ifndef NODO_H
#define NODO_H

#include <iostream>

using namespace std;

template<class T>
class Nodo {
public:
    T m_dato;
    Nodo<T> *m_pSig;

public:
    Nodo(T &d) :
        m_dato(d),
        m_pSig(NULL)
    {}
    friend ostream& operator<<(ostream &os, Nodo &node) {
        os << node.m_dato;
        return os;
    }

    void kill_me();
};

template<class T>
class DNodo {
public:
    T m_dato;
    DNodo<T> *m_pSig;
    DNodo<T> *m_pAnt;

public:
    DNodo(T &d) :
//        m_dato(d),
        m_pSig(NULL),
        m_pAnt(NULL)
    {
        m_dato = d;
    }
    friend ostream& operator<<(ostream &os, DNodo &node) {
        os << node.m_dato;
        return os;
    }

    void kill_me();
};

template <typename T>
class BinTreeNode {
public:
    T m_dato;
    BinTreeNode *m_pChildren[2];

public:
    BinTreeNode(T &d) :
        m_dato(d)
    {
        m_pChildren[0] = m_pChildren[1] = NULL;
    }

    ~BinTreeNode()
    {}

    void kill_me();
};

template <typename T>
class AVL_Node
{
    public:
        T m_dato;
        AVL_Node<T> *m_pChildren[2];
        int balance_factor;

    public:
        AVL_Node(T &d) :
            m_dato(d),
            balance_factor(0)
        {
            m_pChildren[0] = m_pChildren[1] = NULL;
        }

        ~AVL_Node()
        {}

        void kill_me();
};

template <typename T>
class RB_Node {
public:
    enum Color {
        BLACK = 0,
        RED = 1
    };

public:
    RB_Node *m_parent;
    RB_Node *m_pChildren[2];
    T m_Dato;       //Dato
    Color m_Color;   //Color

public:
    RB_Node(T &d, RB_Node * parent=0) :
        m_parent(parent),
        m_Dato(d),
        m_Color(RED)
    {
        m_pChildren[0] = m_pChildren[1] = NULL;
    }

    ~RB_Node()
    {}

    inline bool isRed() {
        return m_Color == RED;
    }

    inline bool isBlack() {
        return m_Color == BLACK;
    }

    inline void getBlack() {
        m_Color = BLACK;
    }

    inline void getRed() {
        m_Color = RED;
    }

    void kill_me();

    RB_Node *uncle();

    RB_Node *grandparent();
};

template<typename T>
T max(T &a, T &b) {
    return (a > b) ? a : b;
}

#include "headers/nodo.cpp"

#endif // NODO_H
