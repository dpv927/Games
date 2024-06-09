#ifndef UTILS

/* Genertates a floating point random number between 0 and 1. */
#define genRandom() ((float)(std::rand())/(float)(RAND_MAX))

/* Genertates a integer between the parameter 'n' and 'm',
 * both limits included. */
#define genRandomFrom(min,max) (std::rand()%(max - min + 1) + min)

/* Aproximates the parameter "n" (the value of a coordinate), to
 * the nearest multiple of "m", usually the width in pixels of a
 * map tile width. */ 
#define aproxCoordinate(n,m) (round((float)(n)/m)*m)

#endif
