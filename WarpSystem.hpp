/*
** EPITECH PROJECT, 2022
** B-PDG-300-STG-3-1-PDGD07am-timothe.coniel
** File description:
** WarpSystem
*/

#ifndef WARPSYSTEM_HPP_
#define WARPSYSTEM_HPP_

namespace WarpSystem {
    class QuantumReactor {
        public:
            QuantumReactor();
            ~QuantumReactor();
            bool isStable();
            void setStability(bool stability);

        protected:
        private:
            bool _stability;
    };
    class Core {
        public:
            Core(WarpSystem::QuantumReactor *QuantumReactor_ptr);
            ~Core();
            WarpSystem::QuantumReactor *checkReactor();

        protected:
        private:
            WarpSystem::QuantumReactor *_coreReactor;
    };
};

#endif /* !WARPSYSTEM_HPP_ */
