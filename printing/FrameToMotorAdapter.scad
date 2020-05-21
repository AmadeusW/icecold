Gap = 0.2;
$fn = 72;

FrameToMotorAdapter();

module FrameToMotorAdapter() {
    Padding = 3.0;

    MotorInnerRadius = 13.0;
    MotorBraceRadius = MotorInnerRadius + Padding;

    SupportHeight = 6.0;
    MotorRadius = 26.0;

    HeadDiameter = 11.0;
    HeadHeight = 4.5 + Gap;

    ThreadDiameter = 6.6 + Gap; // I measured 6.2, but RodToBearingCoupling uses 6.5 for a snug fit
    ThreadHeight = 2.0;

    FrameAdapterWidth = HeadDiameter + 2*Padding;
    FrameAdapterLength = 32;
    FrameAdapterHeight = ThreadHeight + HeadHeight;

    BearingAdapterOffset = MotorRadius + FrameAdapterHeight; // Center of the rod
    BearingAdapterShift = 0;

    MountingNutOffset = 20.4;
    MountingNutRadius = 2.1; // actually 1.925, so 2.1 includes a gap

    ToTheSky = 50;

    union() {
        // Frame adapter
        difference() {
            cube([FrameAdapterLength, FrameAdapterWidth, FrameAdapterHeight]);

            // Volume of the nut head
            translate([0, Padding, ThreadHeight])
                cube([FrameAdapterLength, HeadDiameter, HeadHeight]);

            // Volume of the nut thread
            translate([0, Padding + (HeadDiameter - ThreadDiameter)/2, 0])
                cube([FrameAdapterLength, ThreadDiameter, ThreadHeight]);
        }

        // Motor housing adapter
        rotate([0, -90, 0])
        translate([BearingAdapterOffset, FrameAdapterWidth/2, -FrameAdapterLength])
        difference() {
            union()
            {
                // Resting arm
                translate([-BearingAdapterOffset/2, 0, 0])
                linear_extrude(height = SupportHeight, center = true)
                    polygon(points = [
                    [-BearingAdapterOffset/2, -FrameAdapterWidth/2],
                    [BearingAdapterOffset/2, -MotorRadius],
                    [BearingAdapterOffset/2, MotorRadius],
                    [-BearingAdapterOffset/2, FrameAdapterWidth/2],
                    ]);
            }
            union() {
                // Volume of motor housing
                cylinder(r = MotorRadius, h=SupportHeight, center=true);
            }
        }

        // Motor adapter
        rotate([0, -90, 0])
        translate([BearingAdapterOffset, FrameAdapterWidth/2, -BearingAdapterShift +SupportHeight/2])
        difference() {
            union()
            {
                // Bearing adapter
                difference()
                {
                    cylinder(r = MotorBraceRadius, h=SupportHeight, center=true);
                    // Remove top half (-Padding)
                    translate([-Padding, -ToTheSky/2, -ToTheSky/2])
                        cube([ToTheSky, ToTheSky, ToTheSky]);
                }
                
                // Connection to frame adapter
                p1 = RRTangent([BearingAdapterOffset/2,
                                -(MountingNutOffset+MountingNutRadius*.5)],
                               [-BearingAdapterOffset/2, -FrameAdapterWidth/2],
                               MountingNutRadius + Padding, 0, 1);

                p2 = RRTangent([BearingAdapterOffset/2,
                                (MountingNutOffset+MountingNutRadius*0.5)],
                               [-BearingAdapterOffset/2, FrameAdapterWidth/2],
                               MountingNutRadius + Padding, 0, -1);

                translate([-BearingAdapterOffset/2, 0, 0])
                linear_extrude(height = SupportHeight, center = true)
                    polygon(points = [
                    [-BearingAdapterOffset/2, -FrameAdapterWidth/2],
                    p1,
                    [BearingAdapterOffset/2,-(MountingNutOffset+MountingNutRadius*.5)],
                    [BearingAdapterOffset/2,(MountingNutOffset+MountingNutRadius*.5)],
                    p2,
                    [-BearingAdapterOffset/2, FrameAdapterWidth/2],
                    ]);

                // Mounting nut support
                translate([0, MountingNutOffset, 0])
                hull()
                {
                    translate([0, -MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius + Padding, h=SupportHeight, center=true);
                    translate([0, MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius + Padding, h=SupportHeight, center=true);
                }
                translate([0, -MountingNutOffset, 0])
                hull()
                {
                    translate([0, -MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius + Padding, h=SupportHeight, center=true);
                    translate([0, MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius + Padding, h=SupportHeight, center=true);
                }
            }
            union() {
                // Volume of motor
                translate([0, 0, 0])
                    cylinder(r = MotorInnerRadius + Gap, h=SupportHeight, center=true);

                // Mounting nuts
                translate([0, MountingNutOffset, 0])
                hull()
                {
                    translate([0, -MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius, h=SupportHeight, center=true);
                    translate([0, MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius, h=SupportHeight, center=true);
                }
                    
                translate([0, -MountingNutOffset, 0])
                hull()
                {
                    translate([0, -MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius, h=SupportHeight, center=true);
                    translate([0, MountingNutRadius/2, 0])
                        cylinder(r = MountingNutRadius, h=SupportHeight, center=true);
                }
            }
        }
    }
}

// find p that is r1 from p1 and on a line that
// passes r1 from p1 and p2 from p2.
function RRTangent(p1, p2, r1, r2, s) =
     let(dx = (p2[0] - p1[0]))
     let(dy = (p2[1] - p1[1]))
     let(distance2 = dx*dx + dy*dy)
     let(distance = sqrt(distance2))
     let(nx = dx / distance)
     let(ny = dy / distance)
     let(cosA = (r1-r2)/distance)
     let(sinA = sqrt(1-cosA*cosA))
        [p1[0] + (cosA * r1) * nx - s * (sinA * r1) * ny,
         p1[1] + (cosA * r1) * ny + s * (sinA * r1) * nx];
