#ifndef H38247538_297F_4A80_94D3_8A2897883456
#define H38247538_297F_4A80_94D3_8A2897883456

#include "base/apr_ring.h"

template <typename T> struct List;

template <typename T>
struct ListElem
{
   ListElem()
   {
      link.prev = 0;
      link.next = 0;
   }

   void remove()
   {
       APR_RING_REMOVE(this, link);
   }

   T* getNext()
   {
       return link.next;
   }

   const T* getNext() const
   {
       return link.next;
   }

   T* getPrev()
   {
       return link.prev;
   }

   const T* getPrev() const
   {
       return link.prev;
   }

   friend struct List<T>;

   APR_RING_ENTRY(T) link; // __cacheline_aligned;
};

#endif

