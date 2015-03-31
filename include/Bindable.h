#ifndef BINDABLE_H
#define BINDABLE_H

namespace RE
{

class Bindable
{
protected:

    Bindable() {}
    ~Bindable() {}

public:

    virtual void Bind() const = 0;
    virtual void UnBind() const = 0;
};

}

#endif // BINDABLE_H
