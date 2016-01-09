#ifndef __StateParser__
#define __StateParser__

#include <iostream>
#include <vector>
#include "tinyxml.h"

#include "GameObject.h"

class StateParser
{
public:
    bool parseState(const char* statFile, std::string stateID,
        std::vector<GameObject*>* pObjects,
        std::vector<std::string>* pTextureIDs);
private:
    void parseObjects(TiXmlElement* pStateRoot,
        std::vector<GameObject*>* pObjects);
    void parseTextures(TiXmlElement* pStateRoot,
        std::vector<std::string>* pTextureIDs);
};

#endif /* __StateParser__ */
