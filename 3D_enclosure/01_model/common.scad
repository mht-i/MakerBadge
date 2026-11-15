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


$fa = 1;
$fs = 0.4;


// dimensions for MakerBadge
base_L = 85;
base_W = 55;
base_T = 3;
corner_R = 3;

top_L = 85;
top_W = 55;
top_T = 2;
btm_L = 85;
btm_W = 55;
btm_T = 1.8;

// eInk display dimensions, rounded up to next integer; display type E2206xxx
eInk_L = 30;
eInk_W = 58.4;
eInk_T = 1.4;
fpc_W = 18;
fpc_L = 8;
fpc_T = eInk_T;
//eInk_view_L = 24;
//eInk_view_W = 47;
eInk_view_L = 24 + 1.2;   // add +1.2mm extra space around the viewing area; this is 0.6 on each side!
eInk_view_W = 47 + 1.2;

font_H = 6;
fontSmall_H = 5;
font_extr = 0.4;

//glass_L = eInk_view_L+10;       // larger than view window!!!
//glass_W = eInk_view_W+10;
glass_L = eInk_view_L -1.2 + 10;       // larger than view window!!! -1.2mm to compensate for extra space around viewing area
glass_W = eInk_view_W -1.2 + 10;
glass_T = 1;


// #################  dove tail lock ######################
card_l = 85;   // length = sliding direction (Y)
card_w = 55;   // width (X)
t      = 2;    // plate thickness
rail_h = 1;    // dovetail height (must be less than t)
neck_w = 2;   // rail width at its narrow base
angle  = 45;   // flank angle from vertical (keep <= 45 for support-free printing)
//clr    = 0.2;  // clearance per side: 0.15 - 0.25 is typical, tune to your printer
clr    = 0.25; // clearance per side: 0.15 - 0.25 is typical, tune to your printer
wall   = 3;    // closed end of the groove = stop, so B ends up flush when closed

$fn = 40;

// Trapezoid cross-section: narrow at the base, wider at the tip
module profile() {
    tip = neck_w + 2 * rail_h * tan(angle);
    polygon([[-neck_w/2, 0], [neck_w/2, 0], [tip/2, rail_h], [-tip/2, rail_h]]);
}

// Profile extruded along +Y from y0 to y0+len, standing on z=0 and pointing up.
// grow > 0 enlarges the profile evenly (used for the groove clearance).
module dovetail(y0, len, grow = 0) {
    translate([0, y0 + len, 0]) rotate([90, 0, 0])
        linear_extrude(height = len) offset(delta = grow) profile();
}


// #################  dove tail lock ######################
