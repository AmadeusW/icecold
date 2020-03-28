Gap = 0.2;
$fn = 72;

FrameToBearingL();

module FrameToBearingL() {
    Thickness = 3.0;

    BearingRadius = 11.0;
    BearingInnerRadius = BearingRadius - Thickness;
    BearingHeight = 7.0;

    MountingRadius = BearingRadius + Thickness;

    HeadDiameter = 11.0;
    HeadHeight = 4.5 + Gap;

    ThreadDiameter = 6.6 + Gap; // I measured 6.2, but RodToBearingCoupling uses 6.5 for a snug fit
    ThreadHeight = 2.0;

    FrameAdapterWidth = HeadDiameter + 2*Thickness;
    FrameAdapterLength = 32;
    FrameAdapterHeight = ThreadHeight + HeadHeight;

    MotorRadius = 26.0;
    BearingAdapterOffset = MotorRadius + FrameAdapterHeight;
    BearingAdapterShift = 0;

    GuideRodRadius = 2.75;
    MotorInnerRadius = 12.5;
    GuideRodOffset = MotorInnerRadius + Thickness/2 + GuideRodRadius;

    ToTheSky = 50;

    union() {
        // Frame adapter
        difference() {
            cube([FrameAdapterLength, FrameAdapterWidth, FrameAdapterHeight]);

            // Volume of the nut head
            translate([0, Thickness, ThreadHeight])
                cube([FrameAdapterLength, HeadDiameter, HeadHeight]);

            // Volume of the nut thread
            translate([0, Thickness + (HeadDiameter - ThreadDiameter)/2, 0])
                cube([FrameAdapterLength, ThreadDiameter, ThreadHeight]);
        }

        // Bearing adapter
        rotate([0, -90, 0])
        translate([BearingAdapterOffset, FrameAdapterWidth/2, -FrameAdapterLength -(BearingHeight+Thickness)/2])
        difference() {
            union()
            {
                // Bearing adapter
                cylinder(r = MountingRadius, h=BearingHeight + Thickness, center=true);

                // Connection to frame adapter
                translate([-BearingAdapterOffset/2, 0, 0])
                linear_extrude(height = BearingHeight + Thickness, center = true)
                    polygon(points = [
                    [-BearingAdapterOffset/2, -FrameAdapterWidth/2],
                    [BearingAdapterOffset/2, -MountingRadius],
                    [BearingAdapterOffset/2, MountingRadius],
                    [-BearingAdapterOffset/2, FrameAdapterWidth/2],
                    ]);
            }
            union() {
                // Volume of bearing
                translate([0, 0, -Thickness/2])
                    cylinder(r = BearingRadius, h=BearingHeight, center=true);

                translate([0, 0, Thickness/2])
                    cylinder(r = BearingInnerRadius, h=BearingHeight, center=true);

                // Don't fully enclose the bearing at x=Length
                translate([0, -Thickness/2, -ToTheSky/2])
                    cube([ToTheSky, Thickness, ToTheSky]);

                // Guide rod
                translate([-GuideRodOffset, 0, -(BearingHeight + Thickness)/2])
                    cylinder(r = GuideRodRadius, h = BearingHeight + Thickness);
            }
        }
    }
}
