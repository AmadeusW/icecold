Gap = 0.2;
$fn = 72;

FrameToSensor();

module FrameToSensor() {
    Padding = 3.0;

    HeadDiameter = 11.0;
    HeadHeight = 4.5 + Gap;

    ThreadDiameter = 6.6 + Gap; // I measured 6.2, but RodToBearingCoupling uses 6.5 for a snug fit
    ThreadHeight = 2.0;

    FrameAdapterWidth = HeadDiameter + 2*Padding;
    FrameAdapterLength = 32;
    FrameAdapterHeight = ThreadHeight + HeadHeight;

    MotorRadius = 26.0;
    BearingAdapterOffset = MotorRadius + FrameAdapterHeight;
    BearingAdapterShift = 0;

    MountRadius = 1.0; // it's a 2mm screw
    MountDistance = 14.7;
    MountOffsetFromCenter = MountDistance / 2;
    MountHeight = FrameAdapterHeight + MountRadius + Padding; // As low as possible

    Width = MountDistance + (MountRadius + Padding)*2;
    Depth = 4; // arbitrary
    Height = Width + FrameAdapterHeight;
    ToTheSky = 50;

    union() {
        // Frame adapter
        difference() {
            cube([FrameAdapterLength, FrameAdapterWidth, FrameAdapterHeight]);

            // Volume of the nut head
            translate([0, Padding, ThreadHeight])
                cube([FrameAdapterLength + Gap, HeadDiameter, HeadHeight]);

            // Volume of the nut thread
            translate([0, Padding + (HeadDiameter - ThreadDiameter)/2, 0])
                cube([FrameAdapterLength + Gap, ThreadDiameter, ThreadHeight]);
        }

        // Sensor adapter
        rotate([0, -90, 0])
        translate([0, FrameAdapterWidth/2, Depth/2])
        difference() {
            union()
            {
                // Connection to frame adapter
                linear_extrude(height = Depth, center = true)
                    polygon(points = [
                    [0, -FrameAdapterWidth/2],
                    [Height/2, -Width/2],
                    [Height/2, Width/2],
                    [0, FrameAdapterWidth/2],
                    ]);
            }
            union() {
                // Volume of mount 1
                translate([MountHeight, -MountOffsetFromCenter, 0])
                hull()
                {
                    translate([0, -MountRadius/4, 0])
                        cylinder(r = MountRadius + Gap, h=ToTheSky, center=true);
                    translate([0, MountRadius/4, 0])
                        cylinder(r = MountRadius + Gap, h=ToTheSky, center=true);
                }

                // Volume of mount 2
                translate([MountHeight, MountOffsetFromCenter, 0])
                hull()
                {
                    translate([0, -MountRadius/4, 0])
                        cylinder(r = MountRadius + Gap, h=ToTheSky, center=true);
                    translate([0, MountRadius/4, 0])
                        cylinder(r = MountRadius + Gap, h=ToTheSky, center=true);
                }
            }
        }
    }
}
