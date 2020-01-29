#pragma once

#include "game_object.hpp"
#include "pooled_object.hpp"
#include "game_engine.hpp"
#include "resources_manager.hpp"


template<typename T>
struct PooledGameObject : public GameObject, public PooledObject<T>
{
	PooledGameObject();

	template<typename... Args>
	PooledGameObject(Args&& ...args);

	void kill(T* object);
	void setDead(T* object);
	void checkDead(T* object);

	static void initialize();
	static ResourcesManager resources;
	static uint64_t layer_id;
	static void clean();
};


template<typename T>
ResourcesManager PooledGameObject<T>::resources;

template<typename T>
uint64_t PooledGameObject<T>::layer_id = 0U;


template<typename T>
inline PooledGameObject<T>::PooledGameObject()
	: GameObject()
{
}

template<typename T>
inline void PooledGameObject<T>::setDead(T* object)
{
	dead = true;
}

template<typename T>
inline void PooledGameObject<T>::kill(T* object)
{
	dead = true;
	T::remove(*object);
}

template<typename T>
inline void PooledGameObject<T>::checkDead(T* object)
{
	if (isDone() || dead) {
		kill(object);
		onDone();
	}
}

template<typename T>
inline void PooledGameObject<T>::initialize()
{
	GameEngine::getInstance().registerObjectClass<T>();
	T::init();
}

template<typename T>
inline void PooledGameObject<T>::clean()
{
	resources.clear();
	pool.clear();
}

template<typename T>
template<typename ...Args>
inline PooledGameObject<T>::PooledGameObject(Args&& ...args)
	: GameObject(args...)
{
}
