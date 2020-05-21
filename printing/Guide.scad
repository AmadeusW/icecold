Gap = 0.2;
$fn = 72;

Guide(false);

module Guide(extraClearance) {
    Padding = 3.0;
    SupportThickness = 8.0;

    HexFlatDiameter = 12.45;
    HexRadius = HexFlatDiameter/(2 * cos(30));
    HexThickness = 6.65;

    MountOffset = 22;
    ThreadRodDiameter = 8.1;

    BoltDiameter = 4.85;
    BoltSeparation = 36.4;
    BoltHeadDiameter = 9.0; // The standard indicates 8mm for 5mm screws
    
    Depth = HexThickness + 2*SupportThickness;
    RodOffset = 15; // This is arbitrary, distance from rod to where we mount the bar
    ToTheSky = 100;

    // Measurement of the outside of the channel is 16.5 and 12.37 inside
    // that's 3.2mm for two walls. Add it to smaller value or subtract from larger to get the width
    ChannelWidth = 14.45;
    // Height from the frame to the top of the channel
    ChannelHeight = 12.90; // From the frame to the top of the channel
    // How much into channel we're going. It doesn't have to be deep
    DepthIntoChannel = 6.0;
    // How thick is the channel wall
    ChannelThickness = 2.3;

    BoltRadius = BoltDiameter / 2;
    Width = BoltSeparation + 2*BoltRadius + 2*Padding;
    WidthWithoutBolts = BoltSeparation - 2*BoltHeadDiameter;

    // Additional support for 45 degree angle
    WidthAroundChannel = ChannelWidth + 3*Padding;
    HeightOfSupport = (WidthAroundChannel - WidthWithoutBolts) * 2;

    // Calculate the center of the rod
    // Use the same values as FrameToMotorAdapter
    MotorRadius = 26.0;
    HeadHeight = 4.5 + Gap;
    ThreadHeight = 2.0;
    FrameAdapterHeight = ThreadHeight + HeadHeight;
    CenterOfTheRod = MotorRadius + FrameAdapterHeight;
    // Note that the object sits at Z=0
    // and RodOffset looking from Z=0 equals CenterOfTheRod from Z=max
    // this is where the channel starts
    ZMax = RodOffset + CenterOfTheRod;
    ChannelOffset = ZMax - ChannelHeight;
    // Allow clearance of 8mm, which is the distance from frame to a hex head holding the channel is 8mm
    Height = ChannelOffset + DepthIntoChannel;

    echo(str("Rod center:", RodOffset));
    echo(str("Furthest reach:", Height));
    echo(str("Distance between rod center and furthest reach:", Height - RodOffset));

    difference() {
        // Main body
        union() {
            translate([0, 0, 0])
                scale([Width/2 + Padding, Depth/2, 1]) {
                    cylinder(r = 1, h = SupportThickness);
                }
            translate([0, 0, Height/2])
                cube([WidthWithoutBolts, Depth, Height], center = true);

            translate([0, 0, ZMax - ChannelHeight + (DepthIntoChannel - Padding)/2])
                cube([WidthAroundChannel, Depth, DepthIntoChannel + Padding], center = true);

            // 45 degree angle connector
            rotate([90, 0, 0])
            translate([0, Height - DepthIntoChannel - Padding - HeightOfSupport, 0])
                linear_extrude(height = Depth, center = true)
                    polygon(points = [
                    [-WidthAroundChannel/2, HeightOfSupport],
                    [WidthAroundChannel/2, HeightOfSupport],
                    [WidthWithoutBolts/2, 0],
                    [-WidthWithoutBolts/2, 0],
                    ]);
        }

        // Bolts for mounting the bearing
        union() {
            translate([BoltSeparation / 2, 0, SupportThickness/2])
                hull()
                {
                    translate([-BoltRadius/2, 0, 0])
                        cylinder(r = BoltRadius + Gap, h=ToTheSky, center=true);
                    translate([BoltRadius/2, 0, 0])
                        cylinder(r = BoltRadius + Gap, h=ToTheSky, center=true);
                }
            translate([-BoltSeparation / 2, 0, SupportThickness/2])
                hull()
                {
                    translate([-BoltRadius/2, 0, 0])
                        cylinder(r = BoltRadius + Gap, h=ToTheSky, center=true);
                    translate([BoltRadius/2, 0, 0])
                        cylinder(r = BoltRadius + Gap, h=ToTheSky, center=true);
                }
        }

        // Nut which attaches to the rod
        union () {
            translate([0, 0, RodOffset + ToTheSky/2])
                // Gap*4 should make it easy to insert the nut
                cube([HexFlatDiameter+Gap, HexThickness+Gap*4, ToTheSky], center=true);
            
            translate([0, 0, RodOffset])
                rotate([90,30,0])
                    cylinder(r = HexRadius+Gap, h=HexThickness+Gap, center=true, $fn = 6);
            
            // TODO: Make the roof triangular so that there is no support
            translate([0, 0, RodOffset])
                rotate([90,0,0])
                    cylinder(r=ThreadRodDiameter/2, h = 100, center=true);

            // >45 degree roof
            rotate([90, 0, 0])
            translate([0, RodOffset, 0])
                linear_extrude(height = Depth + Gap, center = true)
                    polygon(points = [
                    [-ThreadRodDiameter/2, 0],
                    [ThreadRodDiameter/2, 0],
                    [0, ThreadRodDiameter],
                    ]);
        }

        // Channel
        union () {
            translate([ChannelWidth / 2, 0, ChannelOffset + DepthIntoChannel/2])
                cube([ChannelThickness + Gap, ToTheSky, DepthIntoChannel + Gap], center=true);
            translate([-ChannelWidth / 2, 0, ChannelOffset + DepthIntoChannel/2])
                cube([ChannelThickness + Gap, ToTheSky, DepthIntoChannel + Gap], center=true);
        }
    }
}
