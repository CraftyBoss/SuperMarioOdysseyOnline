#pragma once

struct GameTime {
    float mMilliseconds = 0;
    int mSeconds = 0;
    int mMinutes = 0;
    int mHours = 0;
};

class GameModeTimer {
public:
    GameModeTimer(bool isCountUp, float milli, int seconds, int minutes, int hours); // can set start time or max time, depending on isCountUp
    GameModeTimer(float milli, int seconds, int minutes, int hours);                 // defaults to counting down with a start time
    GameModeTimer(GameTime const& time);                                             // sets timer's current time to time struct argument, defaults to incrementing
    GameModeTimer();                                                                 // defaults to counting up with zero time
    
    void toggleTimer()  { mIsEnabled = !mIsEnabled; }
    void enableTimer()  { mIsEnabled = true; }
    void disableTimer() { mIsEnabled = false; }

    void enableControl()  { mIsUseControl = true; }
    void disableControl() { mIsUseControl = false; }

    void setTime(float milli, int seconds, int minutes, int hours);

    void setTime(GameTime const& time);

    void resetTime() { setTime(0, 0, 0, 0); }

    float getMilliseconds() { return mTime.mMilliseconds; }
    int getSeconds() { return mTime.mSeconds; }
    int getMinutes() { return mTime.mMinutes; }
    int getHours() { return mTime.mHours; }

    GameTime getTime() { return mTime; }
    GameTime *getTimePtr() { return &mTime; }

    void updateTimer();

    void timerControl();

    void setPaneTime();

private:
    bool mIsCountUp = true;
    bool mIsEnabled = false;
    bool mIsUseControl = true;
    GameTime mTime;
};