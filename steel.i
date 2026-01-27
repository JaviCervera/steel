%module steel
%{
  #include "procedural/anim_model.h"
  #include "procedural/camera.h"
  #include "procedural/collision.h"
  #include "procedural/color.h"
  #include "procedural/drawing.h"
  #include "procedural/entity.h"
  #include "procedural/font.h"
  #include "procedural/input.h"
  #include "procedural/light.h"
  #include "procedural/material.h"
  #include "procedural/math.h"
  #include "procedural/memblock.h"
  #include "procedural/model.h"
  #include "procedural/pixmap.h"
  #include "procedural/scene.h"
  #include "procedural/screen.h"
  #include "procedural/texture.h"
%}

typedef bool bool_t;
class Entity { protected: Entity(); ~Entity(); };
class AnimModel : public Entity { protected: AnimModel(); ~AnimModel(); };
class Camera : public Entity { protected: Camera(); ~Camera(); };
class Light : public Entity { protected: Light(); ~Light(); };
class Model : public Entity { protected: Model(); ~Model(); };

%include "src/interface/input_codes.h"
%include "src/procedural/common.h"
%include "src/procedural/anim_model.h"
%include "src/procedural/camera.h"
%include "src/procedural/collision.h"
%include "src/procedural/color.h"
%include "src/procedural/drawing.h"
%include "src/procedural/entity.h"
%include "src/procedural/font.h"
%include "src/procedural/input.h"
%include "src/procedural/light.h"
%include "src/procedural/material.h"
%include "src/procedural/math.h"
%include "src/procedural/memblock.h"
%include "src/procedural/model.h"
%include "src/procedural/pixmap.h"
%include "src/procedural/scene.h"
%include "src/procedural/screen.h"
%include "src/procedural/texture.h"
