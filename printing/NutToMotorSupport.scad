Gap = 0.2;
$fn = 72;

NutToMotorSupport();

module NutToMotorSupport() {
    Padding = 3.0;

    MotorInnerRadius = 13.0;
    MotorBraceRadius = MotorInnerRadius + Padding;

    SupportHeight = Padding * 3;
    MotorRadius = 26.0;

    HeadDiameter = 11.0;
    HeadHeight = 4.5 + Gap;

    ThreadDiameter = 6.6 + Gap; // I measured 6.2, but RodToBearingCoupling uses 6.5 for a snug fit
    ThreadHeight = 2.0;

    FrameAdapterWidth = HeadDiameter + 2*Padding;
    NutAdapterLength = 32;
    FrameAdapterHeight = ThreadHeight;

    MotorAdapterOffset = MotorBraceRadius; // Center of the rod
    BearingAdapterShift = 0;

    ToTheSky = 50;

    union() {
        // Frame adapter
        difference() {
            cube([NutAdapterLength, FrameAdapterWidth, ThreadHeight]);

            // Volume of the nut thread
            translate([0, Padding + (HeadDiameter - ThreadDiameter)/2, 0])
                cube([NutAdapterLength, ThreadDiameter, ThreadHeight]);
        }

        // Motor adapter
        rotate([0, -90, 0])
        translate([MotorAdapterOffset, FrameAdapterWidth/2, -BearingAdapterShift +SupportHeight/2])
        difference() {
            union()
            {
                // Connection to frame adapter
                translate([-MotorAdapterOffset/2, 0, 0])
                linear_extrude(height = SupportHeight, center = true)
                    polygon(points = [
                    [-MotorAdapterOffset/2, -FrameAdapterWidth/2],
                    [MotorAdapterOffset/2 - Padding, -MotorBraceRadius],
                    [MotorAdapterOffset/2 - Padding, MotorBraceRadius],
                    [-MotorAdapterOffset/2, FrameAdapterWidth/2],
                    ]);
            }
            union() {
                // Volume of motor
                translate([0, 0, SupportHeight/3])
                    cylinder(r = MotorInnerRadius + Gap, h=Padding*3, center=true);
            }
        }
    }
}
