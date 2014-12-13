#ifndef FIFOQUEUE_HPP
#define FIFOQUEUE_HPP

#include "Queue.hpp"
#include <deque>

namespace mindspy {

namespace util {

/*!
 * The Queue class is simple thread safe concept.
 */
template <class T>
class FifoQueue : public Queue<T>
{

protected:
    std::deque<T> container;

    void push_nolock(T &element)
    {
        container.push_back(element);
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

#endif // FIFOQUEUE_HPP
