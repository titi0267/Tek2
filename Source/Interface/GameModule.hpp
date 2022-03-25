#pragma once

#include "../../arcade-interface-master/IGameModule.hpp"

class GameModule : public IGameModule {
    public:
        ~GameModule() = default;
        void init(ICore *coreHandle);
        void update();
        void draw();
};

extern "C" std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle();
