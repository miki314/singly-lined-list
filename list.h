#include<iostream>
#include<memory>

template<class T>
class List
{
    struct li //node of the list
    {
        T data;
        std::shared_ptr<li> next=nullptr;

        li& operator[](int x)
        {
            if(x==0) return *this;
            return next->operator[](x-1);
        }
    };

    typedef std::shared_ptr<li> pointer;
    li first;
    int size;
    
    public:

    // Constructors:
    List() {size=0;}
    List(T x);
    List(const List<T>& x);

    // Functions to insert and delete elements:
    void push_back(T x);
    void pop_back();

    void push_front(T x);
    void pop_front();

    void insert(T x, int y);
    void remove(int y);

    //Serialisation
    void load(std::string file);
    void save(std::string file);

    //Other functions
    int getSize() {return size;}
    int find(T x); //Return position of the looked value, or -1 if there is nu such value
    void sort();
    void interface();
    
    //Operators
    li& operator[](int x) {return first[x];}
    void operator=(List<T> x);
    
    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, List<U>& x);

    template<typename U>
    friend std::istream& operator>>(std::istream& is, List<U>& x);
};