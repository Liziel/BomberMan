#ifndef __MENU_H__
# define __MENU_H__

# include "Component.hh"
# include "GraphicEngine.hh"
# include "planVertex.hh"

namespace Component{
  class Button {
  public:
    std::string _texture;
    std::string _textureFocus;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    bool _isFocus;
    Engine::Graphic* _graphic;
    object3d::AObject* _gp;
    Button(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture, const std::string& textureFocus, bool _isFocus);
    ~Button();
    void onFocus();
    void onLooseFocus();
  };

  class Menu : public Component::abstract{
  protected:
    bool _validBackground;
    std::string _texture;
    int _sizeX;
    int _sizeY;
    int _posX;
    int _posY;
    std::list<Button*> _buttons;
    object3d::AObject* _gp;
    Engine::Graphic* _graphic;
  public:
    Menu(Entity::GameObject* _p, Engine::Graphic* g);
    Menu(Entity::GameObject* _p, Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture);
    ~Menu();
    void addButton(Engine::Graphic* g, int sizeX, int sizeY, int posX, int posY, const std::string& texture, const std::string& textureFocus, bool _isFocus);
    void draw();

  public:
    std::string serialization() { return (""); }
    void	setBySerial(const Tokenizer&) {}
  };
};

#endif
