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

void Backend::validateData()
{
    // check if both genders belong to each team
    // check if in each team, are at least 6 players
    // check if each team choosed captain
    // (additional) check if in each team, captain was choosed only once
    // check if there are at least 8 teams (some of them could be checked as "not playing")

    emit this->dataValidatedCorrectly();
}
