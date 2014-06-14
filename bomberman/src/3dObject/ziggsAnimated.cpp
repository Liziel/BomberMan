#include "ziggsAnimated.hpp"
namespace object3d{
  ziggsAnimated::ziggsAnimated()
    : animatedVertex("./3dObject/Ziggs/Ziggs.FBX", 0.02f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 50);
  }
};
