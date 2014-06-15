#include "bookAnimated.hh"

namespace object3d{
  bookAnimated::bookAnimated()
    : animatedVertex("./3dObject/bonus/Book.FBX", 0.05f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 150);
  }
};
