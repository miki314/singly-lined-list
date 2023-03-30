#include<iostream>
#include<fstream>
#include<memory>
#include<string>
#include"list.h"

template<typename T>
List<T>::List(T x)
{
    first.data=x;
    size=1;
}

template<typename T>
List<T>::List(const List<T>& x)
{
    this->size=x.size;
    this->first=x.first;
}

template<typename T>
void List<T>::push_back(T x)
{
    if(!size)
    {
        first[size].data=x;
        size++;
        return;
    }

    first[size-1].next.reset(new li);
    first[size-1].next->data=x;
    size++;
}

template<typename T>
void List<T>::pop_back()
{
    first[size-2].next=nullptr;
    size--;
}

template<typename T>
void List<T>::push_front(T x)
{
    if(!size)
    {
        first[size].data=x;
        size++;
        return;
    }

    pointer tmp;
    tmp.swap(first.next);
    
    first.next.reset(new li);
    first.next->data=first.data;
    first.data=x;
    first.next->next.swap(tmp);
    
    size++;    
}

template<typename T>
void List<T>::pop_front()
{
    pointer tmp;
    tmp.swap(first.next->next);
    
    first.data=first.next->data;
    first.next.swap(tmp);
    size--;
}

template<typename T>
void List<T>::insert(T x, int y)
{
    if(y==0)
    {
        this->push_front(x);
        return;
    }
    if(y==size)
    {
        this->push_back(x);
        return;
    }

    pointer tmp=nullptr;
    tmp.swap(first[y-1].next);

    first[y-1].next.reset(new li);
    first[y-1].next->data=x;
    first[y-1].next->next.swap(tmp);

    size++;
}

template<typename T>
void List<T>::remove(int y)
{
    if((y>=size)||(y<0)) return;
    if(y==0) return this->pop_front();
    if(y==size-1) return this->pop_back();

    pointer tmp=nullptr;
    tmp.swap(first[y].next);
    first[y-1].next.swap(tmp);
    size--;
}

template<typename T>
int List<T>::find(T x)
{
    for(int i=0;i<size;i++)
    {
        if(x==first[i].data) return i;
    }
    return -1;
}

template<typename T>
void List<T>::sort()
{
    for(int i=1;i<size;i++)
    {
        T x = first[i].data;
        int j=i;
        while((j>0)&&(first[j-1].data>first[j].data))
        {
            T tmp=first[j].data;
            first[j].data=first[j-1].data;
            first[j-1].data=tmp;
            j--;
        }
    }
}

template<typename T>
void List<T>::interface()
{
    std::cout
    <<"1[value, position] add an element"   <<'\n'
    <<"2[position] remove an element"       <<'\n'
    <<"s[filename] save"                    <<'\n'
    <<"o[filename] open list from file"     <<'\n'
    <<"3[value} search value within list"   <<'\n'
    <<"4 show size of the list"             <<'\n'
    <<"5 sort"                              <<'\n'
    <<"6 see lists content"                 <<'\n'
    <<"h helt"                              <<'\n'
    <<"q quit"                              <<'\n';
    std::string arg;
    T val; //value
    int pos; //position
    while(std::cin>>arg)
    {
        if(arg.size()>1)
        {
            system("clear");
            std::cout
            <<"1[value, position] add an element"   <<'\n'
            <<"2[position] remove an element"       <<'\n'
            <<"s[filename] save"                    <<'\n'
            <<"o[filename] open list from file"     <<'\n'
            <<"3[value} search value within list"   <<'\n'
            <<"4 show size of the list"             <<'\n'
            <<"5 sort"                              <<'\n'
            <<"6 see lists content"                 <<'\n'
            <<"h helt"                              <<'\n'
            <<"q quit"                              <<'\n';
            continue;
        }

        switch (arg[0])
        {
        case '1':
            std::cin>>val>>pos;
            this->insert(val,pos);
            break;
        case '2':
            std::cin>>pos;
            this->remove(pos);
            break;
        case '3':
            std::cin>>pos;
            std::cout<<this->find(pos);
            break;
        case '4':
            std::cout<<this->getSize()<<std::endl;
            break;
        case '5':
            this->sort();
            break;
        case 's':
            std::cin>>arg;
            this->save(arg);
            break;
        case '6':
            std::cout<<*this;
            break;
        case 'o':
            std::cin>>arg;
            this->load(arg);
            break;
        case 'q':
            return;
        default:
            system("clear");
            std::cout
            <<"1[value, position] add an element"   <<'\n'
            <<"2[position] remove an element"       <<'\n'
            <<"s[filename] save"                    <<'\n'
            <<"o[filename] open list from file"     <<'\n'
            <<"3[value} search value within list"   <<'\n'
            <<"4 show size of the list"             <<'\n'
            <<"5 sort"                              <<'\n'
            <<"6 see lists content"                 <<'\n'
            <<"h helt"                              <<'\n'
            <<"q quit"                              <<'\n';
        }
    }
}

template<typename T>
void List<T>::save(std::string file)
{
    std::ofstream os;
    os.open(file);
    os<<*this;
    os.close();
}

template<typename T>
void List<T>::load(std::string file)
{
    std::ifstream is;
    std::string element;

    is.open(file);
    while(is>>element) this->push_back(element);
    is.close();
}

template<>
void List<int>::load(std::string file)
{
    std::ifstream is;
    std::string element;

    is.open(file);
    while(is>>element) this->push_back(stoi(element));
    is.close();
}

template<>
void List<double>::load(std::string file)
{
    std::ifstream is;
    std::string element;

    is.open(file);
    while(is>>element) this->push_back(stod(element));
    is.close();
}

template<>
void List<float>::load(std::string file)
{
    std::ifstream is;
    std::string element;

    is.open(file);
    while(is>>element) this->push_back(stof(element));
    is.close();
}

template<typename T>
void List<T>::operator=(List<T> x)
{
    this->size=x.size;
    this->first=x.size;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, List<T>& x)
{
    for(int i=0;i<x.size;i++)
    {
        os<<x.first[i].data<<' ';
    }
    return os;
}

template<typename T>
std::istream& operator>>(std::istream& is, List<T>& x)
{
    T tmp;
    while(is>>tmp) x.push_back(tmp);
    return is;
}