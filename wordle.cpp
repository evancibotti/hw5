#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helperfunct(string& currword, int currindex, string floating, const set<string>& valwords, set<string>& answers);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict){
  // Add your code here
  // set initial
  string currword = in;
  // create set of strings to return
  set<string> answers;
  // call helper
  helperfunct(currword, 0, floating, dict, answers);
  // return
  return answers;
}

// Define any helper functions here
void helperfunct(string& currword, int currindex, string floating, const set<string>& valwords, set<string>& answers){
  // base case for helper is when the word is complete
  if(static_cast<size_t>(currindex) == currword.size()){
    if(floating.empty() == true){
      if(valwords.find(currword) != valwords.end()){
        answers.insert(currword);
      }
    }
    // end the function
    return;
  }

  // make sure theres not a letter in the current spot in the word
  if(currword[currindex] != '-'){
    // call helper and progress into the word
    helperfunct(currword, currindex+1, floating, valwords, answers);
  }

  // now try to fill in letters if its not
  if(currword[currindex] == '-'){
    // check the floating letters to see if they fit
    for(size_t i = 0; i < floating.size(); ++i){
      // insert into word
      currword[currindex] = floating[i];
      // save new floating string without character
      string tempfloat = floating;
      tempfloat.erase(i, 1);
      // recursive call
      helperfunct(currword, currindex+1, tempfloat, valwords, answers);
      // backtrack 
      currword[currindex] = '-';
    }

    // now check if a non floating letter can be used
    // figure out how many blanks are left
    int blanksamt = 0;
    for(size_t i = currindex+1; i < currword.size(); ++i){
      if(currword[i] == '-'){
        blanksamt++;
      }
    }

    // only do it if theres enough blanks 
    if(floating.size() <= static_cast<size_t>(blanksamt)){
      // try all letters
      for(char c = 'a'; c <= 'z'; ++c){
        // insert into word
        currword[currindex] = c;
        // call recursively
        helperfunct(currword, currindex+1, floating, valwords, answers);
        // backtrack 
        currword[currindex] = '-';
      }
    }
  }
}