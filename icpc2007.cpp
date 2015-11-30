//
// Created by Jesse on 11/30/2015.
//
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <regex>
#include <vector>
using namespace std;

//reads the data in
void read_data(istream &input);
//checks for a valid tag
vector <string> get_tag(const string &io);
bool is_contained(const string &io, const char find);
bool tag_checker(string lhs, const string &rhs);
void clear_stack();
string slash_tag_maker(string &io);
//stores the current tags.
stack <string> tag_holder;
regex tag("(<([A-Z])>)");
string slash_tag_finder(const string &io);
string tag_make(const string &io);

regex slash_tag("(<\/([A-Z])>)");

//---------------------------------------------------------------------------------
// A 163 style bullshit method. Cuz i was mad at regular expressions. It should be
// noted that this statement will break when the tag doesn't follow a specific order.
// For instance, "</...stuff ABCJKL(capitals)>" followed by a </B> correctly formatted tag.
// I've not tested it. Works for basic things. Needs nested if statements.
//---------------------------------------------------------------------------------
void check_tag(const string &io, string &curr_res){
    if(io == "#"){
        if(tag_holder.empty()){
            cout << "Correctly tagged paragraph"<<endl;
            return;
        }else{
            cout << "Expected "<<slash_tag_maker(tag_holder.top())<<" found #"<<endl;
            for(auto &dump = tag_holder; !dump.empty(); dump.pop()){}
            return;
        }
    }
    if(io.length() == 0){
        return;
    }
    if(io.at(0)=='<'){

        if(io.length()>2 && io.at(1) == '/'){
            curr_res = slash_tag_finder(io);
        }else{
            curr_res = tag_make(io);
        }

        if(regex_match(curr_res.begin(), curr_res.end(), tag)){
            tag_holder.push(curr_res);
            curr_res = "";
        }

        else if(regex_match(curr_res.begin(), curr_res.end(), slash_tag)){
            if(tag_holder.empty()){
                cout << "Expected "<<"#"<< " found "<<curr_res<<endl;
                for(auto &dump = tag_holder; !dump.empty(); dump.pop()){}
                return;
            }
            else if(tag_checker(tag_holder.top(), curr_res) ){

                tag_holder.pop();
            }
            else{
                cout << "Expected "<<slash_tag_maker(tag_holder.top())<<" found "<<curr_res<<endl;
                for(auto &dump = tag_holder; !dump.empty(); dump.pop()){}
                return;
            }

            curr_res = "";
        }

    }
    check_tag(io.substr(1), curr_res);
}


string tag_make(const string &io){
    if(io.length()<3){
        return "";
    }
    string result = "<";
    int i = 1;

    while( i<io.length() && (io.at(i) >= 'A' && io.at(i) <= 'Z') && io.at(i) != '>'){
        result += io.at(i);
        ++i;
    }
    result += '>';
    return result;
}

string slash_tag_finder(const string &io){
    if(io.length() < 3){
        return "";
    }
    string result = "</";
    int i = 2;
    while(i<io.length() && (io.at(i) >= 'A' && io.at(i) <= 'Z') && io.at(i) != '>'){
        result += io.at(i);
        ++i;
    }
    result += '>';
    return result;
}


//checks if the lefthand side is equal to the right hand side.
//
bool tag_checker(string lhs, const string &rhs){
    lhs = "</"+lhs.substr(1);
    if(lhs == rhs){
        return true;
    }
    return false;
}

void clear_stack(){ for(auto &dump = tag_holder; !dump.empty(); dump.pop()){} }

string slash_tag_maker(string &io){
    return "</"+io.substr(1);
}

void read_data(istream &input){
    string word;
    while(input >> ws >> word){
        if(word.length()>= 3){
            string w = "";
            check_tag(word, w);
        }
    }
}

bool is_contained(const string &io, const char find){
    for(auto i = io.cbegin(); i != io.cend(); ++i){
        if(*i == find){
            return true;
        }
    }
    return false;
}

int main() {
    istream& data = cin;
    read_data(data);


    return 0;
}
