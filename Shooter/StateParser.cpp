#include "StateParser.h"

#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"

bool StateParser::parseState(const char* statFile, std::string stateID,
    std::vector<GameObject*>* pObjects,
    std::vector<std::string>* pTextureIDs)
{
    // Create the XML document
    TiXmlDocument xmlDoc;

    // Load the states file
    if (!xmlDoc.LoadFile(statFile))
    {
        std::cout << xmlDoc.ErrorDesc() << std::endl;
        return false;
    }

    // Get the root element
    TiXmlElement* pRoot = xmlDoc.RootElement();

    // Pre-declare the states root node
    TiXmlElement* pStateRoot = NULL;

    // Get this states root node and assign it to pStateRoot
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        if (e->Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    // Pre-declare the texture root
    TiXmlElement* pTextureRoot = NULL;

    // Get the root of the texture elements
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }

    // Now parse the textures
    parseTextures(pTextureRoot, pTextureIDs);

    // Pre-declare the object root node
    TiXmlElement* pObjectRoot = NULL;

    // Get the root node and assign it to pObjectRoot
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("OBJECTS"))
        {
            pObjectRoot = e;
        }
    }

    // Now parse the objects
    parseObjects(pObjectRoot, pObjects);

    return true;
}

void StateParser::parseObjects(TiXmlElement* pStateRoot,
    std::vector<GameObject*>* pObjects)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        int x, y, width, height, numFrames, callbackID, animSpeed;
        std::string textureID;

        e->Attribute("x", &x);
        e->Attribute("y", &y);
        e->Attribute("width", &width);
        e->Attribute("height", &height);
        e->Attribute("numFrames", &numFrames);
        e->Attribute("callbackID", &callbackID);
        e->Attribute("animSpeed", &animSpeed);

        textureID = e->Attribute("textureID");

        GameObject* pGameObject =
            GameObjectFactory::Instance()->create(e->Attribute("type"));
        pGameObject->load(new LoaderParams(
            x, y, width, height, textureID, /*numFrames,*/ callbackID, animSpeed));
        pObjects->push_back(pGameObject);
    }
}

void StateParser::parseTextures(TiXmlElement* pStateRoot,
    std::vector<std::string>* pTextureIDs)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL;
        e = e->NextSiblingElement())
    {
        std::string fileNameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");

        pTextureIDs->push_back(idAttribute);

        TextureManager::Instance()->load(
            fileNameAttribute, idAttribute,
            Game::Instance()->getRenderer());
    }
}
