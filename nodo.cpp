#include "headers/nodo.h"

template<typename T>
void Nodo<T>::kill_me() {
    if(m_pSig)
        m_pSig->kill_me();
    delete this;
}

template<typename T>
void DNodo<T>::kill_me() {
    if(m_pSig)
        m_pSig->kill_me();
    delete this;
}

template<typename T>
void BinTreeNode<T>::kill_me() {
    if(m_pChildren[0])
        m_pChildren[0]->kill_me();
    if(m_pChildren[1])
        m_pChildren[1]->kill_me();
    delete this;
//    EN CASO DE REALIZAR UN NODO DINÁMICO
//    for(register size_t i = 0; i < 2; ++i)
//        if(m_pChildren[i])
//            m_pChildren[i]->kill_me();
//    delete this;
}

template <typename T>
void AVL_Node<T>::kill_me()
{
    if(m_pChildren[0])
        m_pChildren[0]->kill_me();
    if(m_pChildren[1])
        m_pChildren[1]->kill_me();
    delete this;
}

template <typename T>
void RB_Node<T>::kill_me()
{
    if(m_pChildren[0])
        m_pChildren[0]->kill_me();
    if(m_pChildren[1])
        m_pChildren[1]->kill_me();
    delete this;
}

template <typename T>
RB_Node<T> *RB_Node<T>::uncle() {
    if(m_parent->m_parent->m_pChildren[0] == m_parent)
        return m_parent->m_parent->m_pChildren[1];
    return m_parent->m_parent->m_pChildren[0];
}

template <typename T>
RB_Node<T> *RB_Node<T>::grandparent() {
    if(m_parent)
        return m_parent->m_parent;
    return NULL;
}
