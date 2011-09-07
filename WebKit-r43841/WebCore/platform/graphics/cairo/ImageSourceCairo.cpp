/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2007 Alp Toker <alp.toker@collabora.co.uk>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ImageSource.h"

#if PLATFORM(CAIRO)

#include "BMPImageDecoder.h"
#include "GIFImageDecoder.h"
#include "ICOImageDecoder.h"
#include "JPEGImageDecoder.h"
#include "PNGImageDecoder.h"
#include "SharedBuffer.h"
#include <cairo.h>
#include "DitherImageSource.h"
#include "KindleProfiling.h"
#if !PLATFORM(WIN)
#include "XBMImageDecoder.h"
#endif

// <lab126> 
int m_imageDitherType = USE_SIMPLE_ALGORITHM;

extern "C" {

WEBCORE_EXPORT extern void setDitherType(int DitherType)
{
    m_imageDitherType = DitherType;
}

}

 //</lab126>

namespace WebCore {

ImageDecoder* createDecoder(const Vector<char>& data)
{
    // We need at least 4 bytes to figure out what kind of image we're dealing with.
    int length = data.size();
    if (length < 4)
        return 0;

    const unsigned char* uContents = (const unsigned char*)data.data();
    const char* contents = data.data();

    // GIFs begin with GIF8(7 or 9).
    if (strncmp(contents, "GIF8", 4) == 0)
        return new GIFImageDecoder();

    // Test for PNG.
    if (uContents[0]==0x89 &&
        uContents[1]==0x50 &&
        uContents[2]==0x4E &&
        uContents[3]==0x47)
        return new PNGImageDecoder();

    // JPEG
    if (uContents[0]==0xFF &&
        uContents[1]==0xD8 &&
        uContents[2]==0xFF)
        return new JPEGImageDecoder();

    // BMP
    if (strncmp(contents, "BM", 2) == 0)
        return new BMPImageDecoder();

    // ICOs always begin with a 2-byte 0 followed by a 2-byte 1.
    // CURs begin with 2-byte 0 followed by 2-byte 2.
    if (!memcmp(contents, "\000\000\001\000", 4) ||
        !memcmp(contents, "\000\000\002\000", 4))
        return new ICOImageDecoder();

#if !PLATFORM(WIN)
    // XBMs require 8 bytes of info.
    if (length >= 8 && strncmp(contents, "#define ", 8) == 0)
        return new XBMImageDecoder();
#endif

    // Give up. We don't know what the heck this is.
    return 0;
}

ImageSource::ImageSource()
    : m_decoder(0)
{
}

ImageSource::~ImageSource()
{
    clear(true);
}

void ImageSource::clear(bool destroyAll, size_t clearBeforeFrame, SharedBuffer* data, bool allDataReceived)
{
    if (!destroyAll) {
        if (m_decoder)
            m_decoder->clearFrameBufferCache(clearBeforeFrame);
        return;
    }

    delete m_decoder;
    m_decoder = 0;
    if (data)
        setData(data, allDataReceived);
}

bool ImageSource::initialized() const
{
    return m_decoder;
}

void ImageSource::setData(SharedBuffer* data, bool allDataReceived)
{
    // Make the decoder by sniffing the bytes.
    // This method will examine the data and instantiate an instance of the appropriate decoder plugin.
    // If insufficient bytes are available to determine the image type, no decoder plugin will be
    // made.
    if (!m_decoder)
        m_decoder = createDecoder(data->buffer());

    if (!m_decoder)
        return;

    m_decoder->setData(data, allDataReceived);
}

String ImageSource::filenameExtension() const
{
    if (!m_decoder)
        return String();

    return m_decoder->filenameExtension();
}

bool ImageSource::isSizeAvailable()
{
    if (!m_decoder)
        return false;

    return m_decoder->isSizeAvailable();
}

IntSize ImageSource::size() const
{
    if (!m_decoder)
        return IntSize();

    return m_decoder->size();
}

IntSize ImageSource::frameSizeAtIndex(size_t) const
{
    return size();
}

int ImageSource::repetitionCount()
{
    if (!m_decoder)
        return cAnimationNone;

    return m_decoder->repetitionCount();
}

size_t ImageSource::frameCount() const
{
    return m_decoder ? m_decoder->frameCount() : 0;
}
static int dither_buffer[3333];
static int dither_inited=0;
static int dither_index=0;
NativeImagePtr ImageSource::createFrameAtIndex(size_t index)
{
    if (!initialized())
        return 0;

    if (!m_decoder)
        return 0;

    RGBA32Buffer* buffer = m_decoder->frameBufferAtIndex(index);
    if (!buffer || buffer->status() == RGBA32Buffer::FrameEmpty)
        return 0;
        
    // Cairo does not like zero height images.
    // If we have a zero height image, just pretend we don't have enough data yet.
    if (!buffer->height())
        return 0;
     /* <lab126> */   
    struct timespec startTime;
    KINDLE_BEGIN(Kindle_Debug_Perf)
      clock_gettime(CLOCK_MONOTONIC, &startTime);
    KINDLE_END()
   
    if (m_imageDitherType == USE_SIMPLE_ALGORITHM) {
        int imageWidth = size().width();
        int imageHeight = buffer->height();
	if(!dither_inited) 
		for(int i=0;i<3333;i++)
			dither_buffer[i]=rand()%17;
        for (int n = 0; n < imageHeight; n++)
        {
            for (int m = 0; m < imageWidth; m++)
            {
		int rgb=buffer->bytes().data()[ (n*imageWidth) + m ];
		int r = (rgb >> 16) & 0xff;
    		int g = (rgb >> 8) & 0xff;
    		int b = rgb & 0xff;
		int gray = (r == g && g == b) ?  r : ((77 * r + 150 * g + 29 * b) >> 8);	
		dither_index=(dither_index+1)%3333;
		int ngray=gray+dither_buffer[dither_index];
		ngray-=ngray%17;
		if(ngray>0xff) ngray=0xff;
                buffer->bytes().data()[ (n*imageWidth) + m ] =   (rgb&STRIP_ALPHA)|(ngray<<16)|(ngray<<8)|ngray;
            }
        }
    }
    else if (m_imageDitherType == USE_STUCKI_ALGORITHM) 
    {
        int imageWidth = size().width();
        int imageHeight = buffer->height();
        DitherStuckiStateType *ditherStuckiStatePtr = (DitherStuckiStateType*) malloc(sizeof(DitherStuckiStateType)+imageWidth);
        ditherStuckiStatePtr->lineWidth  = imageWidth;
        ditherStuckiStatePtr->line1 = (int *) malloc((imageWidth*4) + 8); //Allocate 2 (2 * sizeof(int) ) pixels wider so that we cover the edges
        ditherStuckiStatePtr->line2 = (int *) malloc((imageWidth*4) + 8); //Allocate 2 (2 * sizeof(int) ) pixels wider so that we cover the edges
        for (int n = 0; n < imageHeight; n++)
        {
            for (int m = 0; m < imageWidth; m++)
            {

                 buffer->bytes().data()[ (n*imageWidth) + m ] =   ditherStucki(m, n, buffer->bytes().data()[ (n*imageWidth) + m ], ditherStuckiStatePtr);
            }
        }
        free(ditherStuckiStatePtr->line1);
        free(ditherStuckiStatePtr->line2);
        free(ditherStuckiStatePtr);
        
    } else if (m_imageDitherType == USE_FS_ALGORITHM) 
    {
    	int imageWidth = size().width();
        int imageHeight = buffer->height();
        DitherStateType *ditherStatePtr = (DitherStateType*) malloc(sizeof(DitherStateType)+imageWidth);
        for (int n = 0; n < imageHeight; n++)
        {
            for (int m = 0; m < imageWidth; m++)
            {
                 buffer->bytes().data()[ (n*imageWidth) + m ] = 	ditherFS(m, n, (buffer->bytes().data()[ (n*imageWidth) + m ]), ditherStatePtr);
            }
        }
        free(ditherStatePtr);

    }
    KINDLE_BEGIN(Kindle_Debug_Perf )
       struct timespec endTime;
       clock_gettime(CLOCK_MONOTONIC, &endTime);
       float renderingTime = kindle_time_diff(startTime, endTime);
       KINDLE_BEGIN(Kindle_Debug_Perf_Details)
          KINDLE_PRINT("\033[33mPerf: Image dithered in %.3fs\033[0m\n", renderingTime);
       KINDLE_END()
    KINDLE_END()
   /* </lab126> */
    return cairo_image_surface_create_for_data((unsigned char*)buffer->bytes().data(),
                                               CAIRO_FORMAT_ARGB32,
                                               size().width(),
                                               buffer->height(),
                                               size().width()*4);

}

bool ImageSource::frameIsCompleteAtIndex(size_t index)
{
    if (!m_decoder)
        return false;

    RGBA32Buffer* buffer = m_decoder->frameBufferAtIndex(index);
    return buffer && buffer->status() == RGBA32Buffer::FrameComplete;
}

float ImageSource::frameDurationAtIndex(size_t index)
{
    if (!m_decoder)
        return 0;

    RGBA32Buffer* buffer = m_decoder->frameBufferAtIndex(index);
    if (!buffer || buffer->status() == RGBA32Buffer::FrameEmpty)
        return 0;

    // Many annoying ads specify a 0 duration to make an image flash as quickly
    // as possible.  We follow WinIE's behavior and use a duration of 100 ms
    // for any frames that specify a duration of <= 50 ms.  See
    // <http://bugs.webkit.org/show_bug.cgi?id=14413> or Radar 4051389 for
    // more.
    const float duration = buffer->duration() / 1000.0f;
    return (duration < 0.051f) ? 0.100f : duration;
}

bool ImageSource::frameHasAlphaAtIndex(size_t index)
{
    // When a frame has not finished decoding, always mark it as having alpha,
    // so we don't get a black background for the undecoded sections.
    // TODO: A better solution is probably to have the underlying buffer's
    // hasAlpha() return true in these cases, since it is, in fact, technically
    // true.
    if (!frameIsCompleteAtIndex(index))
        return true;

    return m_decoder->frameBufferAtIndex(index)->hasAlpha();
}

}

#endif // PLATFORM(CAIRO)
