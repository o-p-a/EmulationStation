#pragma once
#ifndef ES_CORE_AUDIO_MANAGER_H
#define ES_CORE_AUDIO_MANAGER_H

#include <SDL_audio.h>
#include <memory>
#include <vector>

class Sound;

class AudioManager
{
	static SDL_AudioSpec sAudioFormat;
	static std::vector<std::shared_ptr<Sound>> sSoundVector;
	static AudioManager* sInstance;

	static void mixAudio(void *unused, Uint8 *stream, int len);

	AudioManager() {};
	~AudioManager() {};

public:
	static AudioManager* getInstance();

	void init();
	void deinit();

	void registerSound(std::shared_ptr<Sound> & sound);
	void unregisterSound(std::shared_ptr<Sound> & sound);

	void play();
	void stop();
};

#endif // ES_CORE_AUDIO_MANAGER_H
