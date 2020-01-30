#pragma once

#include <vector>
#include <memory>


template<typename T>
struct PooledObject
{
	using ptr = std::unique_ptr<T>;
	template<typename... Args>
	static T& create(Args&&... args);

	static void remove(const T& obj);
	
	static std::vector<ptr> pool;
};

template<typename T>
std::vector<std::unique_ptr<T>> PooledObject<T>::pool;

template<typename T>
template<typename ...Args>
inline T& PooledObject<T>::create(Args&& ...args)
{
	ptr new_obj = std::make_unique<T>(args...);
	pool.push_back(std::move(new_obj));
	return *new_obj;
}

template<typename T>
inline void PooledObject<T>::remove(const T& obj_to_remove)
{
	const uint64_t pool_size = pool.size();
	for (uint64_t i(0U); i < pool_size; ++i) {
		ptr& obj = pool[i];
		if (&(*obj) == &obj_to_remove) {
			std::swap(obj, pool.back());
			pool.pop_back();
			break;
		}
	}
}
