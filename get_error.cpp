#include <bits/stdc++.h> 
#include <iostream>
#include <fstream>
#include "sbox.h"
#include "permute.h"
#include "generate_56k.h"
#include "DES.h"

using namespace std; 

//permutation
 int per_inv[32] = { 9,	17,	23,	31,
					13,	28,	2,	18,
					24,	16,	30,	6,
					26,	20,	10,	1,
					8,	14,	25,	3,
					4,	29,	11,	19,
					32,	12,	22,	7,
					5,	27,	15,	21};

//Sboxes
 int s[8][4][16] = { { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7, 
                          0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8, 
                          4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0, 
                          15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 }, 
                        { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10, 
                          3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5, 
                          0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15, 
                          13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 }, 
                        { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8, 
                          13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1, 
                          13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7, 
                          1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 }, 
                        { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15, 
                          13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9, 
                          10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4, 
                          3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 }, 
                        { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9, 
                          14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6, 
                          4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14, 
                          11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 }, 
                        { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11, 
                          10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8, 
                          9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6, 
                          4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 }, 
                        { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1, 
                          13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6, 
                          1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2, 
                          6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 }, 
                        { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7, 
                          1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2, 
                          7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8, 
                          2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 } }; 

//Expansion
int exp_d[48] = { 32, 1, 2, 3, 4, 5, 4, 5, 
                      6, 7, 8, 9, 8, 9, 10, 11, 
                      12, 13, 12, 13, 14, 15, 16, 17, 
                      16, 17, 18, 19, 20, 21, 20, 21, 
                      22, 23, 24, 25, 24, 25, 26, 27, 
                      28, 29, 28, 29, 30, 31, 32, 1 }; 

//R15 et R15'
string expand1 = "";
string expand2 = "";

 
string get_diff_crypt(string pt, string pt2, string path) 
{ 
    // Hexadecimal to binary 
    pt = hex2bin(pt); 
    pt2 = hex2bin(pt2); 
    
    ofstream f;
    f.open(path);
  
    // Initial Permutation Table 
    int initial_perm[64] = { 58, 50, 42, 34, 26, 18, 10, 2, 
                             60, 52, 44, 36, 28, 20, 12, 4, 
                             62, 54, 46, 38, 30, 22, 14, 6, 
                             64, 56, 48, 40, 32, 24, 16, 8, 
                             57, 49, 41, 33, 25, 17, 9, 1, 
                             59, 51, 43, 35, 27, 19, 11, 3, 
                             61, 53, 45, 37, 29, 21, 13, 5, 
                             63, 55, 47, 39, 31, 23, 15, 7 }; 
                             
    int initial_perm_inv[64] = { 	40, 8, 48, 16, 56, 24, 64, 32,
									39, 7, 47, 15, 55, 23, 63, 31,
									38, 6, 46, 14, 54, 22, 62, 30,
									37, 5, 45, 13, 53, 21, 61, 29,
									36, 4, 44, 12, 52, 20, 60, 28,
									35, 3, 43, 11, 51, 19, 59, 27,
									34, 2, 42, 10, 50, 18, 58, 26,
									33, 1, 41, 9, 49, 17, 57, 25, };
    // Initial Permutation 
    pt = permute(pt, initial_perm, 64); 
    pt2 = permute(pt2, initial_perm, 64); 
  
    // Splitting 
    //r16
    string left = pt.substr(0, 32); 
    //r16'
    string left_error = pt2.substr(0, 32);
    
    //r15 = l16
    string right = pt.substr(32, 32); 
    //r15' = l16
    string right_error = pt2.substr(32, 32); 
    
    //stockage de R15 et R15' expansion
    expand1 = permute(right, exp_d, 48);
    expand2 = permute(right_error, exp_d, 48);
    
    //r16 + r16'
    string diff_left = xor_(left, left_error);
    
    //r15+r15' = l16+l16'
    string diff_right = xor_(right, right_error);
    
    cout << "split et xor :  L=" << diff_left << " R=" << diff_right << endl << endl;
    f << "position faute : " << diff_right << endl; 
    
    f.close();
    return diff_left;
    
}

int solve_equation(string R15, string R15prime, string result, int box, string path)
{
	int row1 = 0;
	int col1 = 0;
	
	int row2 = 0;
	int col2 = 0;
	
	string tmp1 = "";
	string tmp2 = "";
	
	string tmpR15 = R15;
	string tmpR15prime = R15prime;
	
	string res = "";
	
	ofstream f;
    f.open(path, ios::app);
	
	string find_key = "000000";
	for(int k = 0; k < 64; k++)
	{
		find_key = std::bitset<6>(k).to_string();
		tmpR15 = xor_(R15, find_key);
		tmpR15prime = xor_(R15prime, find_key);
		
		//S(E(R15)+K)
		if(tmpR15[0] == '0' && tmpR15[5] == '0')
		{
			row1 = 0;
		}
		else if(tmpR15[0] == '0' && tmpR15[5] == '1')
		{
			row1 = 1;
		}
		else if(tmpR15[0] == '1' && tmpR15[5] == '0')
		{
			row1 = 2;
		}
		else if(tmpR15[0] == '1' && tmpR15[5] == '1')
		{
			row1 = 3;
		}
		else
		{
			cout << "ERREUR" << endl;
		}
		col1 = bin2dec(tmpR15.substr(1, 4));
		
		//S(E(R15')+K)
		if(tmpR15prime[0] == '0' && tmpR15prime[5] == '0')
		{
			row2 = 0;
		}
		else if(tmpR15prime[0] == '0' && tmpR15prime[5] == '1')
		{
			row2 = 1;
		}
		else if(tmpR15prime[0] == '1' && tmpR15prime[5] == '0')
		{
			row2 = 2;
		}
		else if(tmpR15prime[0] == '1' && tmpR15prime[5] == '1')
		{
			row2 = 3;
		}
		else
		{
			cout << "ERREUR" << endl;
		}
		col2 = bin2dec(tmpR15prime.substr(1, 4));
		
		//(S(E(R15)+K) + S(E(R15')+K))
		tmp1 = dec2bin(s[box][row1][col1]);
		tmp2 = dec2bin(s[box][row2][col2]);
		res = xor_(tmp1, tmp2);
		
		//cout << "res = " << res << "result = " << result << endl;
		if(res == result)
		{
			cout << "===MATCH===" << endl;
			f << find_key << endl;
		}
	}
	f.close();
}

int main(int argc, char** argv)
{
	
	if(argv[1] != "")
	{
		string chiffre = "878CF693C87EC079";
		string chiffre_error = argv[1];
		string msg = "";
		
		string path = "/home/user/Bureau/AttaqueDES/output/" ;
		path += argv[1];
		path += ".txt";
		ofstream f;
		
		//retourne R16+R16'
		//remplit également les variables expand1 et expand2 correspondant à E(R15) et E(R15')
		msg = get_diff_crypt(chiffre, chiffre_error, path);
		
		//Retourne P(R16+R16')
		msg = permute(msg, per_inv, 32);
		//cout << "permutation : " << msg << endl;
		f.open(path, ios::app);
		
		for(int i = 0; i < 8; i++)
		{
			f << "#" << i << "#" << endl;
			f.close();
			
			if(expand1.substr(i*6, 6) != expand2.substr(i*6, 6))
			{
				cout << "solving " << " R15 = " << expand1.substr(i*6, 6) << " R15' = " << expand2.substr(i*6, 6) << " target = " << msg.substr(i*4, 4) << " box = " << i << endl;
				solve_equation(expand1.substr(i*6, 6), expand2.substr(i*6, 6), msg.substr(i*4, 4), i, path);
			}
			f.open(path, ios::app);
			
			
		}
	}
	else
	{
		
		search_key64("010110001001001010001101000110000000010100011000", hex2bin("DF 51 8C EC BF 61 E3 D9"), hex2bin("87 8C F6 93 C8 7E C0 79 "));
	}
	return 0;
}
