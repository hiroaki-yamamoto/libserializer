#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;
vector<string> &operator<<(vector<string> &,const string &);
vector<string> &operator>>(vector<string> &, string &);
ostream &operator<<(ostream &,const vector<string> &);
istream &operator>>(istream &in,vector<string> &vec);
