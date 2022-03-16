#include "Scheduler.h"

Scheduler::Scheduler(int nMaxTasks){
  taskList = new List<Task*>(nMaxTasks);
  tasksToBeAdded = new List<Task*>(nMaxTasks);
  tasksToBeRemoved = new List<Task*>(nMaxTasks);
}

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timer.setupPeriod(basePeriod);  
}

bool Scheduler::addTask(Task* task){
  return tasksToBeAdded->add(task);
}

bool Scheduler::removeTask(Task* task){
  return tasksToBeRemoved->add(task);
}
  
void Scheduler::schedule(){
  if (tasksToBeRemoved->size() > 0){
    for (int i=0; i < tasksToBeRemoved->size(); i++){
      Task* task = tasksToBeRemoved->get(i);
      taskList->remove(task);    
    }
    tasksToBeRemoved->empty();
  }
  if (tasksToBeAdded->size() > 0){
    for (int i=0; i < tasksToBeAdded->size(); i++){
      taskList->add(tasksToBeAdded->get(i));    
    }
    tasksToBeAdded->empty();
  }

  timer.waitForNextTick();
  
  for (int i = 0; i < taskList->size(); i++){
    Task* task = taskList->get(i);
    if (task->updateAndCheckTime(basePeriod)){
      task->tick();
    }
  }
}

