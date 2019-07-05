#ifndef PARSER_HPP
#define PARSER_HPP
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <regex>
#include <array>
#include <vector>


#include "tree.hpp"
enum token{tag_b=1, tag_e, tag_SC, tex};
std::map<token, std::string> word{{tag_b,"^\\s*(<\\w+>)\\n*"},
                                  {tag_e ,"^\\s*(</\\w+>)\\n*"},
                                  {tag_SC,"^\\s*(<\\w+\\s*/\\s*>)\\n*"},
                                  {tex,"^\\s*(\\w+[\\s*\\w+]*)\\n*"}};
std::map<token, std::string> WORDN{{tag_b,"begin tag"},
                                  {tag_e ,"end tag"},
                                  {tag_SC,"self closer tag"},
                                  {tex,"tex"}};

typedef std::pair<int, std::string> pair;


class parser{

public:
  parser(std::string htmlPath);
  void pars(std::vector<pair> &v);

private:
  std::string htmlSrc;
  std::stringstream htmlStream;
  friend class tree;

};


void parser::pars(std::vector<pair> &v){


  std::regex reg;
  auto pos=htmlSrc.cbegin();
  auto end=htmlSrc.cend();
  std::smatch m;

do {
  for(auto[t ,sr]:word){
  reg=sr;
  if (regex_search(pos, end, m, reg)) {
    pos = m.suffix().first;
  /*  std::cout << "................................" << '\n';
    std::cout << "match:  " << m.str() << std::endl;
    std::cout << " tag:   " << m.str(1) << std::endl;
    std::cout << "name:   " << WORDN.at(t) << std::endl;*/
    v.push_back(std::make_pair(t,m.str(1)));

    break;
  }
}
}while(!m.empty());

}


parser::parser(std::string htmlPath){
  std::ifstream htmlFile;
  htmlFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
  try
  {
    htmlFile.open(htmlPath);
    htmlStream << htmlFile.rdbuf();
    htmlFile.close();
    htmlSrc = htmlStream.str();
  }catch (const std::ios_base::failure& e)
  {
    std::cout << " FILE NOT SUCCESFULLY READ" << std::endl;
  }
    //std::cout << htmlSrc << std::endl;


  };
#endif
