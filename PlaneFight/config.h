#pragma once
#include <qrect.h>

inline constexpr QRect battlefield_border(10, 10, 480, 680);
inline constexpr int update_rate = 10;
inline constexpr int player_max_health = 500;
enum play_mode_t { mouse_mode, key_mode };
inline constexpr play_mode_t play_mode = key_mode;
