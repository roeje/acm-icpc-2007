//
// Created by Jesse on 11/30/2015.
//
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <regex>

using namespace std;

void solver(string& input, string& word);
void readData(istream& input);
bool checkValidTag(string left, string& right);
string findClosing(string& input);
string createTag(string& input);
string createClosingTag(string &input);
stack <string> tagStack;

/*Regex expressions used to located opening and closing tags within text data*/
regex openTag("(<([A-Z])>)");
regex closingTag("(<\/([A-Z])>)");

void readData(istream &input){
    string c;

    /*read in each word delimited by ws*/
    while(input >> ws >> c){

        /*Words less than the min tag size of 3 are not considered*/
        if(c.length() >= 3){
            string temp = "";
            solver(c, temp);
        }
    }
}

/*Logic method used to check for valid tags and valid tag pairs*/
void solver(string& input, string& word){

    /*If end of paragraph is hit and stack is not empty, create error message*/
    if (input == "#") {
        if (tagStack.empty()) {
            cout << "Correctly tagged paragraph" << endl;
            return;
        }
        else {
            cout << "Expected " << createClosingTag(tagStack.top()) << " found #" << endl;

            /*Clear stack of remaining items*/
            while(!tagStack.empty()) {
                tagStack.pop();               
            }
            return;
        }
    }
    
    if(input.length() == 0){
        return;
    }
    
    if(input.at(0) == '<'){

        
        if(input.length() > 2 && input.at(1) == '/'){
            word = findClosing(input);
        }else{
            word = createTag(input);
        }

        /*If a tag matches an open tag, push to stack for later comparison*/
        if(regex_match(word.begin(), word.end(), openTag)){
            tagStack.push(word);
            word = "";
        }

        else if(regex_match(word.begin(), word.end(), closingTag)){
            if(tagStack.empty()){
                cout << "Expected " << "#" << " found " << word << endl;
                for(auto &dump = tagStack; !dump.empty(); dump.pop()){}
                return;
            }
                
            else if(checkValidTag(tagStack.top(), word) ){

                tagStack.pop();
            }
                
            else{
                cout << "Expected " << createClosingTag(tagStack.top()) << " found " << word << endl;
                for(auto &dump = tagStack; !dump.empty(); dump.pop()){}
                return;
            }

            word = "";
        }

    }
    string temp = input.substr(1);
    solver(temp, word);
}

bool checkValidTag(string left, string &right){
    left = "</" + left.substr(1);
    if(left == right){
        return true;
    }
    return false;
}

string createTag(string &input){
    if(input.length() < 3){
        return "";
    }
    string result = "<";
    int i = 1;

    while(i < input.length() && (input.at(i) >= 'A' && input.at(i) <= 'Z') && input.at(i) != '>'){
        result += input.at(i);
        ++i;
    }
    result += '>';
    return result;
}

string createClosingTag(string &input){
    return "</" + input.substr(1);
}


string findClosing(string &input){
    if(input.length() < 3){
        return "";
    }
    string result = "</";
    int i = 2;
    while(i < input.length() && (input.at(i) >= 'A' && input.at(i) <= 'Z') && input.at(i) != '>'){
        result += input.at(i);
        ++i;
    }
    result += '>';
    return result;
}

int main() {
    istream& data = cin;
    readData(data);
}
