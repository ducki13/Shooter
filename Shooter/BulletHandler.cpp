#include "BulletHandler.h"

BulletHandler* BulletHandler::s_pInstance = NULL;

void BulletHandler::addPlayerBullet(int x, int y, int width, int height,
    std::string textureID, int numFrames, Vector2D heading)
{
    PlayerBullet* pPlayerBullet = new PlayerBullet();
    pPlayerBullet->load(new LoaderParams(x, y, width, height, textureID, numFrames),
        heading);
    m_playerBullets.push_back(pPlayerBullet);
}

void BulletHandler::updateBullets()
{
    for (PlayerBullet* pPlayerBullet : m_playerBullets)
    {
        pPlayerBullet->update();
    }
}

void BulletHandler::drawBullets()
{
    for (PlayerBullet* pPlayerBullet : m_playerBullets)
    {
        pPlayerBullet->draw();
    }
}