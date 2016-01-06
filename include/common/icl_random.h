/*
 * icl_conf.h
 *
 *  Created on: 2014-01-24
 *      Author: peterxmw
 */

#ifndef ICL_RANDOM_H_
#define ICL_RANDOM_H_



int get_random(char *p, int size, int nmemb, int seed);
char *get_char32_random(int seed);
char *get_char64_random(int seed);
char *get_char128_random(int seed);


#endif /* ICL_RANDOM_H_ */
