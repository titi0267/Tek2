#include <thread>
#include <iostream>

class Oui {
    public:
    Oui() {
        std::thread thread(&Oui::loop, this);
    }
    ~Oui() {}

    void loop() const {while (1) std::cout << "oui\n";}
};

int main() {
    std::make_unique<Oui>();
}