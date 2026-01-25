%module steel
%{
  #include "procedural/camera.h"
  #include "procedural/color.h"
  #include "procedural/drawing.h"
  #include "procedural/entity.h"
  #include "procedural/font.h"
  #include "procedural/input.h"
  #include "procedural/math.h"
  #include "procedural/memblock.h"
  #include "procedural/pixmap.h"
  #include "procedural/scene.h"
  #include "procedural/screen.h"
  #include "procedural/texture.h"
%}

typedef bool bool_t;

%include "src/interface/input_codes.h"
%include "src/procedural/common.h"
%include "src/procedural/camera.h"
%include "src/procedural/color.h"
%include "src/procedural/drawing.h"
%include "src/procedural/entity.h"
%include "src/procedural/font.h"
%include "src/procedural/input.h"
%include "src/procedural/math.h"
%include "src/procedural/memblock.h"
%include "src/procedural/pixmap.h"
%include "src/procedural/scene.h"
%include "src/procedural/screen.h"
%include "src/procedural/texture.h"
