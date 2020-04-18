
#include "generate_56k.h"
#include "permute.h"
#include "DES.h"

//bits perdus mis à zéro
int PC2inv[56] = {
	5,	24,	7,	16,	6,	10,
	20,	18,	0,	12,	3,	15,
	23,	1,	9,	19,	2,	0,
	14,	22,	11,	0,	13,	4,
	0,	17,	21,	8,	47,	31,
	27,	48,	35,	41,	0,	46,
	28,	0,	39,	32,	25,	44,
	0,	37,	34,	43,	29,	36,
	38,	45,	33,	26,	42,	0,
	30,	 40
};

//bits parité
int PC1inv[64] = {
	8,	16,	24,	56,	52,	44,
	36,	0,	7,	15,	23,	55,
	51,	43,	35,	0,	6,	14,
	22,	54,	50,	42,	34,	0,
	5,	13,	21,	53,	49,	41,
	33,	0,	4,	12,	20,	28,
	48,	40,	32,	0,	3,	11,
	19,	27,	47,	39,	31,	0,
	2,	10,	18,	26,	46,	38,
	30,	0,	1,	9,	17,	25,
	45,	37,	29,	0
};

string permute_bigger(string k, int* arr, int n) 
{ 
    string tmp = ""; 
    for (int i = 0; i < n; i++) 
    { 
		if(arr[i] > 0)
		{
			tmp += k[arr[i] - 1];
		}
		else
		{
			tmp += '0';
		}
    } 
    return tmp; 
}  

string ajout_bits_test(string key, int i)
{
	string i_str = std::bitset<8>(i).to_string();
	string key_to_add = "0000000000000000000000000000000000000000000000000000000000000000";
	key_to_add[13] = i_str[0];
	key_to_add[14] = i_str[1];
	key_to_add[18] = i_str[2];
	key_to_add[19] = i_str[3];
	key_to_add[50] = i_str[4];
	key_to_add[53] = i_str[5];
	key_to_add[57] = i_str[6];
	key_to_add[59] = i_str[7];
	//cout << key_to_add << endl;
	//cout << "key in ajoutbitstest : " << key << endl;
	//cout << xor_(key, key_to_add) << endl << endl;
	
	
	return xor_(key, key_to_add);
}

string search_key64(string key, string clair, string chiffre)
{
	//récupération de la clé avec 8 bits de parité et 8 bits à trouver. Ils sont initialisés à 0.
	string key_56 = permute_bigger(permute_bigger(key, PC2inv, 56), PC1inv, 64);
	
	string key_56test = key_56;
	string chiffre_test = "";
	
	cout << "cherche le chiffré suivant : " << chiffre << endl;
	//position des bits à trouver : 14, 15, 19, 20, 51, 54, 58, 60
	for(int i = 0; i<256; i++)
	{
		//cout << "key 56 : " << key_56 << endl;
		key_56test = ajout_bits_test(key_56, i);
		chiffre_test = DES(bin2hex(clair), bin2hex(key_56test));
		
		//cout << "key : " << key_56test << " result : " << hex2bin(chiffre_test) << endl << endl;
		
		if(hex2bin(chiffre_test) == chiffre)
		{
			cout << "found key : " << key_56test << endl;
			cout << "to hex : " << bin2hex(key_56test) << endl;
			return key_56test;
		}
	}
	cout << "no key found" << endl;
	
	
	return "";
	
}
