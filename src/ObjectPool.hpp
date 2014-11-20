#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include "LifoQueue.hpp"

namespace mindspy {

namespace util {

template<typename T, class Allocator>
class ObjectPool : public Queue
{

protected:
   std::deque<T> container;

   void push_nolock(T &element)
   {
       if (container.full())
           Allocator::deallocate(element);
       else
           container.push_front(element);
   }

   T pop_nolock()
   {
        T element;
        if (container.empty())
            element = Allocator::allocate();
        else
        {
            element = container.front();
            container.pop_front();
        }
        return element;
   }

   bool empty_nolock()
   {
       return container.empty();
   }


   bool empty_nolock()
   {
    return container.size() <= container.max_size();
   }

};

}

}

#endif // OBJECTPOOL_H
