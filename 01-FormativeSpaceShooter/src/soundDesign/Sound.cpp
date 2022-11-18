
#include "soundDesign/Sound.h"

Sound::Sound()
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

    if (!_bombExplosionBuffer.loadFromFile("data/sound/bombExplosion.wav"))
    {
        return;
    }

    _bombExplosionSound.setBuffer(_bombExplosionBuffer);

    if (!_meteorExplosionBuffer.loadFromFile("data/sound/explosion.wav"))
    {
        return;
    }

    _meteorExplosionSound.setBuffer(_meteorExplosionBuffer);
    _meteorExplosionSound.setVolume(50);

    if (!_damageBuffer.loadFromFile("data/sound/damage.wav"))
    {
        return;
    }

    _damageSound.setBuffer(_damageBuffer);
}