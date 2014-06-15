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
		   new Event::FixedCallback([this, _a] (Event::Data& e) {
		       Event::Type::Keyboard* event =
			 reinterpret_cast<Event::Type::Keyboard*>(&e);
		       if (event->key >= 0 &&  event->key <= 3)
			 dispatchSelf(new Event::Type::selfMovement
				      (static_cast<Component::Phisix::Vector::Direction>(event->key), event->state));
		       else if (event->state && event->key == 4) {
			 double x,y, add;
			 parent->getPosition(x,y);
			 add = 0.5 - 1 * (x < 0);
			 x = static_cast<int>(x) + add;
			 add = 0.5 - 1 * (y < 0);
			 y = static_cast<int>(y) + add;
			 if (_a->Map.find(x) != _a->Map.end()) {
			   std::cout << "X in MAP!!" << std::endl;
			   if (_a->Map[x].find(y) != _a->Map[x].end()) {
			     std::cout << "Y in MAP!!" << std::endl;
			     if (_a->Map[x][y] == Arena::Empty) {
			       dispatchSelf(new Event::Type::selfPlantBomb());
			       std::cout << "it's ok!" << std::endl;
			       return ;
			     }
			   }
			 }
			 if (_a->Map.find(x) == _a->Map.end() || _a->Map[x].find(y) == _a->Map[x].end())
			   dispatchSelf(new Event::Type::selfPlantBomb());
		       } else if (event->state)
			 dispatchSelf(new Event::Type::addElement(static_cast<Component::Effects::type>(event->key - 5)));
		     }));

    attachCallback(Event::Info::dead,
		   new Event::FixedCallback([this, _p] (Event::Data&) {
		       _p->disable();
		       imDead(true);
		       std::cout << "im DEAAAAAD" << std::endl;
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
    : Component::abstract(_p), hitted(false) {
    parent->getPosition(x,y);
    attachCallback(Event::Info::Explosion,
		   new Event::FixedCallback([this] (Event::Data& e) {
		       Event::Type::Explosion* event =
			 reinterpret_cast<Event::Type::Explosion*>(&e);
		       auto hitbox = parent->getHitBox();
		       if (hitted)
			 return ;
		       if (x + hitbox[0] <= event->x && event->x <= x + hitbox[1] &&
			   y + hitbox[2] <= event->y && event->y <= y + hitbox[3]) {
			 dispatchSelf(new Event::Type::disableCollision());
			 dispatchSelf(new Event::Type::EnableGlyph());
			 if (!(rand() % 3))
			   dispatchSelf(new Event::Type::LootBonus());
			 hitted = true;
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

		       std::cout << "Map is being generated" << std::endl;
		       if (event->_map == Component::Game::square)
			 GenerateSquareMap(event->nbPlayer, event->nbIa, event->mapSizex, event->mapSizex);
		     }));
    _d->addCallbackOnEvent(Event::Info::plantBomb,
			   new Event::FixedCallback([this] (Event::Data& e) {
			       Event::Type::PlantBomb* event = 
				 reinterpret_cast<Event::Type::PlantBomb*>(&e);
			       Entity::GameObject* b = _Efactory->allocateEntityByType("bomb", false);
			       double add;
			       add = 0.5 - 1 * (event->x < 0);
			       event->x = static_cast<int>(event->x) + add;
			       add = 0.5 - 1 * (event->y < 0);
			       event->y = static_cast<int>(event->y) + add;
			       b->setPosition(event->x, event->y);
			       b->attachComponent(_Efactory
						  ->getComponentFactory()->allocateComponentByType("ColliderMovable", b));
			       Component::abstract* exp = _Efactory
				 ->getComponentFactory()->allocateComponentByType("Explode", b);
			       Component::abstract* disp = _Efactory
				 ->getComponentFactory()->allocateComponentByType("bombDisplay", b);
			       disp->setBySerial(Tokenizer::subserialize(0, event->prim));
			       exp->setBySerial(Tokenizer::subserialize(0, /* achanger */100, event->prim, event->second, event->ter));
			       b->attachComponent(exp);
			       b->attachComponent(disp);
			     }));
  }

  void		Arena::GenerateSquareMap(int nplay, int nIa, int x, int y) {
    std::array<std::array<double , 2>, 4> dispoPlace = { std::array<double, 2>({(-x/2 + 1.5f), (-y/2 + 1.5f)}),  std::array<double, 2>({x/2 - 1.5, -y/2 + 1.5}),
						      std::array<double, 2>({x/2 - 1.5,y/2 - y-1.5}), std::array<double, 2>({x/2 - x-1.5,y/2 - y-1.5})  };
    Entity::GameObject*	obj;
    for (int xi = 0; xi <= x; xi++) {
      Map.insert(std::pair< double, std::map<double, Arena::type> >(x/2 - xi + 0.5, std::map<double, Arena::type>()));
      for (int yi = 0; yi <= y; yi++) {
	if (xi == 0 || xi == x || yi == 0 || yi == y || (!(xi % 2) && !(yi % 2))) {
	  Map[x/2 - xi].insert(std::pair<double, Arena::type>(y/2 - yi + 0.5, Arena::Indestructible));
	  obj = _Efactory->allocateEntityByType("indestructibleBloc", false);
	  obj->setPosition(x/2 - xi + 0.5, y/2 - yi + 0.5);
	  _Efactory->allocateComponentByEntityType("indestructibleBloc", obj);
	} else if (!((xi == 1 && (yi == 1 || yi == 2 || yi == y - 2)) ||
		     (xi == x - 1 && (yi == 1 || yi == 2 || yi == y - 2)) ||
		     (yi == 1 && (xi == 1 || xi == 2 || xi == x - 2)) ||
		     (yi == y - 1 && (xi == 1 || xi == 2 || xi == x - 1 || xi == x - 2))
		     )) {
	  Map[x/2 - xi].insert(std::pair<double, Arena::type>(y/2 - yi + 0.5, Arena::Breakable));
	  obj = _Efactory->allocateEntityByType("destructibleBloc", false);
	  obj->setPosition(x/2 - xi + 0.5, y/2 - yi + 0.5);
	  _Efactory->allocateComponentByEntityType("destructibleBloc", obj);
	} else {
	  Map[x/2 - xi].insert(std::pair<int, Arena::type>(y/2 - yi + 0.5, Arena::Empty));
	  obj = _Efactory->allocateEntityByType("EmptyBloc", false);
	  obj->setPosition(x/2 - xi + 0.5, y/2 - yi + 0.5);
	  _Efactory->allocateComponentByEntityType("EmptyBloc", obj);
	}
      }
    }
    int iplay = 0;
    for (; iplay < nplay; iplay++) {
      obj = _Efactory->allocateEntityByType("player" + std::to_string(iplay), false);
      obj->setPosition(dispoPlace[iplay][0], dispoPlace[iplay][1]);
      obj->getPosition(dispoPlace[iplay][0], dispoPlace[iplay][1]);
      _Efactory->allocateComponentByEntityType("player" + std::to_string(iplay), obj);
    }
    for (int iIa = iplay; iIa < nIa + iplay; iIa++) {
      _Efactory->allocateEntityByType("Ia")->setPosition(dispoPlace[iIa][0], dispoPlace[iIa][1]);
    }
  }

  void	Arena::addSelf(Arena::Winner* _w) {
    fighter.push_back(_w);
  }
};
