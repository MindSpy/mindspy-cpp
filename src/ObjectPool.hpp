#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <cstddef>
#include <queue>
#include <memory>
#include <exception>

namespace mindspy {

namespace util {

/*!
 * The class is simple object pool.
 * This class allocate and deallocate object.
 */
template<typename T>
class ObjectPool
{
public:

    /*!
     * \brief Constructor. Create object pool with size object.
     * \param size object pool.
     */
    ObjectPool(std::size_t size);
    // Disable copy and assignment constructor.
    ObjectPool(const ObjectPool<T>& source) = delete;
    ObjectPool<T>& operator = (const ObjectPool<T>& source) = delete;

    /*!
     * Reserves an object for use. Clients must not free the object!
     */
    std::shared_ptr<T> get();

    /*!
     * Returns the object to the pool. Clients must not use the object after
     * it has been returned to the pool.
     */
    void put(std::shared_ptr<T> obj);


protected:

    /*!
     * \brief stores the objects.
     */
    std::deque<std::shared_ptr<T>> pool;

    /*!
     * \brief Local size object;
     */
    std::size_t size;

    /*!
     * \brief Allocate size new object and adds pool.
     */
    void allocate();

    /*!
     * \brief Return size object pool;
     */
    std::size_t sizepool() { return pool.size(); }
};

template <typename T>
ObjectPool<T>::ObjectPool(std::size_t size)
{
    if(size == 0)
    {
        throw std::invalid_argument("Size must be positive");
    }

    this->size = size;

    allocate();
}

template <typename T>
std::shared_ptr<T> ObjectPool<T>::get()
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
void ObjectPool<T>::put(std::shared_ptr<T> obj)
{
    pool.push(obj);
}

template <typename T>
void ObjectPool<T>::allocate()
{
    for(std::size_t i = 0; i < size; ++i)
    {
        pool.push(std::make_shared<T>());
    }

}

} // namespace

} // namespace

#endif // OBJECTPOOL_H
