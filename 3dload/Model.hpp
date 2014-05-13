#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <iomanip>
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>

template <typename T>
struct s_val
{
  T vals[9];
};

class Model
{
public:
  Model(std::string name);
  ~Model() {}
  void show(float angle) const;
  void load();
private:
  void serializeVertex();
  void parseV(std::string values);
  void parseVn(std::string values);
  void parseVt(std::string values);
  void parseF(std::string values);
  std::string _name;
  std::string _dist;
  std::vector<struct s_val<float> > v;
  std::vector<struct s_val<float> > vn;
  std::vector<struct s_val<float> > vt;
  std::list<struct s_val<int> > f;
};

typedef void(Model::*parseModel)(std::string);

#endif //MODEL_H
