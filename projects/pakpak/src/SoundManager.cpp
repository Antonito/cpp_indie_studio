//
// Created by duhieu_b on 15/06/17.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include "SoundManager.hpp"
#include "Logger.hpp"
#include "IOError.hpp"

namespace core
{
  SoundManager::SoundManager()
      : m_device(nullptr), m_context(nullptr), m_buffer(), m_source(),
        m_state(AL_INITIAL)
  {
    nope::log::Log(Debug) << "**Initialization SoundManager**";
  }

  SoundManager::SoundManager(SoundManager const &cpy)
      : m_device(cpy.m_device), m_context(cpy.m_context),
        m_buffer(cpy.m_buffer), m_source(cpy.m_source), m_state(cpy.m_state)
  {
  }

  SoundManager::~SoundManager()
  {
    shutdownOpenAl();
    nope::log::Log(Debug) << "**Deleting SoundManager**";
  }

  SoundManager &SoundManager::operator=(SoundManager &that)
  {
    if (&that != this)
      {
	m_device = that.m_device;
	m_context = that.m_context;
	m_buffer = that.m_buffer;
	m_source = that.m_source;
	m_state = that.m_state;
      }
    return *this;
  }

  // Load a specific sound, where "Filename" is the name of the sound file.
  void SoundManager::loadSound(const std::string &Filename)
  {
    // Open audio file with libsndfile
    SF_INFO FileInfos;
    nope::log::Log(Debug) << "Prepare open file sound";
    SNDFILE *File = sf_open(Filename.c_str(), SFM_READ, &FileInfos);
    if (!File)
      {
	throw IOError("Unable to open audio file");
      }

    nope::log::Log(Debug) << "File has been open : " << Filename;
    // Reading the number of samples and the sampling rate (number of samples
    // to
    // be read / second)
    ALsizei NbSamples =
        static_cast<ALsizei>(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = static_cast<ALsizei>(FileInfos.samplerate);

    nope::log::Log(Debug) << "Reading samples of " << Filename;
    // Reading the samples with 16 bit signed format (More common)
    std::vector<ALshort> Samples(NbSamples);
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
      {
	throw IOError("Unable to read samples stored in audio file.");
      }

    nope::log::Log(Debug) << "Reading samples of " << Filename
                          << " has succeed.\n"
                          << "Choose a specific format";
    // Close file
    sf_close(File);

    // Determine format with the specific number of channels
    ALenum Format;
    switch (FileInfos.channels)
      {
      case 1:
	Format = AL_FORMAT_MONO16;
	break;
      case 2:
	Format = AL_FORMAT_STEREO16;
	break;
      default:
	throw IOError("Audio format not supported (More than 2 channels).");
      }

    nope::log::Log(Debug) << "Format has been chosen";
    // Create the OpenAl buffer
    ALuint buffer;
    alGenBuffers(1, &buffer);

    // Filling of samples read
    alBufferData(buffer, Format, &Samples[0],
                 NbSamples * static_cast<ALsizei>(sizeof(ALushort)),
                 SampleRate);

    // check Error
    if (alGetError() != AL_NO_ERROR)
      {
	if (static_cast<int>(alGetError()) != 0)
	  {
	    throw IOError("Unable to fill openAl buffer with audio file's "
	                  "samples, error : " +
	                  std::to_string(static_cast<int>(alGetError())));
	  }
      }
    nope::log::Log(Debug) << "No error while loading " << Filename << " sound";
    // set Source
    ALuint source;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, buffer);
    m_buffer.push_back(buffer);
    m_source.push_back(source);
  }

  // Init device and context of OpenAl
  void SoundManager::initOpenAl(char const *deviceName)
  {
    // Open the device
    m_device = alcOpenDevice(deviceName);
    nope::log::Log(Debug) << "Device setting";
    if (!m_device)
      {
	throw IOError("Cannot load the default device");
      }

    // Create the context
    nope::log::Log(Debug) << "Device set && Context setting";
    m_context = alcCreateContext(m_device, NULL);
    if (!m_context)
      {
	throw IOError("Unable to create an audio context");
      }

    nope::log::Log(Debug) << "Context set && attribute context";
    // Activate the context
    if (!alcMakeContextCurrent(m_context))
      {
	throw IOError("Unable to activate the audio context");
      }
  }

  // Clear devices and context of openAl
  void SoundManager::shutdownOpenAl()
  {
    nope::log::Log(Debug) << "Clear openAl";
    // Deactivate the current context
    alcMakeContextCurrent(NULL);

    // Destroy current context
    alcDestroyContext(m_context);

    // Close current device
    alcCloseDevice(m_device);
  }

  // Set the position of the sound
  void SoundManager::setPosition(float x, float y, float z)
  {
    nope::log::Log(Debug) << "Setting sound to position {" << x << ", " << y
                          << ", " << z << "}.";
    alSourcei(m_source[0], AL_SOURCE_RELATIVE, AL_TRUE);
    alSource3f(m_source[0], AL_POSITION, x, y, z);
  }

  // Put the current sound in looping
  void SoundManager::loopSound()
  {
    nope::log::Log(Debug) << "Looping sound";
    alSourcei(m_source[0], AL_LOOPING, AL_TRUE);
  }

  // Stop the sound
  void SoundManager::stopSound()
  {
    nope::log::Log(Debug) << "Stopping sound";
    alSourceStop(m_source[0]);
  }

  // Put sound in pause
  void SoundManager::pauseSound()
  {
    nope::log::Log(Debug) << "Pause sound";
    alSourcePause(m_source[0]);
  }

  // Play the sound
  void SoundManager::playSound()
  {
    nope::log::Log(Debug) << "Play sound";
    alSourcePlay(m_source[0]);
  }

  // Set the current state of the volume
  void SoundManager::state()
  {
    alGetSourcei(m_source[0], AL_SOURCE_STATE, &m_state);
  }

  // Get the actual sound state
  ALint SoundManager::getState() const
  {
    return m_state;
  }

  // Clear current buffer and source of the sound
  void SoundManager::clear()
  {
    nope::log::Log(Debug) << "Clear sound";

    for (std::vector<ALuint>::iterator it = m_buffer.begin(); it != m_buffer.end(); ++it)
      alDeleteBuffers(1, &(*it));
    for (std::vector<ALuint>::iterator it = m_source.begin(); it != m_source.end(); ++it)
    {
      alSourcei(*it, AL_BUFFER, 0);
      alDeleteSources(1, &(*it));
    }
  }

  void SoundManager::setVolume(float volume)
  {
    nope::log::Log(Debug) << "Setting volume : " << volume;
    for (std::vector<ALuint>::iterator it = m_source.begin(); it != m_source.end(); ++it)
      alSourcef(*it, AL_GAIN, volume);
  }

  // Set the orientation of the sound to a specific direction
  void SoundManager::setOrientation(float x, float y, float z)
  {
    nope::log::Log(Debug) << "Set sound to direction ; {" << x << ", " << y
                          << ", " << z << "}.";
    alSource3f(m_source[0], AL_ORIENTATION, x, y, z);
  }

  // Get the Source of the sound
  ALuint SoundManager::getSource(std::int32_t idx) const
  {
    nope::log::Log(Debug) << "Getting Source";
    return m_source[idx];
  }

  // Get info on the lecture sound.
  void SoundManager::getInfoLectureSound(std::int32_t idx) const
  {
    ALfloat Seconds = 0.f;

    alGetSourcef(m_source[idx], AL_SEC_OFFSET, &Seconds);
    nope::log::Log(Debug) << "\rLecture en cours... " << std::fixed
                          << std::setprecision(2) << Seconds << " sec";
  }
}