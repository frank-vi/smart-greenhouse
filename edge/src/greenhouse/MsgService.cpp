#include "Arduino.h"
#include "MsgService.h"

#define N_MAX_MSG 10

String content;
Msg* currentMsg;

void MsgService::init() {
  Serial.begin(9600);
  content.reserve(256);
  content = "";
  currentMsg = NULL;
}

bool MsgService::isMsgAvailable(){
  return currentMsg != NULL;
}

Msg* MsgService::receiveMsg(){
	if (currentMsg != NULL){
		Msg* msg = currentMsg;
		currentMsg = NULL;
		content = "";
		return msg;
	} else {
		return NULL;
	}
}

void MsgService::sendMsg(Msg msg) {
  String text = "<" + msg.getAction() + "," + msg.getContent() + ">";
  Serial.println(text);
}

void createMsg() {
  int separatorIndex = content.indexOf(",");
  if(separatorIndex != -1) {
    String action = content.substring(0, separatorIndex);
    String contentArg = content.substring(separatorIndex+1, content.length());
    currentMsg = new Msg(action, contentArg);
  } else {
    currentMsg = new Msg(content, "");
  }
}

void serialEvent() {
  while(Serial.available()) {
      char rc = (char) Serial.read();
      if (rc == '<') {
          content = "";
      } else if(rc != '>') {
          content += rc;
      } else if(rc == '>' && content.length() > 0 && content.indexOf('\r') == -1 && content.indexOf('\n') == -1) {
          createMsg();
          content = "";
      }
  }
}

bool MsgService::isMsgAvailable(Pattern& pattern){
	return (currentMsg != NULL && pattern.match(*currentMsg));
}

Msg* MsgService::receiveMsg(Pattern& pattern){
  if (currentMsg != NULL && pattern.match(*currentMsg)){
    Msg* msg = currentMsg;
    currentMsg = NULL;
    content = "";
    return msg;
  } else {
    return NULL;
  }
}
