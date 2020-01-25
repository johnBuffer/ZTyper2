#pragma once

#include <list>
#include <memory>


template<typename T>
struct PooledObject
{
	template<typename... Args>
	static std::shared_ptr<T> create(Args&&... args);

	static void remove(const T& obj);

	static std::list<std::shared_ptr<T>> pool;
};

template<typename T>
std::list<std::shared_ptr<T>> PooledObject<T>::pool;

template<typename T>
template<typename ...Args>
inline std::shared_ptr<T> PooledObject<T>::create(Args&& ...args)
{
	std::shared_ptr<T> new_obj = std::make_shared<T>(args...);
	pool.push_back(new_obj);
	return new_obj;
}

template<typename T>
inline void PooledObject<T>::remove(const T& obj_to_remove)
{
	pool.remove_if([&](std::shared_ptr<T> obj) {return &(*obj) == &obj_to_remove; });
}
