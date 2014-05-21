#include "CondVar.hh"

CondVar::CondVar(Mutex &mutmut): _cond(), _mutex(mutmut)
{
  pthread_cond_init(&(this->_cond), NULL);
}

CondVar::~CondVar()
{
  pthread_cond_destroy(&(this->_cond));
}

void		CondVar::wait()
{
  pthread_cond_wait(&(this->_cond), &(this->_mutex.getMutex()));
}

void		CondVar::signal()
{
  pthread_cond_signal(&(this->_cond));
}
    
void		CondVar::broadcast()
{
  pthread_cond_broadcast(&(this->_cond));
}

void		CondVar::dwait(const struct timespec *dtime)
{
  pthread_cond_timedwait(&(this->_cond), &(this->_mutex._mutex), dtime);
}

CondVar&	CondVar::operator=(const CondVar &incase)
{
  return (*this);
}
