#pragma once

#define COLOR_RED 0xffff0000
#define COLOR_GREEN 0xff00ff00
#define COLOR_BLUE 0xff0000ff
#define COLOR_CYAN 0xff00ffff
#define COLOR_MAGENTA 0xffff00ff
#define COLOR_YELLOW 0xffffff00
#define COLOR_BLACK 0xff000000
#define COLOR_WHITE 0xffffffff
#define COLOR_GRAY 0xff808080
#define COLOR_LIGHTGRAY 0xffbfbfbf
#define COLOR_DARKGRAY 0xff404040
#define COLOR_ORANGE 0xffffa500
#define COLOR_BROWN 0xff8b4513

struct Color
{
  static int rgb(int r, int g, int b, int a = 255)
  {
    r = clamp(r, 0, 255);
    g = clamp(g, 0, 255);
    b = clamp(b, 0, 255);
    a = clamp(a, 0, 255);
    return (a << 24) | (r << 16) | (g << 8) | b;
  }

  static int rgbf(float r, float g, float b, float a)
  {
    return rgb(int(r * 255), int(g * 255), int(b * 255), int(a * 255));
  }

  static int red(int color)
  {
    return (color >> 16) & 0xff;
  }

  static int green(int color)
  {
    return (color >> 8) & 0xff;
  }

  static int blue(int color)
  {
    return color & 0xff;
  }

  static int alpha(int color)
  {
    return (color >> 24) & 0xff;
  }

  static float redf(int color)
  {
    return float(red(color)) / 255.0f;
  }

  static float greenf(int color)
  {
    return float(green(color)) / 255.0f;
  }

  static float bluef(int color)
  {
    return float(blue(color)) / 255.0f;
  }

  static float alphaf(int color)
  {
    return float(alpha(color)) / 255.0f;
  }

  static int fade(int color, int new_alpha)
  {
    return (clamp(new_alpha, 0, 255) << 24) | (color & 0x00ffffff);
  }

  static int multiply(int color, float factor)
  {
    return rgbf(redf(color) * factor, greenf(color) * factor, bluef(color) * factor, alphaf(color));
  }

  static int swap(int color)
  {
    return rgb(blue(color), green(color), red(color), alpha(color));
  }

private:
  static int clamp(int value, int min, int max)
  {
    return (value < min) ? min : (value > max) ? max
                                               : value;
  }
};
