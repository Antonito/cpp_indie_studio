//
// Created by duhieu_b on 23/05/17.
//

#include "GUI.hpp"

void core::GUI::init(std::string const &p_path)
{
    m_renderer = &CEGUI::OgreRenderer::bootstrapSystem();

    CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
    rp->setResourceGroupDirectory("imagesets", p_path + "/imagesets/");
    rp->setResourceGroupDirectory("schemes", p_path + "/schemes/");
    rp->setResourceGroupDirectory("fonts", p_path + "/fonts/");
    rp->setResourceGroupDirectory("layouts", p_path + "/layouts/");
    rp->setResourceGroupDirectory("looknfeels", p_path + "/looknfeel/");
    rp->setResourceGroupDirectory("lua_scripts", p_path + "/lua_scripts/");

    CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
    CEGUI::Font::setDefaultResourceGroup("Fonts");
    CEGUI::Scheme::setDefaultResourceGroup("Schemes");
    CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
    CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
    CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
    CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");
    m_context = CEGUI::System::getSingleton().getDefaultGUIContext();
    m_root = CEGUI::WindowManage::getSingleton().createWindow("DefaultWindow", "root");
    m_context->setRootWindow();
}

void core::GUI::destroy()
{
    CEGUI::System::getSingleton().destroyGUIContext(*m_context);
    CEGUI::WindowManager::getSingleton().destroyWindow(m_root);
}

void core::GUI::setFont(std::string const &p_font)
{
    CEGUI::FontManager::getSingleton().createFromFile(p_font + ".font");
    m_context.setDefaultFront(p_font);
}

CEGUI::Window *core::GUI::createButton(CEGUI::Window *p_win,
                                            std::string const &p_type,
                                            glm::vec4 const &p_dim1,
                                            glm::vec4 const &p_dim2,
                                            std::string const &p_name = "")
{
    CEGUI::Window* p_newWin = CEGUI::WindowManager::getSingleton().createWindow(p_type, p_name);
    p_win->addChild(p_newWin);
    setPos(p_newWin, p_dim1, p_dim2);
    return p_newWin;
}

CEGUI::Window *core::GUI::createButton(std::string const &p_type,
                                            glm::vec4 const &p_dim1,
                                            glm::vec4 const &p_dim2,
                                            std::string const &p_name = "")
{
    CEGUI::Window* p_newWin = CEGUI::WindowManager::getSingleton().createWindow(p_type, p_name);
    m_root->addChild(p_newWin);
    setPos(p_newWin, p_dim1, p_dim2);
    return p_newWin;
}

void core::GUI::setPos(CEGUI::Window *p_win, glm::vec4 const &p_dim1, glm::vec4 const &p_dim2)
{
    p_win->setPosition(CEGUI::UVector2(CEGUI::UDim(p_dim1.x, p_dim2.x),
                                        CEGUI::UDim(p_dim1.y, p_dim2.y)));
    p_win->setSize(CEGUI::USize(CEGUI::UDim(p_dim1.z, p_dim2.z),
                                CEGUI::UDIM(p_dim1.w, p_dim2.w)));

}



CEGUI::OgreRenderer *core::GUI::getRender() const
{
    return m_renderer;
}

CEGUI::GUIContext *core::GUI::getContext() const
{
    return m_context;
}

core::GUI::~GUI()
{
    destroy();
}

void core::GUI::draw()
{
    m_renderer->beginRendering();
    m_context->draw();
    m_renderer->endRedering();
}

core::GUI::GUI() : m_renderer(nullptr), m_root(nullptr), m_context(nullptr)
{
}

void core::GUI::loadSheme(std::string const &p_shem)
{
    CEGUI::SchemeManager::getSingleton().createFromFile(p_shem);
}
