#ifndef ASSIGNMENTCLASSES_H_
#define ASSIGNMENTCLASSES_H_


#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib> 

using namespace std;

/*
		
		cout << endl;
		for (int i = 0; i < keyHalf; i++) { cout << left[i]; }
		cout << endl;
		for (int i = 0; i < keyHalf; i++) { cout << right[i]; }

*/

class Sdes {
public:

	/* for LS-2 and LS-1 */
	vector<int> shift(int shiftAmount, vector<int> key) 
	{
		vector<int> temp;
		vector<int> left;
		vector<int> right;

		
		int keySize = key.size();
		int keyHalf = keySize / 2;

		for (int i = 0; i < keyHalf; i++)
		{
			left.push_back(key[i]);
			right.push_back(key[i + keyHalf]);
		}
		
		// shift amout 1
		if (shiftAmount == 1) {
			// do left first

			vector<int> holder;
			int lone = left[0];

			for (int i = 1; i < keyHalf; i++)
			{
				holder.push_back(left[i]);
			}
			holder.push_back(lone);
			left.clear();
			left = holder;

			// do right
			holder.clear();
			int rone = right[0];

			for (int i = 1; i < keyHalf; i++)
			{
				holder.push_back(right[i]);
			}
			holder.push_back(rone);
			right.clear();
			right = holder;
		}
		else if (shiftAmount == 2) {
			// do left first
			vector<int> holder;
			int lone = left[0];
			int ltwo = left[1];
			for (int i = 2; i < keyHalf; i++)
			{
				holder.push_back(left[i]);
			}
			holder.push_back(lone);
			holder.push_back(ltwo);
			left.clear();
			left = holder;

			// do right
			holder.clear();
			int rone = right[0];
			int rtwo = right[1];
			for (int i = 2; i < keyHalf; i++)
			{
				holder.push_back(right[i]);
			}
			holder.push_back(rone);
			holder.push_back(rtwo);
			right.clear();
			right = holder;
		}
		else {
			cout << "\nWRONG SHIFT AMOUNT!!!!\n";
		}

		// combine left and right into temp and return
		for (int i = 0; i < keyHalf; i++)
		{
			temp.push_back(left[i]);
		}
		for (int i = 0; i < keyHalf; i++)
		{
			temp.push_back(right[i]);
		}
		return temp;
	}

	/* Get k1 and k2 */
	pair<vector<int>, vector<int>> getKeys(vector<int> ikey, vector<int> pTen, vector<int> pEight)
	{
		vector<int> keyOne;
		vector<int> keyTwo;
		vector<int> TempOne;
		vector<int> TempTwo;
		int length = ikey.size();
		// Apply pTen
		for (int i = 0; i < length; i++)
		{
			keyOne.push_back(ikey[(pTen[i]) - 1]);
			keyTwo.push_back( ikey[(pTen[i]) - 1]);
		}

		// Apply shift on both keys
		TempOne = shift(1, keyOne);
		TempTwo = shift(1, keyTwo);

		keyOne = TempOne;
		keyTwo = TempTwo;

		TempOne.clear();
		TempTwo.clear();

		/* Apply pEight to get keyOne */
		for (int i = 0; i < 8; i++)
		{
			TempOne.push_back(keyOne[(pEight[i]) - 1]);
		}
		keyOne = TempOne;

		// shift key2 2 more times to get correct value
		TempTwo = shift(2, keyTwo);
		keyTwo = TempTwo;

		TempTwo.clear();
		/* Apply pEight to get keyTwo */
		for (int i = 0; i < 8; i++)
		{
			TempTwo.push_back(keyTwo[(pEight[i]) - 1]);
		}
		keyTwo = TempTwo;
		cout << endl << "k1 = {";
		for (int i = 0; i < 8; i++) { cout << keyOne[i]; }
		cout <<  "}   ";
		cout << "k2 = {";
		for (int i = 0; i < 8; i++) { cout << keyTwo[i]; }
		cout <<  "}   \n";
		return make_pair(keyOne, keyTwo);
	}

	/* Initial Permutation */
	vector<int> initialPermutation(vector<int> plaintext, vector<int> ip)
	{
		vector<int> temp;
		int len = plaintext.size();
		for (int i = 0; i < 8; i++)
		{
			temp.push_back(plaintext[(ip[i]) - 1]);
		}

		cout << endl << "Plaintext after ip: ";
		for (int i = 0; i < len; i++) { cout << temp[i]; }
		return temp;
	}

	/* FINAL PERMUTATION */
	vector<int> finalPermutation(vector<int> plaintext, vector<int> fp)
	{
		vector<int> temp;
		int len = plaintext.size();
		for (int i = 0; i < 8; i++)
		{
			temp.push_back(plaintext[(fp[i]) - 1]);
		}

		cout << endl << "Plaintext after fp: ";
		for (int i = 0; i < len; i++) { cout << temp[i]; }
		return temp;
	}

	/* XOR FUNCTION */
	vector<int> xorFunction(vector<int> one, vector<int> two)
	{
		vector<int> temp;

		int size = one.size();

		for (int i = 0; i < size; i++)
		{
			if (two[i] == one[i]) {
				temp.push_back(0);
			}
			else if (two[i] != one[i]) {
				temp.push_back(1);
			}
		}
		return temp;
	}

	/* BINARY TO DECIMAL FUNCTION WORKS ONLY WITH TWO DIGIT BINARIES */
	int toDec(string s)
	{
		if (s == "00") {
			return 0;
		}
		else if (s == "01") {
			return 1;
		}
		else if (s == "10") {
			return 2;
		}
		else if (s == "11") {
			return 3;
		}
		else {
			cout << "wrong string !!!";
		}

		return 100;
	}

	/* DEC TO BINARY */
	vector<int> toBin(int r)
	{
		vector<int> result;
		// Only works for integers from 0-3 (use case only for sboxes)
		if (r == 0) {
			result = { 0,0 };
		}
		else if (r == 1) {
			result = { 0,1 };
		}
		else if (r == 2) {
			result = { 1,0 };
		}
		else if (r == 3) {
			result = { 1,1 };
		}
		else
			return result; // return empty vector
	}

	/* SBOX FUNCTION */
	vector<int> sboxFunction(vector<int> res, vector<vector<int>> SZero, vector<vector<int>> SOne)
	{
		vector<int> de = { 1,2 };
		vector<int> returnVector;

		string rcol, lcol, rrow, lrow;
		int sOrow, sOcol, sZrow, sZcol;

		int rl, rr; // result left and right
		int length = res.size();

		lrow = to_string(res[0])+ to_string(res[3]);
		lcol = to_string(res[1])+ to_string(res[2]);
		rrow = to_string(res[4])+ to_string(res[7]);
		rcol = to_string(res[5])+ to_string(res[6]);
		sZrow = toDec(lrow);
		sZcol = toDec(lcol);
		sOrow = toDec(rrow);
		sOcol = toDec(rcol);

		rl = SZero[sZrow][sZcol];
		rr = SOne[sOrow][sOcol];

		vector<int>left = toBin(rl);
		vector<int>right = toBin(rr);

		for (int i = 0; i < right.size(); i++)
		{
			returnVector.push_back(left[i]);
		}
		for (int i = 0; i < right.size(); i++)
		{
			returnVector.push_back(right[i]);
		}

		return returnVector;
	}

	/* SWAP FUNCTION (SWAPS HALVES AROUND) */
	vector<int> swapHalves(vector<int> res)
	{
		int size = res.size();
		int halfsize = (size / 2);

		vector<int> left, right, returnVector;

		for (int i = 0; i < halfsize; i++)
		{
			left.push_back(res[i]);
			right.push_back(res[i+halfsize]);
		}
		// change order of insertion to swap halves
		for (int i = 0; i < halfsize; i++)
		{
			returnVector.push_back(right[i]); // here
		}
		for (int i = 0; i < halfsize; i++)
		{
			returnVector.push_back(left[i]);
		}

		

		return returnVector;

	}

	
	/* ENCRYPTION PROCESS */
	/* STEPS														*/

	/* 1: EXPANSION PERMUTATION ON THE RIGHT						*/
	// -> EP(IPR(R))

	/* 2: XOR WITH K1												*/
	// -> (EP(IPR(R))) xor K1

	/* 3: USE S-BOXES												*/
	// -> S-Boxes((EP(IPR(R))) xor K1)

	/* 4: PERMUTATE WITH P4											*/
	// -> P4(S-Boxes((EP(IPR(R))) xor K1))

	/* 5: XOR WITH LEFT HAND OF IPR									*/
	// -> (P4(S-Boxes((EP(IPR(R))) xor K1))) xor IPR(L)

	/* 6: COMBINE RESULT WITH RIGHT HALF OF IPR						*/
	// -> ((P4(S-Boxes((EP(IPR(R))) xor K1))) xor IPR(L)) + IPR(R)
	
	vector<int> round(vector<int> ipr, vector<int> EP, vector<vector<int>>SZero, 
		vector<vector<int>> SOne, vector<int> pFour, vector<int> keyOne)
	{
		/* STEPS */
		/* 1: EXPANSION PERMUTATION ON THE RIGHT = step1R		*/
		/* 2: XOR WITH K1 = step2R								*/
		/* 3: USE S-BOXES = step3R 								*/
		/* 4: PERMUTATE WITH P4	= step4R 						*/
		/* 5: XOR WITH LEFT HAND OF IPR	= step5R 				*/
		/* 6: COMBINE RESULT WITH RIGHT HALF OF IPR	= step6R	*/
		

		/* Vector used to store result after every step */
		vector<int> step1R, step2R, step3R, step4R, step5R, step6R, step7R;
		vector<int> leftIPR, rightIPR;
		int iprSize = ipr.size();
		int iprHalfSize = iprSize/2;
		int epSize = EP.size();

		// SPLIT THE IPR INTO TWO HALVES
		for (int i = 0; i < iprHalfSize; i++)
		{
			leftIPR.push_back(ipr[i]);
			rightIPR.push_back(ipr[i + iprHalfSize]);
		}

		for (int i = 0; i < epSize; i++)
		{
			step1R.push_back(rightIPR[(EP[i]) - 1]);
		}

		step2R = xorFunction(step1R, keyOne);

		step3R = sboxFunction(step2R, SZero, SOne);

		for (int i = 0; i < 4; i++)
		{
			step4R.push_back(step3R[(pFour[i])-1]);
		}
	
		step5R = xorFunction(step4R, leftIPR);

		for (int i = 0; i < 4; i++)
		{
			step6R.push_back(step5R[i]);
		}for (int i = 0; i < 4; i++)
		{
			step6R.push_back(rightIPR[i]);
		}		

		return step6R;

	}

	/*DO SDES ENCRYPTION */
	vector<int> sdesEncrypt(vector<int> plaintext, vector<int> initialKey, 
		vector<int> pTen, vector<int> pEight, vector<int> Ip, vector<int> pFinal,
		vector<int> EP, vector<vector<int>> SZero, vector<vector<int>> SOne, vector<int> pFour)
	{
		pair<vector<int>, vector<int>> keys;   
		vector<int> initialPermutationResult;
		vector<int> roundOneresult, roundTworesult;
		vector<int> ciphertext;
		
		keys = getKeys(initialKey, pTen, pEight);
		initialPermutationResult = initialPermutation(plaintext, Ip);
		roundOneresult = round(initialPermutationResult, EP, SZero, SOne, pFour, keys.first);
		cout << endl << "Result after swap: ";
		roundTworesult = swapHalves(roundOneresult);
		for (int i = 0; i < roundTworesult.size(); i++) { cout << roundTworesult[i]; }
		roundTworesult = round(roundTworesult, EP, SZero, SOne, pFour, keys.second);
		ciphertext = finalPermutation(roundTworesult, pFinal);
		return ciphertext;
	}

	/* DO SDES DECRYPTION (BASICALLY SWAP K1 AND K2 ORDER) */
	vector<int> sdesDecrypt(vector<int> ciphertext, vector<int> initialKey,
		vector<int> pTen, vector<int> pEight, vector<int> Ip, vector<int> pFinal,
		vector<int> EP, vector<vector<int>> SZero, vector<vector<int>> SOne, vector<int> pFour)
	{
		pair<vector<int>, vector<int>> keys;
		vector<int> initialPermutationResult;
		vector<int> roundOneresult, roundTworesult;
		vector<int> plaintext;

		keys = getKeys(initialKey, pTen, pEight);
		initialPermutationResult = initialPermutation(ciphertext, Ip);
		roundOneresult = round(initialPermutationResult, EP, SZero, SOne, pFour, keys.second);
		cout << endl << "Result after swap: ";
		roundTworesult = swapHalves(roundOneresult);
		for (int i = 0; i < roundTworesult.size(); i++) { cout << roundTworesult[i]; }
		roundTworesult = round(roundTworesult, EP, SZero, SOne, pFour, keys.first);
		plaintext = finalPermutation(roundTworesult, pFinal);

		return plaintext;
	}
};




class DiffieHellman
{
public:

	/* CONVERT N TO BINARY AND RETURN STACK */
	/*
	- Repeatedly do result = result/2 unitl result = 0
	- Push the result % 2 value into stack 
	- This builds the binary value for n
	*/
	stack<int> toBinary(int n)
	{
		stack<int> binary;
		int remainder;
		int result = n;
		while (result != 0)
		{
			remainder = result % 2;
			binary.push(remainder);
			result = result /= 2;
		}
		return binary;
	}

	/* CHECK IF A NUMBER IS A PRIME NUMBER */
	/*
	- Get the square root of p
		-> floor to round down
	- Check if the number p is within set bounds
	- If p == 1 return false as we loop starting at 2
	- Loop from 2 to rounded down square root 
	- If it is divisible by any other number except 1 and itself
		i.e. 0 remainder p%i where i = (2 to (P-1)) it is not prime.
	- If false is not returned and loop ends return true
	*/
	bool isPrime(int p)
	{
		bool isItPrime = true;
		float sqrtValue;
		int roundedDownValue;

		sqrtValue = sqrt(p);
		//cout << "\nSquare root value: " << sqrtValue;
		roundedDownValue = floor(sqrtValue);
		//cout << "\nrounded Value: " << roundedDownValue;
		// Check if number is within the bounds of 1 and 100
		if (p > 100) 
		{
			cout << "\nNUMBER IS TOO BIG!!\n";
			return false;
		}
		if (p < 1) 
		{
			cout << "\nNUMBER IS TOO SMALL!!\n";
			return false;
		}
		// one is not a prime number
		if (p == 1) 
		{
			//cout << endl << p << " is not PRIME\n";
			return false;
		}

		for (int i = 2; i < roundedDownValue + 1; i++)
		{
			int remainder = 0;
			remainder = p % i;
			if (remainder == 0) {
				return false;
			}
		}
		//cout << endl << p << " is PRIME\n";
		return isItPrime;
	}

	/* SQUARE AND MULTIPLY ALGORITHM & (ABSTRACTED INDIVIDYAL STEPS) */
	/*
	- Takes a base, exponential and mod value
	- Convert exponential to binary
	- Traverse (through popping) the stack (left to right)
	- If bit == 0 square and keep track of currentValue
	- If bit == 1 square and multiply
	- Keep looping until final currentValue is found 
	*/
	int squareAndMultiply(int base, int mod, int multVal) 
	{
		/* square -> mod -> multiply -> mod */
		int res;
		res = (base*base);		// square
		res = res % mod;		// mod
		res = res * multVal;	// multiply
		res = res % mod;		// mod
		return res;
	}

	int squareOnly(int base, int mod) 
	{
		/* square -> mod */
		int res;
		res = (base*base);	// square
		res = res % mod;	// mod	
		return res;
	}

	int squareAndMultiplyAlgorithm(int base, int expo, int modv)
	{
		stack<int> expBin;
		expBin = toBinary(expo);
		int stackSize = expBin.size();

		int currentVal = 1;
		for (int i = 0; i < stackSize; i++)
		{
			if (expBin.top() == 0)
			{
				currentVal = squareOnly(currentVal, modv);
			}
			else if (expBin.top() == 1)
			{
				currentVal = squareAndMultiply(currentVal, modv, base);
			}
			else {
				cout << "\nERROR: WRONG BINARY IN THE STACK!!\n";
			}
			expBin.pop();
		}
		return currentVal;
	}

	/* FIND THE PRIMITAVE ROOT OF P */
	/*
	DEFINITION (Primitive Root): A primitive root (PR) of a PRIME (P) number 
	is such that: PR^(P-1) mod P generates all numbers from 1 to P-1.

	- Push 1 to P-1 values into vector and sort
	- Only test candidates from 2 to P (Going above P is pointless)
	- For each candidate apply square and multiply algorithm
		-> Declare local scope variable storing numbers generated by candidate
	- Sort the generated numbers vector and compare
		-> If vectors are equal then it is a primitive root
		-> Return
	*/
	int findPrimitiveRoot(int p)
	{
		vector<int> valuesNeeded;
		for (int i = 1; i < p; i++)
		{
			valuesNeeded.push_back(i);
		}
		sort(valuesNeeded.begin(), valuesNeeded.end());

		for (int i = 2; i < p; i++) 
		{
			bool isPrimitive = true;
			vector<int> generated;
			for (int j = 1; j < p; j++) 
			{
				int resVal = squareAndMultiplyAlgorithm(i, j, p);
				generated.push_back(resVal);
			}
			sort(generated.begin(), generated.end());

			if (generated == valuesNeeded) {
				//cout << "\nGenerated value is: \n" << i << endl;
				return i;
			}
		}
		return -1; // somthing is wrong above i.e. couldnt find a primitive root
	}

	/* MAIN DIFFIE HELLMAN ALGORITHM (MANUAL) */
	/*
	- Alice & Bob calculate respective values using secret keys
	- Send A and B from above step to each other
	- B^Xa mod Prime == A^Xb mod Prime (shared Key)
	*/
	int diffieHellmanKeyExchange_manual(int prime,int g, int Xa, int Xb) {

		int Ya,Yb; // The calculated numbers after applying secret.
		int keyA, keyB;

		Ya = squareAndMultiplyAlgorithm(g, Xa, prime);
		Yb = squareAndMultiplyAlgorithm(g, Xb, prime);
		
		cout << "\nThe prime number (p) is: " << prime;
		cout << "\nThe primitive root (g) is: " << g;
		cout << "\nAlice's secret number (Xa) is: " << Xa;
		cout << "\nBob's secret number (Xb) is: " << Xb;
		cout << "\nAlice calculates (Ya) as: g^Xa mod p = " << Ya;
		cout << "\nBob calculates (Yb) as: g^Xb mod p = " << Yb;

		keyA = squareAndMultiplyAlgorithm(Yb, Xa, prime);
		keyB = squareAndMultiplyAlgorithm(Ya, Xb, prime);

		cout << "\n Alice calculates the key as: ";
		cout << "Yb^Xa mod p = " << keyA;

		cout << "\n Bob calculates the key as: ";
		cout << "Ya^Xb mod p = " << keyB;

		// prove both keys are the same
		if (keyA == keyB) {
			cout << "\nThe keys are the same!\n";
			cout << "\nThe shared secret key is: " << keyA << endl;
		}
		else {
			cout << "\nThe keys are NOT the same!!\n";
		}

		return keyA;
	}

	/* GET RANDOM NUMBER 1-100 */
	int getRandomNumber()
	{
		int randNum = (rand() % 100)+1; // from 1 to 100
		return randNum;
	}

	/* GET RANDOM PRIME NUMBER */
	int getPrimeNumber() 
	{
		int prime = getRandomNumber();
		while (isPrime(prime) != true)
		{
			prime = getRandomNumber();
		}
		return prime;
	}

	/* MAIN DIFFIE HELLMAN ALGORITHM (AUTO) */
	/*
	- SAME AS MANUAL BUT SOME VALUES ARE CALCULATED OR RANDOM
	- Alice & Bob calculate respective values using secret keys
	- Send A and B from above step to each other
	- B^Xa mod Prime == A^Xb mod Prime (shared Key)
	*/
	int diffieHellmanKeyExchange_auto() 
	{
		cout << "\nAUTO DIFFIE HELLMAN KEY EXCHANGE\n";

		// Xa and Xb are secret numbers not known to the public
		// Ya and Yb are exchanged products of applying the secret
		int prime, g, Xa, Xb, Ya, Yb, keyA, keyB;
		
		prime = getPrimeNumber();
		g;
		g = findPrimitiveRoot(prime);
		Xa = getRandomNumber();
		Xb = getRandomNumber();
		Ya = squareAndMultiplyAlgorithm(g, Xa, prime);
		Yb = squareAndMultiplyAlgorithm(g, Xb, prime);

		// out put what the random values and calculated values are
		cout << "\nThe prime number (p) is: " << prime;
		cout << "\nThe primitive root (g) is: " << g;
		cout << "\nAlice's secret number (Xa) is: " << Xa;
		cout << "\nBob's secret number (Xb) is: " << Xb;
		cout << "\nAlice calculates (Ya) as: g^Xa mod p = " << Ya;
		cout << "\nBob calculates (Yb) as: g^Xb mod p = " << Yb;

		keyA = squareAndMultiplyAlgorithm(Yb, Xa, prime);
		keyB = squareAndMultiplyAlgorithm(Ya, Xb, prime);

		// output the shared secret keys and show how they are calculated
		cout << "\n Alice calculates the key as: ";
		cout << "Yb^Xa mod p = "<<keyA;
		
		cout << "\n Bob calculates the key as: ";
		cout << "Ya^Xb mod p = " << keyB;

		// prove both keys are the same
		if (keyA == keyB) {
			cout << "\nThe keys are the same!\n";
			cout << "\nThe shared secret key is: " << keyA << endl;
		}
		else {
			cout << "\nThe keys are NOT the same!!\n";
		}
		
		return keyA;
	}
};


#endif /* ASSIGNMENTCLASSES_H_ */
