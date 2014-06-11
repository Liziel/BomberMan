#include "GameEngine.hh"

namespace Engine{

  /* ## Game ## */
  Game::Game(Event::Dispatcher* _d, Engine::Graphic* _g)
    : _dispatcher(_d), _grEngine(_g),
      _Cfactory(new Component::Factory()),
      _Efactory(new Entity::Factory(_Cfactory)) {

    /* Superior Component */
    arena = new Component::Arena(_d, _Efactory);
    collider = new Component::Collider();
    phisix = new Component::Phisix(_dispatcher);

    /* pLayer Component & Entity */
    _Cfactory->storeComponentAllocator("ColliderMovable",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::
						 Collider::Movable(_player, collider));
				       });

    _Cfactory->storeComponentAllocator("Player",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::
						 Arena::Player(_player, arena));
				       });

    _Cfactory->storeComponentAllocator("Status",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::
						 Effects::Status(_player));
				       });

    _Cfactory->storeComponentAllocator("Health",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::Health(_player));
				       });

    _Cfactory->storeComponentAllocator("PhisixVector",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::
						 Phisix::Vector(_player, phisix));
				       });

    _Cfactory->storeComponentAllocator("BombCast",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::BombCast(_player));
				       });

    _Cfactory->storeComponentAllocator("BonusReceiver",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::Bonus::Receiver(_player));
				       });

    _Cfactory->storeComponentAllocator("Explode",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::Explode(_player));
				       });

    _Cfactory->storeComponentAllocator("Ground",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::groundDisplay(_player, _grEngine));
				       });
    
    _Efactory->addAllocator("player0", [this](bool _ini) -> Entity::GameObject* {
	Entity::GameObject*	player = new Entity::Player(_dispatcher);
	if (!_ini)
	  return (player);
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("ColliderMovable", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Player", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Status", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Health", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("PhisixVector", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("BombCast", player));	
	return (player);
      });

    _Efactory->addAllocator("player1", [this](bool _ini) -> Entity::GameObject* {
	Entity::GameObject*	player = new Entity::Player(_dispatcher);
	if (!_ini)
	  return (player);
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("ColliderMovable", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Player", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Status", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Health", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("PhisixVector", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("BombCast", player));	
	return (player);
      });

    _Efactory->addAllocator("bomb", [this](bool _ini) -> Entity::GameObject* { /* Entity::Bomb */
	Entity::GameObject*	bomb = new Entity::Bomb(_dispatcher);
	if (!_ini)
	  return (bomb);
	bomb
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("ColliderMovable", bomb));
	bomb
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Explode", bomb));
	return (bomb);
      });

    _Cfactory->storeComponentAllocator("BonusGiver",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::Bonus::Giver(_player));
				       });

    _Cfactory->storeComponentAllocator("ColliderStatic",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::Collider::Static(_player, collider));
				       });

    _Cfactory->storeComponentAllocator("Runic",
				       [this] (Entity::GameObject* _player)
				       -> Component::abstract* {
					 return (new Component::Runic(_player));
				       });


    _Efactory->addAllocator("destructibleBloc", [this](bool _ini) -> Entity::GameObject* {
	Entity::GameObject*	bloc = new Entity::Bloc(_dispatcher);
	if (!_ini)
	  return (bloc);
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("ColliderStatic", bloc));
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("BonusGiver", bloc));
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Ground", bloc));
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Bloc", bloc));//Arena::Bloc a faire
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Runic", bloc));//Runic
	return (bloc);
      });

    _Efactory->addAllocator("EmptyBloc", [this](bool _ini) -> Entity::GameObject* {
	Entity::GameObject*	bloc = new Entity::Bloc(_dispatcher);
	if (!_ini)
	  return (bloc);
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Ground", bloc));
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Runic", bloc));//ColliderStatic
	return (bloc);
      });

    _Efactory->addAllocator("indestructibleBloc", [this](bool _ini) -> Entity::GameObject* {
	Entity::GameObject*	bloc = new Entity::Bloc(_dispatcher);

	if (!_ini)
	  return (bloc);
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Ground", bloc));
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("ColliderStatic", bloc));//ColliderStatic
	return (bloc);
      });

  }
  Game::~Game() {}

  void	Game::refresh() {
    _dispatcher->dispatchEvent(new Event::Type::Clock);
    _dispatcher->dispatchEvent(new Event::Type::Refresh);
  }
};
