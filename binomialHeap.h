#ifndef BINOMIALHEAP_H
#define BINOMIALHEAP_H

#include "list.h"

template<typename T>
class binomialTree
{
    template<typename U>
    friend class binomialHeap;

    class Node
    {
        public:

            T m_dato;
            Node * m_pFather;
            Node * m_pChild;
            Node * m_pSibling;

        public:

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

    private:
        Node_T* makeTree(sizet degree, Node_T *father);

    public:
        binomialTree() :m_pRoot(0), m_degree(0) {}
        binomialTree(T&d) :m_degree(0) {m_pRoot = new Node_T(d);}
        virtual ~binomialTree() {if(m_pRoot) m_pRoot->killMe();}

        inline Node_T* makeTree(sizet degree) {return makeTree(degree,0);}

        bool op_union(binomialTree<T> *A);
};

template<typename T>
class binomialHeap
{
    typedef typename binomialTree<T>::Node_T Node_T;

    private:

        sizet m_size;
        list<binomialTree<T> * > m_list;

    public:

        binomialHeap()  :m_size(0){}
        virtual ~binomialHeap(){}

        void insert(T&d);
        bool remove(T&d);
        T getMin();

        void makeRelations(Node_T * origin, ofstream& file);
        void makeRelations(ofstream& file);
        void graph();

};

//just union between binomial trees with same degree
template<typename T>
bool binomialTree<T>::op_union(binomialTree<T> *tree)
{
    if(m_degree!=tree->m_degree)
        return false;

    Node_T* A=tree->m_pRoot;
    tree=0;

    A->m_pFather=m_pRoot;
    A->m_pSibling=m_pRoot->m_pChild;
    m_pRoot->m_pChild=A;

    m_degree++;
    return true;
}

template<typename T>
void binomialHeap<T>::insert(T&d)
{
    binomialTree<T> * tmp=0;
    if(m_list.m_pHead)
        tmp=m_list.m_pHead->m_dato;
    binomialTree<T> * nu= new binomialTree<T>(d);
    m_list.push_front(nu);

    if(!tmp)
        return;

    while(nu->m_degree==tmp->m_degree)
    {
        if(nu->m_pRoot->m_dato > tmp->m_pRoot->m_dato)
        {
            tmp->op_union(nu);
            m_list.pop_front();
        }
        else
        {
            nu->op_union(tmp);
            m_list.m_pHead->swap(m_list.m_pHead->m_pNext);
            m_list.pop_front();
        }
        nu=m_list[0];
        if(m_list.m_pHead->m_pNext)
            tmp=m_list[1];
        else break;
    }
    m_size++;
}

template<typename T>
T binomialHeap<T>::getMin()
{
    Nodo<binomialTree<T> * > * p=m_list.m_pHead;
    sizet list_size=m_list.size();

    //Node_T * mem_dir=p->m_dato->m_pRoot;
    T mem=p->m_dato->m_pRoot->m_dato;//mem_dir->m_dato;

    for(sizet i=0; i<list_size; i++)
    {
        T dato=p->m_dato->m_pRoot->m_dato;
        if(dato < mem)
        {
            mem=dato;
            //mem_dir=p->m_dato->m_pRoot;
        }
        p=p->m_pNext;
    }
    return mem;//_dir->m_dato;
}

template<typename T>
void binomialHeap<T>::makeRelations(ofstream& file)
{
    Nodo<binomialTree <T> * > * p=m_list.m_pHead;
    while(p->m_pNext)
    {
        file<<"\t"<<p->m_dato->m_pRoot->m_dato<<"->"<<p->m_pNext->m_dato->m_pRoot->m_dato<<endl;
        p=p->m_pNext;
    }
}

template<typename T>
void binomialHeap<T>::makeRelations(Node_T * origin, ofstream& file)
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
        //file<<m_list.m_pHead->m_dato<<";"<<endl;
        makeRelations(m_list.m_pHead->m_dato->m_pRoot,file);
	else
	{
        Nodo<binomialTree<T> * > * tmp=m_list.m_pHead;
        while(tmp)
        {
            Node_T * p= tmp->m_dato->m_pRoot;
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
