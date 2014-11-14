#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

namespace mindspy {

namespace util {

/*!
 * The Queue class is simple thread safe concept.
 */
template <class T>
class Queue
{
public:


    Queue() = default;
    // Disable copy and assignment.
    Queue(const &Queue) = delete;
    Queue& operator=(const Queue&) = delete;

    /*!
     * Remove element from queue.
     */
    void pop();

    /*!
     * Add element to queue.
     */
    void push();

    /*!
     * Checking empty queue.
     * \return bool value according to stage queue.
     */
    bool empty() const;

private:

    std::queue<T> queue;
    std::mutex queueMutex;
    std::condition_variable queueCondicion;
};

} // namespace

} // namespace

#endif // QUEUE_HPP
