#include "_Effect.h"

_Effect::_Effect(std::initializer_list<const char*> __images_path)
    : _valid(true), _picture_index(0), _timer(0) {
	for (const char* path : __images_path) {
		_pictures.push_back(new QPixmap(path));
	}
}

_Effect::~_Effect() {
	for (QPixmap* picture : _pictures) {
		delete picture;
	}
}

bool _Effect::valid() const {
	return _valid;
}
