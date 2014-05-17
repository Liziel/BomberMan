#ifndef __DATAPOOL_H__
# define __DATAPOOL_H__

# include <list>
# include <unordered_map>

# include "Component.hh"

class DataPool{
  /* Component List */
private:
  std::unordered_map< std::string, std::list< Component* > > ComponentMap;

  /* Add Component */
public:
  void	addComponent(Component*, std::string type = "default");
  void	disableType(std::string type = "default");
  void	enableType(std::string type = "default");

  /* Ctor */
public:
  Component();
};

#endif
