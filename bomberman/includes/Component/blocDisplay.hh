#ifndef __GROUNDDISPLAY_H__
# define __GROUNDDISPLAY_H__

# include "Component.hh"

# include "cubeVertex.hh"
# define __GROUNDTEXTURE "./textures/ground/lava.tga"
# define __GLYPHEDTEXTURE "./textures/ground/glyphe.tga"
# define __INDESTEXTURE "./textures/diamond/Diamond.tga"
# define __BOOKSHELFTEXTURE "./textures/bookshelf/bookshelf.tga"

namespace Component{
  class groundDisplay : public Component::abstract{
  private:
    object3d::cubeVertex	*cube;
    object3d::cubeVertex	*glyphed;
    Engine::Graphic*		engine;

  public:
    groundDisplay(Entity::GameObject*, Engine::Graphic*);
    ~groundDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };

  class indestructibleDisplay : public Component::abstract {
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

  class bookshelfDisplay : public Component::abstract {
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

  class playerDisplay : public Component::abstract {
  private:
    object3d::animatedVertex	*ziggs;
    Engine::Graphic*		engine;

  private:
    double x,y;
    std::array<bool, 4>	_direction;
  public:
    playerDisplay(Entity::GameObject*, Engine::Graphic*);
    ~playerDisplay();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };
};

namespace Component{
# ifndef __PHISIX_H__
#  ifndef __ARENA_H__
  namespace Phisix{
    namespace Vector{
      enum Direction {Up, Down, Right, Left};
    };
  };
#  endif
# endif
};

namespace Event{
  namespace Type{
# ifndef __PHISIX_H__
    struct selfMovement : Event::Data{
      selfMovement(Component::Phisix::Vector::Direction _d, bool _b)
	: Event::Data(Event::Info::selfMovement, sizeof(struct selfMovement), false), direction(_d), state(_b) {}
      Component::Phisix::Vector::Direction	direction;
      bool					state;
    };
# endif
  };
};

#endif
