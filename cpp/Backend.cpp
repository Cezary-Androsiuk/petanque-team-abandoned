#include "Backend.h"

Backend::Backend(QObject *parent)
    : QObject{parent}
    , m_event(new Event(this))
{

}

Backend::~Backend()
{
}

Event *Backend::getEvent() const
{
    return m_event;
}
