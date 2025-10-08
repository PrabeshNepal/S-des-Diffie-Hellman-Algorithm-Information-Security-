#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <bitset>
#include <limits> 
#include <stack> 
#include <algorithm>
#include <cstdlib> 
#include "AssignmentClasses.h"

using namespace std;


bool validChoices(int cOne, int cTwo)
{
    if (cOne != 1 && cOne != 2) {
        return false;
    }

    if (cTwo != 1 && cTwo != 2) {
        return false;
    }
    return true;
}

vector<int> stov(string s)
{
    // string to vector
	vector<int> temp;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '0') {
            temp.push_back(0);
        }
        else if (s[i] == '1') {
            temp.push_back(1);
        }
        else {
            cout << "\nWRONG INPUT!!!!\n";
            temp.clear();
            return temp;
        }
    }
	// print and return vector

    for (int i = 0; i < 8; i++) { cout << temp[i]; }
	return temp;
}

int main()
{
    srand(time(0)); // seed time for better rand()
    DiffieHellman d;
    Sdes s;
    
    // Pre defined permutations for sdes
    vector<int> pTen = { 3,5,2,7,4,10,1,9,8,6 };
    vector<int> pEight = { 6,3,7,4,8,5,10,9 };
    vector<int> pFour = { 2,4,3,1 };
    vector<int> Ip = { 2,6,3,1,4,8,5,7 };
    vector<int> pFinal = { 4,1,3,5,7,2,8,6 };
    vector<int> EP = { 4,1,2,3,2,3,4,1 };
 
    vector<vector<int>> SZero = { {1,0,3,2},
                                  {3,2,1,0},
                                  {0,2,1,3},
                                  {3,1,3,2} };

    vector<vector<int>> SOne = { {0,1,2,3},
                                 {2,0,1,3},
                                 {3,0,1,0},
                                 {2,1,0,3} };

    int choiceOne;
    int choiceLoop = 1;

    while (choiceLoop == 1) 
    {
        cout << "(1) S-DES Encryption\n(2) S-DES Decryption\n"; 
        cout << "(3) Diffie Hellman Key Exchange (MANUAL)\n(4) Diffie Hellman Key Exchange (AUTO)\n";
        cin >> choiceOne;
		if (choiceOne == 1) // S-DES Encryption
        {
            vector<int> plaintext;
            vector<int> initialKey;
            string ptext, ikey;
            cout << "\nPlease enter the 8 bit plaintext: ";
            cin >> ptext;
            plaintext = stov(ptext);
            cout << "\nPlease enter 10 bit key: ";
            cin >> ikey;
            initialKey = stov(ikey);

            vector<int> sdesCiphertext;
            sdesCiphertext = s.sdesEncrypt(plaintext, initialKey,
                pTen, pEight, Ip, pFinal, EP, SZero, SOne, pFour);
            cout << endl << "Ciphertext from function: ";
            for (int i = 0; i < sdesCiphertext.size(); i++) { cout << sdesCiphertext[i]; }

        }
		else if (choiceOne == 2) // S-DES Decryption
        {
            vector<int> sdesciphertext;
            vector<int> initialKey;
            vector<int> plainText;

            string ctext, ikey;
            cout << "\nPlease enter the 8 bit cipherText: ";
            cin >> ctext;
            sdesciphertext = stov(ctext);
            cout << "\nPlease enter 10 bit key: ";
            cin >> ikey;
            initialKey = stov(ikey);

            plainText = s.sdesDecrypt(sdesciphertext, initialKey,
                pTen, pEight, Ip, pFinal, EP, SZero, SOne, pFour);

            // output
            cout << endl << "Plaintext from function: ";
            for (int i = 0; i < plainText.size(); i++) { cout << plainText[i]; }
        }
		else if (choiceOne == 3) // Diffie Hellman Key Exchange (AUTO)
        {
			int pr, g, Xa, Xb, Key;
            pr = 1; 
            while (d.isPrime(pr) != true) 
            {
                cout << "Enter a prime number between 1 and 100: ";
                cin >> pr;
            }
			cout << "\n Enter the primitive root (g) for the prime number: ";
            cin >> g;               
            cout << "\n Please Enter Alices (Xa) secret Number: \n";
            cin >> Xa;
            cout << "\n Please Enter Bobs (Xb) secret Number: \n";
            cin >> Xb;
            Key = d.diffieHellmanKeyExchange_manual(pr, g,Xa, Xb);
        }
        else
        {
            // Diffie Hellman Key Exchange (AUTO)
			d.diffieHellmanKeyExchange_auto();
        }
        cout << "\n\n(1) DO MORE\n(2) QUIT\n\n";
        cin >> choiceLoop;
    }


}
