//
// Copyright (c) 2015 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//

// DisplayGL.h: FGL implementation of egl::Display

#include "libANGLE/renderer/gl/DisplayGL.h"

#include "libANGLE/AttributeMap.h"
#include "libANGLE/Context.h"
#include "libANGLE/Display.h"
#include "libANGLE/Surface.h"
#include "libANGLE/renderer/gl/RendererGL.h"
#include "libANGLE/renderer/gl/SurfaceGL.h"

#include <EGL/eglext.h>

namespace rx
{

DisplayGL::DisplayGL()
    : mRenderer(nullptr)
{
}

DisplayGL::~DisplayGL()
{
}

egl::Error DisplayGL::initialize(egl::Display *display)
{
    mRenderer = new RendererGL(getFunctionsGL(), display->getAttributeMap());

    const gl::Version &maxVersion = mRenderer->getMaxSupportedESVersion();
    if (maxVersion < gl::Version(2, 0))
    {
        return egl::Error(EGL_NOT_INITIALIZED, "OpenGL ES 2.0 is not supportable.");
    }

    return egl::Error(EGL_SUCCESS);
}

void DisplayGL::terminate()
{
    SafeDelete(mRenderer);
}

ImageImpl *DisplayGL::createImage(EGLenum target,
                                  egl::ImageSibling *buffer,
                                  const egl::AttributeMap &attribs)
{
    UNIMPLEMENTED();
    return nullptr;
}

gl::Context *DisplayGL::createContext(const egl::Config *config,
                                      const gl::Context *shareContext,
                                      const egl::AttributeMap &attribs)
{
    ASSERT(mRenderer != nullptr);
    return new gl::Context(config, shareContext, mRenderer, attribs);
}

StreamImpl *DisplayGL::createStream(const egl::AttributeMap &attribs)
{
    UNREACHABLE();
    return nullptr;
}

egl::Error DisplayGL::makeCurrent(egl::Surface *drawSurface, egl::Surface *readSurface, gl::Context *context)
{
    if (!drawSurface)
    {
        return egl::Error(EGL_SUCCESS);
    }

    SurfaceGL *glDrawSurface = GetImplAs<SurfaceGL>(drawSurface);
    return glDrawSurface->makeCurrent();
}

const gl::Version &DisplayGL::getMaxSupportedESVersion() const
{
    ASSERT(mRenderer != nullptr);
    return mRenderer->getMaxSupportedESVersion();
}

}
