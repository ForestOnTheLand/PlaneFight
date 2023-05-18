#pragma once
#include "_Plane.h"

/**
 * Player's plane.
 * A Singleton class derived from class `_Plane`
 */
class PlayerPlane : public _Plane {
private:
	PlayerPlane(const char* const __image_path);
	static PlayerPlane* _plane;

public:
	static PlayerPlane* plane();
	static void init();
	static void free();
	PlayerPlane(const PlayerPlane&) = delete;
	PlayerPlane& operator=(const PlayerPlane&) = delete;

public:
	void shootMissiles() final;
};
