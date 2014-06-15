#include "Arena.hh"
#include "Entity.hh"

namespace Component{
  /* Winner */
  Arena::Winner::Winner(Entity::GameObject* _p, Component::Arena* _g)
    : Component::abstract(_p), game(_g), id(-1), dead(false) {
    _g->addSelf(this);
  }

  void	Arena::Winner::setId(Arena::Winner::Id _id) {
    id = _id;
  }

  Entity::GameObject*	Arena::Winner::getParent(void) { return (parent); }

  void	Arena::Winner::imDead(bool _s) {dead = _s;}
  bool	Arena::Winner::amIDead(void) {return (dead);}
  /*   IA   */
  Arena::IA::IA(Entity::GameObject* _p, Component::Arena* _a)
    : Arena::Winner(_p, _a), arena(_a) {
    _movement = {-1,-1};
    attachCallback(Event::Info::Clock,
		   new Event::FixedCallback([this, _a] (Event::Data&) { /* Up, Down, Left, Right */
		       dispatchSelf(new Event::Type::addElement(static_cast<Component::Effects::type>(rand() % 5)));
		       dispatchSelf(new Event::Type::addElement(static_cast<Component::Effects::type>(rand() % 5)));
		       dispatchSelf(new Event::Type::addElement(static_cast<Component::Effects::type>(rand() % 5)));

		       double x,y,add;
		       parent->getPosition(x,y);
		       add = 0.5 - 1 * (x < 0);
		       x = static_cast<int>(x) + add;
		       add = 0.5 - 1 * (y < 0);
		       y = static_cast<int>(y) + add;

		       std::array<bool, 4> safe = {checkForBomb(x, y, 1, 0), checkForBomb(x, y, -1, 0),
						   checkForBomb(x, y, 0, -1), checkForBomb(x, y, 0, 1)};
		       std::array<int, 2> movement = {-1, -1};
		       if (!findSafe(safe, movement, x, y))
			 calculate(movement);

		       if (lootBomb(x,y))
			 dispatchSelf(new Event::Type::selfPlantBomb());			 

		       if (_movement[0] != -1)
			 dispatchSelf(new Event::Type::selfMovement
				      (static_cast<Component::Phisix::Vector::Direction>(_movement[0]), false));			 
		       if (_movement[1] != -1)
			 dispatchSelf(new Event::Type::selfMovement
				      (static_cast<Component::Phisix::Vector::Direction>(_movement[1]), false));			 

		       if (movement[0] != -1)
			 dispatchSelf(new Event::Type::selfMovement
				      (static_cast<Component::Phisix::Vector::Direction>(movement[0]), true));			 
		       if (movement[1] != -1)
			 dispatchSelf(new Event::Type::selfMovement
				      (static_cast<Component::Phisix::Vector::Direction>(movement[1]), true));			 


		       _movement = movement;
		     }));
  }

  void	Arena::IA::calculate(std::array<int, 2>& movement) {
    movement[0] = 0;
    movement[1] = 3;
  }

  bool	Arena::IA::lootBomb(double, double) {
    return (true);
  }

  bool	Arena::IA::findSafe(const std::array<bool, 4>& safe, std::array<int, 2>& movement, double x, double y) {
    std::array<bool, 4> shouldnt = {false, false, false, false};

    if (safe[0] || safe[1]) {
      shouldnt[0] = true;
      shouldnt[1] = true;
    }

    if (safe[2] || safe[3]) {
      shouldnt[3] = true;
      shouldnt[2] = true;
    }

    if (shouldnt[3]) {
      if (arena->Map[x + 1][y] == Arena::Empty)
	movement[0] = 1;
      if (arena->Map[x + -1][y] == Arena::Empty)
	movement[0] = 0;
    }
    if (shouldnt[2]) {
      if (arena->Map[x + -1][y] == Arena::Empty)
	movement[0] = 0;
      if (arena->Map[x + 1][y] == Arena::Empty)
	movement[0] = 1;
    }

    if (shouldnt[1]) {
      if (arena->Map[x][y + -1] == Arena::Empty)
	movement[1] = 2;
      if (arena->Map[x][y + 1] == Arena::Empty)
	movement[1] = 3;
    }
    if (shouldnt[0]) {
      if (arena->Map[x][y + 1] == Arena::Empty)
	movement[1] = 2;
      if (arena->Map[x][y + -1] == Arena::Empty)
	movement[1] = 3;
    }
    return (false);
  }

  bool	Arena::IA::checkForBomb(double x, double y, double _x, double _y) {
    double	k = 1.f;

    for (;arena->Map.find(x + k * _x) != arena->Map.end() && arena->Map[x].find(y + k * _y) != arena->Map[x].end(); k += 1) {
      if (arena->Map[x][y] == Arena::Bomb)
	return (true);
      else if (arena->Map[x][y] != Arena::Empty)
	return (false); /* protected */
    }
    return (false);
  }

  std::string Arena::IA::serialization(){
    return (Tokenizer::serialize("Player", amIDead()));
  }

  void	Arena::IA::setBySerial(const Tokenizer& t){
    imDead(t.get<bool>(1));
  }

  /* Player */
  Arena::Player::Player(Entity::GameObject* _p, Component::Arena* _a)
    : Arena::Winner(_p, _a) {
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
			   if (_a->Map[x].find(y) != _a->Map[x].end()) {
			     if (_a->Map[x][y] == Arena::Empty) {
			       dispatchSelf(new Event::Type::selfPlantBomb());
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
  Arena::Bloc::Bloc(Entity::GameObject* _p, Component::Arena* arena)
    : Component::abstract(_p), hitted(false) {
    parent->getPosition(x,y);
    attachCallback(Event::Info::Explosion,
		   new Event::FixedCallback([this, arena] (Event::Data& e) {
		       Event::Type::Explosion* event =
			 reinterpret_cast<Event::Type::Explosion*>(&e);
		       auto hitbox = parent->getHitBox();
		       if (x + hitbox[0] <= event->x && event->x <= x + hitbox[1] &&
			   y + hitbox[2] <= event->y && event->y <= y + hitbox[3])
			 arena->Map[x][y] = Arena::Empty;
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
    _d->addCallbackOnEvent(Event::Info::Explosion,
			   new Event::FixedCallback([this] (Event::Data& e) {
			       Event::Type::Explosion* event =
				 reinterpret_cast<Event::Type::Explosion*>(&e);
			       double x = event->x, y = event->y;
				 if (Map.find(x) != Map.end() && Map[x].find(y) != Map[x].end())
				   Map[x][y] = Arena::Empty;
		     }));
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
			       if (Map.find(event->x) != Map.end() && Map[event->x].find(event->y) != Map[event->x].end())
				 Map[event->x][event->y] = Arena::Bomb;
			       b->setPosition(event->x, event->y);
			       b->attachComponent(_Efactory
						  ->getComponentFactory()->allocateComponentByType("ColliderMovable", b));
			       Component::abstract* exp = _Efactory
				 ->getComponentFactory()->allocateComponentByType("Explode", b);
			       Component::abstract* disp = _Efactory
				 ->getComponentFactory()->allocateComponentByType("bombDisplay", b);
			       disp->setBySerial(Tokenizer::subserialize(0, event->prim));
			       exp->setBySerial(Tokenizer::subserialize(0, /* achanger */50, event->prim, event->second, event->ter));
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
	  Map[x/2 - xi + 0.5].insert(std::pair<double, Arena::type>(y/2 - yi + 0.5, Arena::Indestructible));
	  obj = _Efactory->allocateEntityByType("indestructibleBloc", false);
	  obj->setPosition(x/2 - xi + 0.5, y/2 - yi + 0.5);
	  _Efactory->allocateComponentByEntityType("indestructibleBloc", obj);
	} else if (!((xi == 1 && (yi == 1 || yi == 2 || yi == y - 2)) ||
		     (xi == x - 1 && (yi == 1 || yi == 2 || yi == y - 2)) ||
		     (yi == 1 && (xi == 1 || xi == 2 || xi == x - 2)) ||
		     (yi == y - 1 && (xi == 1 || xi == 2 || xi == x - 1 || xi == x - 2))
		     )) {
	  Map[x/2 - xi + 0.5].insert(std::pair<double, Arena::type>(y/2 - yi + 0.5, Arena::Breakable));
	  obj = _Efactory->allocateEntityByType("destructibleBloc", false);
	  obj->setPosition(x/2 - xi + 0.5, y/2 - yi + 0.5);
	  _Efactory->allocateComponentByEntityType("destructibleBloc", obj);
	} else {
	  Map[x/2 - xi + 0.5].insert(std::pair<double, Arena::type>(y/2 - yi + 0.5, Arena::Empty));
	  std::cout << "{{{{{{{{{{{{{{{{"<< (y/2-yi+0.5) <<"}}}}}}}}}}}}}}}}" << std::endl;
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
      _Efactory->allocateComponentByEntityType("player" + std::to_string(iplay), obj);
    }

    for (int iIa = iplay; iIa < nIa + iplay; iIa++) {
      std::cout << "oui" << std::endl;
      obj = _Efactory->allocateEntityByType("Ia", false);
      obj->setPosition(dispoPlace[iIa][0], dispoPlace[iIa][1]);
      _Efactory->allocateComponentByEntityType("Ia", obj);
    }
  }

  void	Arena::addSelf(Arena::Winner* _w) {
    fighter.push_back(_w);
  }

  bool	Arena::PlayerAt(double x, double y, Arena::Winner* _ignore) {
    double _x,_y;
    for (auto _f : fighter) {
      if (_f != _ignore) {
	_f->getParent()->getPosition(_x,_y);
	if (Component::matchPosition(_x,_y, x, y))
	  return (true);
      }
    }
    return (true);
  }
};
