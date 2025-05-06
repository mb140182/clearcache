/* =====================================================================================
 *       Filename:  my_threads.h
 *    Description:  my_threads header
 *        Version:  1.2
 *        Created:  22.09.2016 3:00:30
 *       Revision:  2019.08.31  /  00:26:56
 *       Compiler:  gcc 9.1.0
 *         Author:  mb14 (mb14), mb14@yandex.ru
 *   Organization:  mb14 home
 * =====================================================================================
 */

#ifndef MY_THREADS
#define MY_THREADS

#ifdef __WIN32__
#include <winsock2.h>
#include <windows.h>
#endif

//#istream>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <vector>
#include <time.h>
//#include <dirent.h>

#include <erlog.h>
//#include <sqlite3.h>
#include <semaphorem.h>
#include <time.h>

class my_threads
{
    private:

    protected:
        //threads
        semaphorem sem_ThreadFirst, sem_ThreadSecond, sem_Thread_Timer;// semafori upravlayshie potokami
#if (__cplusplus >= 201103L)//for gcc>c++11
        std::thread pthread_first, pthread_second, pthread_Timer; // ukazateli na potoki
#else//for boost
        boost::thread pthread_first, pthread_second, pthread_Timer; // ukazateli na potoki
#endif
        bool bLoopThreadFirst, bLoopThreadSecond, bLoopThreadTimer;
        //boost::try_mutex mutex_WA0, mutex_flAttak, mutex_AddWA0, mutex_DeleteWA0, mutex_Atmosfera, mutex_Move; // mutexi
        virtual void ThreadFirst(); // funkcia prevogo potoka
        virtual void ThreadSecond(); // funkcia vtorogo potoka
        virtual void ThreadTimer(); // funkcia timera
        //threads

        my_threads(const my_threads &arhs); 
        virtual my_threads& operator=(const my_threads &arhs);

    public:
        virtual ~my_threads();
        my_threads();
        virtual void start();
};

#endif

