#ifndef LIST_H
#define LIST_H

#include "listNodes.h"

template<typename T>
class list
{
    public: typedef Nodo<T> Node_T;
    private: typedef Node_T * pNode_T;

    public:
        pNode_T m_pHead;
        pNode_T m_pTail;
        sizet m_size;

        bool inner_find(T&d, pNode_T *&pointer);
        void reverse(pNode_T father, pNode_T son, pNode_T grandSon);

    public:
        list() :m_pHead(0), m_pTail(0), m_size(0) {}
        virtual ~list() {if(m_pHead) m_pHead->killMe();}

        inline sizet size() {return m_size;}
        T& operator [](sizet position);

        friend ostream & operator << (ostream &os, list<T>& L)
        {
            pNode_T tmp=L.m_pHead;
            while(tmp)
            {
                os<<tmp->m_dato<<"\t";
                tmp=tmp->m_pNext;
            }
            os<<endl;
            return os;
        }

        list & operator >> (T&d)
        {
            push_back(d);
            return *this;
        }

        void push_front(T&d);
        void push_back(T&d);
        void pop_front();
        void pop_back();

        bool add(T&d);
        bool find(T&d);
        bool find(T&d, pNode_T *&pointer);
        void reverse();
        void sort();

        list<T>& operator + (list<T> &L);
        list<T>& operator * (list<T> &L);
};

template<typename T>
void list<T>::push_front(T&d)
{
    pNode_T nu = new Node_T (d,m_pHead);

    if(!m_pHead)
        m_pTail=nu;

    m_pHead=nu;
    m_size++;
}

template<typename T>
void list<T>::push_back(T&d)
{
    pNode_T nu = new Node_T (d);
    if(!m_pHead)
        m_pHead=nu;
    else
        m_pTail->m_pNext=nu;
    m_pTail=nu;
    m_size++;
}

template<typename T>
void list<T>::pop_front()
{
    if(!m_pHead)
        return;
    if(m_size==1)
    {
        delete m_pHead;
        m_pHead=m_pTail=0;
    }
    else
    {
        pNode_T tmp=m_pHead;
        m_pHead=m_pHead->m_pNext;
        delete tmp;
    }
    m_size--;
}

template<typename T>
void list<T>::pop_back()
{
    if(!m_pHead)
        return;
    if(m_size==1)
    {
        delete m_pHead;
        m_pHead=m_pTail=0;
    }
    else
    {
        pNode_T tmp=m_pHead, father;
        while(tmp->m_pNext)
        {
            father=tmp;
            tmp=tmp->m_pNext;
        }
        delete tmp;
        father->m_pNext=0;
        m_pTail=father;
    }
    m_size--;
}

template<typename T>
bool list<T>::add(T&d)
{
    if(!m_pHead || m_pHead->m_dato>d)
    {
        push_front(d);
        return true;
    }

    pNode_T tmp=m_pHead;
    while(tmp)
    {
        if(tmp->m_dato==d)
            return false;

        if(tmp->m_pNext && tmp->m_pNext->m_dato>d)
        {
            pNode_T nu = new Node_T (d,tmp->m_pNext);
            tmp->m_pNext=nu;
            m_size++;
            return true;
        }
        tmp=tmp->m_pNext;
    }
    push_back(d);
    return true;
}

template<typename T>
bool list<T>::inner_find(T&d, pNode_T *&pointer)
{
    while(*pointer)
    {
        if((*pointer)->m_dato==d)
            return true;
        if((*pointer)->m_dato>d)
            return false;
        pointer=&((*pointer)->m_pNext);
    }
    return false;
}

template <typename T>
bool list<T>::find(T&d, pNode_T *&pointer)
{
    pointer=&this->m_pHead;
    return inner_find(d,pointer);
}

template <typename T>
bool list<T>::find(T&d)
{
    pNode_T tmp=m_pHead;
    while(tmp)
    {
        if(tmp->m_dato==d)
            return true;
        tmp=tmp->m_pNext;
    }
    return false;
}

template<typename T>
T& list<T>::operator [](sizet position)
{
    if(position>=m_size)
        throw 0;

    pNode_T tmp=m_pHead;
    for(; position; position--)
        tmp=tmp->m_pNext;

    return tmp->m_dato;
}

template<typename T>
void list<T>::reverse(pNode_T father, pNode_T son, pNode_T grandSon)
{
    son->m_pNext=father;
    if(!grandSon->m_pNext)
    {
        grandSon->m_pNext=son;
        m_pHead->m_pNext=0;
        pNode_T tmp=m_pHead;
        m_pHead=m_pTail;
        m_pTail=tmp;
        return;
    }
    reverse(son, grandSon, grandSon->m_pNext);
}

template<typename T>
void list<T>::reverse()
{
    pNode_T father=m_pHead;
    if(!father) return;                 /** empty */
    pNode_T son=m_pHead->m_pNext;
    if(!son) return;                    /** one element */
    pNode_T grandSon=son->m_pNext;
    if(!grandSon)                       /** two elements */
    {
        father->swap(son);
        return;
    }
    reverse(father, son, grandSon);      /** more than three */
}

template<typename T>
list<T>& list<T>::operator + (list<T> &L)
{
    list<T> * res= new list<T>;
    pNode_T tmp=m_pHead;
    if(m_size)
        while(tmp)
        {
            if(!res->find(tmp->m_dato))
                res->push_back(tmp->m_dato);
            tmp=tmp->m_pNext;
        }
    tmp=L.m_pHead;
    if(L.m_size)
        while(tmp)
        {
            if(!res->find(tmp->m_dato))
                res->push_back(tmp->m_dato);
            tmp=tmp->m_pNext;
        }
    return *res;
}

template<typename T>
list<T>& list<T>::operator * (list<T> &L)
{
    list<T> * res= new list<T>;

    pNode_T tmp=m_pHead;
    while(tmp)
    {
        if(L.find(tmp->m_dato)&&!res->find(tmp->m_dato))
            res->push_back(tmp->m_dato);
        tmp=tmp->m_pNext;
    }
    return *res;
}

template<typename T>
void list<T>::sort()
{
    sizet i,j;
    T tmp;
    pNode_T p=m_pHead;
    for(i=0; i<m_size; i++,p=p->m_pNext)
    {
        T &a=p->m_dato;
        pNode_T q=m_pHead;
        for(j=0; j<i; j++,q=q->m_pNext)
        {
            T &b=q->m_dato;
            if(a<b)
            {
                tmp=a;
                a=b;
                b=tmp;
            }
        }
    }
}

#endif // LIST_H
