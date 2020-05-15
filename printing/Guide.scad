Gap = 0.2;
$fn = 72;

Guide();

module Guide() {
    Padding = 3.0;
    SupportThickness = 8.0;

    HexFlatDiameter = 12.45;
    HexRadius = HexFlatDiameter/(2 * cos(30));
    HexThickness = 6.65;

    MountOffset = 22;
    ThreadRodDiameter = 8.1;

    BoltDiameter = 4.85;
    BoltSeparation = 36.5;
    BoltHeadDiameter = 9.0; // The standard indicates 8mm for 5mm screws
    
    Width = BoltSeparation + 2*BoltDiameter + 2*Padding;
    WidthWithoutBolts = BoltSeparation - 2*BoltHeadDiameter;
    Depth = HexThickness + 2*SupportThickness;
    RodOffset = 20;
    ToTheSky = 50;

    // Measurement of the outside of the channel is 16.5 and 12.37 inside
    // that's 3.2mm for two walls. Add it to smaller value or subtract from larger to get the width
    ChannelWidth = 13.3; // need to thicken up the tower!
    // Height from the frame to the top of the channel
    ChannelHeight = 11.30; // Note: this measurement excludes distance from frame to top of channel floor
    // How much into channel we're going
    DepthIntoChannel = 8.0;
    // How thick is the channel wall
    ChannelThickness = 1.7;

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
    Height = ChannelOffset + DepthIntoChannel;

    difference() {
        // Main body
        union() {
            translate([0, 0, 0])
                scale([Width/2 + Padding, Depth/2, 1]) {
                    cylinder(r = 1, h = SupportThickness);
                }
            translate([0, 0, Height/2])
                cube([WidthWithoutBolts, Depth, Height], center = true);

            // TODO: Make the incline at at least 45 degrees
            translate([0, 0, ZMax - ChannelHeight + (DepthIntoChannel - Padding)/2])
                cube([WidthWithoutBolts + Padding, Depth, DepthIntoChannel + Padding], center = true);
        }

        // Bolts for mounting the bearing
        union() {
            translate([BoltSeparation / 2, 0, SupportThickness/2])
                cylinder(r = BoltDiameter, h = SupportThickness + Gap, center = true);
            translate([-BoltSeparation / 2, 0, SupportThickness/2])
                cylinder(r = BoltDiameter, h = SupportThickness + Gap, center = true);
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
        }

        // Channel
        union () {
            translate([ChannelWidth / 2, 0, ChannelOffset + DepthIntoChannel/2])
                cube([ChannelThickness + Gap, ToTheSky, DepthIntoChannel + Gap], center=true);
            translate([-ChannelWidth / 2, 0, ChannelOffset + DepthIntoChannel/2])
                cube([ChannelThickness + Gap, ToTheSky, DepthIntoChannel + Gap], center=true);
        }
    }
    /*
    difference() {
        translate([0,0,-MountOffset]) {
            intersection () {
                scale([Width/2, Depth/2, 1]) {
                    cylinder(r = 1, h = Thickness);
                }
                square([Width, Depth]);
            }
        }
        union () {
            translate([0,0,50])
                cube([HexFlatDiameter+Gap, HexThickness+Gap, 100], center=true);
            
            rotate([90,30,0])
            cylinder(r = HexRadius+Gap, h=HexThickness+Gap, center=true, $fn = 6);
            
            rotate([90,0,0])
                cylinder(r=ThreadRodDiameter/2, h = 100, center=true);

            translate([0,0,-ChannelOffset])
                rotate([90,0,0])            
                    cylinder(r=GuideRodRadius, h = 100, center = true);
            
            translate([BoltSeparation/2,0,0])
                cylinder(r=BoltDiameter/2, h=100, center=true);
            translate([-BoltSeparation/2,0,0])
                cylinder(r=BoltDiameter/2, h=100, center=true);
        }
    }
    */
}
