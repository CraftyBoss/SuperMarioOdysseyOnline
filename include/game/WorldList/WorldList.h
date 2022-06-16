#pragma once

class WorldList {
    public:
        const char *getWorldDevelopName(int) const;
        int tryFindWorldIndexByStageName(char const *stageName) const;
        int getMoonRockScenarioNo(int worldId) const;
        int findUseScenarioNo(const char *stageName) const;
        bool checkIsMainStage(char const *stageName) const;
};