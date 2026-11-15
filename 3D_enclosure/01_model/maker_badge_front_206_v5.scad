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


// top part (badge front) - includes glass, slide into the base
//      bottom - 0 layers: 0mm + glass 1mm + 5 layers on top 1mm = 2mm
// lower part (badge backside): 2 layers bottom 0.4mm + 1.4mm display = 1.8mm
//
// total = 3.8mm thick
//
difference() {
  union() {
      // front plate
      color("#ffffff") translate([0, 0, top_T/2])    
      cuboid([top_W, top_L, top_T], rounding=1.8,
        edges=[TOP+FRONT, TOP+RIGHT, TOP+BACK, TOP+LEFT, FRONT+LEFT, FRONT+RIGHT, BACK+LEFT, BACK+RIGHT]);

      color("#ff0000") translate([0, base_L/2 - font_H/2 - fontSmall_H - 3.5 - 3, top_T + font_extr/2])    
      linear_extrude(height = font_extr, center = true, convexity = 10, twist = 0)
      rotate([0, 0, 180])
      text("SALZBURG", font = "Audiowide", size = font_H, valign = "center", halign = "center");

      color("#ff0000") translate([0, base_L/2 - fontSmall_H/2 - 3.5, top_T + font_extr/2])    
      linear_extrude(height = font_extr, center = true, convexity = 10, twist = 0)
      rotate([0, 0, 180])
      text("2026", font = "Audiowide", size = fontSmall_H, valign = "center", halign = "center");
  }       
  
  // display viewing area - smaller than the display body!!!
  translate([0, -eInk_W/2 + eInk_view_W/2 + 3.75 - 3/2, top_T + 1/2])     // -3/2 is extra space around viewing area
  hull() {
      cube([eInk_view_L+2, eInk_view_W+2, 1], center = true);
      translate([0, 0, -1])
      cube([eInk_view_L, eInk_view_W, 1], center = true);
  }
   
  // window holding inner shoulder; window is 5mm larger than the view area, on each side
  translate([0, -eInk_W/2 + eInk_view_W/2 + 2.75, glass_T/2])
    cube([glass_L, glass_W, glass_T], center = true);
       
  // corner cutouts for hanging; extra +1 comes from offset +1
  translate([-top_W/2 + 3 + 1, -top_L/2 + 3 + 1, top_T/2])    
   linear_extrude(height = top_T, center = true, convexity = 10, twist = 0)
    offset(r=+1)
      polygon([[0,0],[5,0],[0,5]]);

  translate([top_W/2 - 3 - 1, top_L/2 - 3 - 1, top_T/2])    
   linear_extrude(height = top_T, center = true, convexity = 10, twist = 0)
    offset(r=+1)
      polygon([[0,0],[-5,0],[0,-5]]);

  translate([top_W/2 - 3 - 1, -top_L/2 + 3 + 1, top_T/2])    
   linear_extrude(height = top_T, center = true, convexity = 10, twist = 0)
    offset(r=+1)
      polygon([[0,0],[-5,0],[0,5]]);

  // single hanging hole on long edge
  translate([top_W/2 - 3 -2 -1, -10/2, top_T/2])
  linear_extrude(height = top_T, center = true, convexity = 10, twist = 0)
  offset(r=+1)
  polygon([[0,0],[2,0],[2,10],[0,10]]);
  
  // on short edge
  translate([-10/2, -top_L/2 + 3 +2 -1, top_T/2])
  linear_extrude(height = top_T, center = true, convexity = 10, twist = 0)
  offset(r=+1)
  polygon([[0,0],[10,0],[10,2],[0,2]]);  
  
  // dove tail lock
  translate([top_W/2 - 6, 0, 0]) mirror([0, 1, 0])
    dovetail(-top_L/2 + wall, top_L, grow = clr);
  translate([-top_W/2 + 6, 0, 0]) mirror([0, 1, 0])
    dovetail(-top_L/2 + wall, top_L, grow = clr);
    
//  // sphere lock
//  translate([top_W/2 - 15, -top_L/2 + 5, -0.4])    
//    sphere(r=1.8);
}
