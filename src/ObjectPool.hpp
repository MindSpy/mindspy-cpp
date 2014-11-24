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
    ObjectPool(std::size_t size = defaultsize);
    // Disable copy and assignment constructor.
    ObjectPool(const ObjectPool<T>& source) = delete;
    ObjectPool<T>& operator = (const ObjectPool<T>& source) = delete;

    /*!
     * Reserves an object for use. Clients must not free the object!
     */
    std::shared_ptr<T> acquireObject();

    /*!
     * Returns the object to the pool. Clients must not use the object after
     * it has been returned to the pool.
     */
    void releaseObject(std::shared_ptr<T> obj);


protected:

    /*!
     * \brief stores the objects.
     */
    std::queue<std::shared_ptr<T>> pool;

    /*!
     * \brief Default size object pool.
     */
    static const std::size_t defaultsize = 10;

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

} // namespace

} // namespace

#endif // OBJECTPOOL_H
