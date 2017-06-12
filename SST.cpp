#include <TimeLib.h>
#include <SST.h>


SST::SST(int portIdx, void (*stateChangeCb)(int, enum SstState)) {
    this->portIdx = portIdx;
    this->mode = INACTIVE;
    this->state = OFF;
    this->fromHour = 0;
    this->fromMinute = 0;
    this->toHour = 0;
    this->toMinute = 0;
    this->stateChangeCb = stateChangeCb;

    // Update the state
    this->update();
}

void SST::reset(void) {
    this->mode = INACTIVE;
    this->state = OFF;
    this->fromHour = 0;
    this->fromMinute = 0;
    this->toHour = 0;
    this->toMinute = 0;

    // Update the state
    this->update();
}

void SST::set(int portIdx, enum SstMode mode, int fromHour, int fromMinute, int toHour, int toMinute) {
    this->portIdx = portIdx;
    this->mode = mode;
    this->fromHour = fromHour;
    this->fromMinute = fromMinute;
    this->toHour = toHour;
    this->toMinute = toMinute;

    // Update the state
    this->update();
}

void SST::get(int& portIdx, enum SstMode& mode, enum SstState& state, int& fromHour, int& fromMinute, int& toHour, int& toMinute) {
    portIdx = this->portIdx;
    mode = this->mode;
    state = this->state;
    fromHour = this->fromHour;
    fromMinute = this->fromMinute;
    toHour = this->toHour;
    toMinute = this->toMinute;
}

inline bool SST::isOn(void) {
    return (this->state == ON);
}

inline bool SST::isOff(void) {
    return (this->state == OFF);
}

inline bool SST::isInAutoMode(void) {
    return (this->mode == AUTO);
}

inline bool SST::isInInactiveMode(void) {
    return (this->mode == INACTIVE);
}

inline bool SST::isInActivePeriod(void) {
    int current = hour() * 60 + minute();
    int from = this->fromHour * 60 + this->fromMinute;
    int to = this->toHour * 60 + this->toMinute;

    return(from <= current && current < to);
}

inline bool SST::turnOn(void) {
    this->state = ON;
    this->stateChangeCb(this->portIdx, this->state);
}

inline bool SST::turnOff(void) {
    this->state = OFF;
    this->stateChangeCb(this->portIdx, this->state);
}

void SST::update(void) {

    if (this->isInInactiveMode() && this->isOn()) {
        this->turnOff();
    } else if (this->isInAutoMode()) {
        if (this->isInActivePeriod() && this->isOff()) {
            this->turnOn();
        }
        if (! this->isInActivePeriod() && this->isOn()) {
            this->turnOff();
        }
    }
}
