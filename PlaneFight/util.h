#pragma once

#include "config.h"
#include <cstdlib>
#include <random>

struct KeyState {
	bool W = 0;
	bool A = 0;
	bool S = 0;
	bool D = 0;
	bool K = 0;
};

inline double _rand_double() {
	static std::default_random_engine random_engine;
	static std::uniform_real_distribution<double> uniform_dist;
	return uniform_dist(random_engine);
}

inline int randint(int begin, int end) {
	return rand() % (end - begin) + begin;
}

inline int random_x() {
	return randint(battlefield_border.left(), battlefield_border.right());
}

inline int random_y() {
	return randint(battlefield_border.top(), battlefield_border.bottom());
}

inline double randdouble(double begin, double end) {
	return _rand_double() * (end - begin) + begin;
}

inline int _checked(int t, int begin, int end) {
	return t <= begin ? begin : t >= end ? end : t;
}

inline bool with_probability(double p) {
	return _rand_double() < p;
}

template <typename T>
inline int distribution_as(T __list) {
	int i = 0;
	double d = _rand_double(), p_sum = 0;
	for (double p : __list) {
		if (d < (p_sum += p))
			break;
		else
			++i;
	}
	return i;
}
