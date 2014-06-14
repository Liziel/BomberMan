#include "bombAnimated.hh"
namespace object3d{
  bombGlace::bombGlace()
    : animatedVertex("./3dObject/Bombe Glace/Glace.FBX", 0.02f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 100);
  }
  bombThunder::bombThunder()
    : animatedVertex("./3dObject/Bombe thunder/thunder.FBX", 0.02f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 100);
  }
  bombFeu::bombFeu()
    : animatedVertex("./3dObject/Bombe lava/BombLava.FBX", 0.02f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 100);
  }
  bombHealth::bombHealth()
    : animatedVertex("./3dObject/Bombe Health/Health.FBX", 0.02f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 100);
  }
  bombGlyph::bombGlyph()
    : animatedVertex("./3dObject/Bombe Glyphe/Glyphe.FBX", 0.02f) {
    _model.createSubAnim(0, "stop", 0, 0);
    _model.createSubAnim(0, "run", 0, 100);
  }
};
