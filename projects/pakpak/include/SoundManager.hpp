//
// Created by duhieu_b on 15/06/17.
//

#ifndef CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
#define CPP_INDIE_STUDIO_SOUNDMANAGER_HPP

#if defined __APPLE__
#include <OpenAL/al.h>
#include <OpenAL/alc.h>
#else
#include <AL/al.h>
#include <AL/alc.h>
#endif

#include <vector>
#include <sndfile.h>
#include <iostream>

namespace core
{
  class SoundManager
  {
  public:
    SoundManager();

    SoundManager(SoundManager const &);

    ~SoundManager();

    SoundManager &operator=(SoundManager &);

    void initOpenAl(char const *);

    void shutdownOpenAl();

    void playSound();

    void pauseSound();

    void stopSound();

    void loopSound();

    void setVolume(float);

    void state();

    ALint getState() const;

    ALuint getSource(std::int32_t) const;

    void setPosition(float, float, float);

    void setOrientation(float, float, float);

    ALfloat getVolume() const;

    void loadSound(std::string const &);

    void clear();

    void getInfoLectureSound(std::int32_t) const;

  private:
    ALCdevice *         m_device;
    ALCcontext *        m_context;
    std::vector<ALuint> m_buffer;
    std::vector<ALuint> m_source;
    ALint               m_state;
    ALfloat             m_volume;
  };
}
#endif // CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
