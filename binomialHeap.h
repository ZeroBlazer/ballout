#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include "list.h"

template<typename T>
class binomialTree
{
    template<typename U>
    friend class binomialHeap;

    public:
    class Node
    {
        public:

            T m_dato;
            Node * m_pFather;
            Node * m_pChild;
            Node * m_pSibling;

        public:

            Node() : m_pFather(0), m_pChild(0), m_pSibling(0) {}
            Node(T dato, Node* father=0, Node* child=0, Node* sibling=0)
            : m_dato(dato), m_pFather(father), m_pChild(child), m_pSibling(sibling) {}

            virtual ~Node(){}

            void killMe()
            {
                if(m_pSibling) m_pSibling->killMe();
                if(m_pChild) m_pChild->killMe();
                delete this;
            }
    };

    typedef Node Node_T;

    private:
        Node_T * m_pRoot;
        sizet m_degree;

    public:
        binomialTree() :m_pRoot(0) {}
        binomialTree(T&d) :m_degree(0) {m_pRoot = new Node_T(d);}

        virtual ~binomialTree() {if(m_pRoot) m_pRoot->killMe();}

        bool op_union(binomialTree<T> *A);
};

template<typename T>
class binomialHeap
{
    typedef typename binomialTree<T>::Node_T Node_binTree_T;
    typedef list<binomialTree<T> * > binTree_list;
    typedef typename binTree_list::Node_T Node_list_binTree_T;

    private:

        sizet m_size;
        binTree_list m_list;

    public:

        binomialHeap()  :m_size(0){}
        virtual ~binomialHeap(){}
        inline sizet size() {return m_size;}

        void insert(T&d);
        bool removeMin();
        bool remove(T&d);
        T getMin(Node_list_binTree_T * &p);
        void decreaseKey(Node_binTree_T *p);
        void op_union(binomialHeap &H);
        void fix();

        void middle_union(binomialHeap &H);

        void makeRelations(Node_binTree_T * origin, ofstream& file);
        void makeRelations(ofstream& file);
        void graph();

};

//just union between binomial trees with same degree
template<typename T>
bool binomialTree<T>::op_union(binomialTree<T> *tree)
{
    if(m_degree!=tree->m_degree)
        return false;

    if(m_pRoot->m_dato > tree->m_pRoot->m_dato)
    {
        Node_T* tmp=m_pRoot;
        m_pRoot=tree->m_pRoot;
        tree->m_pRoot=tmp;
    }

    Node_T* A=tree->m_pRoot;
    tree=0;

    A->m_pFather=m_pRoot;
    A->m_pSibling=m_pRoot->m_pChild;
    m_pRoot->m_pChild=A;

    m_degree++;
    return true;
}

template<typename T>
void binomialHeap<T>::fix()
{
    if(m_list.m_size < 2) return;

    binomialTree<T> * nu=m_list[0], * tmp=m_list[1];

    while(nu->m_degree==tmp->m_degree)
    {
        tmp->op_union(nu);
        m_list.pop_front();
        nu=m_list[0];
        if(m_list.size()>1)
            tmp=m_list[1];
        else break;
    }
}

template<typename T>
void binomialHeap<T>::insert(T&d)
{
    binomialTree<T> * tmp=0;
    if(m_list.m_size)
        tmp=m_list[0];
    binomialTree<T> * nu= new binomialTree<T>(d);
    m_list.push_front(nu);

    if(tmp) fix();
    m_size++;
}

template<typename T>
T binomialHeap<T>::getMin(Node_list_binTree_T * &p)
{
    if(!m_size) return -1;
    Node_list_binTree_T * tmp=p=m_list.m_pHead;
    sizet list_size=m_list.size();

    T mem=tmp->m_dato->m_pRoot->m_dato;

    for(sizet i=0; i<list_size; i++)
    {
        T dato=tmp->m_dato->m_pRoot->m_dato;
        if(dato < mem)
        {
            mem=dato;
            p=tmp;
        }
        tmp=tmp->m_pNext;
    }
    return mem;
}

template<typename T>
void binomialHeap<T>::middle_union(binomialHeap &H)
{
    if(m_size<H.m_size)
    {
        Node_list_binTree_T * tmp= H.m_list.m_pHead;
        m_list.m_pHead=m_list.m_pHead;
        m_list.m_pHead=tmp;

        sizet tmp_size=m_size;
        m_size=H.m_size;
        H.m_size=tmp_size;
    }
    op_union(H);
}

//El heap que se ingresa debe tener size menor
template<typename T>
void binomialHeap<T>::op_union(binomialHeap &H)
{
    Node_list_binTree_T * p=m_list.m_pHead;
    Node_list_binTree_T * q=H.m_list.m_pHead;

    sizet   deg_p, deg_q;

    while(q)
    {
        deg_p=p->m_dato->m_degree,
        deg_q=q->m_dato->m_degree;

        if(deg_p==deg_q)
        {
            p->m_dato->op_union(q->m_dato);
            fix();
            p=m_list.m_pHead;
            q=q->m_pNext;
            H.m_list.pop_front();
        }
        else
        {
            if(deg_p > deg_q)
            {
                binomialTree<T> * tmp=p->m_dato;
                p->m_dato=q->m_dato;
                q->m_dato=0;
                p->m_pNext=new Node_list_binTree_T(tmp,p->m_pNext);
                m_list.m_size++;
                q=q->m_pNext;
            }
            else p=p->m_pNext;
        }
    }
    m_size+=H.m_size;
}

//Does not work
template<typename T>
bool binomialHeap<T>::removeMin()
{
    if(!m_size) return false;
    if(m_size==1)
    {
        m_list.pop_front();
        m_size--;
        return true;
    }
    Node_list_binTree_T * min;
    getMin(min);

    sizet cur_degree=min->m_dato->m_degree, size_nu_heap=0;
    binomialHeap<T> tmp_heap;
    Node_binTree_T * cur=min->m_dato->m_pRoot->m_pChild, *sib;

    while(cur)
    {
        binomialTree<T> * A=new binomialTree<T>;
        cur_degree--;
        size_nu_heap += 2^cur_degree;
        sib=cur->m_pSibling;
        cur->m_pFather=cur->m_pSibling=0;
        A->m_pRoot=cur;
        A->m_degree=cur_degree;
        tmp_heap.m_list.push_front(A);
        cur=sib;
    }


    Node_list_binTree_T **tmp;
    m_list.find(min->m_dato,tmp);
    (*tmp)->m_pNext=(*tmp)->m_pNext->m_pNext;
    graph();
    delete min;
    m_size-=size_nu_heap;
    tmp_heap.m_size=size_nu_heap;

    middle_union(tmp_heap);

    return true;
}

//Linked list
template<typename T>
void binomialHeap<T>::makeRelations(ofstream& file)
{
    Node_list_binTree_T * p=m_list.m_pHead;
    while(p->m_pNext)
    {
        file<<"\t"<<p->m_dato->m_pRoot->m_dato<<"->"<<p->m_pNext->m_dato->m_pRoot->m_dato<<endl;
        p=p->m_pNext;
    }
}

//Binomial trees
template<typename T>
void binomialHeap<T>::makeRelations(Node_binTree_T * origin, ofstream& file)
{
    if(!origin) return;
    if(origin->m_pChild)
    {
        file<<"\t"<<origin->m_dato<<"->"<<origin->m_pChild->m_dato<<";"<<endl;
        makeRelations(origin->m_pChild,file);
    }
    if(origin->m_pSibling)
    {
        file<<"\t"<<origin->m_dato<<"->"<<origin->m_pSibling->m_dato<<";"<<endl;
        makeRelations(origin->m_pSibling,file);
    }
    if(origin->m_pFather)
        file<<"\t"<<origin->m_dato<<"->"<<origin->m_pFather->m_dato<<";"<<endl;
}

template<typename T>
void binomialHeap<T>::graph()
{
    if(!m_list.m_pHead) return;

    ofstream file("graph.dot");
    file<<"digraph Text{"<<endl;
    file<<"edge [arrowhead=none]"<<endl;

    if(m_size==1)
        file<<"\t"<<m_list.m_pHead->m_dato->m_pRoot->m_dato<<endl;
	else
	{
        Node_list_binTree_T * tmp=m_list.m_pHead;
        while(tmp)
        {
            Node_binTree_T * p= tmp->m_dato->m_pRoot;
            makeRelations(p, file);
            tmp=tmp->m_pNext;
        }
        makeRelations(file);
    }

    file<<"}";
    file.close();

    system("dot -Tpng -O graph.dot");
    system("eog graph.dot.png");
}

#endif // BINOMIALHEAP_H
