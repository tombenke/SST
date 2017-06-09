/*
 * SST.h
 * Daily Start-Stop Timer.
 * Created by Tamás Benke, May 20, 2017.
 * Released into the public domain.
 */

#ifndef _SST_h
#define _SST_h

#include <Arduino.h>

enum SstMode { INACTIVE=0, MANUAL=1, AUTO=2 };
enum SstState { OFF=false, ON=true };

class SST {
    private:
        /** The index of the port to switch on/off */
        int portIdx;

        /** The current mode of the timer. Default is INACTIVE after reset. */
        enum SstMode mode;

        /** The current state of the timer. Default is OFF after reset. */
        enum SstState state;

        /** The hour the timer starts every day */
        int fromHour;

        /** The minute the timer starts every day */
        int fromMinute;

        /** The hour the timer stops every day */
        int toHour;

        /** The minute the timer stops every day */
        int toMinute;

        /** Callback function that is called when state change occurs */
        void (*stateChangeCb)(int, enum SstState);

        inline bool isOn(void);
        inline bool isOff(void);
        inline bool turnOn(void);
        inline bool turnOff(void);
        inline bool isInAutoMode(void);
        inline bool isInActivePeriod(void);
        inline bool isInInactiveMode(void);

    public:
        SST(int portIdx, void (*stateChangeCb)(int, enum SstState));
        void reset(void);
        void set(int portIdx, enum SstMode mode, int fromHour, int fromMinute, int toHour, int toMinute);
        void get(int& portIdx, enum SstMode& mode, enum SstState &state, int& fromHour, int& fromMinute, int& toHour, int& toMinute);
        inline enum SstMode getMode(void){
            return this->mode;
        };
        inline enum SstState getState(void){
            return this->state;
        };
        void update(void);
};

#endif
