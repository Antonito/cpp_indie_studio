//
// Created by duhieu_b on 14/06/17.
//

#ifndef CPP_INDIE_STUDIO_DATA_HPP
#define CPP_INDIE_STUDIO_DATA_HPP

#include <iostream>
#include <zconf.h>

struct Data
{
  float        s_bestTime[10];
  std::int32_t s_maxSpeed[10];
  std::int32_t s_trackFinished[10];
  std::int32_t s_totalKm[10];
  std::int32_t s_collisionCount[10];

  Data()
  {
    reset();
  }

  Data(Data const &cpy)
  {
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_bestTime[i] = cpy.s_bestTime[i];
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_maxSpeed[i] = cpy.s_maxSpeed[i];
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_trackFinished[i] = cpy.s_trackFinished[i];
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_totalKm[i] = s_totalKm[i];
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_collisionCount[i] = s_collisionCount[i];
      }
  }

  Data &operator=(Data &that)
  {
    if (&that != this)
      {
	for (std::int32_t i = 0; i < 10; ++i)
	  {
	    s_bestTime[i] = that.s_bestTime[i];
	  }
	for (std::int32_t i = 0; i < 10; ++i)
	  {
	    s_maxSpeed[i] = that.s_maxSpeed[i];
	  }
	for (std::int32_t i = 0; i < 10; ++i)
	  {
	    s_trackFinished[i] = that.s_trackFinished[i];
	  }
	for (std::int32_t i = 0; i < 10; ++i)
	  {
	    s_totalKm[i] = that.s_totalKm[i];
	  }
	for (std::int32_t i = 0; i < 10; ++i)
	  {
	    s_collisionCount[i] = that.s_collisionCount[i];
	  }
      }
    return *this;
  }

  void reset()
  {
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_bestTime[i] = 0.0f;
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_maxSpeed[i] = 0;
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_trackFinished[i] = 0;
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_totalKm[i] = 0;
      }
    for (std::int32_t i = 0; i < 10; ++i)
      {
	s_collisionCount[i] = 0;
      }
  }
};

#endif // CPP_INDIE_STUDIO_DATA_HPP
