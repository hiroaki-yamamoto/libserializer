#include "operator.h"
#include <cassert>
using namespace std;
vector<string> &operator<<(vector<string> &vec,const string &el){
    vec.push_back(el);
    return vec;
}
vector<string> &operator>>(vector<string> &vec, string &el){
    el=vec[vec.size()-1];
    vec.pop_back();
    return vec;
}
ostream &operator<<(ostream &out,const vector<string> &vec){
    for(string el:vec) out<<el<<";"<<endl;
    return out;
}
istream &operator>>(istream &in,vector<string> &vec){
    assert(in);
    while(!in.eof()){
        string l;
        getline(in,l);
        vec<<l;
    }
    return in;
}
