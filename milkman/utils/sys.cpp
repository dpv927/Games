#include "../sys.hpp"
#include <raylib.h>

namespace Milkman {
  
  float Window::scaleX;
  float Window::scaleY;
  int Window::width;
  int Window::height;
  sysTime Window::timeNow;

  bool Window::isOutside(Vector2 point) {
    return !(point.x > Window::width || point.x < 0 ||
             point.y > Window::height || point.y < 0);
  }
}
