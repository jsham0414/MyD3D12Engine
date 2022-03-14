#pragma once
#include "../Object/GameObject.h"

class SYSTEM_DLL ObjectManager {
private:
    static ObjectManager* instance;
public:
    static ObjectManager* GetInstance() {
        if (instance == nullptr)
            instance = new ObjectManager();
        return instance;
    }
private:
    std::vector<GameObject*> m_Objects;

private:
	ObjectManager();
public:
	~ObjectManager();


public:
    VOID Initialize();
    VOID Update();
    VOID Render();
    VOID Release();

public:
    GameObject* AddObject(GameObject* _object);

public:
    const std::vector<GameObject*>* GetObjects() { return &m_Objects; }
};