/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2013 CERN
 * @author Maciej Suminski <maciej.suminski@cern.ch>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/**
 * @file opengl_compositor.h
 * @brief Class that handles multitarget rendering (ie. to different textures/surfaces) and
 * later compositing into a single image (OpenGL flavour).
 */

#ifndef OPENGL_COMPOSITOR_H_
#define OPENGL_COMPOSITOR_H_

#include <gal/compositor.h>
#include <GL/glew.h>
#include <vector>

namespace KiGfx
{

class OPENGL_COMPOSITOR : public COMPOSITOR
{
public:
    OPENGL_COMPOSITOR();
    virtual ~OPENGL_COMPOSITOR();

    ///< @copydoc COMPOSITOR::Initialize()
    virtual void Initialize();

    ///< @copydoc COMPOSITOR::Resize()
    virtual void Resize( unsigned int aWidth, unsigned int aHeight );

    ///< @copydoc COMPOSITOR::GetBuffer()
    virtual unsigned int GetBuffer();

    ///< @copydoc COMPOSITOR::SetBuffer()
    virtual void SetBuffer( unsigned int aBufferHandle );

    ///< @copydoc COMPOSITOR::ClearBuffer()
    virtual void ClearBuffer();

    ///< @copydoc COMPOSITOR::BlitBuffer()
    virtual void BlitBuffer( unsigned int aBufferHandle );

    ///< @copydoc COMPOSITOR::DrawBuffer()
    virtual void DrawBuffer( unsigned int aBufferHandle, double aDepth );

protected:
    typedef struct
    {
        GLuint textureTarget;                ///< Main texture handle
        GLuint attachmentPoint;
    } BUFFER_ITEM;

    bool                        m_initialized;
    unsigned int                m_current;
    GLuint                      m_framebuffer;            ///< Main FBO handle
    GLuint                      m_depthBuffer;            ///< Depth buffer handle
    unsigned int                m_maxBuffers;             ///< Maximal amount of buffers
    typedef std::vector<BUFFER_ITEM> Buffers;
    Buffers                     m_buffers;

    /// Store the currently used FBO name in case there was more than one compositor used
    static GLuint               m_currentFbo;

    /**
     * Function clean()
     * performs freeing of resources.
     */
    void clean();

    ///< Returns number of used buffers
    unsigned int usedBuffers()
    {
        return m_buffers.size();
    }
};

} // namespace KiGfx

#endif /* COMPOSITOR_H_ */
