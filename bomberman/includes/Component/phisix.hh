#ifndef __PHISIX_H__
# define __PHISIX_H__

# include "Component.hh"

namespace Component{

  /* ###################### PHISIX ############################# */
  class Phisix : public Component::abstract{
  public:
    class Vector{
    public:
      Vector(Phisix*, int, int, double);

    private:
      double	speed;
      bool	movementDirection[4];

    private:
      bool	authorization;
      int	positionX;
      int	positionY;

    private:
      Phisix	*myPhisix;      

    public:
      enum Direction{ Up, Down, Left, Right };
      void	modifyMovement(enum Direction, bool mask);
      void	modifySpeed(double speed);
      void	setSpeed(double speed);
      void	authorizeMovement(bool);

    public:
      void	move(void);
      void	getPosition(int& x, int& y) const;
    }; /*  -- vector end --  */

  private:
    Event::Dispatcher*	DispatchCopy;
    const Collider&	ColliderCopy;
    double		globalFriction;
  public:
    Phisix(Event::Dispatcher*, const Collider&);

  public:
    void		setGlobalFriction(double);
    double		getGlobalFriction(void) const;
    const Collider&	getCollider(void) const;
  };
};
#endif
