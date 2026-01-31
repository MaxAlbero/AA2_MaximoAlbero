#pragma once
#include <SDL3/SDL_audio.h>
#include <atomic>
#include <vector>

//Estructura para guardar los datos de un .wav
struct SoundData {
	SDL_AudioSpec spec; //Formato del audio
	Uint8* wavData;
	Uint32 wavDataLength; //Cuantos bytes hay en wavData
};

enum StreamState {
	READY = 1,
	PLAYING = 2,
	STOPPED = 3
};

class Stream {
private:
	SDL_AudioStream* _stream;
	StreamState _state;

	void StopStream() {
		//1) Limpia el SDL_AudioStream
		SDL_ClearAudioStream(_stream);

		//2) Desvincular el SDL_AudioStream del dispositivo de Audio
		SDL_UnbindAudioStream(_stream);

		//3) Destruir el SDL_AudioStream
		SDL_DestroyAudioStream(_stream);

		//4) Actualizar el estado
		_state = STOPPED;
	}

public:
	Stream(SDL_AudioSpec spec, SDL_AudioDeviceID deviceId) {
		//1) Crea un SDL_AudioStream
			//- Utiliza como formato de origne el mismo que el del .wav
			//- Deja el formato destino a NULL (cambiara al desado por el hardware en hacer bind)
		_stream = SDL_CreateAudioStream(&spec, NULL);

		//2) Bindear, vincula el stream al dispositivo de audio deseado
		SDL_BindAudioStream(deviceId, _stream);

		//3) Indicar el estado
			// - Ahora mismo el stream esta listo para añadirle datos, pero por ahora esta vacio
		_state = READY;
	}

	~Stream() {}

	void CheckPlayback(SoundData* soundData, std::atomic<bool>& haltRequest) {
		while (_state != STOPPED) {
			//Si ya se ha reproducido una vez el stream y la reproduccion ha acabado
			//O hay que parar el proceso / la reproduccion
			if ((_state != READY && SDL_GetAudioStreamQueued(_stream) == 0) || haltRequest) {
				StopStream();
			}

			//Si el stream todavia no se reproducido y esta preparado para hacerlo
			if (_state == READY) {
				Uint32 bytesQueued = SDL_GetAudioStreamQueued(_stream);
				int bytesRemaining = ((int)soundData->wavDataLength) - bytesQueued;

				//Paso para conseguir array con tamaño variable
				std::vector<Uint8> wavDataRemainingVec = std::vector<Uint8>(bytesRemaining, '\0');
				Uint8* wavDataRemaining = &wavDataRemainingVec[0];

				//dst, src, len
				SDL_memcpy(wavDataRemaining, (const Uint32*)&soundData->wavData[bytesQueued], bytesRemaining);
				SDL_PutAudioStreamData(_stream, wavDataRemaining, bytesRemaining);

				//Indicar que no se desea añadir nada más al stream hasta que no acabe (añadimos-consumimos, añadimos-consumimos...)
				SDL_FlushAudioStream(_stream);

				//Evitar que en la siguiente iteracion se repita la copia de memoria 
				_state = PLAYING;
			}
		}
	}

	void CheckPlaybackLooping(SoundData* soundData, std::atomic<bool>& haltRequest) {
		while (_state != STOPPED) {
			//Si hay que parar el proceso / la reproduccion
			if (haltRequest) {
				StopStream();
			}

			//Si el stream todavia no se reproducido y esta preparado para hacerlo
			if (_state == READY) {
				Uint32 bytesQueued = SDL_GetAudioStreamQueued(_stream);
				int bytesRemaining = ((int)soundData->wavDataLength) - bytesQueued;

				//Paso para conseguir array con tamaño variable
				std::vector<Uint8> wavDataRemainingVec = std::vector<Uint8>(bytesRemaining, '\0');
				Uint8* wavDataRemaining = &wavDataRemainingVec[0];

				//dst, src, len
				SDL_memcpy(wavDataRemaining, (const Uint32*)&soundData->wavData[bytesQueued], bytesRemaining);
				SDL_PutAudioStreamData(_stream, wavDataRemaining, bytesRemaining);

				//Indicar que no se desea añadir nada más al stream hasta que no acabe (añadimos-consumimos, añadimos-consumimos...)
				SDL_FlushAudioStream(_stream);

				//Evitar que en la siguiente iteracion se repita la copia de memoria 
				_state = PLAYING;
			}

			//Si ha acabado el sonido y hay que empezar un nuevo ciclo de reproduccion
			if (_state == PLAYING && SDL_GetAudioStreamQueued(_stream) == 0) {
				SDL_ClearAudioStream(_stream);
				_state = READY;

			}
		}
	}
};