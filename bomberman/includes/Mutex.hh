#ifndef MUTEX_HH__
# define MUTEX_HH__

class Mutex
{
public:
  Mutex(void);
  ~Mutex(void);

  pthread_mutex_t&	getMutex(void);
  
  void			lock(void);
  void			unlock(void);
  bool			trylock(void);
  
private:
  /*  Mutex&	operator=(const Mutex&); */
  Mutex(const Mutex&);

public:
  pthread_mutex_t		_mutex;
};

#endif
