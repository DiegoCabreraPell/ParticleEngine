#ifndef SIMTYPES_H
#define SIMTYPES_H

typedef float (*forceFunc)(float);
typedef void (*collisionResolver)(Particle&, Particle&, float dist);

#endif