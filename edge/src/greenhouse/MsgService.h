#ifndef __MSGSERVICE__
#define __MSGSERVICE__

#include "Arduino.h"

class Msg {
  String action;
  String content;

public:
  Msg(const String& action){
    this->action = action;
  }

  Msg(const String& action, const String& content) : Msg(action) {
    this->content = content;
  }

  void setContent(const String& content) {
    this->content = content;
  }

  String getAction(){
    return this->action;
  }

  String getContent(){
    return this->content;
  }
};

class Pattern {
public:
  virtual bool match(const Msg& m) = 0;
};

class MsgService {

public:
  void init();

  Msg* receiveMsg();
  void sendMsg(Msg msg);
  bool isMsgAvailable();

  Msg* receiveMsg(Pattern& pattern);
  bool isMsgAvailable(Pattern& pattern);

};

#endif
