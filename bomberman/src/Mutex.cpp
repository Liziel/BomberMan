#include <pthread.h>
#include "Mutex.hh"

Mutex::~Mutex()
{
  pthread_mutex_destroy(&(this->_mutex));
}

Mutex::Mutex(const Mutex &incase)
{
  this->_mutex = incase._mutex;
}

Mutex::Mutex(): _mutex()
{
  pthread_mutex_init(&(this->_mutex), NULL);
}

void	Mutex::lock()
{
  pthread_mutex_lock(&(this->_mutex));
}

void	Mutex::unlock()
{
  pthread_mutex_unlock(&(this->_mutex));
}

bool	Mutex::trylock()
{
  /*choper le EBUSY */
  return (pthread_mutex_trylock(&(this->_mutex)));
}

/*Mutex&	operator=(const Mutex&)
{
  return (*this);
}*/

pthread_mutex_t&	Mutex::getMutex()
{
  return (this->_mutex);
}
