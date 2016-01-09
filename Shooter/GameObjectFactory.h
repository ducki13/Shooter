#ifndef __GameObjectFactory__
#define __GameObjectFactory__

#include <iostream>
#include <string>
#include <map>
#include "GameObject.h"

class BaseCreator
{
public:
    virtual GameObject* createGameObject() const = 0;
    virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:
    bool registerType(std::string typeID, BaseCreator* pCreator);
    GameObject* create(std::string typeID);
private:
    std::map<std::string, BaseCreator*> m_creators;
};

#endif /* __GameObjectFactory__ */
