Gap = 0.2;
$fn = 72;

RodToMotorCoupling(true);

// TODO: rename to RodCoupling. Parameter indicates whether we couple to motor or bearing
module RodToMotorCoupling(motorConnection) {
    Padding = 3.0;
    
    // Determine what kind of "bearing" this is
    // This is related to the motor. Probably the outside of the total shaft
    BearingDiameter = 20.0;
    BearingHeight = 14.0;

    // And that's for the actual bearing
    // BearingDiameter = 8;
    // BearingHeight = 12;
        
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

    TotalShaftHeight = motorConnection ? ShaftHeight + MiddleInnerHeight : BearingHeight;
    TotalShaftRadius = motorConnection ? SocketRadius : BearingRadius;

    union () {
        // Part which wraps around the motor
        difference() {
            cylinder(r=TotalShaftRadius, h = TotalShaftHeight);

            // When connecting to the motor, hollow out the shaft and a guide screw
            if (motorConnection)
            {
                translate([0,TotalShaftRadius,GuideHeight])
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
        }

        // Connection between the two parts
        translate([0,0,TotalShaftHeight])
            difference() {
                // Outside connection
                cylinder(r1=TotalShaftRadius, r2= TopRadius, h = MiddleHeight);
                // hollow dome with 45 degree roof
                translate([0,0,Gap])
                    cylinder(r=StopperDiameter / 2, h = StopperHeight);
            }
        
        // Part which hosts the hex stopper
        translate([0,0, TotalShaftHeight + MiddleHeight])
            difference() {
                cylinder(r=TopRadius, h = TopHeight);

                translate([0,0,0])
                    cylinder(r = HexRadius + Gap, h = TopHeight + Gap, $fn = 6);
            }
    }
}
