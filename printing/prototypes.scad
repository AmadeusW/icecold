Gap = 0.2;
$fn = 72;

translate([-10,40,0])
    Helper(false, hide=true)
        RodToMotorCoupling();
    
intersection() {
    Helper(false, hide=false)
        Guide();
}

translate([0,-40,0])
    Helper(false, hide=true)
        RodConnect();

// If debug is set, renders a cross section of the object
module Helper(debug, hide = false) {
    if (!hide)
    {
        if (debug) {
            intersection() {
                children();
                translate([0,-100,-100])
                    cube([200,200,200]);
            }
        } else {
            children();
        }
    }
}


module Guide() {
    Thickness = 30;
    Depth = 20;

    HexFlatDiameter = 11.0;
    HexRadius = HexFlatDiameter/(2 * cos(30));
    HexThickness = 5.4;

    MountOffset = 22;
    ThreadRodDiameter = 6.7;

    GuideRodRadius = 2.75;
    MotorInnerRadius = 12.5;
    // Offset from the thread center
    GuideRodOffset = MotorInnerRadius + 1.5 + GuideRodRadius;
    
    BoltDiameter = 4.6;
    BoltSeparation = 35.0;
    
    Width = BoltSeparation + BoltDiameter + 4;

    
    difference() {
        translate([0,0,-MountOffset])
            scale([Width/2, Depth/2, 1])
                cylinder(r = 1, h = Thickness);
        union () {
            translate([0,0,50])
                cube([HexFlatDiameter+Gap, HexThickness+Gap, 100], center=true);
            
            rotate([90,30,0])
            cylinder(r = HexRadius+Gap, h=HexThickness+Gap, center=true, $fn = 6);
            
            rotate([90,0,0])
                cylinder(r=ThreadRodDiameter/2, h = 100, center=true);

            translate([0,0,-GuideRodOffset])
                rotate([90,0,0])            
                    cylinder(r=GuideRodRadius, h = 100, center = true);
            
            translate([BoltSeparation/2,0,0])
                cylinder(r=BoltDiameter/2, h=100, center=true);
            translate([-BoltSeparation/2,0,0])
                cylinder(r=BoltDiameter/2, h=100, center=true);
        }
    }
}

module RodToMotorCoupling() {
    BearingDiameter = 20.0;
    BearingHeight = 14.0;
        
    HexFlatDiameter = 11.0;
    HexRadius = HexFlatDiameter/(2 * cos(30));
    HexHeight = 8;
    
    ShaftDiameter = 8.2;
    SocketThickness = 3.0;
    ShaftHeight = 35.0;

    GuideHeight = 6.0;
    GuideDiameter = 2.8;
    
    ShaftRadius = ShaftDiameter / 2;
    SocketRadius = ShaftRadius + SocketThickness;
    SocketDiameter = SocketRadius * 2;
    BearingRadius = BearingDiameter / 2;
    MiddleHeight = BearingRadius - SocketRadius; // ensure angle of 45 degrees on the outer wall
    GuideRadius = GuideDiameter / 2;
    MiddleInnerHeight = ShaftRadius + Gap; // ensure angle of 45 degrees on the inner wall

    union () {
        // Part which wraps around the motor
        difference() {
            cylinder(r=SocketRadius, h = ShaftHeight + MiddleInnerHeight);

            translate([0,SocketRadius,GuideHeight])
                rotate([90,0,0])
                    cylinder(r=GuideRadius + Gap, h = SocketDiameter);

            translate([0,0,-1]) // -1 to Ensure the difference
                union()
                {
                    cylinder(r=ShaftRadius + Gap, h = ShaftHeight+1);
                    translate([0,0,ShaftHeight + 1])
                        cylinder(r1=ShaftRadius + Gap, r2= 0, h = MiddleInnerHeight);
                }
        }

        // Connect to the other part
        translate([0,0,ShaftHeight + MiddleInnerHeight])
            cylinder(r1=SocketRadius, r2= BearingRadius  - Gap, h = MiddleHeight);
        
        // Fit in the bearing
        translate([0,0, ShaftHeight + MiddleInnerHeight + MiddleHeight])
            difference() {
                cylinder(r=BearingRadius - Gap, h = BearingHeight);

                translate([0,0,0])
                    cylinder(r = HexRadius + Gap, h = BearingHeight + 1, $fn = 6);
            }
    }
}

// Rod: https://www.homedepot.com/p/Everbilt-1-2-in-x-36-in-Aluminum-Flat-Bar-800217/204604762
// Rod connect Bearing: https://www.amazon.com/gp/product/B00N4138LU/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
// Motor coupling bearing https://www.amazon.com/uxcell-KFL002-Aligning-Pillow-Bearing/dp/B073KTGZ1H/ref=sr_1_20?keywords=uxcell%2Bflange%2Bbearing&qid=1576645950&sr=8-20&th=1