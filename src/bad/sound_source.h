

#ifndef SOUND_SOURCE_H
#define SOUND_SOURCE_H

#include <AL/al.h>

class SoundSource
{
public:
	SoundSource();
	~SoundSource();

	void Play(const ALuint buffer);

private:
	ALuint Source;
	ALuint Buffer = 0;
};

#endif

