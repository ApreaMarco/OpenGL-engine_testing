

#include "sound_source.h"

SoundSource::SoundSource()
{
	alGenSources(1, &Source);
	alSourcei(Source, AL_BUFFER, Buffer);
}

SoundSource::~SoundSource()
{
	alDeleteSources(1, &Source);
}

void SoundSource::Play(const ALuint buffer)
{
	if (buffer != Buffer)
	{
		Buffer = buffer;
		alSourcei(Source, AL_BUFFER, (ALint)Buffer);
	}

	alSourcePlay(Source);

	// ALint state = AL_PLAYING;
	// std::cout << "playing sound\n";
	// while (state == AL_PLAYING && alGetError() == AL_NO_ERROR)
	// {
	// 	std::cout << "currently playing sound\n";
	// 	alGetSourcei(Source, AL_SOURCE_STATE, &state);
	// }
	// std::cout << "done playing sound\n";
}

