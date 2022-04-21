// https://gist.github.com/wandrson/10000147
// This example sketch shows how to provide a truly random seed value to the built in
// library pseudo random number generator. This ensures that your sketch will be
// using a different sequence of random numbers every time it runs. Unlike the
// usually suggested randomSeed(analogRead(0)) this method will provide a much more
// uniform and varied seed value. For more information about the basic technique used
// here to produce a random number or if you need more than one such number you can
// find a library, Entropy from the following web site along with documentation of how
// the library has been tested to provide TRUE random numbers on a variety of AVR
// chips and arduino environments.
//
// https://sites.google.com/site/astudyofentropy/project-definition/
// timer-jitter-entropy-sources/entropy-library
//
// Copyright 2014 by Walter Anderson, wandrson01 at gmail dot com
//

#ifndef MY_RANDOM_H
#define MY_RANDOM_H

void CreateTrulyRandomSeed();
void setupSeed();
#endif