#include "permute.h"
       
string permute(string k, int* arr, int n) 
{ 
    string tmp = ""; 
    for (int i = 0; i < n; i++) { 
        tmp += k[arr[i] - 1]; 
    } 
    return tmp; 
}  

/*int main ()
{
	string message = "00001000000000101000100000100010";
	cout << permute(message, per, 32) << endl;
	return 0;
}*/
