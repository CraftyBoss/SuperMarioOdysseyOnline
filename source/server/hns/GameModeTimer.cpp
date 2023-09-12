#include "server/gamemode/GameModeTimer.hpp"
#include <math.h>
#include "al/util/ControllerUtil.h"
#include "server/DeltaTime.hpp"
#include "logger.hpp"

GameModeTimer::GameModeTimer(bool isCountUp, float milli, int seconds, int minutes, int hours) {
    mIsCountUp = isCountUp;
    setTime(milli, seconds, minutes, hours);
}

GameModeTimer::GameModeTimer(float milli, int seconds, int minutes, int hours) {
    mIsCountUp = false;
    setTime(milli, seconds, minutes, hours);
}

GameModeTimer::GameModeTimer(GameTime const& time) {
    mIsCountUp = true;
    setTime(time);
}

GameModeTimer::GameModeTimer() {
    mIsCountUp = true;
    resetTime();
}

void GameModeTimer::setTime(float milli, int seconds, int minutes, int hours) {
    if (milli >= 0)
        mTime.mMilliseconds = milli;
    if (seconds >= 0)
        mTime.mSeconds = seconds;
    if (minutes >= 0)
        mTime.mMinutes = minutes;
    if (hours >= 0)
        mTime.mHours = hours;
}

void GameModeTimer::setTime(GameTime const& time) {
    mTime = time;
}

void GameModeTimer::updateTimer() {
    if (mIsUseControl) {
        timerControl();
    }

    if (mIsEnabled) {
        if (mIsCountUp) {
            mTime.mMilliseconds += Time::deltaTime;

            if (mTime.mMilliseconds >= 1) {
                mTime.mMilliseconds--;
                mTime.mSeconds++;
                if (mTime.mSeconds >= 60) {
                    mTime.mSeconds = 0;
                    mTime.mMinutes++;
                    if (mTime.mMinutes >= 60) {
                        mTime.mMinutes = 0;
                        mTime.mHours++;
                    }
                }
            }
        } else {
            mTime.mMilliseconds += Time::deltaTime;
            if (mTime.mMilliseconds >= 1) {
                mTime.mMilliseconds--;
                mTime.mSeconds--;
                if (mTime.mSeconds < 0) {
                    mTime.mSeconds = 59;
                    mTime.mMinutes--;
                    if (mTime.mMinutes < 0) {
                        if (mTime.mHours > 0) {
                            mTime.mMinutes = 59;
                            mTime.mHours--;
                        } else {
                            mIsEnabled = false;
                        }
                    }
                }
            }
        }
    }
}

void GameModeTimer::timerControl() {
    if (al::isPadHoldL(-1)) {
        if (al::isPadTriggerDown(-1)) {
            mTime.mMilliseconds = 0;
            mTime.mSeconds = 0;
            mTime.mMinutes = 0;
            mTime.mHours = 0;
        }
    } else {
        if (al::isPadHoldRight(-1)) {
            mTime.mMilliseconds = 0;
            mTime.mSeconds++;
            if (mTime.mSeconds >= 60) {
                mTime.mSeconds = 0;
                mTime.mMinutes++;
                if (mTime.mMinutes >= 60) {
                    mTime.mMinutes = 0;
                    mTime.mHours++;
                }
            }
        }

        if (al::isPadTriggerLeft(-1)) {
            mTime.mMilliseconds = 0;
            if (mTime.mMinutes != 0) {
                mTime.mSeconds--;
                if (mTime.mSeconds < 0) {
                    mTime.mSeconds = 59;
                    mTime.mMinutes--;
                    if (mTime.mMinutes < 0) {
                        if (mTime.mHours > 0) {
                            mTime.mMinutes = 59;
                            mTime.mHours--;
                        } else {
                            mTime.mMinutes = 0;
                        }
                    }
                }
            }
        }
    }
}