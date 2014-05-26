#ifndef __ENTITY_H__
# define __ENTITY_H__

# include <list>
# include <utility>
# include <string>
# include <iostream>

# include "Event.hpp"
# include "Tokenizer.hpp"

namespace Component{
  class abstract;
  class Factory;
};

namespace Entity{
  class GameObject{
  private:
    GameObject();
    
  private:
    Event::Dispatcher*		_Dispatch;
  private:
    std::list< std::pair< Event::Info::Type,
			  Event::Callback* > > _CallbackArray;
    
  public:
    GameObject(Event::Dispatcher* Dispatch);

  private:
    std::vector<Component::abstract*>	ComponentList;
  public:
    void	attachComponent(Component::abstract*);

  public:
    virtual void	setBySerial(const Tokenizer&);
    virtual std::string	serialization();
    virtual std::string getName() { return ("entity"); }

  public:
    ~GameObject();
    Event::Callback::Id	addCallback(Event::Info::Type, Event::Callback*,
				    Event::Info::Priority
				    = Event::Info::medium);
    void	dispatchSelf(Event::Data*);
    void	dispatchAll(Event::Data*);

    void	unsetCallback(Event::Callback*);
    void	unsetCallback(Event::Callback::Id);
    
  public:
    void	enable(void);
    void	disable(void);

  protected:
    int x;
    int y;
  public:
    void	getPosition(double& x, double& y) const;
    void	setPosition(double x, double y);

  public:
    virtual int	getLifeAmount(void) { return (-1); }
  };

};

#endif
