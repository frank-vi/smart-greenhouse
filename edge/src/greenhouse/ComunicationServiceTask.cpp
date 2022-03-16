#include "ComunicationServiceTask.h"

#define MAX_SIZE 10

ComunicationServiceTask::ComunicationServiceTask(MsgService* msgService) {
  this->msgService = msgService;
  this->receiversOnTopic = new List<ReceiversOnTopic*>(MAX_SIZE);
}

void ComunicationServiceTask::init(unsigned long period) {
  Task::init(period);
}

void ComunicationServiceTask::subscribe(const String& topic, BroadcastReceiver* receiver) {
  bool find = false;
  for(int i=0; i < receiversOnTopic->size(); i++) {
    if(receiversOnTopic->get(i)->getTopic().equals(topic)) {
      receiversOnTopic->get(i)->addReceiver(receiver);
      find = true;
      break;
    }
  }
  if(!find) {
    ReceiversOnTopic* r = new ReceiversOnTopic(MAX_SIZE, topic);
    r->addReceiver(receiver);
    receiversOnTopic->add(r);
  }
}

void ComunicationServiceTask::unsubscribe(const String& topic) {
  for(int i=0; i < receiversOnTopic->size(); i++) {
    if(receiversOnTopic->get(i)->getTopic().equals(topic)) {
      receiversOnTopic->remove(receiversOnTopic->get(i));
      break;
    }
  }
}

void ComunicationServiceTask::tick() {
  if(msgService->isMsgAvailable()) {
    Msg* msg = msgService->receiveMsg();

    for(int i=0; i < receiversOnTopic->size(); i++) {
      if(receiversOnTopic->get(i)->getTopic().equals(msg->getAction())) {
        List<BroadcastReceiver*>* receivers = receiversOnTopic->get(i)->getReceivers();
        for(int j=0; j < receivers->size(); j++) {
          receivers->get(i)->onReceive(msg->getAction(), msg->getContent());
        }
        break;
      }
    }

    delete msg;
  }
}
