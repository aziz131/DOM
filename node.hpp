#ifndef NODE_HPP
#define NODE_HPP
#include <string>
#include <vector>
#include <regex>
#include <iostream>
#include "tree.hpp"

enum type_node{text,selfClose ,openly};


class Node {
private:
  friend class tree;
public:
  virtual void GetString(void)=0;
};


class text_node : public Node
{
public:
  text_node(std::string t):tex(t){};
     void GetString(void);
private:
  std::string tex;
};

 void text_node::GetString(void){
  std::cout << tex;
};

//...........................................................
class Self_close : public Node
{
public:
    Self_close(std::string s);
    virtual void GetString(void);
    void print(void);
    std::string getvalue(void){return value;};
private:
  std::string value;
  std::vector<std::string > attrib;
};

void Self_close::print(void){
  std::cout << "<" << value <<" ";
  if(!attrib.empty()){
  for (auto a : attrib) {
    std::cout << a  << ' ';
  }
  }
}


void Self_close::GetString(void){
print();
std::cout << "/>" ;
};

Self_close::Self_close(std::string s){
  std::regex tagn("<(\\s*\\w+)");
  auto pos=s.cbegin();
  auto end=s.cend();
  std::smatch m;

  if(regex_search(pos, end, m, tagn))
  {  pos = m.suffix().first;
    value = m.str(1);
  }else{value ="";}
  tagn=("\\s*(\\w+\\s*=\\s*\"[^\"]*\")");
  for ( ; regex_search(pos, end, m, tagn); pos = m.suffix().first)
  {
      attrib.push_back(std::move(m.str(1)));
  }
};


//..........................................
class Openly : public Self_close
{
public:
  Openly(std::string s):Self_close(s){};
   void addchild_t(std::string s);
   void addchild_sc(std::string s);
   void addchild(std::string s);
   void GetString(void);
private:
     friend class tree;
//protected:
std::vector<Node*> child;

};

void Openly::GetString(void){
  print();
  std::cout << ">" ;

  if(!child.empty()){
    for (auto a:child) {
      a->GetString();
    }

  }
  std::cout <<"<" << getvalue() <<"/>";


};


void Openly::addchild_t(std::string s){
  text_node *n = new text_node(s);
  child.push_back(n);
};

void Openly::addchild_sc(std::string s){
  Self_close *n = new Self_close(s);
  child.push_back(n);
};
void Openly::addchild(std::string s){
  Openly *n = new Openly(s);
  child.push_back(n);
};

#endif
