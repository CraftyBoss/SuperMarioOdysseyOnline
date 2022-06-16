#pragma once

class WorldResourceLoader {
    public:
        void loadWorldResource(int,int,bool,char const *);
        bool requestLoadWorldHomeStageResource(int worldIndex, int scenario);
};