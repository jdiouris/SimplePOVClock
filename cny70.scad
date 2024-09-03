W=20;
Hc=23;
H=Hc+5;
e=2;
w=2.54;
$fn=100;
difference()
{
    union()
    {
    cube([W,H,e]);
    cube([W,5,10]);
    }
    // Cny70
    translate([W/2-w/2,Hc+w/2,-1]) cylinder(d=1.5,h=10);
    translate([W/2+w/2,Hc+w/2,-1]) cylinder(d=1.5,h=10);
    translate([W/2-w/2,Hc-w/2,-1]) cylinder(d=1.5,h=10);
    translate([W/2+w/2,Hc-w/2,-1]) cylinder(d=1.5,h=10);
    // resistance
     translate([3,Hc,-1]) cylinder(d=1.5,h=10);
    translate([3,Hc-3*w,-1]) cylinder(d=1.5,h=10);
    // resistance
     translate([W-3,Hc,-1]) cylinder(d=1.5,h=10);
    translate([W-3,Hc-3*w,-1]) cylinder(d=1.5,h=10);
    // vis
    translate([3,-1,5]) rotate([-90,0,0]) cylinder(d=2.5,h=10);
     translate([W-3,-1,5]) rotate([-90,0,0]) cylinder(d=2.5,h=10);
    // passage
    translate([W/2-3,-1,-1]) cube([6,10,30]);
    
}