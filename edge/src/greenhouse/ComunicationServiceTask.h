#ifndef __COMUNICATION_SERVICE_TASK__
#define __COMUNICATION_SERVICE_TASK__

#include "List.h"
#include "Task.h"
#include "MsgService.h"
#include "BroadcastReceiver.h"

class ReceiversOnTopic {
private:
  int maxSize;
  String topic;
  List<BroadcastReceiver*>* receivers;

public:
  ReceiversOnTopic(int maxSize, const String& topic) {
    this->maxSize = maxSize;
    this->topic = topic;
    this->receivers = new List<BroadcastReceiver*>(maxSize);
  }

  bool addReceiver(BroadcastReceiver* receiver) {
    if(receivers->size() >= maxSize) {
      return false;
    }
    receivers->add(receiver);
    return true;
  }

  String getTopic() {
    return topic;
  }

  List<BroadcastReceiver*>* getReceivers() {
    return receivers;
  }
};

class ComunicationServiceTask : public Task {
public:
  ComunicationServiceTask(MsgService* msgService);
  void init(unsigned long period);
  void tick();

  void subscribe(const String& topic, BroadcastReceiver* receiver);
  void unsubscribe(const String& topic);

private:
  MsgService* msgService;
  List<ReceiversOnTopic*>* receiversOnTopic;
};

#endif
