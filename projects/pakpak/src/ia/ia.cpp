//
// Created by duhieu_b on 13/06/17.
//

#include "ia.hpp"

Ia::~Ia()
{

}

Ia::Ia(Ogre::Vector3 &l_posCar) : m_pos(l_posCar), m_curNode(0)
{

}

void Ia::feedNodeRace(std::vector<Ogre::Vector3> &l_nodes)
{
    m_nodes = l_nodes;
}

Ogre::Vector3 &Ia::getPos() const
{
    return m_pos;
}

void Ia::race(Ogre::Vector3 &l_carPos, Ogre::Vector3 &l_carDir, float l_speed)
{
    m_pos = l_carPos;
    distNode();
    l_carDir = m_nodes[m_curNode] - m_pos;
}

void Ia::distNode()
{
    Ogre::Vector3 m_relativeVector = m_nodes[m_curNode] - m_pos;
    if (m_relativeVector.length() < 0.5)
    {
        if (m_curNode == m_nodes.size() - 1)
            m_curNode = 0;
        else
            m_curNode++;
    }
}

Ogre::Vector3 &Ia::getDir() const
{
    return m_newDir;
}
