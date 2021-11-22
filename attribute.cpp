#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "attribute.h"

using namespace std;

//a)
//
string Attribute::Get_Name() const{
	return name;
}

void Attribute::Set_Name(const string& s){
	//try to find the name of the attribue within the line in the txt file
		name = s;
}

//b)
//
void Attribute::Set_Numeric(bool b){
	is_numeric = b;
	//sets whether the attribute is numeric
	//if statement saying whether found {} or not
}

bool Attribute::Numeric() const{
	return is_numeric;
}

//c)
//
void Attribute::Add_Category(string s){
	if(Numeric() == false){
		categories.push_back(s);
	}

}

//d)
//
int Attribute::Num_Categories() const{
	return categories.size();

}

//e)
//
bool Attribute::In_Domain(string s){
	if(Numeric()){
		return true;
	}
	for(int i = 0; i < categories.size(); i++){
		if(s == categories[i] || s == "?"){
			return true;
		}
		
	}	
	return false;
		
}

//f)
//
vector<string> Attribute::Get_Category_List() const{
	return categories;
}







