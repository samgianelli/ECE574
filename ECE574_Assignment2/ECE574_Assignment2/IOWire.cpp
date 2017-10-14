#include "IOWire.h"

IOWire::IOWire()
{
	this->name = "";
	this->type = "";
	this->prev = NULL;
	this->next = NULL;
}

IOWire::IOWire(string name, string type)
{
	this->name = name;
	this->type = type;
	this->prev = NULL;
	this->next = NULL;

	//cout << "IOWire constructor:  Name: " << this->name << ",  Type: " << this->type << endl;
}

void IOWire::setPrev(Module *prev)
{
	this->prev = prev;
	return;
}

void IOWire::setNext(Module *next)
{
	this->next = next;
	return;
}

string IOWire::getName()
{
	return this->name;
}

string IOWire::getType()
{
	return this->type;
}

string IOWire::printIOWire()
{
	cout << "Name: " + this->name + "\tType: " + this->type << endl;
	//this->prev->PrintModule();
	//this->next->PrintModule();
	return "";
}