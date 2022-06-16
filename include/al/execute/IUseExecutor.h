#pragma once

namespace al {
class IUseExecutor {
public:
    virtual void execute() = 0;
    virtual void draw() = 0;
};
}