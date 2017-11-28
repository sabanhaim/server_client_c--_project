#pragma once
#include "cynetProtocole.h"
#include "protocole.h"
#include "currentServerTime.h"
#include "numberOfCalles.h"
#include "multiplication.h"
#include "message.h"

cynetProtocole::cynetProtocole(void) {};


void cynetProtocole::setMessage(void)
{
	message** m = new message*[10];
	m[0] = new currentServerTime();
	m[0]->sed_id(1);
	m[1] = new numberOfCalles();
	m[1]->sed_id(2);
	m[2] = new multiplication();
	m[2]->sed_id(3);
	this->set(m);
	this->setCurrentMessage(3);
}

