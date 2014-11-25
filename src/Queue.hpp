#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <mutex>
#include <condition_variable>
#include <memory>

namespace mindspy {

namespace util {

/*!
 * The Queue class is simple thread safe concept.
 */
template <class T>
class Queue
{
public:
    // Defined default constructor.
    Queue() = default;
    // Disable copy constructor.
    Queue(const Queue&) = delete;
    // Disable assignment constructor.
    Queue& operator=(const Queue&) = delete;

    virtual ~Queue() { }

    /*!
     * \brief Remove element from queue.
     * \return element that has been removed
     */
    std::unique_ptr<T> get()
    {
        // acquire lock
        std::unique_lock<std::mutex> lock(mutex);
        // wait for next element
        while(empty_nolock())
            condition.wait(lock);
        // pop front element
        return pop_nolock();
    }

    /*!
     * \brief Remove element from queue.
     * \param element that has been removed
     */
    void get(std::unique_ptr<T> element)
    {
        element = get();
    }

    /*!
     * \brief Add element to queue.
     * \param element to be added
     */
    void put(std::unique_ptr<T> element)
    {
        // acquire lock
        std::unique_lock<std::mutex> lock(mutex);
        // add element
        push_nolock(element);
        // unlock
        lock.unlock();
        // notify waiting threads
        condition.notify_one();
    }

    bool empty()
    {
        // acquire lock
        std::unique_lock<std::mutex> lock(mutex);
        return empty_nolock();

    }

    bool full()
    {
        // acquire lock
        std::unique_lock<std::mutex> lock(mutex);
        return full_nolock();
    }

protected:
    virtual void push_nolock(std::unique_ptr<T> &element) = 0;
    virtual std::unique_ptr<T> pop_nolock() = 0;
    virtual bool empty_nolock() = 0;
    virtual bool full_nolock() = 0;

private:
    std::mutex mutex;
    std::condition_variable condition;

};

} // namespace

} // namespace

#endif // QUEUE_HPP
