#pragma once
#include "util.h"

class BackgroundMusic {
private:
	BackgroundMusic() = delete;
	~BackgroundMusic() = default;
	BackgroundMusic(const BackgroundMusic&) = delete;
	BackgroundMusic& operator=(const BackgroundMusic&) = delete;

	// private:
	//	static QSoundEffect _sound;

public:
	static void load(const QString& path);
	static void pause();
	static void play();
};