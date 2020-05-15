Gap = 0.2;
$fn = 72;

RodCoupling(false);

// When parameter is true, we couple the rod to the motor
// When parameter is false, we couple the rod to a bearing
module RodCoupling(motorConnection) {
    Padding = 3.0;

    // Motor coupling properties
    ShaftDiameter = 8.2;
    ShaftHeight = 35.0;

    GuideHeight = 6.0;
    GuideDiameter = 2.8;

    // Bearing coupling properties
    BearingDiameter = 8;
    BearingHeight = 12;
    
    // Rod coupling properties
    HexFlatDiameter = 12.60;
    HexHeight = 4.50;
    StopperDiameter = 12.50;
    StopperHeight = 2.75;

    // Calculations
    HexRadius = HexFlatDiameter/(2 * cos(30));

    GuideRadius = GuideDiameter / 2;
    ShaftRadius = ShaftDiameter / 2;
    TopRadius = HexRadius + Padding;
    TopHeight = HexHeight + StopperHeight;
    MiddleInnerHeight = ShaftRadius + Gap; // ensure angle of 45 degrees on the inner wall
    BottomRadius = motorConnection ? (ShaftDiameter / 2 + Padding) : BearingDiameter / 2;
    BottomHeight = motorConnection ? ShaftHeight + MiddleInnerHeight : BearingHeight;
    MiddleHeight = TopRadius - BottomRadius; // ensure angle of 45 degrees on the outer wall

    union () {
        // Part which wraps around the motor
        difference() {
            cylinder(r=BottomRadius, h = BottomHeight);

            // When connecting to the motor, hollow out the shaft and a guide screw
            if (motorConnection)
            {
                translate([0,BottomRadius,GuideHeight])
                    rotate([90,0,0])
                        cylinder(r=GuideRadius + Gap, h = BottomRadius * 2);

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
        translate([0,0,BottomHeight])
            difference() {
                // Outside connection
                cylinder(r1=BottomRadius, r2= TopRadius, h = MiddleHeight);

                // hollow dome with 45 degree roof
                translate([0,0,MiddleHeight - StopperHeight + Gap])
                    cylinder(r=StopperDiameter / 2, h = StopperHeight);
            }
        
        // Part which hosts the hex stopper
        translate([0,0, BottomHeight + MiddleHeight])
            difference() {
                cylinder(r=TopRadius, h = TopHeight);

                translate([0,0,0])
                    cylinder(r = HexRadius + Gap, h = TopHeight + Gap, $fn = 6);
            }
    }
}
