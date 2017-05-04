//
// Created by duhieu_b on 04/05/17.
//

#ifndef CPP_INDIE_STUDIO_PLAYER_HPP
#define CPP_INDIE_STUDIO_PLAYER_HPP

#include <cstdint>
#include "Car.hpp"

class Player : public IDrawable, public Object
{
public:
  Player() = default;
  Player(Player const &) = default;
  Player(Player &&) = delete;
  Player &operator=(Player &) = delete;
  Player &operator=(Player &&) = delete;

  Car &getCar() const;
  void attributeCar(const Car &m_car);
  Account &getAccount() const;
  void setAccount(const Account &m_account);
  std::int32_t        getLap() const;
  void                setLap(std::int32_t);
  std::int32_t        getRank() const;
  void                setRank(std::int32_t);
  std::vector<Bonus> &getBonus() const;
  void                addBonus(Bonus);
  void                setPosition(Position const);
  Position &          getPosition() const;
  Sprite &            getSprite() const;
  void setSprite(const Sprite &m_sprite);

  bool useBonus(std::int32_t);

private:
  Car                m_car;
  Account            m_account;
  std::int32_t       m_lap;
  std::int32_t       m_rank;
  std::vector<Bonus> m_bonus;
  Position           m_position;
  Sprite             m_sprite;
};

#endif // CPP_INDIE_STUDIO_PLAYER_HPP
