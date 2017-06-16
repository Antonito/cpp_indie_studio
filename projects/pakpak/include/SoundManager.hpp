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
#include <sndfile.h>
#include <iostream>

class SoundManager
{
public:
  SoundManager();
  SoundManager(SoundManager const &);
  ~SoundManager();
  SoundManager &operator=(SoundManager &);
  void          initOpenAl(char const *);
  void          shutdownOpenAl();

  void   playSound();
  void   pauseSound();
  void   stopSound();
  void   loopSound();
  void   upVolume(float);
  void   downVolume(float);
  void   state();
  ALint  getState() const;
  ALuint getSource() const;
  void   setPosition(float, float, float);
  void   setOrientation(float, float, float);
  void   loadSound(std::string const &);
  void   clear();
  void   getInfoLectureSound() const;

private:
  ALCdevice * m_device;
  ALCcontext *m_context;
  ALuint      m_buffer;
  ALuint      m_source;
  ALint       m_state;
};

#endif // CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
