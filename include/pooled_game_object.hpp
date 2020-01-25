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

	static void initialize();
	static ResourcesManager resources;
};


template<typename T>
ResourcesManager PooledGameObject<T>::resources;


template<typename T>
inline PooledGameObject<T>::PooledGameObject()
	: GameObject()
{
}

template<typename T>
inline void PooledGameObject<T>::initialize()
{
	T::init();
}

template<typename T>
template<typename ...Args>
inline PooledGameObject<T>::PooledGameObject(Args&& ...args)
	: GameObject(args...)
{
}
