#include "BackgroundMusic.h"

QSoundEffect BackgroundMusic::_sound;

void BackgroundMusic::load(const QString& path) {
	_sound.setSource(QUrl::fromLocalFile(path));
	_sound.setLoopCount(QSoundEffect::Infinite);
}

void BackgroundMusic::pause() {
	_sound.stop();
}

void BackgroundMusic::play() {
	_sound.play();
}
