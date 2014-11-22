#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

namespace mindspy {

namespace util {

/*!
 * The class is simple object pool.
 * This class allocate and deallocate object.
 */
template<typename T, class Allocator>
class ObjectPool
{

protected:

   std::deque<T> container;

   void push_nolock(T &element)
   {
       if (container.full())
       {
            Allocator::deallocate(element);
       }
       else
       {
           container.push_front(element);
       }
   }

   T pop_nolock()
   {
        T element;
        if (container.empty())
        {
            element = Allocator::allocate();
        }
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


   bool max_size()
   {
    return container.size() <= container.max_size();
   }

};

}

}

#endif // OBJECTPOOL_H
