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
#include <vector>
#include <iomanip>

// Disable clang warning for templated class padding
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif

namespace core
{
    enum ESound
    {
        THEME_SONG = 0,
        SPLASH_SONG,
        PASS_BUTTON,
        CLICK_BUTTON,
        GAME_SONG,
        IDLE_KART_SOUND,
        ACC_KART_SOUND,
        KLAXON_KART_SOUND,
        BOOST_SONG,
        START_SONG,
        SLOW_KART_SOUND,
        SOLO_LAUNCH_SOUND,
        SCORE_LAUNCH_SOUND,
        FALIED_CONNECTION_SOUND,
        SETTING_LAUNCH_SOUND,
        GO_RACE_SOUND,
        BACK_RACE_SOUND,
        NUMBER_SOUND
    };
  class SoundManager
  {
  public:
    SoundManager();

    SoundManager(SoundManager const &);

    ~SoundManager();

    SoundManager &operator=(SoundManager &);

    void initOpenAl(char const *);

    void shutdownOpenAl();

    void playSound(std::size_t const);

    void pauseSound(std::size_t const);

    void stopSound(std::size_t const);

    void loopSound(std::size_t const);

    void setVolumeSource(std::size_t const, float);

    void setVolume(float);

    void state(std::size_t const);

    ALint getState() const;

    ALuint getSource(std::size_t const idx) const;

    void setPosition(std::size_t const, float, float, float);

    void setOrientation(std::size_t const, float, float, float);

    ALfloat getVolume() const;

    void loadSound(std::string const &);

    void loadAllSound();

    void clear();

    void getInfoLectureSound(std::size_t const idx) const;

  private:
    ALCdevice *         m_device;
    ALCcontext *        m_context;
    std::vector<ALuint> m_buffer;
    std::vector<ALuint> m_source;
    ALint               m_state;
    ALfloat             m_volume;
  };
}
#if defined(__clang__)
#pragma clang diagnostic pop
#endif

#endif // CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
