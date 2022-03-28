#pragma once

#include "../../arcade-interface-master/IGameModule.hpp"
#include "Core.hpp"

class GameModule : public IGameModule {
    public:
        GameModule();
        ~GameModule();
        void init(Core *coreHandle);
        void update();
        void draw();
};

extern "C" std::unique_ptr<IGameModule> gEpitechArcadeGetGameModuleHandle();
