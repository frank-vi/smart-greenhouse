#ifndef __SCHEDULER__
#define __SCHEDULER__

#include "Timer.h"
#include "Task.h"
#include "List.h"

class Scheduler {

public:
  Scheduler(int nMaxTasks);
  void init(int basePeriod);  
  virtual bool addTask(Task* task); 
  virtual bool removeTask(Task* task); 
  virtual void schedule();

private:  
  int basePeriod;
  List<Task*>* taskList;
  List<Task*>* tasksToBeAdded;
  List<Task*>* tasksToBeRemoved;
  Timer timer;
};

#endif

