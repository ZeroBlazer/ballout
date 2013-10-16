#ifndef RB_TREE_H
#define RB_TREE_H

#include "headers/nodo.h"

template<typename T>
class RB_Tree
{
public:
    typedef RB_Node<T> Node_T;

    enum RotationWay {
        LEFT = 0,
        RIGHT = 1
    };

private:
    Node_T *m_pRoot;

private:        //Funciones Privadas

    void singleRotationTo(Node_T *&p, RotationWay way);

    void doubleRotationTo(Node_T *&p, RotationWay way);

public:         //Funciones Públicas
    RB_Tree() :
        m_pRoot(NULL)
    {}

    bool findParent(T &d, Node_T *&father);

    bool insert(T &d);

    void graph(){}
};

//#include "rb_tree.cpp"

template <typename T>
bool RB_Tree<T>::findParent(T &d, Node_T *&father) {
    father = m_pRoot;
    Node_T * p;
    while(p)
    {
        if(p->m_Dato == d)
            return true;
        father=p;
        p = p->m_pChildren[p->m_Dato < d];
    }
    return false;
}


template <typename T>
void RB_Tree<T>::fix(Node_T *p) {
    if(p->isBlack())
        return;

}

template <typename T>
bool RB_Tree<T>::insert(T &d) {
    if(!m_pRoot) {
        m_pRoot = new Node_T(d);
        m_pRoot->getBlack();
        return true;
    }

    Node_T * p;
    if(findParent(d,p))
        return false;

    Node_T *nu=new Node_T(d,p);
    p->m_pChildren[d > p->m_Dato] = nu;

    if(p->isBlack())
        return true;

    Node_T *unc = nu->uncle();
    if(unc && unc->isRed()) {
        p->getBlack();
        unc->getBlack();
        nu->grandparent()->getRed();
    }

    if(!unc || unc->isBlack()) {
        nu->m_parent->m_pChildren[nu->grandparent()->m_Dato < nu->m_Dato]
    }

    return false;
}

template <typename T>
void RB_Tree<T>::singleRotationTo(Node_T *&p, RotationWay way) {
    Node_T *q = p->m_pChildren[!way];
    p->m_pChildren[!way] = q->m_pChildren[way];
    q->m_pChildren[way] = p;
    p = q;
}

template <typename T>
void RB_Tree<T>::doubleRotationTo(Node_T *&p, RotationWay way) {
    Node_T  *q = p->m_pChildren[!way],
            *r = q->m_pChildren[way];
    p->m_pChildren[!way] = r->m_pChildren[way];
    q->m_pChildren[way] = r->m_pChildren[!way];
    r->m_pChildren[!way] = q;
    r->m_pChildren[way] = p;
    p = r;
}

#endif // RB_TREE_H
