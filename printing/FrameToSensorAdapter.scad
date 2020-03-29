Gap = 0.2;
$fn = 72;

FrameToSensor();

module FrameToSensor() {
    Thickness = 3.0;

    SensorRadius = 5.0;
    SensorInnerRadius = 3.5;
    SensorHeight = 5.0;

    MountingRadius = SensorRadius + Thickness;

    HeadDiameter = 11.0;
    HeadHeight = 4.5 + Gap;

    ThreadDiameter = 6.6 + Gap; // I measured 6.2, but RodToBearingCoupling uses 6.5 for a snug fit
    ThreadSafeRadius = (ThreadDiameter + Thickness) / 2;
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

        // Sensor adapter
        rotate([0, -90, 0])
        translate([BearingAdapterOffset, FrameAdapterWidth/2, -FrameAdapterLength -(SensorHeight+Thickness)/2])
        difference() {
            union()
            {
                // Sensor adapter
                cylinder(r = MountingRadius, h=SensorHeight + Thickness, center=true);

                // Connection to frame adapter
                translate([-BearingAdapterOffset/2, 0, 0])
                linear_extrude(height = SensorHeight + Thickness, center = true)
                    polygon(points = [
                    [-BearingAdapterOffset/2, -FrameAdapterWidth/2],
                    [BearingAdapterOffset/2, -MountingRadius - SensorRadius * 2],
                    [BearingAdapterOffset/2, MountingRadius + SensorRadius * 2],
                    [-BearingAdapterOffset/2, FrameAdapterWidth/2],
                    ]);
            }
            union() {
                // Volume of sensor 1. Move it away from the threaded rod
                translate([-ThreadSafeRadius - SensorRadius, ThreadSafeRadius + Thickness, -Thickness/2])
                    cylinder(r = SensorRadius, h=SensorHeight, center=true);

                translate([-ThreadSafeRadius - SensorRadius, ThreadSafeRadius + Thickness, Thickness/2])
                    cylinder(r = SensorInnerRadius, h=SensorHeight, center=true);

                // Allow the other sensor to face away
                // Volume of sensor 2. Move it away from the threaded rod
                translate([-ThreadSafeRadius - SensorRadius, - ThreadSafeRadius - Thickness, Thickness/2])
                    cylinder(r = SensorRadius, h=SensorHeight, center=true);

                translate([-ThreadSafeRadius - SensorRadius, - ThreadSafeRadius - Thickness, -Thickness/2])
                    cylinder(r = SensorInnerRadius, h=SensorHeight, center=true);

                // Guide rod
                translate([-GuideRodOffset, 0, -(SensorHeight + Thickness)/2])
                    cylinder(r = GuideRodRadius, h = SensorHeight + Thickness);

                // Threaded rod!!!
                /// We need to make sure that the sensor does not overlap with the threaded rod.
                translate([0, 0, -Thickness/2])
                    cylinder(r = ThreadSafeRadius, h=ToTheSky, center=true);

                // Don't fully enclose the thread at x=Length
                translate([0, -Thickness/2, -ToTheSky/2])
                    cube([ToTheSky, Thickness, ToTheSky]);
            }
        }
    }
}
