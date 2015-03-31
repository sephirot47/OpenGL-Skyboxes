#ifndef RENDERTARGET_H
#define RENDERTARGET_H

namespace RE
{

class RenderTarget
{
protected:

    RenderTarget() {}
    ~RenderTarget() {}

public:

    virtual void BindRenderTarget() const = 0;
    virtual void UnBindRenderTarget() const = 0;
};

}

#endif // RENDERTARGET_H
