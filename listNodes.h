#ifndef LISTNODES_H
#define LISTNODES_H

#include "foundations.h"

template<typename T>
class Nodo
{
    public:
        T m_dato;
        Nodo<T> * m_pNext;

    public:
        Nodo(T&d): m_dato(d), m_pNext(0){}
        Nodo(T&d, Nodo* next) : m_dato(d), m_pNext(next){}
        ~Nodo(){}
        inline friend ostream& operator << (ostream &os, Nodo &N){os<<N.m_dato; return os;}
        inline void killMe() {if(m_pNext) m_pNext->killMe(); delete this;}
        inline void swap(Nodo* &N) {T tmp=m_dato; m_dato=N->m_dato; N->m_dato=tmp;}
};

template<typename T>
class NodoD
{
    public:
        T m_dato;
        NodoD<T> * m_pPrev;
        NodoD<T> * m_pNext;

    public:
        NodoD(T&d): m_dato(d), m_pPrev(0), m_pNext(0){}
        NodoD(T&d, NodoD* prev, NodoD* next) : m_dato(d), m_pPrev(prev), m_pNext(next){}
        ~NodoD(){}
        inline friend ostream& operator << (ostream &os, NodoD &N){os<<N.m_dato; return os;}
        inline void killMe() {if(m_pNext) m_pNext->killMe(); delete this;}
        inline void swap(NodoD* &N) {T tmp=m_dato; m_dato=N->m_dato; N->m_dato=tmp;}
};

#endif // LISTNODES_H
