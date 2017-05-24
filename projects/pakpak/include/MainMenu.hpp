//
// Created by duhieu_b on 23/05/17.
//

#ifndef CPP_INDIE_STUDIO_MAINMENU_HPP_
#define CPP_INDIE_STUDIO_MAINMENU_HPP_

#include "IMenuLayer.hpp"
#include "GUI.hpp"

namespace core
{
    class MainMenu : public IMenuLayer
    {
    public:
        GameState changeScreen() const;

        void draw();

        void entry();

        void exit();

        void destroy();

        void update();

        void build();

    private:
        GUI m_gui;
        //Camera m_camera;
        //Window m_window;
    };
}


#endif //CPP_INDIE_STUDIO_MAINMENU_HPP_
