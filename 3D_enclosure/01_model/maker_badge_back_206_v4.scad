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


use <MCAD/boxes.scad>
include <BOSL2/std.scad>
include <BOSL2/gears.scad>

include <common.scad>


// top part - includes glass, slide into the base
// bottom - 2 layers: 0.4mm + glass 1mm + 3 layers on top 0.6mm = 2mm
// lower part: 2 layers bottom 0.4mm + 1.4mm display = 1.8mm
// total = 3.8mm thick
difference() {
  // back plate + dove tail rails
  union() {
      translate([0, 0, btm_T/2])    
      cuboid([btm_W, btm_L, btm_T], rounding=1.79,
        edges=[BOTTOM+FRONT, BOTTOM+RIGHT, BOTTOM+BACK, BOTTOM+LEFT, FRONT+LEFT, FRONT+RIGHT, BACK+LEFT, BACK+RIGHT]);

      // dove tail lock
      translate([top_W/2 - 6, 0, btm_T])
        dovetail(-top_L/2, top_L - wall - clr);
      translate([-top_W/2 + 6, 0, btm_T])
        dovetail(-top_L/2, top_L - wall - clr);
  }

  // the cutout for the display
  translate([0, 0, btm_T - eInk_T/2])
    union() {
        cube([eInk_L, eInk_W, eInk_T], center = true);
        translate([0, eInk_W/2 + fpc_L/2, 0])
            cube([fpc_W, fpc_L, fpc_T], center = true);
    }
       

  // corner cutouts for hanging; extra +1 comes from offset +1
  translate([-top_W/2 + 3 + 1, -top_L/2 + 3 + 1, top_T/2])    
   linear_extrude(height = top_T + 10, center = true, convexity = 10, twist = 0)
    offset(r=+1)
      polygon([[0,0],[5,0],[0,5]]);

  translate([top_W/2 - 3 - 1, top_L/2 - 3 - 1, top_T/2])    
   linear_extrude(height = top_T + 10, center = true, convexity = 10, twist = 0)
    offset(r=+1)
      polygon([[0,0],[-5,0],[0,-5]]);

  translate([top_W/2 - 3 - 1, -top_L/2 + 3 + 1, top_T/2])    
   linear_extrude(height = top_T + 10, center = true, convexity = 10, twist = 0)
    offset(r=+1)
      polygon([[0,0],[-5,0],[0,5]]);

  // single hanging hole on long edge
  translate([top_W/2 - 3 -2 -1, -10/2, top_T/2])
  linear_extrude(height = top_T + 10, center = true, convexity = 10, twist = 0)
  offset(r=+1)
  polygon([[0,0],[2,0],[2,10],[0,10]]);
  // cut out the thin rail rest on the side of the hole
  translate([top_W/2 - 3 -2 -1, 0, btm_T + 2/2])
  cube([4, 12, 2], center = true);
  
  // on short edge
  translate([-10/2, -top_L/2 + 3 +2 -1, top_T/2])
  linear_extrude(height = top_T + 10, center = true, convexity = 10, twist = 0)
  offset(r=+1)
  polygon([[0,0],[10,0],[10,2],[0,2]]);  
  
}
