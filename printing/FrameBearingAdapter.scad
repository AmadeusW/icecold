Gap = 0.2;
$fn = 72;

FrameToBearing();

module FrameToBearing() {
    BearingRadius = 11.0;
    BearingHeight = 7.0;
    Thickness = 3.0;
    MountingRadius = BearingRadius + Thickness;

    HeadDiameter = 11.0;
    HeadHeight = 4.5 + Gap;

    ThreadDiameter = 6.6 + Gap; // I measured 6.2, but RodToBearingCoupling uses 6.5 for a snug fit
    ThreadHeight = 2.0;

    FrameAdapterWidth = HeadDiameter + 2*Thickness;
    FrameAdapterLength = MountingRadius*2;
    FrameAdapterHeight = ThreadHeight + HeadHeight;

    ToTheSky = 50;

    intersection()
    {
        // Enclose everything in the radius of bearing adapter
        translate([FrameAdapterLength/2, FrameAdapterWidth/2, 0])
            cylinder(r = MountingRadius, h=ToTheSky, center=false);
        union()
        {
            difference() {
                union() {
                    // Frame adapter
                    cube([FrameAdapterLength, FrameAdapterWidth, FrameAdapterHeight]);
                    // Bearing adapter
                    translate([FrameAdapterLength/2, FrameAdapterWidth/2, FrameAdapterHeight])
                        cylinder(r = MountingRadius, h=BearingHeight, center=false);
                    // Their connection
                    translate([FrameAdapterLength/2, FrameAdapterWidth/2, 0])
                        cylinder(r2 = MountingRadius, r1=FrameAdapterWidth/2, h=FrameAdapterHeight, center=false);
                }
                union() {
                    // Volume of bearing
                    translate([FrameAdapterLength/2, FrameAdapterWidth/2, FrameAdapterHeight])
                        cylinder(r = BearingRadius + Gap, h=BearingHeight);
                    
                    // Volume of the nut head
                    translate([0, Thickness, ThreadHeight])
                        cube([FrameAdapterLength, HeadDiameter, HeadHeight]);

                    // Volume of the nut thread
                    translate([0, Thickness + (HeadDiameter - ThreadDiameter)/2, 0])
                        cube([FrameAdapterLength, ThreadDiameter, ThreadHeight]);

                    // Don't fully enclose the bearing at x=Length
                    translate([FrameAdapterLength/2, Thickness, ThreadHeight])
                        cube([FrameAdapterLength, HeadDiameter, HeadHeight + ToTheSky]);
                }
            }
            // Additional support wall at x=0
            intersection()
            {
                // Cylindrical wall
                difference()
                {
                    translate([FrameAdapterLength/2, FrameAdapterWidth/2, 0])
                        cylinder(r = MountingRadius, h=FrameAdapterHeight, center=false);
                    translate([FrameAdapterLength/2, FrameAdapterWidth/2, 0])
                        cylinder(r = BearingRadius + Gap, h=BearingHeight);
                }
                translate([0, Thickness, 0])
                    cube([FrameAdapterLength/2, HeadDiameter, HeadHeight + ToTheSky]);                
            }
        }
    }
}