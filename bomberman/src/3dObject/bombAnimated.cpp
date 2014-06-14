#include "bombAnimated.hpp"
namespace object3d{
  bombAnimated::bombAnimated()
    : animatedVertex("./3dObject/Bomb/Bomb.FBX", 0.02f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 50);
  }
};
