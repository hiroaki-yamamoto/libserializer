#pragma once

#include<string>
#include<vector>
#include<list>
#include<map>
#include<iostream>
#include<iomanip>
#include<typeinfo>

#if defined(_WIN32)||defined(_WIN64)
__declspec(dllexport)
#endif
extern size_t tab_count;

using namespace std;

template<class S> list<S> &operator<<(list<S> &lst,const S str){
    lst.push_back(str);
    return lst;
}
template<class T> vector<T> &operator<<(vector<T> &vec,const T v){
    vec.push_back(v);
    return vec;
}
template<class S,class T> map<S,T> &operator<<(map<S,T> &m,const pair<S,T> &v){
    m.insert(v);
    return m;
}

template<class T> ostream &operator<<(ostream &out,const list<T> &ref){
    for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    out<<"list{"<<endl;
    size_t counter=1;
    for(const T value:ref){
        out<<counter<<":";
        for(size_t tab_index=0;tab_index<tab_count+1;tab_index++) out<<'\t';
        out<<value<<endl;
        counter++;
    }
    for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    out<<"}"<<endl;
    return out;
}
template<class T> ostream &operator<<(ostream &out,const vector<T> &ref){
    for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    out<<"vector{"<<endl;
    size_t counter=1;
    for(const T value:ref){
        out<<counter<<":";
        for(size_t tab_index=0;tab_index<tab_count+1;tab_index++) out<<'\t';
        out<<value<<endl;
        counter++;
    }
    for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    out<<"}"<<endl;
    return out;
}
template<class S,class T> ostream &operator<<(ostream &out,const pair<S,T> &ref){
    for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    out<<"pair{"<<endl;
        for(size_t tab_index=0;tab_index<tab_count+1;tab_index++) out<<'\t';
        out<<"\t"<<"Key("<<typeid(S).name()<<"):"<<ref.first<<endl;
        for(size_t tab_index=0;tab_index<tab_count+1;tab_index++) out<<'\t';
        out<<"\t"<<"Value("<<typeid(T).name()<<"):"<<ref.second<<endl;
        for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    out<<"}"<<endl;
    return out;
}

template<class S,class T> ostream &operator<<(ostream &out,const map<S,T> &ref){
    for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    size_t counter=1;
    out<<"map{"<<endl;
    tab_count++;
    for(const pair<S,T> p:ref){
        out<<counter<<":"<<p;
        counter++;
    }
    tab_count--;
    for(size_t tab_index=0;tab_index<tab_count;tab_index++) out<<'\t';
    out<<"}"<<endl;
    return out;
}
