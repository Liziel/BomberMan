#include "Component.hh"


namespace Component
{

  /*  Vector  */

  Phisix::Vector::Vector(Phisix *Phisik, int x, int y, double _speed = 1)
    : speed(_speed), authorization(true), positionX(x), positionY(y), myPhisix(Phisik)
  {  movementDirection[0] = false; movementDirection[1] = false; movementDirection[2] = false; movementDirection[3] = false; }
  
  void		Phisix::Vector::modifyMovement(enum Direction Direction, bool mask)
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
    this->authorization = orderToMove;
  }

  void	    Phisix::Vector::move()
  {
    double	x = 0;
    double	y = 0;

    if (!authorization)
      return ;
    if (movementDirection[Up])
      y -= this->speed * this->myPhisix->getGlobalFriction();
    if (movementDirection[Down])
      y += this->speed * this->myPhisix->getGlobalFriction();
    if (movementDirection[Right])
      x += this->speed * this->myPhisix->getGlobalFriction();
    if (movementDirection[Left])
      x -= this->speed * this->myPhisix->getGlobalFriction();
    if (!this->myPhisix->getCollider()(this->positionX + x, this->positionY + y)){
      if (x != 0 && this->myPhisix->getCollider()(this->positionX + x, this->positionY)) {
	this->positionX += x;
      } else if (y != 0 && !this->myPhisix->getCollider()(this->positionX, this->positionY + y)){
	this->positionY += y;
      } else { return ; }
    }
    this->positionX += x;
    this->positionY += y;
  }

  void	    Phisix::Vector::getPosition(int& x, int& y) const
  {
    x = this->positionX;
    y = this->positionY;
  }
  
  /* Phisix */
  Phisix::Phisix(Event::Dispatcher *Dispatch, const Collider &Collide)
    :DispatchCopy(Dispatch), ColliderCopy(Collide) {}
  


  void	   Phisix::setGlobalFriction(double friction)
  {
    this->globalFriction = friction;
  }

  double   Phisix::getGlobalFriction() const
  {
    return (globalFriction);
  }

  const Collider &Phisix::getCollider() const
  {
    return (ColliderCopy);
  }

};
