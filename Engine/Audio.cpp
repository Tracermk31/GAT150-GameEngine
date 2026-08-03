#include "pch.h"
#include "Audio.h" 

#include <iostream>
#include <fmod_errors.h>

namespace ChiefEngine {
	bool Audio::Initialize() {
		FMOD_RESULT result = FMOD::System_Create(&m_audio);
		if (!CheckFMODResult(result))
			return false;

		void* extradriverdata = nullptr;

		result = m_audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
		if (!CheckFMODResult(result))
			return false;

		return true;

		m_channel_1->setPriority(0);
		m_channel_2->setPriority(1);
	}

	void Audio::Shutdown() {
		FMOD_RESULT result = m_audio->close();
		CheckFMODResult(result);
	}

	void Audio::Update() {
		FMOD_RESULT result = m_audio->update();
		CheckFMODResult(result);
	}

	bool Audio::AddSound(const std::string& name, const std::string filepath) {
		if (m_sounds.contains(name)) {
			std::cerr << "Audio System : name already exists " << name << std::endl;
			return false;
		}

		FMOD::Sound* sound = nullptr;
		FMOD_RESULT result = m_audio->createSound(filepath.c_str(), FMOD_DEFAULT, 0, &sound);
		if (!CheckFMODResult(result)) {
			return false;
		}

		m_sounds[name] = sound;

		return true;
	}

	bool Audio::setSoundLoop(const std::string& name, bool willLoop) {
		if (!m_sounds.contains(name)) {
			std::cerr << "Audio System: name doesn't exist " << name << std::endl;
			return false;
		}

		if (willLoop){
			m_sounds[name]->setLoopCount(-1);
		}
		else {
			m_sounds[name]->setLoopCount(0);
		}
		return true;
	}

	bool Audio::PlaySound(std::string name, FMOD::Channel* channelToPlayOn) {
		if (!m_sounds.contains(name)) {
			std::cerr << "Audio System : name doesn't exist " << name << std::endl;
			return false;
		}

		FMOD_RESULT result = m_audio->playSound(m_sounds[name], m_channelGroup_1, false, &channelToPlayOn);
		if (!CheckFMODResult(result))
			return false;

		return true;
	}

	bool Audio::CheckFMODResult(FMOD_RESULT result) {
		if (result != FMOD_OK) {
			std::cerr << FMOD_ErrorString(result) << std::endl;
			return false;
		}

		return true;
	}
}