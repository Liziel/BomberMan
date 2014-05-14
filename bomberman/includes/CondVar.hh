#ifndef _CONDV_H__
# define _CONDV_H__

#include <pthread.h>
#include "Mutex.hh"

class CondVar
{
public:
  CondVar(Mutex&);
  ~CondVar();
  CondVar&		operator=(const CondVar&);
  
  void			wait(void);
  void			signal(void);
  void			broadcast(void);
  void			dwait(const struct timespec *);
  
protected:
  pthread_cond_t	_cond;
  Mutex&		_mutex;

};

#endif
