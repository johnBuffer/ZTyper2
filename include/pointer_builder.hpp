#pragma once

#include <memory>


template<typename T>
struct PointerBuilder
{
	template<typename... Args>
	static std::shared_ptr<T> create(Args&&... args);
};

template<typename T>
template<typename... Args>
inline std::shared_ptr<T> PointerBuilder<T>::create(Args&& ...args)
{
	return std::make_shared<T>(args...);
}
