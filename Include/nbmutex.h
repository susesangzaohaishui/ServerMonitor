#ifndef __NB_MUTEX_HPP_INCLUDED__
#define __NB_MUTEX_HPP_INCLUDED__

#include "windowshelp.hpp"
namespace dahlia
{
    class nb_mutex_t
    {
    public:
        inline nb_mutex_t ()
        {
            InitializeCriticalSection (&cs);
        }

        inline ~nb_mutex_t ()
        {
            DeleteCriticalSection (&cs);
        }

        inline void lock ()
        {
            EnterCriticalSection (&cs);
        }

        inline void unlock ()
        {
            LeaveCriticalSection (&cs);
        }

    private:

        CRITICAL_SECTION cs;

        nb_mutex_t (const nb_mutex_t&);
        void operator = (const nb_mutex_t&);
    };

    class nb_locker_t
    {
    public:
        nb_locker_t( nb_mutex_t* lk):
          mLock(NULL)
          {
              mLock = lk;
              mLock->lock();
          }
          ~nb_locker_t()
          {
              if (mLock)
              {
                  mLock->unlock();
              }
          }
    private:
        nb_mutex_t* mLock;
    };
}
#endif