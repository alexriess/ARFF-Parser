#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "instance.h"
#include "attribute.h"

using namespace std;

int Instance::Get_Num_Attributes(){
	return Attribute_List.size();
}

void Instance::Set_Attributes(const vector<Attribute>& c){
	
	Attribute_List = c;
	Element_List.resize(c.size());
	Attribute_List.resize(c.size());

}

bool Instance::Add_Value(int attribute_num, string val){	
	//adding the value to the attribute number
	if(Is_Valid_Attribute(attribute_num)){
		if(Attribute_List[attribute_num].In_Domain(val)){
			Element_List[attribute_num] = val;
			return true;
			cout << "hello" << endl;
		}
	return false;
	}
	return false;
}

string Instance::Get_Nominal_Value(int attribute_num){
	if(Is_Valid_Attribute(attribute_num) &&  !Is_Numeric_Attribute(attribute_num)){
		if(!Is_Numeric_Attribute(attribute_num))
			return Element_List[attribute_num];
	}
	
	return "?";
	
}

double Instance::Get_Numeric_Value(int attribute_num){
	// "stod" converts a string version of a floating point number to a double
	//turn string of our number into double version
	if(Is_Valid_Attribute(attribute_num) && Is_Numeric_Attribute(attribute_num)){
		if(Is_Numeric_Attribute(attribute_num))
			return stod(Element_List[attribute_num]);
	}
	
	return 0;


}


bool Instance::Is_Numeric_Attribute(int attribute_num){
	//checking to see if attribute number is legal
	if(Is_Valid_Attribute(attribute_num)){
		if(Attribute_List[attribute_num].Numeric())
			return true;
	}
	
		return false;

}

string Instance::Get_Attribute_Name(int attribute_num){
	if(Is_Valid_Attribute(attribute_num))
		return Attribute_List[attribute_num].Get_Name();
	else
 		return "?";
}

bool Instance::Is_Valid_Attribute(int attribute_num){

	if(attribute_num >= 0 && attribute_num <= Attribute_List.size()-1){
		return true;
	}
	else
		return false;
}







