#include "ObjectPool.hpp"

namespace mindspy {

namespace util {

template<typename T>
const std::size_t ObjectPool<T>::defaultsize;

template <typename T>
ObjectPool<T>::ObjectPool(std::size_t size)
{
    if(size == 0)
    {
        throw std::invalid_argument("Size must be positive");
    }

    allocate();
}

template <typename T>
std::shared_ptr<T> ObjectPool<T>::acquireObject()
{
    if (pool.empty())
    {
        allocate();
    }

    auto obj = pool.front();
    pool.pop();

    return obj;
}

template <typename T>
void ObjectPool<T>::releaseObject(std::shared_ptr<T> obj)
{
    pool.push(obj);
}

template <typename T>
void ObjectPool<T>::allocate()
{
    for(std::size_t = 0; i < size; ++i)
    {
        pool.push(std::make_shared<T>());
    }

}

} // namespace
} // namespace
