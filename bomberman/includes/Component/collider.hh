#ifndef __COLLIDER_H__
# define __COLLIDER_H__

# include "Component.hh" 

# define XMIN 0
# define XMAX 1
# define YMIN 2
# define YMAX 3

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
      ~Movable();

    private:
      Collider::Id		id;
    public:
      Collider::Id		getId();

    private:
      double	x;
      double	y;
    public:
      bool doCollide(double x, double y, const glm::vec4& hitbox);

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
      ~Static();

    private:
      Collider::Id		id;
    public:
      Collider::Id		getId();

    private:
      double	x;
      double	y;
      bool	disabled;
    public:
      bool doCollide(double x, double y, const glm::vec4& hitbox);

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

    void	removeSelf(Component::Collider::Static*);
    void	removeSelf(Component::Collider::Movable*);

    bool	operator()(double x, double y, const glm::vec4& hitbox,
			   Collider::Type ignoreType = _noType,
			   Component::Collider::Id = -1) const;
  };
};

namespace Event{
  namespace Type{

    struct StopCollide{};

# ifndef __EXPLODE_H__
# ifndef __PHISIX_H__
    struct RequireMovement :  Event::Data{
      RequireMovement(double _x, double _y, double vx, double vy)
	: Event::Data(Event::Info::RequireMovement, sizeof(struct RequireMovement), false),
	  x(_x), y(_y), vectorX(vx), vectorY(vy) {}
      double x;
      double y;
      double vectorX;
      double vectorY;
    };

    struct RequireExplosion :  Event::Data{
      RequireExplosion(double _x, double _y, double vx, double vy)
	: Event::Data(Event::Info::RequireExplosion, sizeof(struct RequireMovement), false),
	  x(_x), y(_y), vectorX(vx), vectorY(vy) {}
      double x;
      double y;
      double vectorX;
      double vectorY;
    };

    struct Colliding : Event::Data{
      Colliding(double _x, double _y, double _f)
	: Event::Data(Event::Info::Colliding, sizeof(struct Colliding), false),
	  endX(_x), endY(_y), collide(_f) {}
      double endX;
      double endY;
      double collide;
    }; 
# endif
# endif

# ifndef __ARENA_H__
    struct disableCollision : Event::Data {
      disableCollision()
	: Event::Data(Event::Info::disableCollision,
		      sizeof(struct disableCollision), false) {}
    };
# endif

  };
};

#endif
