#include "Arena.hh"
#include "Entity.hh"

namespace Component{
  /* Winner */
  Arena::Winner::Winner(Component::Arena* _g) : game(_g), id(-1), dead(false) {
    _g->addSelf(this);
  }

  void	Arena::Winner::setId(Arena::Winner::Id _id) {
    id = _id;
  }

  void	Arena::Winner::imDead(bool _s) {dead = _s;}
  bool	Arena::Winner::amIDead(void) {return (dead);}
  /* Player */
  Arena::Player::Player(Entity::GameObject* _p, Component::Arena* _a)
    : Component::abstract(_p), Arena::Winner(_a) {
    attachCallback(Event::Info::Keyboard,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Keyboard* event = 
			 reinterpret_cast<Event::Type::Keyboard*>(&e);
		       if (event->key >= 0 &&  event->key <= 3)
			 dispatchSelf(new Event::Type::selfMovement
				      (static_cast<Component::Phisix::Vector::Direction>(event->key), event->state));
		       else if (event->state && event->key == 4)
			 dispatchSelf(new Event::Type::selfPlantBomb());
		       else if (event->state)
			 dispatchSelf(new Event::Type::addElement(static_cast<Component::Effects::type>(event->key - 5)));
		     }));

    attachCallback(Event::Info::dead,
		   new Event::FixedCallback([this, _p] (Event::Data&) {
		       _p->disable();
		       imDead(true);
		     }));
  }

  std::string Arena::Player::serialization(){
    return (Tokenizer::serialize("Player", amIDead()));
  }

  void	Arena::Player::setBySerial(const Tokenizer& t){
    imDead(t.get<bool>(1));
  }

  /* ####  Bloc #### */
  Arena::Bloc::Bloc(Entity::GameObject* _p)
    : Component::abstract(_p) {
    parent->getPosition(x,y);
    attachCallback(Event::Info::Explosion,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Explosion* event =
			 reinterpret_cast<Event::Type::Explosion*>(&e);
		       if (event->x == x && event->y == y) {
			 dispatchSelf(new Event::Type::disableCollision());
			 if (!(rand() % 10))
			   dispatchSelf(new Event::Type::LootBonus());
		       }
		     }));
  }

  std::string	Arena::Bloc::serialization()
  { return (Tokenizer::serialize("Bloc")); }

  void		Arena::Bloc::setBySerial(const Tokenizer&) {
    parent->getPosition(x,y);
  }

  /* #### ARENA #### */
  Arena::Arena(Event::Dispatcher* _d, Entity::Factory* _f)
    : Component::Superior(_d), _Efactory(_f) {
    _d->addCallbackOnEvent(Event::Info::Clock,
			      new Event::FixedCallback([this] (Event::Data&) {
				  if (!fighter.size())
				    return ;
				  int	id = 0;
				  int	whosnotdead = 0;
				  for (auto itt = fighter.begin(); itt != fighter.end(); itt++) {
				    if (!((*itt)->amIDead()) && whosnotdead == 0)
				      whosnotdead = id + 1;
				    else if (!((*itt)->amIDead()))
				      whosnotdead = -1;
				    id++;
				  }
				  if (whosnotdead > 0)
				    dispatcher->dispatchEvent(new Event::Type::winner(whosnotdead - 1));
				  dispatcher->dispatchEvent(new Event::Type::endGame());
				}));
    _d->addCallbackOnEvent(Event::Info::beginGame,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::beginGame* event = 
			 reinterpret_cast<Event::Type::beginGame*>(&e);

		       if (event->_map == Component::Game::square)
			 GenerateSquareMap(event->nbPlayer, event->nbIa, event->mapSizex, event->mapSizex);
		     }));
    _d->addCallbackOnEvent(Event::Info::plantBomb,
			   new Event::FixedCallback([this] (Event::Data& e) {
			       Event::Type::PlantBomb* event = 
				 reinterpret_cast<Event::Type::PlantBomb*>(&e);
			       Entity::GameObject* b = _Efactory->allocateEntityByType("Bomb", false);
			       b->setPosition(event->x, event->y);
			       b->attachComponent(_Efactory->getComponentFactory()->allocateComponentByType("ColliderMovable", b));
			       Component::abstract* exp = _Efactory->getComponentFactory()->allocateComponentByType("Explode", b);
			       exp->setBySerial(Tokenizer::subserialize(0, /* achanger */10, event->prim, event->second, event->ter));
			       b->attachComponent(exp);
			     }));
  }

  void		Arena::GenerateSquareMap(int nplay, int nIa, int x, int y) {
    std::array<std::array<int , 2>, 4> dispoPlace = { std::array<int, 2>({1, 1}),  std::array<int, 2>({x-1, 1}),
						      std::array<int, 2>({1,y-1}), std::array<int, 2>({x-1,y-1})  };
    for (int xi = 0; xi <= x; xi++) {
      for (int yi = 0; yi <= y; yi++) {
	if (xi == 0 || xi == x || yi == 0 || yi == y)
	  _Efactory->allocateEntityByType("indestructibleBloc")->setPosition(xi, yi);
	else if ((xi != 1 && yi != 1 && xi != x -1 && yi != y -1) &&
		 (!(xi % 2) || !(yi % 2)))
	  _Efactory->allocateEntityByType("destructibleBloc")->setPosition(xi, yi);
	else
	  _Efactory->allocateEntityByType("EmptyBloc")->setPosition(xi, yi);
      }
    }
    int iplay = 0;
    for (; iplay < nplay; iplay++) {
      _Efactory->allocateEntityByType("player" + std::to_string(iplay))->setPosition(dispoPlace[iplay][0], dispoPlace[iplay][1]);
    }
    for (int iIa = iplay; iIa < nIa + iplay; iIa++) {
      _Efactory->allocateEntityByType("Ia")->setPosition(dispoPlace[iIa][0], dispoPlace[iIa][1]);
    } 
  };
};
