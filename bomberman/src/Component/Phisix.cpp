#include "Component.hh"


namespace Component
{

  /* Phisix */

  Phisix::Phisix(Event::Dispatcher *, const Collider&)
  {
    
  }
  

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
    
  }

  void	    Phisix::Vector::getPosition(int& x, int& y)
  {
    this->positionX = x;
    this->positionY = y;
  }


};
