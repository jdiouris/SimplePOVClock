Dm=24.2;
eh=10;
H=70;
e=4;

$fn=100;

piece=3;

module sup()
{
difference()
{
    union()
    {
        cylinder(d=Dm+2*e,h=eh);
        translate([-25,-6/2,0]) cube([50,6,eh]);
    }
    translate([0,0,-1]) cylinder(d=Dm,h=eh+2);
    // Vis moteur
    translate([-20,-5,eh/2]) rotate([-90,0,0]) cylinder(h=10,d=3.6);
    translate([+20,-5,eh/2]) rotate([-90,0,0]) cylinder(h=10,d=3.6);
    
}
// pied
difference()
{
translate([-eh/2,Dm/2+e/2,0])  cube([eh,H-Dm/2-e/2,eh]);
    // vis attaches coupelles
    translate([0,20,0])  cylinder(h=20,d=2);
    translate([0,40,0])  cylinder(h=20,d=2);
}
difference()
{
    translate([-30,H-e,0])  cube([60,e,eh]);
    // Vis pied
    translate([-25,0,eh/2]) rotate([-90,0,0]) cylinder(h=100,d=3.6);
    translate([+25,0,eh/2]) rotate([-90,0,0]) cylinder(h=100,d=3.6);
}


}

module pied3()
{
  // 3ème pied
difference()
{
    union()
    {
    translate([-eh/2,H-e,0])  cube([eh,e,40]);
    translate([-eh/2,Dm/2+e/2,0])  cube([eh,60-e,e]);    
    }
    translate([0,H-5,37]) rotate([-90,0,0]) cylinder(h=100,d=3.6);
    translate([0,20,0])  cylinder(h=20,d=3);
    translate([0,40,0])  cylinder(h=20,d=3);
}  
translate([-eh/2,47.5,0]) rotate([45,0,0]) cube([eh,30,e]);
}

if (piece==2)
{
difference()
{
    sup();
    translate([-50,0,-1]) cube([100,100,100]);
}
}
if (piece==1)
{
difference()
{
    sup();
    translate([-50,-100,-1]) cube([100,100,100]);
}
}
if (piece==3)
{
        pied3();
}