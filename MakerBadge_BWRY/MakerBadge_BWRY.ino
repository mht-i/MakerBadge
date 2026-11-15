/*
 * Maker Badge - created for Maker Faire Salzburg 2026
 * Copyright (c) 2026 Mihai T. 
 *
 * Description:
 *    Educational Arduino project - e-Ink (ePaper) badge for Maker Faire, usable as digital business card. 
 *
 *
 * SPDX-License-Identifier: MIT
 * See LICENSE file in the project root for full license text.
 *
 */


#include "PDLS_Common.h"
#include "Pervasive_BWRY_Small.h"     // Driver
#include "PDLS_Basic.h"               // Screen



// select your badge template
#define TEMPLATE_MAKERFAIRE_LOGO      1     // img is 128 x 128 on the right side => 128 x 128 empty area for text & QR code
#define TEMPLATE_INVENTOR             2     // img is 100 x 128 on the left side => 147 x 128 empty area for text and QR code
#define TEMPLATE_MAD_SCIENTIST        3     // img is 123 x 128 on the left side => 124X x 128Y empty area for text and QR code

// ------------------- SELECT YOUR BADGE BACGROUND ---------------------------------
//
#define BADGE_TEMPLATE      TEMPLATE_MAKERFAIRE_LOGO
//
// ---------------------------------------------------------------------------------

// ------------------- ADD YOUR NAME & Title ---------------------------------------
//
const char *name = "Mihai";
const char *title ="Maker";
//
// ---------------------------------------------------------------------------------

// ------------------- ADD YOUR details --------------------------------------------
// VCARD string - usually keep a "proven" string array as a backup (commented); if somethign goes wrong during 
// string adaptation, simply start over with a new copy of the commented string.
//
// the character ; is a field separator - keep it! for empty fields, there will be a sequence of ;;; characters
//
// const char vcardStr[] = "BEGIN:vCard\r\n"                                             // for MHT vCard - ~256 chars
//                             "VERSION:3.0\r\n"
//                             "FN:Mihai T.\r\n"                                         // add complete name here
//                             "N:T.;Mihai;;Dipl. Ing.;\r\n"                             // add family name; given name; middle name; titles prefixes; titles suffixes
//                             "ORG:MHT instruments e.U.\r\n"                            // organization/comapny
// /*                            "Title:True Maker\r\n"           if added, might need to increase QR code version to 11 */
//                             "TEL;TYPE=VOICE,MSG,WORK:+436766834953\r\n"               // phone number
//                             "EMAIL;TYPE=INTERNET,PREF:mht@mht-instruments.at\r\n"     // email address
//                             "URL:https://www.mht-instruments.at\r\n"                  // URL website...
//                         "END:vCard\r\n";
const char vcardStr[] = "BEGIN:vCard\r\n"                                             // for MHT vCard - ~256 chars
                            "VERSION:3.0\r\n"
                            "FN:Mihai T.\r\n"                                         // add complete name here
                            "N:T.;Mihai;;Dipl. Ing.;\r\n"                             // add family name; given name; middle name; titles prefixes; titles suffixes
                            "ORG:MHT instruments e.U.\r\n"                            // organization/comapny
/*                            "Title:True Maker\r\n"           if added, might need to increase QR code version to 11 */
                            "TEL;TYPE=VOICE,MSG,WORK:+436766834953\r\n"               // phone number
                            "EMAIL;TYPE=INTERNET,PREF:mht@mht-instruments.at\r\n"     // email address
                            "URL:https://www.mht-instruments.at\r\n"                  // URL website...
                        "END:vCard\r\n";





// QR Code capacity of data codewords per version and error correction level, and whether the data fits (green/red background):
// Version	ECC L	ECC M	ECC Q	ECC H
// 1	19	16	13	9  --> start dimension 21 x 21 modules, each version adds 4 modules/side; first number is the capacity with weakest err correction
// 2	34	28	22	16 --> 25 x 25
// 3	55	44	34	26 --> 29 x 29
// 4	80	64	48	36 --> 33 x 33
// 5	108	86	62	46 --> 37 x 37
// 6	136	108	76	60 --> 41 x 41
// 7	156	124	88	66 --> 45 x 45
// 8	194	154	110	86 --> 49 x 49 
// 9	232	182	132	100 --> 53 x 53
// 10	274	216	154	122 --> 57 x 57
// 11	324	254	180	140 --> 61 x 61
// 12	370	290	206	158
// 13	428	334	244	180
// 14	461	365	261	197
// 15	523	415	295	223
// 16	589	453	325	253
// 17	647	507	367	283
// 18	721	563	397	313
// 19	795	627	445	341
// 20	861	669	485	385
// 21	932	714	512	406
// 22	1006	782	568	442
// 23	1094	860	614	464
// 24	1174	914	664	514
// 25	1276	1000	718	538
// 26	1370	1062	754	596
// 27	1468	1128	808	628
// 28	1531	1193	871	661
// 29	1631	1267	911	701
// 30	1735	1373	985	745
// 31	1843	1455	1033	793
// 32	1955	1541	1115	845
// 33	2071	1631	1171	901
// 34	2191	1725	1231	961
// 35	2306	1812	1286	986
// 36	2434	1914	1354	1054
// 37	2566	1992	1426	1096
// 38	2702	2102	1502	1142
// 39	2812	2216	1582	1222
// 40	2956	2334	1666	1276
//
// ---------------------------------------------------------------------------------


#if BADGE_TEMPLATE == TEMPLATE_MAKERFAIRE_LOGO
  #include "tmpl_1.h"
#elif BADGE_TEMPLATE == TEMPLATE_INVENTOR
  #include "tmpl_3.h"
#else
  #include "tmpl_4.h"
#endif


#include "Vujahday48Bold.h"             // this header includes drawText.h too
#include "BadgeWide25.h"

#if (SCREEN_EPD_RELEASE < 902)
#error Required SCREEN_EPD_RELEASE 902
#endif // SCREEN_EPD_RELEASE

#define SCRN 206                        // update this number to reflect the display used

#include <cstdint>
#include "qrcode.h"           // library by Richard Moore; https://github.com/ricmoo/qrcode/; encodes a string into a QR code; no rendering



// Driver
Pervasive_BWRY_Small myDriver(eScreen_EPD_206_QS_06, boardXIAO_nRF52840);

// Screen
Screen_EPD myScreen(&myDriver);

long randomNo;

/*
 * @brief Add name to the yellow rectangle and "title" to the red rectangle. Assumes 128 pixels available 
 * horizontally for the text. The routine attempls placing the text centered in the rectangle. If the text 
 * is too long, it will overflow or overwrite the logo/image. 
 *
 * @param xOffset top left horizontal coordinate of the yellow rectangle
 * @param yOffsetName top left vertical coordinate of the yellow rectangle
 * @param yOffsetTitle top left vertical coordinate of the red rectangle
 * @param fntName font to be used for the name
 * @param fntTitle font to be used for the title   
 *
 */ 
void _addNameAndTitle(uint8_t xOffset, uint8_t yOffsetName, uint8_t yOffsetTitle, const GFXfont *fntName, const GFXfont *fntTitle) {
  uint16_t txtLen = textWidth(name, fntName);
  if (128 > txtLen) {
    drawText(myScreen, xOffset + ((128 - txtLen)/2), yOffsetName, name, myColours.black, fntName);
  } else {
    drawText(myScreen, xOffset, yOffsetName, name, myColours.black, fntName);
  }
  
  // print "job"
  txtLen =  textWidth(title, fntTitle);
  if (128 > txtLen) {
    drawText(myScreen, xOffset + ((128 - txtLen)/2), yOffsetTitle, title, myColours.white, fntTitle);
  } else {
    drawText(myScreen, xOffset, yOffsetTitle, title, myColours.white, fntTitle);
  }
}


/*
 * @brief Add QR code at the specified position. QR code must be initialized when this function is called. 
 *
 * @param _x top left horizontal coordinate of the QR code top left corner
 * @param _y top left vertical coordinate of the QR code top left corner
 *
 */ 
void _addQRcode(uint8_t _x, uint8_t _y, QRCode qrcode) {
    uint8_t x, y;
    for (y = 0; y < qrcode.size; y++) {
        for (x = 0; x < qrcode.size; x++) {
            qrcode_getModule(&qrcode, x, y) ? myScreen.point(_x+x, _y+y, myColours.black): myScreen.point(_x+x, _y+y, myColours.white);
        }
    }
}

///
/// @brief Setup
///
void setup() {
    // Serial.begin(115200);    open by hV_HAL_begin(); call below
    // while (!Serial) { }     // optional: wait for USB serial 
    hV_HAL_begin(); // with Serial at 115200; hV_HAL_Serial = Serial by default, otherwise edit hV_HAL_Peripherals.h

    myScreen.begin();
    myScreen.setOrientation(ORIENTATION_LANDSCAPE);
    myScreen.clear();
    memcpy(myScreen.getFrameBufferAddr(), tmpl_bkgrd, TMPL_BKGRD_SIZE);     // copy template
 
    // Create the QR code
    QRCode qrcode;
    uint8_t qrcodeData[qrcode_getBufferSize(10)];      // argument is the version of QR code - see above
    qrcode_initText(&qrcode, qrcodeData, 10, 0, vcardStr);

#if BADGE_TEMPLATE == TEMPLATE_MAKERFAIRE_LOGO
  // img is 128 x 128 on the right side => 128 x 128 empty area for text & QR code on the LEFT side!
  // red & yellow rectangles already in place, as part of the background
  _addNameAndTitle(1, 1, 36, &Vujahday48Bold, &BadgeWide25);  
  _addQRcode(35, 68, qrcode);
#elif BADGE_TEMPLATE == TEMPLATE_INVENTOR
  // img is 100 x 128 on the left side => 147 x 128 empty area for text and QR code
  myScreen.setPenSolid(true);                                         // filled rectangle       
  myScreen.rectangle(101, 1, 247, 36, myColours.yellow);              // add yellow rectangle
  myScreen.rectangle(101, 37, 247, 62, myColours.red);                // add red rectangle

  _addNameAndTitle(101, 1, 38, &Vujahday48Bold, &BadgeWide25);  
  _addQRcode(101+45, 68, qrcode);
#else
  // img is 123 x 128 on the left side => 124X x 128Y empty area for text and QR code
  myScreen.setPenSolid(true);                                     // filled rectangle
  myScreen.rectangle(124, 1, 247, 36, myColours.yellow);          // add yellow rectangle
  myScreen.rectangle(124, 37, 247, 62, myColours.red);            // add red rectangle

  _addNameAndTitle(124, 1, 38, &Vujahday48Bold, &BadgeWide25);  
  _addQRcode(124+35, 68, qrcode);
#endif

  myScreen.flushFast();           // update screen - transfer the framebuffer to screen

  pinMode(LED_GREEN, OUTPUT); digitalWrite(LED_GREEN, HIGH);   // LED off
  pinMode(LED_BLUE, OUTPUT);  digitalWrite(LED_BLUE, HIGH);    // LED off
  pinMode(LED_RED, OUTPUT);   digitalWrite(LED_RED, HIGH);     // LED off

//    hV_HAL_exit();
}

///
/// @brief Main loop - blink randomly to indicate the system is running (and not blocked or crashed)
///
void loop() {
    randomNo = random(2, 12);          // randomn number of seconds to wait till next blink; min 2s - max 12s
    // Serial.println(randomNo);

    // if odd number -> blink green
    // if even number -> blink blue
    // if multiple of 3 -> blink red

    if (0 == randomNo % 3) {
      digitalWrite(LED_RED, LOW);
      delay(50);                      // short blink
      digitalWrite(LED_RED, HIGH);   
    }
    else if (randomNo & 0x01) {
      digitalWrite(LED_GREEN, LOW);
      delay(50);                      // short blink
      digitalWrite(LED_GREEN, HIGH);   
    }
    else {
      digitalWrite(LED_BLUE, LOW);
      delay(50);                      // short blink
      digitalWrite(LED_BLUE, HIGH);   
    }

    delay(randomNo * 1000);
}
