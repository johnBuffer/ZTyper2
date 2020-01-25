#pragma once

#include "game_object.hpp"
#include "pooled_object.hpp"


template<typename T>
struct PooledGameObject : public GameObject, public PooledObject<T>
{
	PooledGameObject();

	template<typename... Args>
	PooledGameObject(Args&& ...args);
};

template<typename T>
inline PooledGameObject<T>::PooledGameObject()
	: GameObject()
{
}

template<typename T>
template<typename ...Args>
inline PooledGameObject<T>::PooledGameObject(Args&& ...args)
	: GameObject(args...)
{
}
