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

string IOWire::printIOWire()
{
	return "Name: " + this->name + "\tType: " + this->type;
}