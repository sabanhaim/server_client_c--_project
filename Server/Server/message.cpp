#include "message.h"

message::message() {};
int message::get_id() { return id; };
void message::sed_id(int id) { this->id = id; }
string message::getNmae() { return this->nameMessage; }
void message::setName(string s) { this->nameMessage = s; }
