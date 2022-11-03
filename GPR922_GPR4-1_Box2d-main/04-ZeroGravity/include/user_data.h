#pragma once

enum class UserDataType
{
    BALL,
    LIMIT,
    BOUNCER,
    NONE
};

struct UserData
{
    UserDataType userData = UserDataType::NONE;
};
