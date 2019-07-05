#ifndef TREE_HPP
#define TREE_HPP
#include "node.hpp"
#include "parser.hpp"
#include <stack>
#include <vector>
#include <string>
#include <utility>
//enum token{tag_b=1, tag_e, tag_SC, tex};

typedef std::pair<int, std::string> pair;

class tree{
public:
  tree();
  void build(std::vector<pair> &s);
  void GetString(void);

private:
  Openly * ROOT;
  std::vector<Openly*> v;
};

void tree::GetString(void){
  std::vector<uint> v;
  std::cout << "enter counter node :" ;
  uint n,t;
  std::cin >> n;
  for (size_t i = 0; i < n; i++) {
    std::cin >> t;
    v.push_back(t);
  }

  Node * p =ROOT;
  Node * ne =ROOT;
  for (uint a:v) {
    ne=static_cast<Openly*>(p)->child.at(a);
    p=ne;
  }
  p->GetString();
}




tree::tree(){

}

void tree::build(std::vector<pair> &s){

  ROOT = new Openly("< document >");
  Openly* n;
  v.push_back(ROOT);
  for (auto[ t, sr]:s){
    switch (t) {
      case 4:
        v.back()->addchild_t(sr);
        break;
      case 3:
        v.back()->addchild_sc(sr);
        break;
      case 1:
          v.back()->addchild(sr);
          n = static_cast<Openly*>( v.back()->child.back());
          v.push_back(n);
          break;
        case 2 :
            v.pop_back();
        break;
    }

  }
  std::cout << "end" << '\n';
};
#endif
