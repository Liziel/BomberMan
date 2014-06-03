#include "GameEngine.hh"

namespace Engine{
  /* ## Game ## */
  Game::Game(Event::Dispatcher* _d, Engine::Graphic* _g)
    : _dispatcher(_d), _grEngine(_g),
      _Cfactory(new Component::Factory()),
      _Efactory(new Entity::Factory(_Cfactory)) {    

    /* Superior Component */
    arena = new Component::Arena();
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
    
    _Efactory->addAllocator("player", [this](bool _ini) -> Entity::GameObject* {
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

    _Efactory->addAllocator("player", [this](bool _ini) -> Entity::GameObject* {
	Entity::GameObject*	player = new Entity::Player(_dispatcher);
	if (!_ini)
	  return (player);
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("ColliderMovable", player));
	player
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("IA", player));// Arena::IA --> Composante de gameplay a finir
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

    _Efactory->addAllocator("bomb", [this](bool _ini) -> Entity::GameObject* {
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

    _Efactory->addAllocator("bloc", [this](bool _ini) -> Entity::GameObject* {
	Entity::GameObject*	bloc = new Entity::Bloc(_dispatcher);
	if (!_ini)
	  return (bloc);
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("ColliderStatic", bloc));//ColliderStatic
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Status", bloc));
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Health", bloc));
	bloc
	  ->attachComponent(_Cfactory
			    ->allocateComponentByType("Bloc", bloc));//Arena::Bloc a faire
	return (bloc);
      });

  }
};
