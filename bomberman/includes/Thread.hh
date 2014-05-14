#ifndef THREAD_H__
# define THREAD_H__

#include <iostream>
#include "Mutex.hh"

enum Status
  {
    WAITING,
    ALIVE,
    DEAD
  };

class Thread
{
  class scopeLock
  {
    enum Estate
      {
	Force,
	Locked
      };
    
  public:
    scopeLock(Mutex&, Estate);
    ~scopeLock();
    bool		islock();
    Mutex&		_mutex;
  };

public:
  ~Thread();
  Status		getStatus(void);
  virtual bool	       	start(void);
  void			join(void **retVal);
  void			run();
  
public:
  Thread(void*(*start_routine)(void *), void *);
  Thread();
  Thread(const Thread &);
  Thread&      operator=(const Thread &);

protected:
  void*			(*_start_routine)(void*);
  void			*_param;
  Status		_status;
  pthread_t		_thr;
  int			id;
};

void			*tramp(void *);

#endif
