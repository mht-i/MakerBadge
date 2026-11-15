// SPDX-License-Identifier: MIT AND BSD-2-Clause
//
// drawText.h - draw proportional TTF-derived fonts on Pervasive Displays screens
//
// Copyright (c) 2026 Mihai T.
// Licensed under the MIT License (see LICENSE in the project root), EXCEPT the
// GFXglyph / GFXfont structure definitions below, which are taken from
// Adafruit GFX Library (gfxfont.h), Copyright (c) 2012 Adafruit Industries,
// and remain under Adafruit's BSD license reproduced next to them.
// https://github.com/adafruit/Adafruit-GFX-Library
//
// Works with PDLS Basic (Screen_EPD / hV_Screen_Buffer) through myScreen.point(),
// so text follows setOrientation() and can use any screen colour.
// Fonts use the Adafruit GFX font format (GFXfont / GFXglyph): generate them with
// ttf2gfx.py, Adafruit's fontconvert or truetype2gfx.
//
// Text is UTF-8. Supported: code points 0x20-0xFF (ASCII + Latin-1: äöüÄÖÜß ...)
// and the euro sign (stored by ttf2gfx.py in slot 0x80). Other characters are skipped.
//
// Coordinates: (x, y) is the TOP-LEFT of the line box, like gText().
//
// ---------------------------------------------------------------------------
// USAGE
//   #include "Vujahday30Bold.h"            // font header (includes drawText.h)
//
//   myScreen.begin();
//   myScreen.setOrientation(ORIENTATION_LANDSCAPE);   // 248 x 128
//   ...copy template image / draw other things...
//
//   drawText(myScreen, 132, 30, "Mihai T.", myColours.black, &Vujahday30Bold);
//   drawTextCentered(myScreen, 174, 30, "Mihai T.", myColours.black, &Vujahday30Bold);
//   drawTextRight(myScreen, 246, 30, "Mihai T.", myColours.red, &Vujahday30Bold);
//
//   uint16_t w = textWidth("Mihai T.", &Vujahday30Bold);   // pixels, e.g. to fit a box
//   int16_t  a = fontAscent(&Vujahday30Bold);              // top of line -> baseline
//
//   myScreen.flush();                       // one refresh at the end, as usual
//
// Functions
//   int16_t  drawText        (screen, x,       yTop, text, colour, &font)  -> x after text
//   int16_t  drawTextCentered(screen, xCentre, yTop, text, colour, &font)
//   int16_t  drawTextRight   (screen, xRight,  yTop, text, colour, &font)
//   uint16_t textWidth       (text, &font)
//   int16_t  fontAscent      (&font)
//   Next line: yTop += font.yAdvance  (e.g. Vujahday30Bold.yAdvance = 33)
//
// Notes
//   - Draws only the "ink" pixels: the background (template image) stays visible.
//   - Script fonts overlap slightly between letters by design; nothing is erased.
//   - Pixels outside the screen are ignored by the library.
//   - Make new fonts/sizes with:  python3 ttf2gfx.py MyFont.ttf 24 MyFont24 --bold
// ---------------------------------------------------------------------------
//
#pragma once
#include <stdint.h>

// ===========================================================================
// BEGIN third-party code: GFXglyph / GFXfont, from Adafruit GFX Library,
// file gfxfont.h (https://github.com/adafruit/Adafruit-GFX-Library).
// Used unchanged except for comment formatting.
//
// Software License Agreement (BSD License)
//
// Copyright (c) 2012 Adafruit Industries.  All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// - Redistributions of source code must retain the above copyright notice,
//   this list of conditions and the following disclaimer.
// - Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
// ===========================================================================
#ifndef _GFXFONT_H_
#define _GFXFONT_H_
typedef struct
{
    uint16_t bitmapOffset; ///< Offset into GFXfont->bitmap
    uint8_t width;         ///< Bitmap width in pixels
    uint8_t height;        ///< Bitmap height in pixels
    uint8_t xAdvance;      ///< Distance to advance cursor (x axis)
    int8_t xOffset;        ///< X distance from cursor position to upper-left corner
    int8_t yOffset;        ///< Y distance from baseline to upper-left corner
} GFXglyph;

typedef struct
{
    uint8_t * bitmap;  ///< Glyph bitmaps, concatenated
    GFXglyph * glyph;  ///< Glyph array
    uint16_t first;    ///< ASCII extents (first char)
    uint16_t last;     ///< ASCII extents (last char)
    uint8_t yAdvance;  ///< Newline distance (y axis)
} GFXfont;
#endif // _GFXFONT_H_
// END third-party code (Adafruit GFX Library). Everything below: MIT, see top of file.
// ===========================================================================

// Decode the next UTF-8 character and map it to a font slot (0 = skip)
static inline uint16_t dt_nextChar(const char *& s)
{
    uint8_t c = (uint8_t) * s++;
    uint32_t cp;
    if (c < 0x80)
    {
        cp = c;
    }
    else if ((c & 0xE0) == 0xC0 && *s)
    {
        cp = ((c & 0x1F) << 6) | ((uint8_t) * s++ & 0x3F);
    }
    else if ((c & 0xF0) == 0xE0 && s[0] && s[1])
    {
        cp = ((c & 0x0F) << 12) | (((uint8_t)s[0] & 0x3F) << 6) | ((uint8_t)s[1] & 0x3F);
        s += 2;
    }
    else
    {
        while ((*s & 0xC0) == 0x80) s++; // skip unsupported sequence
        return 0;
    }
    if (cp == 0x20AC) return 0x80;  // euro sign -> slot 0x80
    return (cp <= 0xFF) ? cp : 0;
}

// Ascent of a font: pixels from the top of the line box to the baseline
static inline int16_t fontAscent(const GFXfont * font)
{
    int16_t top = 0;
    for (uint16_t i = 0; i <= font->last - font->first; i++)
    {
        const GFXglyph * g = &font->glyph[i];
        if (g->height && g->yOffset < top) top = g->yOffset;
    }
    return -top;
}

// Width of a string in pixels (sum of advances)
static inline uint16_t textWidth(const char * text, const GFXfont * font)
{
    uint16_t w = 0;
    while (*text)
    {
        uint16_t c = dt_nextChar(text);
        if (c >= font->first && c <= font->last)
            w += font->glyph[c - font->first].xAdvance;
    }
    return w;
}

// Draw text with its line box starting at (x, y).
// Returns the x position after the last character (handy for chaining).
// screen : any PDLS screen object, e.g. myScreen
// colour : e.g. myColours.black, myColours.red, myColours.yellow, myColours.white
template <class SCREEN>
int16_t drawText(SCREEN & screen, int16_t x, int16_t y, const char * text,
                 uint16_t colour, const GFXfont * font)
{
    const int16_t baseline = y + fontAscent(font);
    while (*text)
    {
        uint16_t c = dt_nextChar(text);
        if (c < font->first || c > font->last) continue;

        const GFXglyph * g = &font->glyph[c - font->first];
        const uint8_t * bmp = font->bitmap + g->bitmapOffset;
        uint16_t bit = 0;
        uint8_t bits = 0;

        for (uint8_t row = 0; row < g->height; row++)
        {
            for (uint8_t col = 0; col < g->width; col++)
            {
                if ((bit & 7) == 0) bits = bmp[bit >> 3];
                if (bits & 0x80)
                {
                    int16_t px = x + g->xOffset + col;
                    int16_t py = baseline + g->yOffset + row;
                    if (px >= 0 && py >= 0) screen.point(px, py, colour);
                }
                bits <<= 1;
                bit++;
            }
        }
        x += g->xAdvance;
    }
    return x;
}

// Convenience helpers
template <class SCREEN>
int16_t drawTextCentered(SCREEN & screen, int16_t xCentre, int16_t y, const char * text,
                         uint16_t colour, const GFXfont * font)
{
    return drawText(screen, xCentre - (int16_t)textWidth(text, font) / 2, y, text, colour, font);
}

template <class SCREEN>
int16_t drawTextRight(SCREEN & screen, int16_t xRight, int16_t y, const char * text,
                      uint16_t colour, const GFXfont * font)
{
    return drawText(screen, xRight - (int16_t)textWidth(text, font), y, text, colour, font);
}
