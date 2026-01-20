%module steel
%{
  #include "procedural/color.h"
  #include "procedural/drawing.h"
  #include "procedural/screen.h"
%}

typedef bool bool_t;

%include "src/procedural/common.h"
%include "src/procedural/color.h"
%include "src/procedural/drawing.h"
%include "src/procedural/screen.h"
