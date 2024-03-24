#ifndef _SYS_H
#define _SYS_H
#include "types.hpp"

#define BaseWidthPx 1366;
#define BaseHeightPx 768;

struct Sys {
  static int screenWidth;
  static int screenHeight;
  static float scaleX;
  static float scaleY;
  static sysTime timeNow;
};

#endif // !_SYS_H
