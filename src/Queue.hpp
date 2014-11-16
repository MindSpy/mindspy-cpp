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
template <typename T>
class Queue
{
public:

    // Defined default constructor.
    Queue() = default;
    // Disable copy constructor.
    Queue(const Queue&) = delete;
    // Disable assignment constructor.
    Queue& operator=(const Queue&) = delete;

    /*!
     * Remove element from queue.
     */
    T pop()
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        while(queue.empty())
        {
            condition.wait(lock);
        }

        auto element = queue.front();

        queue.pop();

        return element;
    }

    /*!
     * Remove element from queue.
     */
    void pop(T& element)
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        while(queue.empty())
        {
            condition.wait(lock);
        }

        element = queue.front();

        queue.pop();
    }

    /*!
     * Add element to queue.
     */
    void push(T& element)
    {
        std::unique_lock<std::mutex> lock(queueMutex);

        queue.push(element);

        lock.unlock();

        condition.notify_one();
    }

    //void push(T&& element)
    //{
    //    std::unique_lock<std::mutex> lock(queueMutex);
    //
    //    queue.push(std::move(element));
    //
    //    lock.unlock();
    //
    //     condicion.notify_one();
    //}

private:

    std::queue<T> queue;
    std::mutex queueMutex;
    std::condition_variable condition;
};

} // namespace

} // namespace

#endif // QUEUE_HPP
