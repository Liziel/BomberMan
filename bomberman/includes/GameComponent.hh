#ifndef __GAMECOMPONENT_H__
# define __GAMECOMPONENT_H__

#include "Component.hh"

namespace Component{

  /* gameUtils (surely will be changed)*/
  namespace GameUtils{
    int	getBombCooldown(void);
  }

  /* ##### Player ##### */
  class Player : public Component::GameObject{
    /* Id& Ctor*/
  public:
    typedef unsigned int Id;
    Player(GraphicEngine* GrEngine, Event::Dispatcher* Dispatch,
	   Component::Player::Id, double x, double y);
    ~Player();

    /* Id related */
  private:
    Id			_id;

    /* Movement related */
  private:
    double			xAxis;
    double			yAxis;
    double			xP;
    double			yP;
    bool			up;
    bool			down;
    bool			left;
    bool			right;
  public:
    void			onClock();
    void			Draw();

    /* Bombe Related */
  private:
    int				health;
    bool			bomb;
    std::list<int>		cooldownList;
  };

};

#endif
