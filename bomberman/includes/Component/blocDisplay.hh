#ifndef __GROUNDDISPLAY_H__
# define __GROUNDDISPLAY_H__

# include "Component.hh"

# include "cubeVertex.hh"
# define __GROUNDTEXTURE ""
# define __INDESTEXTURE ""
# define __BOOKSHELFTEXTURE ""

namespace Component{
  class groundDisplay : public Component::abstract{
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    groundDisplay(Entity::GameObject*, Engine::Graphic*);
    ~groundDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class indestructibleDisplay : Component::abstract {
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    indestructibleDisplay(Entity::GameObject*, Engine::Graphic*);
    ~indestructibleDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class bookshelfDisplay : Component::abstract {
  private:
    object3d::cubeVertex	*cube;
    Engine::Graphic*		engine;

  public:
    bookshelfDisplay(Entity::GameObject*, Engine::Graphic*);
    ~bookshelfDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };
};

#endif
