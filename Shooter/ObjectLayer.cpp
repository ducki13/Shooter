#include "ObjectLayer.h"

void ObjectLayer::update()
{
    for (GameObject* pGameObject : m_gameObjects)
    {
        pGameObject->update();
    }
    
    for (int i = 1; i < m_gameObjects.size(); ++i)
    {
		if (checkCollision(dynamic_cast<SDLGameObject*>(m_gameObjects[0]),
			dynamic_cast<SDLGameObject*>(m_gameObjects[i])))
		{
			Game::Instance()->getStateMachine()->changeState(new GameOverState());
		}
    }
}

void ObjectLayer::render()
{
    for (GameObject* pGameObject : m_gameObjects)
    {
        pGameObject->draw();
    }
}

bool ObjectLayer::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = p1->getPosition().getX();
    rightA = leftA + p1->getWidth();
    topA = p1->getPosition().getY();
    bottomA = topA + p1->getHeight();

    leftB = p2->getPosition().getX();
    rightB = leftB + p2->getWidth();
    topB = p2->getPosition().getY();
    bottomB = topB + p2->getHeight();

    if (bottomA < topB) return false;
    if (bottomB < topA) return false;
    if (rightA < leftB) return false;
    if (leftA > rightB) return false;

    return true;
}
