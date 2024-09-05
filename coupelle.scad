Dm=26;
D2=100;
D1=60;
e=2;
Dled=10.6;
H=20;

$fn=100;

module anneau(D,e,H)
{
    difference()
    {
        cylinder(h=H,d=D);
    
    // trou moteur
    translate([0,0,-1]) cylinder(h=H+2,d=D-2*e);
    }
}

difference()
{
    union()
    {
    cylinder(h=e,d=D2);
    anneau(D2,2,H);
    anneau(D1,2,H);
    }
    
    // trou moteur
    translate([0,0,-1]) cylinder(h=e+2,d=Dm);
    translate([-20,0,-1]) cylinder(h=e+2,d=3.6);
    translate([+20,0,-1]) cylinder(h=e+2,d=3.6);
    translate([-40,0,-1]) cylinder(h=e+2,d=3.6);
    // trou capteur
    //translate([-D2/2-5,-3.5,H-10]) cube([10,7,20]);
    
    // Leds
    r1=(D1+D2)/4;
    for (a=[0:60:359])
        translate([r1*cos(a+30),r1*sin(a+30),-1]) cylinder(h=e+2,d=Dled);
    r2=(D1+Dm)/4;
    for (b=[0:90:359])
        translate([r2*cos(b+45),r2*sin(b+45),-1]) cylinder(h=e+2,d=Dled);
    
}
