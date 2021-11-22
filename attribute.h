#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Attribute{
 public:
 
  //for names of attributes
  void Set_Name(const string& s);
  string Get_Name() const;
  
  //true - numeric
  //false - nominal
  void Set_Numeric(bool b);
  bool Numeric() const;
  
  //if nominal...
  void Add_Category(string s);
  int Num_Categories() const;
  
  //nominal value is in list of possible categories
  bool In_Domain(string s);
  vector<string> Get_Category_List() const;

 private:
  //the name of the attribute
  string name;
  
  bool is_numeric;
  
  //categories if the attribute is nominal
  vector<string> categories;
};
#endif
