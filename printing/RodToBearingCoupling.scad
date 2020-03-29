Gap = 0.2;
$fn = 72;

RodToBearingCoupling();

module RodToBearingCoupling() {
    CouplingDiameter = 10;
    BearingDiameter = 8;
    BearingHeight = 12;
    MiddleThickness = (CouplingDiameter - BearingDiameter) / 2; // Keep slope at 45 degrees
    RodHeight = 5;
    RodDiameter = 6.5;
    ConeHeight = RodDiameter / 2; // Keep slope at 45 degrees
    RimHeight = 1;
    RimDiameter = 7;

    rotate([180,0,0])
    {
        difference() {
            // Body
            union () {
                cylinder(r=BearingDiameter / 2, h = BearingHeight);
                
                translate([0,0,BearingHeight - ConeHeight])
                    cylinder(r1=BearingDiameter / 2 , r2=CouplingDiameter / 2, h = ConeHeight);

                translate([0,0,BearingHeight])
                    cylinder(r=CouplingDiameter / 2, h = RodHeight + RimHeight);
            }
            // Space for threaded rod
            union () {
                translate([0,0,BearingHeight - ConeHeight])
                    cylinder(r1=0, r2=RodDiameter/2, h = ConeHeight);

                translate([0,0,BearingHeight])
                    cylinder(r=RodDiameter/2, h = RodHeight);

                translate([0,0,BearingHeight+RodHeight])
                    cylinder(r1=RodDiameter/2, r2=RimDiameter/2, h = RimHeight);
            }
        }
    }
}
