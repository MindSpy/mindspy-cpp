#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <mutex>

namespace mindspy {

namespace util {

/*!
 * The Queue class is simple thread safe concept.
 */
class Queue
{
public:

    /*!
     * Constructor.
     */
    Queue();

    /*!
     * Remove element from queue.
     */
    void pop();

    /*!
     * Add element to queue.
     */
    void push();

private:

    std::mutex queueMutex;
};

} // namespace

} // namespace

#endif // QUEUE_HPP
