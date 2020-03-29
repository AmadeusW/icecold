Gap = 0.2;
$fn = 72;

FrameToMotorSupport();

module FrameToMotorSupport() {
    Thickness = 3.0;

    MotorInnerRadius = 12.5;
    MotorBraceRadius = MotorInnerRadius + Thickness;

    SupportHeight = 6.0;
    MotorRadius = 26.0;

    HeadDiameter = 11.0;
    HeadHeight = 4.5 + Gap;

    ThreadDiameter = 6.6 + Gap; // I measured 6.2, but RodToBearingCoupling uses 6.5 for a snug fit
    ThreadHeight = 2.0;

    FrameAdapterWidth = HeadDiameter + 2*Thickness;
    FrameAdapterLength = 32;
    FrameAdapterHeight = ThreadHeight + HeadHeight;

    BearingAdapterOffset = MotorRadius + FrameAdapterHeight; // Center of the rod
    BearingAdapterShift = 0;

    GuideRodSnugRadius = 2.5;
    GuideRodOffset = MotorInnerRadius + Thickness/2 + GuideRodSnugRadius;

    MountingNutOffset = 19;
    MountingNutRadius = 2.0;

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

        // Motor adapter
        rotate([0, -90, 0])
        translate([BearingAdapterOffset, FrameAdapterWidth/2, -BearingAdapterShift +SupportHeight/2])
        difference() {
            union()
            {

                
                // Connection to frame adapter
                translate([-BearingAdapterOffset/2, 0, 0])
                linear_extrude(height = SupportHeight, center = true)
                    polygon(points = [
                    [-BearingAdapterOffset/2, -FrameAdapterWidth/2],
                    [BearingAdapterOffset/2 - Thickness, -MotorBraceRadius],
                    [BearingAdapterOffset/2 - Thickness, MotorBraceRadius],
                    [-BearingAdapterOffset/2, FrameAdapterWidth/2],
                    ]);
            }
            union() {
                // Volume of motor
                translate([0, 0, Thickness])
                    cylinder(r = MotorInnerRadius, h=Thickness, center=true);
                translate([0, 0, -Thickness])
                    cylinder(r = MotorInnerRadius, h=Thickness, center=true);
            }
        }
    }
}
