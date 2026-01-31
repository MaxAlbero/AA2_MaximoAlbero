#pragma once
#include "Stream.h"
#include "AtomicWrapper.h"

#include <SDL3/SDL_audio.h>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <queue>
#include <exception>
#include <thread>

//Para controlar cuando hay que termiar los threads
static std::atomic<bool> shouldHaltAudio = false;
static std::vector<AtomicWrapper<bool>> threadsDone;

#define AM AudioManager::GetInstance()

class AudioManager {
public:
	static AudioManager* GetInstance() {
		static AudioManager instance;
		return &instance;
	}

	//Abre un dispositivo de audio
	bool Init() {
		try {

			if (!SDL_Init(SDL_INIT_AUDIO))
			{
				throw SDL_GetError();
			}

			_audioDevice = SDL_OpenAudioDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, NULL);

			if (_audioDevice == 0)
				throw SDL_GetError();

			return true;
		}
		catch (std::exception& exception) {
			std::cout << "Error: " << exception.what() << std::endl;
			return false;
		}
	}

	//Fundamental llamar antes de cerrar el programa
	void HaltAudio() {
		shouldHaltAudio = true;

		int size = threadsDone.size();
		for (int i = 0; i < size; )
		{
			//Només incrementa comptador si el thread que s'està comprovant ha acabat
			if (threadsDone.at(i)._a)
				i++;
		}

		//NOU! -> Reset
		shouldHaltAudio = false;
		threadsDone.clear();
	}

	//Lee y guarda datos de un .wav a partir de su ruta
	bool LoadSoundData(std::string path) {
		if (_soundsData.find(path) != _soundsData.end())
			return false;

		SoundData* soundData = new SoundData();

		try {
			//Cargar el wav desde la ruta
			if (!SDL_LoadWAV(
				path.c_str(),
				&soundData->spec,
				&soundData->wavData,
				&soundData->wavDataLength
			))
			{
				throw SDL_GetError();
			}

			//Guardar la información de este sonido
			_soundsData[path] = soundData;

			return true;
		}
		catch (std::exception& exception) {
			delete soundData;
			std::cout << "Error: " << exception.what() << std::endl;
			return false;
		}
	}

	//Crear un nuevo stream a partir de los datos del .wav asociado a la ruta
	void PlaySound(std::string path) {
		if (_soundsData.find(path) == _soundsData.end())
			return;

		//Creamos el thread
		threadsDone.push_back(std::atomic<bool>(false));
		std::thread thread(&AudioManager::PlaySoundCallback, this, path, (threadsDone.size() - 1), false);
		thread.detach();
	}

	void PlaySoundLooping(std::string path) {
		if (_soundsData.find(path) == _soundsData.end())
			return;

		//Creamos el thread
		threadsDone.push_back(std::atomic<bool>(false));
		std::thread thread(&AudioManager::PlaySoundCallback, this, path, (threadsDone.size() - 1), true);
		thread.detach();
	}

	void Mute() {
		if (_muted)
			return;

		SDL_PauseAudioDevice(_audioDevice);
		_muted = true;
	}

	void Unmute() {
		if (!_muted)
			return;

		SDL_ResumeAudioDevice(_audioDevice);
		_muted = false;
	}

	SoundData* GetSoundData(std::string path) {
		if (_soundsData.find(path) == _soundsData.end())
			return nullptr;

		return _soundsData[path];
	}

private:
	AudioManager() = default;
	AudioManager(AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;
	~AudioManager() {
		//Limpiar los datos de sonido
		for (std::map<std::string, SoundData*>::iterator it = _soundsData.begin(); it != _soundsData.end(); it++) {
			delete it->second;
		}

		_soundsData.clear();
	}

	void PlaySoundCallback(std::string path, int pos, bool looping) {
		Stream stream = Stream(_soundsData[path]->spec, _audioDevice);
		if (looping)
			stream.CheckPlaybackLooping(_soundsData[path], shouldHaltAudio);
		else
			stream.CheckPlayback(_soundsData[path], shouldHaltAudio);
		threadsDone[pos] = AtomicWrapper<bool>(std::atomic<bool>(true));
	}

	bool _muted = false;
	SDL_AudioDeviceID _audioDevice = 0;

	std::map<std::string, SoundData*> _soundsData;

};