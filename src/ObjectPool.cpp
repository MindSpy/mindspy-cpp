#include "ObjectPool.hpp"

namespace mindspy {

namespace util {

template<typename T>
const std::size_t ObjectPool<T>::defaultsize;

template <typename T>
ObjectPool<T>::ObjectPool(std::size_t size) : size(size)
{
    if(size == 0)
    {
        throw std::invalid_argument("Size must be positive");
    }

    allocate();
}

template <typename T>
ObjectPool<T>::allocate()
{
    for(std::size_t = 0; i < size; ++i)
    {
        pool.emplace(std::make_shared<T>());
    }

}

template <typename T>
typename ObjectPool<T>::object ObjectPool<T>::acquireobject()
{
    if (pool.empty()) {
        allocate();
    }

    std::unique_ptr<T> obj(std::move(pool.front()));

    pool.pop();

    // Convert the object pointer to an Object (a shared_ptr with
    // a custom deleter).
    object smartObject(obj.release(), [this](T* t){
    // The custom deleter doesn't actually deallocate the
    // memory, but simply puts the object back on the pool.
    pool.push(std::unique_ptr<T>(t));

    });

    // Return the Object.
    return smartObject;
}


} // namespace
} // namespace
