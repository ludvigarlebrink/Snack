#pragma once

namespace spy
{
class IEvent
{
public:

    virtual ~IEvent() = default;

    virtual void Notify() = 0;
};

template <typename T>
class Event : public IEvent
{
public:


};
}
