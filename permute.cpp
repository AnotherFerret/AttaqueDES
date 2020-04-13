#include "permute.h"
       
string permute(string k, int* arr, int n) 
{ 
    string tmp = ""; 
    for (int i = 0; i < n; i++) { 
        tmp += k[arr[i] - 1]; 
    } 
    return tmp; 
}  
