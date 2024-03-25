#ifndef _SYS_H
#define _SYS_H

#include "types.hpp"
#include <raylib.h>
#define BaseWidthPx 1366
#define BaseHeightPx 768

namespace Milkman {
  
  struct Window {
    static float scaleX;
    static float scaleY;
    static int width;
    static int height;
    static sysTime timeNow;

    static bool isOutside(Vector2);
  };
}

#endif // !_SYS_H
