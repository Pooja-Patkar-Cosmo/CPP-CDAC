#include <iostream>
#include <memory>
#include <string>

using namespace std;

class AudioClip {
private:
    string name;
    double duration;

public:
    AudioClip(string name, double duration): name(move(name)), duration(duration) {
        cout << "[Audio Clip Loaded]" << endl;
    }

    ~AudioClip() {
        cout << "[Audio Clip Unloaded]" << endl;
    }

    string getName() const {
        return name;
    }
};

int main() {
    auto audio = make_shared<AudioClip>("explosion", 3.5);

    weak_ptr<AudioClip> observer = audio;

    if (auto clip = observer.lock()) {
        cout << "Clip alive: " << clip->getName() << endl;
    }

    audio.reset();

    // 5. Try lock() / expired() to handle unloaded clip gracefully
    if (observer.expired()) {
        cout << "Clip already unloaded." << endl;
    }

    return 0;
}