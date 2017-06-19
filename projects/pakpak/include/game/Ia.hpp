//
// Created by duhieu_b on 13/06/17.
//

#ifndef CPP_INDIE_STUDIO_IA_HPP
#define CPP_INDIE_STUDIO_IA_HPP

#include "pakpak_stdafx.hpp"

namespace game
{
    class Ia
    {
    public:
        explicit Ia(game::ACar &, std::vector<Ogre::Vector3> const&);

        Ia(Ia const &) = delete;

        Ia(Ia &&) = delete;

        Ia &operator=(Ia &) = delete;


        virtual ~Ia();

        void race();

        void distNode();

    private:
        std::int32_t m_curNode;
        std::vector<Ogre::Vector3> const& m_nodes;
        game::ACar &m_car;
        std::int32_t m_dir;
    };
}
#endif // CPP_INDIE_STUDIO_IA_HPP
