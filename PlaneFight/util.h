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

inline int psuedo_randint(int begin, int end) {
	static int a = begin - 1;
	return ++a < end ? a : rand() % (end - begin) + begin;
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

template <typename T>
inline T _checked(T t, T begin, T end) {
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

inline constexpr double to_rad(double degree) {
	return degree * (M_PI / 180);
}

inline constexpr double to_deg(double radius) {
	return radius * (180 / M_PI);
}

void paintRotatedPicture(QPainter& painter, const QPixmap& picture, QPointF center, double deg);
