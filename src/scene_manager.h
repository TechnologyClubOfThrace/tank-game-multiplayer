#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <string>

class SceneManager
{
public:
    SceneManager();
    void LoadFirstScene(std::string tmxFilePath, std::string sceneLayerName);
};

#endif // SCENE_MANAGER_H
