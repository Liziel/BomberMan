#ifndef __DATAPOOL_H__
# define __DATAPOOL_H__

# include <list>
# include <string>
# include <unordered_map>

# include "Entity.hh"

namespace Entity{
  class Pool{
    /* Entity::GameObject List */
  private:
    std::unordered_map
    < std::string, std::list< Entity::GameObject* > > EntityMap;
    
    /* Add Entity */
  public:
    void	addEntity(Entity::GameObject*,
			  std::string type = "default");
    void	disableType(std::string type = "default");
    void	enableType(std::string type = "default");
    
    /* Ctor */
  public:
    Pool();
  };
};

#endif
