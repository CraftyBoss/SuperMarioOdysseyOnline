#pragma once

class PlayerPuppet {
    public: 
        void hide(void);
        void hideShadow(void);
        void hideSilhouette(void);

        void show(void);
        void showShadow(void);
        void showSilhouette(void);

        void invalidateCollisionCheck(void);
        void invalidateSensor(void);

        void validateCollisionCheck(void);
        void validateSensor(void);
};