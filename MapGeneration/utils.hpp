#include <cstdlib>

#ifndef _UTILS
#define _UTILS

namespace utils {

  /* Genertates a float random number between 0 and 1.
   * std::rand must be initialized. */
  inline float gen_random() {
    return static_cast<float>(std::rand())/static_cast<float>(RAND_MAX);
  }

  /* Genertates a integer between the parameter 'n' and 'm',
  * both limits included. */
  inline int gen_random_from(int min, int max) {
    return std::rand()%(max - min + 1) + min;
  }
}
#endif
