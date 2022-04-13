#include "SystemDLL.h"
#include "../Object/GameObject.h"

ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::ObjectManager() {
	instance = this;
	Initialize();
}

ObjectManager::~ObjectManager() {
	Release();
}

VOID ObjectManager::Initialize() {

}

VOID ObjectManager::Update() {
	for (std::vector<GameObject*>::iterator iter = m_Objects.begin(); iter != m_Objects.end(); iter++) {
		(*iter)->Update();
	}
}

VOID ObjectManager::Render() {
	for (int i = 0; i < m_Objects.size(); i++) {
		m_Objects[i]->Render(i);
	}
}

VOID ObjectManager::Release() {
	for (std::vector<GameObject*>::iterator iter = m_Objects.begin(); iter != m_Objects.end(); iter++) {
		SAFE_DELETE(*iter);
	}
}

GameObject* ObjectManager::AddObject(GameObject* _object) {
	m_Objects.push_back(_object);
	//_object->Initialize();
	return _object;
}
