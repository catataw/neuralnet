#include "connection.h"

Connection::Connection(const Connection& connection)
	:	m_Weight(connection.m_Weight),
		m_Delta(connection.m_Delta),
		m_SourceNeuronIndex(connection.m_SourceNeuronIndex)
{
	initProperties();
}

Connection::Connection(unsigned sourceNeuronIndex) : m_SourceNeuronIndex(sourceNeuronIndex) {
	initProperties();
}

void Connection::initProperties() {
	this->Weight.set(&Connection::_setWeight, this);
	this->Weight.get(&Connection::_getWeight, this);
	this->Delta.set(&Connection::_setDelta, this);
	this->Delta.get(&Connection::_getDelta, this);
	this->SourceNeuronIndex.set(&Connection::_setSourceNeuronIndex, this);
	this->SourceNeuronIndex.get(&Connection::_getSourceNeuronIndex, this);
}


double const Connection::_getWeight()
{
	return this->m_Weight;
}

void Connection::_setWeight(double const value)
{
	this->m_Weight = value;
}


double const Connection::_getDelta()
{
	return this->m_Delta;
}


void Connection::_setDelta(double const value)
{
	this->m_Delta = value;
}

unsigned const Connection::_getSourceNeuronIndex()
{
	return this->m_SourceNeuronIndex;
}


void Connection::_setSourceNeuronIndex(unsigned const value)
{
	this->m_SourceNeuronIndex = value;
}
