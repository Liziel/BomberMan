#include "Component.hh"


namespace Component
{

  /*  Vector  */

  Phisix::Vector::Vector(Phisix *Phisik, int x, int y, double _speed = 1)
    : speed(_speed), myPhisix(Phisik), movementDirection({false, false, false, false}),
      authorization(true), positionX(x), positionY(y) {}
  
  void		Phisix::Vector::modifyMovement(enum Direction, bool mask)
  {
    movementDirection[Direction] = mask;
  }

  void      Phisix::Vector::modifySpeed(double speed)
  {
    this->speed = this->speed * speed;
  }

  void	    Phisix::Vector::setSpeed(double speed)
  {
    this->speed = speed;
  }

  void	    Phisix::Vector::authorizeMovement(bool orderToMove)
  {
    this->autorization = orderToMove;
  }

  void	    Phisix::Vector::move()
  {
    double	x = 0;
    double	y = 0;

    if (!autorization)
      return ;
    if (movementDirection[Up])
      y -= this->speed * this->myPhisix->getGlobalFriction();
    if (movementDirection[Down])
      y += this->speed * this->myPhisix->getGlobalFriction();
    if (movementDirection[Right])
      x += this->speed * this->myPhisix->getGlobalFriction();
    if (movementDirection[Left])
      x -= this->speed * this->myPhisix->getGlobalFriction();
    if (!this->phisix->getCollider()(this->positionX + x, this->positionY + y)){
      if (x != 0 && this->phisix->getCollider()(this->positionX + x, this->positionY)) {
	this->positionX += x;
      } else if (y != 0 && !this->phisix->getCollider()(this->positionX, this->positionY + y)){
	this->postionY += y;
      } else { return ; }
    }
    this->positionX += x;
    this->positionY += y;
  }

  void	    Phisix::Vector::getPosition(int& x, int& y)
  {
    this->positionX = x;
    this->positionY = y;
  }
  
  /* Phisix */

  Phisix::Phisix(Event::Dispatcher *Dispatch, const Collider &Collide)
    :DispatchCopy(Dispatch), ColliderCopy(Collide){}
  


  void	   Phisix::setGlobalFriction(double friction) const
  {
    this->globalFriction = friction;
  }

  double   Phisix::getGlobalFriction() const
  {
    return (globalFriction);
  }

  Collider *Phisix::getCollider() const
  {
    return (ColliderCopy);
  }

};
