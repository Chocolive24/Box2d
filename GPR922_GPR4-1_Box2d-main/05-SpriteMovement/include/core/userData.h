#pragma once

#include <string>
#include <box2d/b2_settings.h>

enum UserDataType : char
{
    SHIP = 's',
    LIMIT = 'l',
    ASTEROID = 'a',
    MISSILE = 'n',
    NONE

};

class UserData : public b2BodyUserData
{
public:
    UserData();
    UserData(UserDataType type_);

    static const std::string UserDataTypeToString(UserDataType type_);

    UserDataType getUserDataType();
    signed long getLocalId();

    void setLocalId(signed long id_);
    void setType(UserDataType type_);

private:
    UserDataType m_type;
    signed long m_localId;

};
