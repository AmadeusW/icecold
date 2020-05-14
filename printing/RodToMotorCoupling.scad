Gap = 0.2;
$fn = 72;

RodToMotorCoupling();

module RodToMotorCoupling() {
    Padding = 3.0;
    
    BearingDiameter = 20.0;
    BearingHeight = 14.0;
        
    HexFlatDiameter = 12.60;
    HexRadius = HexFlatDiameter/(2 * cos(30));
    HexHeight = 4.50;
    StopperDiameter = 12.50;
    StopperHeight = 2.75;

    TopRadius = HexRadius + Padding;
    TopHeight = HexHeight + StopperHeight;
    
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
            difference() {
                cylinder(r1=SocketRadius, r2= TopRadius, h = MiddleHeight);
                translate([0,0,Gap])
                    cylinder(r=StopperDiameter / 2, h = StopperHeight);
            }
        
        // Fit in the bearing
        translate([0,0, ShaftHeight + MiddleInnerHeight + MiddleHeight])
            difference() {
                cylinder(r=TopRadius, h = TopHeight);

                translate([0,0,0])
                    cylinder(r = HexRadius + Gap, h = TopHeight + Gap, $fn = 6);
            }
    }
}
