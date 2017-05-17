 //
// Created by duhieu_b on 05/05/17.
//

#ifndef CPP_INDIE_STUDIO_BONUS_HPP
#define CPP_INDIE_STUDIO_BONUS_HPP


class Bonus
{
public:
    enum Type
    {
        SPEED = 0,
        BANANA,
        ROCKET,
        GOD,
        MAGESPEED,
        GUN,
        OIL
    };
    Bonus() = default;
    Bonus(Bonus const&) = default;
    Bonus(Bonus &&) = delete;
    Bonus &operator=(Bonus &) = delete;
    Bonus &operator=(Bonus &&) = delete;

    Type getType() const;

    void setType(Type m_type);

    void use();
    bool canUse() const;

private:
    Type m_type;
    bool m_using;
};


#endif //CPP_INDIE_STUDIO_BONUS_HPP
