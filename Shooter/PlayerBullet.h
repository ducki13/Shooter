#ifndef __PlayerBullet__
#define __PlayerBullet__

#include <iostream>
#include "SDLGameObject.h"

class PlayerBullet : public SDLGameObject
{
public:
    PlayerBullet() : SDLGameObject() {}

    std::string getType() { return "PlayerBullet"; }

    void load(LoaderParams* pParams, Vector2D heading)
    {
        SDLGameObject::load(pParams);
        m_heading = heading;
    }

    void draw()
    {
        SDLGameObject::draw();
    }

    void update()
    {
        m_velocity.setX(m_heading.getX());
        m_velocity.setY(m_heading.getY());

        SDLGameObject::update();
    }

private:
    Vector2D m_heading;
};

#endif /* __PlayerBullet__ */
