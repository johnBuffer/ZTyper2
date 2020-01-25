#pragma once

#include <vector>
#include <memory>


template<typename T>
struct PooledObject
{
	template<typename... Args>
	static std::shared_ptr<T> create(Args&&... args);

	static void remove(const T& obj);

	static std::vector<std::shared_ptr<T>> pool;
};

template<typename T>
std::vector<std::shared_ptr<T>> PooledObject<T>::pool;

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
	const uint64_t pool_size = pool.size();
	for (uint64_t i(0U); i < pool_size; ++i) {
		std::shared_ptr<T>& obj = pool[i];
		if (&(*obj) == &obj_to_remove) {
			std::swap(obj, pool.back());
			pool.pop_back();
			break;
		}
	}
}
