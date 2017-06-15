//
// Created by duhieu_b on 05/05/17.
//

#include "Bonus.hpp"

void Bonus::use()
{
    m_using = false;
}

bool Bonus::canUse() const
{
    return m_using;
}

Bonus::Type Bonus::getType() const
{
    return m_type;
}

void Bonus::setType(Bonus::Type p_type)
{
    m_type = p_type;
}
