#pragma once
#include <qrect.h>

inline constexpr QRect battlefield_border(10, 10, 480, 680);
extern const int UPDATE_RATE;

enum play_mode_t { mouse_mode, key_mode };
extern const play_mode_t play_mode;