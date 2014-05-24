#ifndef __COLLIDER_H__
# define __COLLIDER_H__

# include "Component.hh" 

namespace Component {

  class Collider{

  public:
    enum Type{_noType, _Movable, _Static};
    typedef int	Id;


  public:
    class Movable : public Component::abstract{
    private:
      Component::Collider*		collider;
    public:
      Movable(Entity::GameObject*, Component::Collider*);

    private:
      Collider::Id		id;
    public:
      Collider::Id		getId();

    private:
      double	x;
      double	y;
    public:
      bool doCollide(int x, int y);

    public:
      std::string		serialization();
      void			setBySerial(const Tokenizer&);
      static std::string	getName(void) { return ("ColliderMovable"); }
    };/* movable */



  public:
    class Static : public Component::abstract{
    private:
      Component::Collider*		collider;
    public:
      Static(Entity::GameObject*, Component::Collider*);

    private:
      Collider::Id		id;
    public:
      Collider::Id		getId();

    private:
      double	x;
      double	y;
    public:
      bool doCollide(int x, int y);

    public:
      std::string		serialization();
      void			setBySerial(const Tokenizer&);
      static std::string	getName(void) { return ("ColliderStatic"); }
    };/* static */

  public:
    Collider();

  private:
    std::vector<Collider::Static*>	listStatic;
    std::vector<Collider::Movable*>	listMovable;

  private:
    int			_idGen;
  public:
    Collider::Id	addSelf(Component::Collider::Static*);
    Collider::Id	addSelf(Component::Collider::Movable*);

    bool	operator()(int x, int y,
			   Collider::Type ignoreType = _noType,
			   Component::Collider::Id = -1) const;
  };
};

namespace Event{
  namespace Type{

# ifndef __PHISIX_H__
    struct RequireMovement :  Event::Data{
      RequireMovement(int _x, int _y, int vx, int vy)
	: Event::Data(Event::Info::RequireMovement, sizeof(struct RequireMovement), false),
	  x(_x), y(_y), vectorX(vx), vectorY(vy) {}
      double x;
      double y;
      double vectorX;
      double vectorY;
    };

    struct Colliding : Event::Data{
      Colliding(int _x, int _y)
	: Event::Data(Event::Info::Colliding, sizeof(struct Colliding), false),
	  endX(_x), endY(_y) {}
      int endX;
      int endY;
      double collide;
    }; 
# endif

  };
};

#endif
