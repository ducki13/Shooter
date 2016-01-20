#include "ObjectLayer.h"

void ObjectLayer::update()
{
    for (GameObject* pGameObject : m_gameObjects)
    {
        pGameObject->update();
    }
}

void ObjectLayer::render()
{
    for (GameObject* pGameObject : m_gameObjects)
    {
        pGameObject->draw();
    }
}
