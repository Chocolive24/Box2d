#include "managers/Sound.h"

Sound* Sound::SoundManager_ = nullptr;

Sound::Sound()
{
    if (!soundFxPiou.loadFromFile("data/sounds/Piou.wav"))
    {
        std::cerr << "Error loading : " << "data/sounds/Piou.wav" << std::endl;
    }

    if (!soundFxBrr.loadFromFile("data/sounds/Brr.wav"))
    {
        std::cout << "Error loading : " << "data/sounds/Brr.wav" << std::endl;
    }

	if (!soundFxBoum.loadFromFile("data/sounds/Boum.wav"))
    {
        std::cout << "Error loading : " << "data/sounds/Boum.wav" << std::endl;
    }

}

/**
 * Static methods should be defined outside the class.
 */
Sound* Sound::Instance()
{
    /**
     * This is a safer way to create an instance. instance = new Singleton is
     * dangeruous in case two instance threads wants to access at the same time
     */
    if (SoundManager_ == nullptr) {
        SoundManager_ = new Sound();
    }
    return SoundManager_;
}

void Sound::cleanSounds()
{
    //cleanOneVector(sounds);
    //cleanOneVector(pious);
    //cleanOneVector(brrs);
}

void Sound::cleanOneVector(std::vector<sf::Sound> sounds_)
{
    auto s = std::remove_if(
        sounds_.begin(),
        sounds_.end(),
        [](sf::Sound& s) {return s.getStatus() == sf::SoundSource::Stopped; });

    if (s != sounds_.end())
    {
        sounds_.erase(s, sounds_.end());
    }

}

void Sound::playPiou()
{
    //playOnce(soundFxPiou);
    //sf::Sound soundToAdd;
    pious.setBuffer(soundFxPiou);
    pious.setLoop(false);
	pious.play();
}
void Sound::playBrr()
{
    //playOnce(soundFxBrr);
    sf::Sound soundToAdd;
    brrs.setBuffer(soundFxBrr);
    brrs.setLoop(false);
    brrs.play();
}
void Sound::playBoum()
{
    //playOnce(soundFxBoum);
    boum.setBuffer(soundFxBoum);
    boum.setLoop(false);
    boum.play();
}

void Sound::playOnce(sf::SoundBuffer& soundFx_)
{
    sf::Sound soundToAdd;
    soundToAdd.setBuffer(soundFx_);
    soundToAdd.setLoop(false);

    sounds.push_back(soundToAdd);
    sounds.back().play();

}
