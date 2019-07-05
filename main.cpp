#include "parser.hpp"
#include "node.hpp"
#include "tree.hpp"
#include <iostream>

//enum token{tag_b=1, tag_e, tag_SC, tex};

//typedef std::pair<token, std::string> pair;

int main(int argc, char const *argv[]) {
  std::vector<pair> v;
  parser p("test.html");
  p.pars(v);
  tree dom;
  dom.build(v);
  dom.GetString();

  return 0;
}
