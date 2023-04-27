#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        vector<unsigned long long> w;
        int lastIndex = k.size()-1;
        vector<char> sixChar; 
        while (lastIndex >= 0) {
            sixChar.push_back(k[lastIndex]);
            lastIndex--;
            if (sixChar.size() == 6){
                w.push_back(sixDigitConversion(sixChar));
                sixChar.clear();
            }
        }
        w.push_back(sixDigitConversion(sixChar));
        while (w.size() < 5) {
            w.push_back(0);
        }
        for (size_t i = 0; i < w.size(); i++) {
            cout << i << " " << w[i] << endl;
        }
        return rValues[0]*w[4] + rValues[1]*w[3] + rValues[2]*w[2] + rValues[3]*w[1] + rValues[4]*w[0];
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        letter = tolower(letter);
        if (isalpha(letter)) {
            return int(letter - 97);
        } else {
            return int(letter - 48 + 26);
        }
    }

    unsigned long long sixDigitConversion(vector<char> ch) const {
        //reverse 
        vector<unsigned long long> a;
        for (size_t i = 0; i < ch.size(); i++) {
            a.push_back(letterDigitToNumber(ch[i]));
        }
        while (a.size() < 6) {
            a.push_back(0);
        }
        cout << a[5] << " " << a[4] << " " << a[3] << " " << a[2] << " "<< a[1] << " " << a[0] << endl; 
        unsigned long long ans = ((((((a[5])*36 + a[4])*36 + a[3])*36 + a[2])*36 + a[1])*36 + a[0]);
        return ans;
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
