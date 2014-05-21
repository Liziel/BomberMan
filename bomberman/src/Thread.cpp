#include "Thread.hh"

Thread::scopeLock::scopeLock(Mutex& incase, Estate state)
  :_mutex(incase)
{
  this->_mutex.lock();
}

Thread::scopeLock::~scopeLock()
{
  this->_mutex.unlock();
}

bool	Thread::scopeLock::islock()
{
  return (this->_mutex.trylock());
}

Thread::~Thread()
{
}

Thread::Thread()
{
}

IThread::Status	Thread::getStatus()
{
  return (this->_status);
}

void	Thread::run()
{
  this->_start_routine(this->_param);
}

Thread::Thread(void*(*start_routine)(void*), void* inW)
:_start_routine(start_routine), _param(inW), _status(WAITING)
{

}

void	Thread::join(void **retVal)
{
  int	i;

  i = pthread_join(this->_thr, retVal);
  if (getStatus() != IThread::ALIVE)
    return; //(static_cast<U>(*retVal));
  if (i != 0)
    throw 4;
  _status = IThread::DEAD;
}

bool	Thread::start()
{
  int	err;

  err = pthread_create(&this->_thr, NULL, _start_routine, this);
  if (err == 0)
    {
      this->_status = ALIVE;
      return (true);
    }
  else
    return (false);
}
