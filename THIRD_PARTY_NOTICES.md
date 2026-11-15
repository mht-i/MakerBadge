# Third-party notices

This project is licensed under the MIT License (see `LICENSE`), except for the
parts listed below, which keep their original licenses.

| Part | Files | License |
|---|---|---|
| Adafruit GFX font structures | `drawText.h` (marked section) | BSD-2-Clause |
| Vujahday Script font (bitmap conversion) | `Vujahday48Bold.h` | OFL-1.1 |
| Audiowide font (bitmap conversion, renamed "BadgeWide25") | `BadgeWide25.h` | OFL-1.1 |

## Adafruit GFX Library – font structures

- **Used in:** `drawText.h` (the `GFXglyph` and `GFXfont` structure definitions only,
  clearly marked in the file)
- **Source:** https://github.com/adafruit/Adafruit-GFX-Library, file `gfxfont.h`
- **Copyright:** (c) 2012 Adafruit Industries
- **License:** BSD license (2-clause), full text below

```
Software License Agreement (BSD License)

Copyright (c) 2012 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
```

## Fonts (SIL Open Font License 1.1)

The two font headers are bitmap conversions of TrueType fonts, made with
`ttf2gfx.py`. Under the OFL a format conversion is a "Modified Version", so both
files are distributed under the OFL only (not under MIT). Text drawn on a badge
with these fonts is not affected by the font license.

### Vujahday Script → `Vujahday48Bold.h`

- **Source:** https://github.com/googlefonts/vujahday
- **Copyright:** Copyright 2003 The Vujahday Script Project Authors
  (https://github.com/googlefonts/vujahday)
- **Changes:** converted to a 48 px bitmap font (Latin-1 + euro sign), strokes
  thickened by 1 pixel.
- **Reserved Font Name:** none.

### Audiowide → `BadgeWide25.h`

- **Original font:** Audiowide, designed by Brian J. Bonislawsky / Astigmatic (AOETI)
- **Copyright:** Copyright (c) 2012 by Brian J. Bonislawsky DBA Astigmatic (AOETI)
  (astigma@astigmatic.com), with Reserved Font Name "Audiowide".
- **Changes:** converted to a 25 px bitmap font (Latin-1 + euro sign).
- **Reserved Font Name:** because "Audiowide" is a Reserved Font Name, this modified
  version is named **BadgeWide25** and does not use the name Audiowide. It is not
  endorsed by the original author.

### License text (applies to both fonts above)

```
Copyright 2003 The Vujahday Script Project Authors (https://github.com/googlefonts/vujahday)
Copyright (c) 2012 by Brian J. Bonislawsky DBA Astigmatic (AOETI) (astigma@astigmatic.com),
with Reserved Font Name "Audiowide".

This Font Software is licensed under the SIL Open Font License, Version 1.1.
This license is copied below, and is also available with a FAQ at:
https://openfontlicense.org


-----------------------------------------------------------
SIL OPEN FONT LICENSE Version 1.1 - 26 February 2007
-----------------------------------------------------------

PREAMBLE
The goals of the Open Font License (OFL) are to stimulate worldwide
development of collaborative font projects, to support the font creation
efforts of academic and linguistic communities, and to provide a free and
open framework in which fonts may be shared and improved in partnership
with others.

The OFL allows the licensed fonts to be used, studied, modified and
redistributed freely as long as they are not sold by themselves. The
fonts, including any derivative works, can be bundled, embedded, 
redistributed and/or sold with any software provided that any reserved
names are not used by derivative works. The fonts and derivatives,
however, cannot be released under any other type of license. The
requirement for fonts to remain under this license does not apply
to any document created using the fonts or their derivatives.

DEFINITIONS
"Font Software" refers to the set of files released by the Copyright
Holder(s) under this license and clearly marked as such. This may
include source files, build scripts and documentation.

"Reserved Font Name" refers to any names specified as such after the
copyright statement(s).

"Original Version" refers to the collection of Font Software components as
distributed by the Copyright Holder(s).

"Modified Version" refers to any derivative made by adding to, deleting,
or substituting -- in part or in whole -- any of the components of the
Original Version, by changing formats or by porting the Font Software to a
new environment.

"Author" refers to any designer, engineer, programmer, technical
writer or other person who contributed to the Font Software.

PERMISSION & CONDITIONS
Permission is hereby granted, free of charge, to any person obtaining
a copy of the Font Software, to use, study, copy, merge, embed, modify,
redistribute, and sell modified and unmodified copies of the Font
Software, subject to the following conditions:

1) Neither the Font Software nor any of its individual components,
in Original or Modified Versions, may be sold by itself.

2) Original or Modified Versions of the Font Software may be bundled,
redistributed and/or sold with any software, provided that each copy
contains the above copyright notice and this license. These can be
included either as stand-alone text files, human-readable headers or
in the appropriate machine-readable metadata fields within text or
binary files as long as those fields can be easily viewed by the user.

3) No Modified Version of the Font Software may use the Reserved Font
Name(s) unless explicit written permission is granted by the corresponding
Copyright Holder. This restriction only applies to the primary font name as
presented to the users.

4) The name(s) of the Copyright Holder(s) or the Author(s) of the Font
Software shall not be used to promote, endorse or advertise any
Modified Version, except to acknowledge the contribution(s) of the
Copyright Holder(s) and the Author(s) or with their explicit written
permission.

5) The Font Software, modified or unmodified, in part or in whole,
must be distributed entirely under this license, and must not be
distributed under any other license. The requirement for fonts to
remain under this license does not apply to any document created
using the Font Software.

TERMINATION
This license becomes null and void if any of the above conditions are
not met.

DISCLAIMER
THE FONT SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT
OF COPYRIGHT, PATENT, TRADEMARK, OR OTHER RIGHT. IN NO EVENT SHALL THE
COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
INCLUDING ANY GENERAL, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL
DAMAGES, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF THE USE OR INABILITY TO USE THE FONT SOFTWARE OR FROM
OTHER DEALINGS IN THE FONT SOFTWARE.
```

## Dependencies that are not included in this repository

These are installed separately when setting up the Arduino IDE / build environment,
are not redistributed here, and are governed by their own licenses:

- **Pervasive Displays Library Suite** – `PDLS_Common`, `PDLS_Basic`,
  `Pervasive_BWRY_Small` (Basic edition: CC BY-SA 4.0; see the libraries' own files).
  Note: this project expects the accessor `Screen_EPD::getFrameBufferAddr()`, which is
  not part of the original library; see the README for how to add it.
- **Python packages used by the scripts** – Pillow, NumPy, SciPy, fontTools
  (installed with pip; each under its own permissive license).
