$fn=100;

H=10;
W=H*1.5;
e=4;

module cote()
{
    difference()
    {
    union()
    {
    cube([e,H,H]);
    translate([0,H/2,H]) rotate([0,90,0]) cylinder(d=H,h=e);
    };
    
     translate([-1,H/2,H]) rotate([0,90,0]) cylinder(d=3.6,h=e+2);
    
}
}

cote();
translate([0,0,e])  rotate([0,90,0]) cote();