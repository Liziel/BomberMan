#ifndef __PHISIX_H__
# define __PHISIX_H__

# include "Component.hh"

namespace Component{

  /* ################ Health ############## */
  class Health : public Component::abstract{
  public:
    class Dot {
    private:
      int	damage;
      int	clockLife;
      int	rTime;
      int	aTime;

    public:
      Dot(int damage, int clockLife, unsigned int timeBeetween = 0);

    public:
      int	getDamage(void);
      bool	isOver(void);
    };
  private:
    Event::Callback*	_callback;
    Event::Dispatcher*	dispatcher;
    int			maxLife;
    int			life;
    std::list<Dot*>	dotList;
    bool		_invincible;

  public:
    Health(Event::Dispatcher*, int life = 1);
    ~Health();

  private:
    void	actualize();

  public:
    int		operator+(int n);
    int		operator-(int n);

  public:
    void	revive(unsigned int reviveLife);
    bool	isDead(void);

  public:
    void	addDot(Health::Dot*);

  public:
    bool	isInvicible(void);
    void	invincible(bool);
  };

};

#endif
