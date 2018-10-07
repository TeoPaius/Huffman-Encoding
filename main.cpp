#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <assert.h>
#include <vector>
#include <sstream>

using namespace std;

namespace aaa{ //Node

;
/////////////////////////////////////////
template<class T>
class Node
{
public:
    int left;
    int right;
    int idx;
    T info;

    Node<T>();
    Node<T>(T data);
    bool operator<(Node other);

};

template<class T>
Node<T>::Node()
{

}

template<class T>
Node<T>::Node(T data)
{
    idx = -1;
    left = -1;
    right = -1;
    info = data;
}

template<class T>
bool Node<T>::operator<(Node<T> other)
{
    if(!(info < other.info))
        return true;
    return false;
}
}

namespace aaa{ //bintree

template<class T>
class binTree
{
public:
    Node<T>* tree;
    Node<T> root;
    int capacity;
    int first_empty;

    int code[100];
    int codelen = 0;

    Node<T> iter_current;
    vector<Node<T> > iter_list;
    int iter_cnt;


    binTree<T>();
    void Add(Node<T>* nod);
    void dfs(Node<T> current);
    void decode(char c[100]);

    void iter_next();
    void iter_iterate(Node<T> n);
    Node<T> iter_getCurrent();
};

template<class T>
Node<T> binTree<T>::iter_getCurrent()
{
    return iter_current;
}

template<class T>
void binTree<T>::iter_next()
{
    iter_current = iter_list[iter_cnt++];
}

template<class T>
void binTree<T>::iter_iterate(Node<T> n)
{
    if(n.left == -1 && n.right == -1)
    {
        iter_list.push_back(n);
        return;
    }
    iter_iterate(tree[n.left]);
    iter_list.push_back(n);
    iter_iterate(tree[n.right]);
}

template<class T>
binTree<T>::binTree()
{
    capacity = 100;
    first_empty = 1;
    tree = new Node<T>[capacity];
}

template<class T>
void binTree<T>::Add(Node<T>* nod)
{
    //resize
    tree[first_empty] = *nod;
    nod->idx = first_empty;
    tree[first_empty].idx = first_empty;
    first_empty++;
}

template<class T>
void binTree<T>::dfs(Node<T> current)
{
    if(current.left == -1 && current.right == -1)
    {
        cout << current.info.x << " code: ";
        for(int i = 0; i < codelen; ++i)
        {
            cout << code[i];
        }
        cout << '\n';
        return;
    }
    if(current.left != -1)
    {
        code[codelen] = 1;
        codelen++;
        dfs(tree[current.left]);
        codelen--;
    }
    if(current.right != -1)
    {
        code[codelen] = 0;
        codelen++;
        dfs(tree[current.right]);
        codelen--;
    }


}

template<class T>
void binTree<T>::decode(char c[100])
{
    char decoded[100];
    int cnt = 0;

    Node<T> current = root;
    for(int i = 0; i <= strlen(c);++i)
    {
        if(current.left == -1 && current.right == -1)
        {
            decoded[cnt] = current.info.x;
            cnt++;
            current = root;
        }
        if(c[i] == '1')
        {
            int temp = current.left;
            current = tree[temp];
        }
        else
        {
            int temp = current.right;
            current = tree[temp];
        }
    }
    decoded[cnt] = '\0';
    cout <<  decoded;

}
////////////////////////////////////////
}



namespace aaa{ //prioqueue
template<class T>
class prioQueue
{
public:
    Node<T>* heap;
    int capacity;
    int len;


    prioQueue<T>();
    void Add(T data);
    T pop();
    void rearange(int k);

};

template<class T>
prioQueue<T>::prioQueue()
{
    capacity = 100;
    len = 0;
    heap = new Node<T>[capacity];

}

template<class T>
void prioQueue<T>::rearange(int k)
{
    if(k >= len)
        return;
    int minim = k;
    if(k*2 <= len && !(heap[minim] < heap[k*2]))
        minim = k*2;
    if(k*2+1 <= len && !(heap[minim] < heap[k*2+1]))
        minim = k*2+1;

    if(minim == k)
        return;
    Node<T> aux = heap[minim];
    heap[minim] = heap[k];
    heap[k] = aux;

    rearange(minim);

}

template<class T>
void prioQueue<T>::Add(T data)
{

    Node<T> n = Node<T>(data);
    if(len == 0)
    {
        len++;
        heap[1] = n;
    }
    else
    {
        len++;
        heap[len] = n;
        int parrent = len;
        while(heap[parrent] < heap[parrent/2] && parrent/2 != 0)
        {
            Node<T> aux = heap[parrent];
            heap[parrent] = heap[parrent/2];
            heap[parrent/2] = aux;

            parrent = parrent/2;
        }
    }

}

template<class T>
T prioQueue<T>::pop()
{
    for(int i = 1; i <= len; ++i)
    {
        //cout << heap[i].info.info.x << heap[i].info.info.freq << ' ';
    }
    //cout << '\n';
    if(len == 1)
    {
        len = 0;
        return heap[1].info;
    }
    Node<T> res = heap[1];
    heap[1] = heap[len];
    len--;

    rearange(1);

    return res.info;

}
////////////////////////////////////////
}

namespace aaa{ //character
class Character
{
public:
    char x;
    int freq;
    Character();
    Character(char x);
    Character(char x, int f);
    bool operator < (Character ohter);

};
bool Character::operator<(Character other)
{
    if(freq < other.freq)
        return true;
    return false;
}
Character::Character()
{

}
Character::Character(char a)
{
    x = a;
    freq = 1;
}
Character::Character(char a, int f)
{
    x = a;
    freq = f;
}

//////////////////////////////////////////////

}

using namespace aaa;

void testCharacter()
{
    Character c1('a');
    Character c2('b', 2);
    assert(c1.x == 'a');
    Character c3('c', 3);
    assert(c1 < c2);

}
void testNode()
{
    Node<int> n = Node<int>(2);
    Node<int> n2 = Node<int>(3);
    assert(n.info == 2);
    assert(n2 < n);

}
void testTreeAndQueue()
{
    Character c = Character('a', 2);
    prioQueue<Node<Character> > p3;
    binTree<Character> tree2;
    char a[100] = "this is an example";
    p3.Add(Node<Character>(c));
    assert(p3.heap[1].info.info.x == 'a');
    assert(p3.heap[1].info.info.freq == 2);

    Character c2 = Character('b', 1);
    p3.Add(Node<Character>(c2));

    Node<Character> res = p3.pop();
    assert(res.info.x == 'b');
    assert(res.info.freq == 1);

    tree2.Add(&res);
    assert(res.left == -1);
    assert(res.right == -1);
    assert(res.idx == 1);
    assert(tree2.first_empty == 2);


}

void tests()
{
    testCharacter();
    testNode();
    testTreeAndQueue();
}

void f(stringstream& s)
{

    s << "aa";
    return;
}

class A
{
public:
    void f()
    {
        cout << "a";
    }
};

class B : public A
{
public:
    virtual void f()
    {
        cout << "b";
    }
};



class ex1 : public std::exception
{
public:
    ex1(){cout << "ex1";}
    ex1(const ex1& e){cout << "copy";}
};

int main()
{
    try{
        throw ex1();
    }
    catch(ex1 e)
    {

    }


    cout << "aaa";
    A* b = new B();
    b->f();
    system("pause");
    /*
    tests();


    prioQueue<Node<Character> > p3;
    binTree<Character> tree2;
    cout << "Insert key: ";
    char a[100];// = "this is an example of llalalala";
    cin.getline(a, 100);
    cout << a << '\n';
    for(char ch = 'a'; ch <= 'z'; ++ch)
    {
        int cnt = 0;
        for(int i = 0; i < strlen(a); ++i)
            if(ch == a[i])
                cnt++;
        if(cnt != 0)
        {
            //cout << ch << ' '<< cnt << '\n';
            Character c(ch,cnt);
            Node<Character> n(c);
            p3.Add(n);
        }

    }
    int cnt = 0;
    for(int i = 0; i < strlen(a); ++i)
            if(' ' == a[i])
                cnt++;
    if(cnt != 0)
    {
        Character c(' ',cnt);
        Node<Character> n(c);
        p3.Add(n);
    }



    while(p3.len > 1)
    {
        Node<Character> node1 = p3.pop();
        Node<Character> node2 = p3.pop();
        //node1.idx = tree2.first_empty;
        tree2.Add(&node1);
        //node2.idx = tree2.first_empty;
        tree2.Add(&node2);
        Node<Character> node3;
        node3.idx = tree2.first_empty;
        node3.left = node1.idx;
        node3.right = node2.idx;
        node3.info.freq = node1.info.freq + node2.info.freq;
        p3.Add(node3);

    }
    tree2.root = p3.pop();

    tree2.dfs(tree2.root);

    cout << "decode: ";
    char code[100];

    cin.getline(code, 100);
    tree2.decode(code);

    */

    return 0;
}
