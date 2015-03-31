#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "StateManager.h"
#include "Material.h"
#include "Mesh.h"
#include "glm/glm.hpp"

namespace RE
{

class GameObject
{

friend class Scene;

private:

    int id;

public:

    GameObject();
    virtual ~GameObject();

    int GetId() const;
};

}

#endif // GAMEOBJECT_H
