$fn=100;
evis=16;

D=100;
e=2;



difference()
{
    cylinder(h=e,d=D);
    translate([-evis/2,0,-1]) cylinder(d=3.6,h=10);
    translate([+evis/2,0,-1]) cylinder(d=3.6,h=10);
    translate([0,-evis/2,-1]) cylinder(d=3.6,h=10);
    translate([0,+evis/2,-1]) cylinder(d=3.6,h=10);
     
    translate([15,-2,-1]) cube([30,4,10]);
    // translate([D/2-3,0,-1]) cylinder(h=10,d=5);
}
