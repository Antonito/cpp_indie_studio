//
// Created by duhieu_b on 14/06/17.
//

#ifndef CPP_INDIE_STUDIO_DATA_HPP
#define CPP_INDIE_STUDIO_DATA_HPP

#include <iostream>
#include <zconf.h>

struct Data
{
  long         s_bestTime;
  std::int32_t s_maxSpeed;
  std::int32_t s_trackFinished;
  std::int32_t s_totalKm;
  std::int32_t s_collisionCount;

  Data()
      : s_bestTime(0), s_maxSpeed(0), s_trackFinished(0), s_totalKm(0),
        s_collisionCount(0)
  {
    reset();
  }

  Data(Data const &cpy)
      : s_bestTime(cpy.s_bestTime), s_maxSpeed(cpy.s_maxSpeed),
        s_trackFinished(cpy.s_trackFinished), s_totalKm(cpy.s_totalKm),
        s_collisionCount(cpy.s_collisionCount)
  {
    s_bestTime = cpy.s_bestTime;
    s_maxSpeed = cpy.s_maxSpeed;
    s_trackFinished = cpy.s_trackFinished;
    s_totalKm = cpy.s_totalKm;
    s_collisionCount = cpy.s_collisionCount;
  }

  Data &operator=(Data &that)
  {
    if (&that != this)
      {
	s_bestTime = that.s_bestTime;
	s_maxSpeed = that.s_maxSpeed;
	s_trackFinished = that.s_trackFinished;
	s_totalKm = that.s_totalKm;
	s_collisionCount = that.s_collisionCount;
      }
    return *this;
  }

  void reset()
  {
    s_bestTime = 0;
    s_maxSpeed = 0;
    s_trackFinished = 0;
    s_totalKm = 0;
    s_collisionCount = 0;
  }
};

#endif // CPP_INDIE_STUDIO_DATA_HPP
