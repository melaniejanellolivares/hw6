#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <cctype>

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
        std::string temp = k;
        int len = k.length();
        int loops = k.length()/6;
        long long arr[5] = {0,0,0,0,0};

        if(k.length() % 6 != 0){
            loops += 1;
        }
        // std::cout << "value = " << k << " should be = " <<  k.length() << " loops = " << loops << std::endl;


        for(int i = 0; i < loops; i++){
            long long val = 0;
            int begin = len - 6;
            int end = len; 
            if(begin < 0){
                begin = 0;
                end = len; 
            }
            
            for(int j = begin; j < end; j++){
                if(j == end - 1){
                    val += letterDigitToNumber(temp[j]); 
                    // std::cout << "hello i am here " << val << std::endl;
                    continue;
                }
                val = (val + letterDigitToNumber(temp[j])) * 36 ;
				
            }
            arr[i] = val;//delete last 6
            //temp.erase(begin - 1);
            len = len - 6;
        }
        long long final = 0;

        for(int i = 0; i < 5; i++){
            final = final + rValues[i]*arr[4-i];
            std::cout << "arr = "  << arr[4-i] << " random  = " << rValues[i] << " final = " << final << std::endl;
        }

        return final;



        


    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it

        int ascii = int(tolower(letter));

        if(ascii >= 48 && ascii <= 57 ){
            return ascii - 48 + 26;
        }
        return ascii - 97; 

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
