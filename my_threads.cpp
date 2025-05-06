/* =====================================================================================
 *       Filename:  my_threads.cpp
 *    Description:  my_threads body
 *        Version:  1.03
 *        Created:  22.09.2016 3:02:10
 *       Revision:  2019.08.31  /  00:29:03
 *       Compiler:  gcc 9.1.0
 *         Author:  mb14 (mb14), mb14@yandex.ru
 *   Organization:  mb14 home
 * =====================================================================================
 */

#include <my_threads.h>

void my_threads::ThreadFirst() // funkcia prevogo potoka
{
    while(bLoopThreadFirst)
    {
        sem_ThreadFirst.wait(); // gdem rasreshenie na ispolnenie
        dmess2("pervii otstrelalsa", 0, 1);
    }
    dmess2("Pervii Stop", 0, 1);
}

void my_threads::ThreadSecond() // funkcia vtorogo potoka
{
    while(bLoopThreadSecond)
    {
        sem_ThreadSecond.wait();// gdem rasreshenie na ispolnenie
        dmess2("vtoroi otstrelalsa", 0, 1);
    }
}

void my_threads::ThreadTimer() // funkcia potoka taimera
{
    while(bLoopThreadSecond)
    {
#if (__cplusplus >= 201103L)//for gcc>c++11
        std::this_thread::sleep_for((std::chrono::milliseconds(100)));
#else//for boost
        //boost::this_thread::sleep(boost::posix_time::seconds(5));
        //boost::this_thread::sleep(boost::posix_time::seconds(1));
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
#endif
        dmess2("timer sret", 0, 1);
        sem_ThreadFirst.post();
        sem_ThreadSecond.post();
        dmess2("ThreadTimer Stop", 0, 1);
    }
}

void my_threads::start()
{
    printf("press enter\n");
    char c;
    do{
        c=getchar();
    }while(c!='\n');
};

my_threads::my_threads(const my_threads &arhs){*this=arhs;};
my_threads::my_threads()
{
    //thread1=boost::thread(boost::bind(&world::ThreadWorld1, this)); // pricruchivaem funkciy classa kak funkciy potoka, this ukazatel na class k kotoromu prinadelgit finkcia
    bLoopThreadFirst=bLoopThreadSecond=bLoopThreadTimer=1;

    /*pthread_first=boost::thread(ThreadFirst);
    pthread_second=boost::thread(ThreadSecond);
    pthread_Timer=boost::thread(ThreadTimer);*/

#if (__cplusplus >= 201103L)//for gcc>c++11
    pthread_first=std::thread(std::bind(&my_threads::ThreadFirst, this));
    pthread_second=std::thread(std::bind(&my_threads::ThreadSecond, this));
    pthread_Timer=std::thread(std::bind(&my_threads::ThreadTimer, this));
#else//for boost
    pthread_first=boost::thread(boost::bind(&my_threads::ThreadFirst, this));
    pthread_second=boost::thread(boost::bind(&my_threads::ThreadSecond, this));
    pthread_Timer=boost::thread(boost::bind(&my_threads::ThreadTimer, this));
#endif

    sem_ThreadFirst.post();
    sem_ThreadSecond.post();
};
my_threads::~my_threads()
{
    //ios.stop();
    //boost::thread.interupt_all(); // signal vsem potokam zavershit raboty
    //boost::thread.join_all();  // funkcia gdet zavershenia raboti vseh potokov
    bLoopThreadFirst=bLoopThreadSecond=bLoopThreadTimer=0;
      sem_ThreadFirst.post();
      sem_ThreadSecond.post();
    //pthread_Timer.interrupt(); // signal potoku zavershit raboty
    pthread_Timer.join();  // funkcia gdet zavershenia raboti potoka
    //pthread_first.interrupt(); // signal potoku zavershit raboty
    pthread_first.join();  // funkcia gdet zavershenia raboti potoka
    //pthread_second.interrupt(); // signal potoku zavershit raboty
    pthread_second.join();  // funkcia gdet zavershenia raboti potoka
};
my_threads& my_threads::operator=(const my_threads &arhs)
{
		dmess2(" Etot konstruktor ne dolgen ispolzovatsa ", 1, 1);

	if(&arhs==this)
		return *this;


	return *this;
};

