#include "GameEntity.hh"
#include "EventList.hh"

namespace Entity{
  Player::Player(GraphicEngine* GrEngine, Event::Dispatcher* Dispatch,
		 Entity::Player::Id id, double x, double y)
    : Entity::GameObject(GrEngine, Dispatch),
      _id(id), xAxis(0.f), yAxis(0.f), xP(x), yP(y) {

    this
      ->addCallback(Event::Info::Clock,
		    new Event::Callback([this](Event::Data&) {
			this->onClock();
		      }),
		      Event::Info::high
		    );
    
    this
      ->addCallback(Event::Info::Refresh,
		    new Event::Callback(
					[this](Event::Data&)
					{ this->Draw(); }
					)
		    );

    this
      ->addCallback(Event::Info::DeniedMove,
		    new Event::Callback([this](Event::Data& e) {
			Event::Type::DeniedMove *event
			  = reinterpret_cast<Event::Type::DeniedMove*>(&e);
			if (event->player != this->_id)
			  return ;
			this->xP = event->xLocation;
			this->yP = event->yLocation;
		      }),
		    Event::Info::high
		    );
    
    this
      ->addCallback(Event::Info::DamageFixed,
		    new Event::Callback([this](Event::Data& e) {
			Event::Type::DamageFixed *event
			  = (Event::Type::DamageFixed*)(&e);
			if (event->x == this->xP && event->y == this->yP)
			  this->health -= event->amount;
		      })
		    );

    this
      ->addCallback(Event::Info::Keyboard,
		    new Event::Callback([this](Event::Data& e) {
			Event::Type::Keyboard* event
			  = (Event::Type::Keyboard*)(&e);
			if (event->keyCode == 'z')
			  up = event->state;
			if (event->keyCode == 'q')
			  left = event->state;
			if (event->keyCode == 's')
			  down = event->state;
			if (event->keyCode == 'd')
			  right = event->state;
			if (event->keyCode == 'a')
			  bomb = event->state;
		      }));
  };

  void		Player::onClock(void) {
    bool	only = true;
    if (bomb){
      for (auto cooldown : cooldownList)
	if (cooldown == 0 && only){
	  _Dispatch
	    ->dispatchEvent(new Event::Type
			    ::PlantBomb((int)xP, (int)yP));
	  cooldown = Entity::GameUtils::getBombCooldown();
	  only = false;
	} else if (cooldown != 0) {
	  cooldown -= 1;
	}
    }
    _Dispatch
      ->dispatchEvent(new Event::Type
		      ::PlayerMove(_id, xP, yP, xAxis, yAxis));
    this->xP += this->xAxis;
    this->yP += this->yAxis;
  }

  void		Player::Draw(void) {


  }
};
