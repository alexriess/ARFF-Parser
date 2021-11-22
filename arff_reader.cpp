//Alex Riess

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "attribute.h"
#include "instance.h"


using namespace std;

void New_Attribute(string& s, vector<Attribute>& attribute_list){
	
	//declare my local object
	Attribute local_a;
	
	//using stringstream to go through the words and '{}' between spaces
	stringstream ss;
	ss.str(s);
	string word;
	
	while(ss >> word){
		
		//get rid of @attribute
		if(word == "@attribute"){
			string attribute;
			attribute = word;
		}
		
		else if(word == "numeric"){
			//set attribute to numeric and done
			local_a.Set_Numeric(true);
		}
		
		else if(word == "{"){
			//nominal
			local_a.Set_Numeric(false);
		
			while(ss >> word){
				//pulling categories
				//
				if(word == "{"){
					//storing curly brace
					string cb;
					cb = word;
				}
				if(word[word.size() - 1] == '}'){
					string ccb;
					ccb = word;
				}
				if(word[word.size() - 1] == ','){
					word = word.substr(0, word.size() - 1);
				}
				
				if(word.size() != 0){
					//adding categories to local attribute
					local_a.Add_Category(word);
				}			
			}
		}
		
		else{
			local_a.Set_Name(word);
		}
	}
	//have all categories
	attribute_list.push_back(local_a);
}
	
	
//
//Parse_Data Function that...
//		breaks up a line of the file and 
//  	calls the get and set functions
void Parse_Data(string s,  vector<Attribute>& list, vector<Instance>& instances){
	//create a new instance and..
	//set its attributes to attributes in attribute_list
	Instance cur_instance;
	cur_instance.Set_Attributes(list);
	
	stringstream ss;
	ss.str(s);
	
	string word;
	
	int count = 0;
	//pull out indiv values from string
	while(ss >> word){
	
		if(word[word.size() - 1] == ','){
			//getting rid of ","
			word = word.substr(0, word.size() - 1);
		}	
		//Put those values into the correct attribute numbers of the instance
		cur_instance.Add_Value(count, word);
		count ++;
	
	}
	
	//add the instance we've created to vector of all instances
	instances.push_back(cur_instance);

}
	
	
	

	


//
//Print_Data Function that...
//		asks for the correct attributes of new dataset and
//		displays it
void Print_Data(vector<Instance> examples){


	char choice = 'y';
	while(choice == 'y'){
		cout << "We have " << examples.size() << " examples. Which would you like(1- " << examples.size() << ")? ";
		int cur_example;
		cin >> cur_example;

		
		cout << "Type " << 0 << " to see all attributes" << endl;
		
		for(int i = 1; i <= examples[i].Get_Num_Attributes(); i++){
		
			cout << "Type " << i << " to see " << examples[i - 1].Get_Attribute_Name(i - 1) << endl;
			
		}
		int which_attribute;
		cin >> which_attribute;
		
		
	//output everything we have
	if(which_attribute == 0){
		
		for(int i = 0; i < examples[cur_example -1].Get_Num_Attributes(); i++){
		
			if(examples[cur_example - 1].Is_Numeric_Attribute(i)){
				cout << examples[cur_example - 1].Get_Attribute_Name(i);
				cout << ": " << examples[cur_example - 1].Get_Numeric_Value(i) << endl;
			}
			else{
				cout << examples[cur_example - 1].Get_Attribute_Name(i);
				cout << ": " << examples[cur_example - 1].Get_Nominal_Value(i) << endl;
			}
		}	

	}
	//user entered specific attribute
	else{ 
	//reaching into specific attribute of a specific example
		//checking if numeric
		if(examples[cur_example - 1].Is_Numeric_Attribute(which_attribute - 1)){
			cout << examples[cur_example - 1].Get_Attribute_Name(which_attribute - 1);
			cout << ": " << examples[cur_example - 1].Get_Numeric_Value(which_attribute - 1) << endl;
		}
		else{
		//then it's nominal
			cout << examples[cur_example - 1].Get_Attribute_Name(which_attribute - 1);
			cout << ": " << examples[cur_example - 1].Get_Nominal_Value(which_attribute - 1) << endl;
		}
	}
		cout << "Another? (y/n)" << endl;
		cin >> choice;	
	}		
}

int main(){

	string filename;
  	cout << "Enter the filename: ";
  	cin >> filename;

  	ifstream fin;
  	fin.open(filename.data());
  	while(!fin){
    	cout << "File not found" << endl;
    	cout << "Enter the filename: ";
    	cin >> filename;
    	fin.clear();
    	fin.open(filename.data());
  	}



//declaring objects to put in my parameters for Parse, Print, and New_Attribute
vector<Attribute> attribute_list;
vector<Instance> examples;
string s;


bool data_mode = false;
while(getline(fin, s)){
	if(s.size() > 0 && s[0] != '%'){ 
   		// ignore line if empty or comment
		if(data_mode){// reading attribute line
			if(s[0] == '@')
  				//report an error, we’re getting a command instead of data
  				cout << "error: data is not detected" << endl;
			else
  				Parse_Data(s, attribute_list, examples);
		}
		else{
			if(s == "@data")
  				data_mode = true;
			else if(s.substr(0,10) == "@attribute")
  				New_Attribute(s, attribute_list);
			else
  			//Report an error, we don’t know what this command is
  			cout << "error: we don't know this command" << endl;
  			
 		} // end else
 		
 	} // end “if I shouldn’t skip this line”

} // end while


Print_Data(examples);
 
		
	return 0;

}