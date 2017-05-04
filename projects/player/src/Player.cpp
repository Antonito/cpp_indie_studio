//
// Created by duhieu_b on 04/05/17.
//

#include "Player.hpp"

Car &Player::getCar() const
{
    return m_car;
}

void Player::attributeCar(Car const &p_car)
{
    m_car = p_car;
}

Account &Player::getAccount() const
{
    return m_account;
}

void Player::setAccount(Account const& p_account)
{
    m_account = p_account;
}

std::int32_t Player::getLap() const
{
    return m_lap;
}

void Player::setLap(std::int32_t const p_lap)
{
    m_lap = p_lap;
}

std::int32_t Player::getRank() const
{
    return m_rank;
}

void Player::setRank(std::int32_t const p_rank)
{
    m_rank = p_rank;
}

std::vector<Bonus> &Player::getBonus() const
{
    return m_bonus;
}

void Player::addBonus(Bonus p_bonus)
{
    if (std::find(m_bonus.begin(), m_bonus.end(), p_bonus) == m_bonus.end());
        m_bonus.push_back(p_bonus);
}

Sprite &Player::getSprite() const
{
    return m_sprite;
}

void Player::setSprite(Sprite const& p_sprite)
{
    m_sprite = p_sprite;
}

void Player::setPosition(Position const p_pos)
{
    m_position = p_pos;
}

Position &Player::getPosition() const
{
    return m_position;
}

bool Player::useBonus(Bonus p_bonus)
{
    for (Bonus l_bonus : m_bonus)
    {
        if (l_bonus == p_bonus && l_bonus.canUse())
        {
            l_bonus.use();
            return true;
        }
    }
    return false;
}
