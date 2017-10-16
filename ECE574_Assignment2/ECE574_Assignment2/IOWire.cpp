#include "IOWire.h"

IOWire::IOWire()
{
	this->name = "";
	this->type = "";
	this->prev = NULL;
	this->next = vector<Module*>();
}

IOWire::IOWire(string name, string type)
{
	this->name = name;
	this->type = type;
	this->prev = NULL;
	this->next = vector<Module*>();

	//cout << "IOWire constructor:  Name: " << this->name << ",  Type: " << this->type << endl;
}

void IOWire::setPrev(Module *prev)
{
	this->prev = prev;
	return;
}

void IOWire::setNext(vector<Module*> next)
{
	this->next = next;
	return;
}

void IOWire::addNext(Module *next)
{
	this->next.push_back(next);
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
	cout << "Prev Module: " << prev->getOperation() << "\tNext Module: " << next.at(0)->getOperation();


	
	//this->prev->PrintModule();
	//this->next->PrintModule();
	return "";
}