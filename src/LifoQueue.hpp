#ifndef LIFOQUEUE_HPP
#define LIFOQUEUE_HPP

#include "Queue.hpp"
#include <deque>

namespace mindspy {

namespace util {

/*!
 * The Queue class is simple thread safe concept.
 */
template <class T>
class LifoQueue : public Queue<T>
{

protected:
    std::deque<T> container;

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

    bool full_nolock()
    {
        return container.size() <= container.max_size();
    }
};

} // namespace

} // namespace

#endif // LIFOQUEUE_HPP
