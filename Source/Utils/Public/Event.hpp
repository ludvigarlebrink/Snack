#pragma once

namespace snack
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
