#ifndef DES_H
#define DES_H

#include <bits/stdc++.h> 
using namespace std; 

string hex2bin(string s);
string bin2hex(string s);
string shift_left(string k, int shifts);
string xor_(string a, string b);
string encrypt(string pt, vector<string> rkb, vector<string> rk);
string DES(string pt, string key) ;

#endif
