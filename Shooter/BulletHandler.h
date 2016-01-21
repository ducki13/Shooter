#ifndef __BulletHandler__
#define __BulletHandler__

#include <string>
#include <vector>

#include "Vector2D.h"
#include "PlayerBullet.h"

class BulletHandler
{
public:
    static BulletHandler* Instance()
    {
        if (s_pInstance == NULL)
        {
            s_pInstance = new BulletHandler();
            return s_pInstance;
        }
        return s_pInstance;
    }

    void addPlayerBullet(int x, int y, int width, int height,
        std::string textureID, int numFrames, Vector2D heading);

    void updateBullets();
    void drawBullets();

private:
    BulletHandler() {}
    ~BulletHandler() {}

    static BulletHandler* s_pInstance;

    std::vector<PlayerBullet*> m_playerBullets;
};

#endif /* __BulletHandler__ */
