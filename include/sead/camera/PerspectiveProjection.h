#pragma once

namespace sead {
    class PerspectiveProjection {
        public:
            float getFovy();
            
            unsigned char padding[0xA0];
            float fovy;
    };
}