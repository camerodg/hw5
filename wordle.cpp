// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordleHelper(
std::string& in,
std::string& floating,
const std::set<std::string>& dict, std::set<std::string>& output,int currIndex);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> output;
		string input = in;
		string floated = floating;
    wordleHelper(input, floated, dict, output, 0);
    return output;
}

// Define any helper functions here
void wordleHelper(
    std::string& in,
    std::string& floating,
    const std::set<std::string>& dict, std::set<std::string>& output, int currIndex)
    {
        //check and see how many dashes there are within the problem 
         char dash = '-';
         unsigned int dashes = 0;
        //word is the length of a possible guess for the word 
        for(unsigned int i = 0; i < in.size(); i++)
        {
            if(in[i] == dash)
            {
                dashes++;
            }
        }

        //base case, no dashes = add this word to the set of outputted words 
          if(dashes == 0)
          {
      
            if(dict.find(in) != dict.end() && currIndex == int(in.size()))
            {
							//insert into the set of outputted strings 
                output.insert(in);
            }
            return;
          }

        //go to the next index
        if(in[currIndex] != '-')
        {
				currIndex = currIndex+1;
         wordleHelper(in,floating, dict, output, currIndex);
          return;
        }


        //if the amount of dashes == floating string 
        //meaning it is all dashes 
        if(dashes == floating.size())
        {
            for(unsigned int i = 0; i < floating.size(); i++)
            {
                in[currIndex] = floating[i];
                string nextFloating = floating;
                nextFloating.erase(i,1);
								currIndex = currIndex+1;
                wordleHelper(in,floating, dict, output, currIndex);
            }
        }
        else{
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
        unsigned int n = alphabet.length();
				  //iterate through the whole alphabet
					for(unsigned int i = 0; i <= n; i++)
					{
							char x = alphabet[i];
							in[currIndex] = x;
							//if the letter isn't present within the word 
							if(floating.find(x) == std::string::npos)
							{
								 currIndex = currIndex+1;
									wordleHelper(in,floating, dict, output, currIndex);
							}
							else
							{
									string nextFloating = floating;
									//delete the current char from the alphabet 
									nextFloating.erase(floating.find(x),1);
									currIndex = currIndex+1;
									wordleHelper(in, nextFloating, dict, output, currIndex);
							}
					}
				}
}
