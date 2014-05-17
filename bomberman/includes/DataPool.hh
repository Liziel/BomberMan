#ifndef __DATAPOOL_H__
# define __DATAPOOL_H__

# include <list>
# include <string>
# include <unordered_map>

# include "Component.hh"

class DataPool{
  /* Component::GameObject List */
private:
  std::unordered_map
  < std::string, std::list< Component::GameObject* > > ComponentMap;

  /* Add Component */
public:
  void	addComponent(Component::GameObject*, std::string type = "default");
  void	disableType(std::string type = "default");
  void	enableType(std::string type = "default");

  /* Ctor */
public:
  DataPool();
};

#endif
