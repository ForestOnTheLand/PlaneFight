#pragma once
#include <cstdlib>

struct KeyState {
	bool W = 0;
	bool A = 0;
	bool S = 0;
	bool D = 0;
};

inline int randint(int begin, int end) {
	return rand() % (end - begin) + begin;
}

inline int _checked(int t, int begin, int end) {
	return t <= begin ? begin : t >= end ? end : t;
}
