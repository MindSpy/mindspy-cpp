#ifndef LIFOQUEUE_HPP
#define LIFOQUEUE_HPP

#include "Queue.hpp"
#include <deque>

namespace mindspy {

namespace util {

/*!
 * The Queue class is simple thread safe concept.
 */
template <class T, class Container = std::deque<T>>
class FifoQueue : public Queue<T>
{

protected:
    Container container;

    void push_nolock(T &element)
    {
        container.push_front(element);
    }

    T pop_nolock()
    {
        auto element = container.front();
        container.pop_front();
        return element;
    }

    bool empty_nolock()
    {
        return container.empty();
    }
};

} // namespace

} // namespace

#endif // LIFOQUEUE_HPP
