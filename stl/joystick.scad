
xoffset = -4;

module thumbstickRaw(){
    difference(){
        import("rcjoystickcase.stl");
        translate([-8,10,0])cube([14,8,70]);
    }
    }
module thumbstickL(yoffset){
translate([-20,-yoffset,25])rotate([-0,0,-90])rotate([-90,0,90]) thumbstickRaw();
};

module thumbstickR(yoffset){
translate([-20,yoffset,25])rotate([-0,0,90])rotate([-90,0,90]) thumbstickRaw();
};

module dummyblockL(yoffset){
    color("red")translate([-37.5,-19-yoffset,-10])cube([35,38,40]);
    }

module dummyblockR(yoffset){
    color("red")translate([-37.5,-19+yoffset,-10])cube([35,38,40]);
    }


module hornRaw(){
    translate([0,70,0])rotate([90,0,-90])import("Single_Controller_v2.STL");
}    

module horn(xoffset){
    difference(){
    union(){
    difference(){
        hornRaw();
        dummyblockL(xoffset);
        dummyblockR(xoffset);
    }
        thumbstickL(xoffset);
        thumbstickR(xoffset);
        color("red")translate([-40,-0.5*(yoffset+4),4.4])cube([65,yoffset+4,2]);
        color("blue")translate([-3,-0.5*(yoffset+4),5])cube([28,2,20]);
        color("blue")translate([-3,+0.5*(yoffset),5])cube([28,2,20]);
        color("green")translate([25,-0.5*(yoffset+4),4.4])cube([2,yoffset+4,20.6]);
    }
    
    color("yellow")translate([-45,-8,8])cube([80,16,11]);
    color("cyan")translate([14,-8,4])cube([9,16,11]);
    color("cyan")translate([-30,-8,4])cube([9,16,11]);
    
    for (i = [-30 : 6 : 25]){
        translate([i, 13, 0])cylinder(r=1, h=90, $fn=50);
        translate([i, -13, 0])cylinder(r=1, h=90, $fn=50);
    }
    
    }
}

yoffset = 36;
horn(yoffset);




//color("green")translate([-35,-0.5*31,10])cube([58,31,3]);

//thumbstickL(35);
//color("red")translate([-40,-20-35,-10])cube([40,40,40]);

//thumbstickR(35);
//color("red")translate([-40,-20+35,-10])cube([40,40,40]);

//thumbstickR(35);

//hornRaw();
//color("red")translate([-10,10,0])cube([20,5,70]);
//import("rcjoystickcase.stl");


