
#include "soundDesign/SoundManager.h"

SoundManager::SoundManager()
{
    if (!_laserBuffer.loadFromFile("data/sound/sfx_laser2.wav"))
    {
        return;
    }

    _laserSound.setBuffer(_laserBuffer);

    if (!_bombBuffer.loadFromFile("data/sound/bomb.wav"))
    {
        return;
    }

    _bombSound.setBuffer(_bombBuffer);

    if (!_explosionBuffer.loadFromFile("data/sound/explosion.wav"))
    {
        return;
    }

    _explosionSound.setBuffer(_explosionBuffer);
}
