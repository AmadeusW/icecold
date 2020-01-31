Gap = 0.2;
$fn = 72;

translate([10,40,0])
    RodToBearingCoupling();

translate([-10,40,0])
    RodToMotorCoupling();
    
intersection() {
    Guide();
    //translate([-100,0,-100])
        //cube([200,200,200]);
}

translate([0,-40,0])
    RodConnect();

module RodConnect() {
    RodThickness = 2.0;
    RodDepth = 13.4;
    
    BearingDiameter = 7.9;
    BearingLength = 15;
    
    ConnectorShift = 0.5;
    
    ConnectorWidth = RodThickness+23;
    ConnectorDepth = RodDepth+10;
    
    CornerRadius = 5;
    
    intersection() {
        translate([0,0,ConnectorShift])
            cube([200,200,BearingDiameter - 2 * ConnectorShift], center=true);
        difference() {
            union () {
                rotate([0,-90,0])
                    cylinder(r = BearingDiameter/2, h = BearingLength);
                
                rotate([0,-90,0])
                    cylinder(r1 = BearingDiameter/2+5, r2 = BearingDiameter/2,
                             h = 5);
                
                linear_extrude(height=BearingDiameter, center=true)
                    offset(r=CornerRadius)
                        polygon([[CornerRadius, -ConnectorWidth/2 + CornerRadius],
                                 [ConnectorDepth - CornerRadius,
                                  -ConnectorWidth/2 + CornerRadius],
                                 [ConnectorDepth - CornerRadius,
                                  ConnectorWidth/2 - CornerRadius],
                                 [CornerRadius,
                                  ConnectorWidth/2 - CornerRadius]]);
            }
            
            union () {
                rotate([0,0,2])
                    translate([ConnectorDepth/2,0,0])
                        cube([RodDepth, RodThickness, 100], center = true);
            }
        }
    }    
}

module Guide() {
    Thickness = 28.425;
    Depth = 20;

    HexFlatDiameter = 11.0;
    HexRadius = HexFlatDiameter/(2 * cos(30));
    HexThickness = 5.4;

    MountOffset = 20;
    GuideRodDiameter = 5.5;
    GuideRodOffet = 13;
    ThreadRodDiameter = 6.7;
    
    BoltDiameter = 4.6;
    BoltSeparation = 35.0;
    
    Width = BoltSeparation + BoltDiameter + 4;

    
    difference() {
        translate([0,0,-MountOffset])
            scale([Width/2, Depth/2, 1])
                cylinder(r = 1, h = Thickness);
        
        union () {
            translate([0,0,50])
                cube([HexFlatDiameter+Gap, HexThickness+Gap, 100], center=true);
            
            rotate([90,30,0])
            cylinder(r = HexRadius+Gap, h=HexThickness+Gap, center=true, $fn = 6);
            
            rotate([90,0,0])
                cylinder(r=ThreadRodDiameter/2, h = 100, center=true);
            
            translate([0,0,-GuideRodOffet])
                rotate([90,0,0])
                    cylinder(r=GuideRodDiameter/2, h = 100, center = true);
            
            translate([BoltSeparation/2,0,0])
                cylinder(r=BoltDiameter/2, h=100, center=true);
            translate([-BoltSeparation/2,0,0])
                cylinder(r=BoltDiameter/2, h=100, center=true);
        }
    }
       
}

module RodToMotorCoupling() {
    BearingDiameter = 20.0;
    BearingHeight = 14.0;
        
    HexFlatDiameter = 11.0;
    HexRadius = HexFlatDiameter/(2 * cos(30));
    HexHeight = 8;
    
    ShaftDiameter = 8.2;
    SocketThickness = 3.0;
    ShaftHeight = 35.0;

    GuideHeight = 6.0;
    GuideDiameter = 2.8;
    
    ShaftRadius = ShaftDiameter / 2;
    SocketRadius = ShaftRadius + SocketThickness;
    SocketDiameter = SocketRadius * 2;
    BearingRadius = BearingDiameter / 2;
    MiddleHeight = BearingRadius - SocketRadius; // ensure angle of 45 degrees on the outer wall
    GuideRadius = GuideDiameter / 2;
    MiddleInnerHeight = ShaftRadius + Gap; // ensure angle of 45 degrees on the inner wall

    union () {
        // Part which wraps around the motor
        difference() {
            cylinder(r=SocketRadius, h = ShaftHeight + MiddleInnerHeight);

            translate([0,SocketRadius,GuideHeight])
                rotate([90,0,0])
                    cylinder(r=GuideRadius + Gap, h = SocketDiameter);

            translate([0,0,-1]) // -1 to Ensure the difference
                union()
                {
                    cylinder(r=ShaftRadius + Gap, h = ShaftHeight+1);
                    translate([0,0,ShaftHeight + 1])
                        cylinder(r1=ShaftRadius + Gap, r2= 0, h = MiddleInnerHeight);
                }
        }

        // Connect to the other part
        translate([0,0,ShaftHeight + MiddleInnerHeight])
            cylinder(r1=SocketRadius, r2= BearingRadius  - Gap, h = MiddleHeight);
        
        // Fit in the bearing
        translate([0,0, ShaftHeight + MiddleInnerHeight + MiddleHeight])
            difference() {
                cylinder(r=BearingRadius - Gap, h = BearingHeight);

                translate([0,0,0])
                    cylinder(r = HexRadius + Gap, h = BearingHeight + 1, $fn = 6);
            }
    }
}

module RodToBearingCoupling() {
    CouplingDiameter = 10;
    BearingDiameter = 7.7;
    BearingHeight = 10;
    MiddleThickness = CouplingDiameter - BearingDiameter; // Keep slope at 45 degrees
    RodHeight = 5;
    ConeHeight = 2;
    RodDiameter = 4;
    RimHeight = 1;
    RimDiameter = 5;

    rotate([180,0,0])
    {
        difference() {
            union () {
                cylinder(r=BearingDiameter / 2, h = BearingHeight);
                translate([0,0,BearingHeight])

                cylinder(r1=BearingDiameter / 2, r2=CouplingDiameter / 2, h = MiddleThickness);

                translate([0,0,BearingHeight+MiddleThickness])

                cylinder(r=CouplingDiameter / 2, h = RodHeight);
            }
            translate([0, 0, -RimHeight])
            union () {
                translate([0,0,BearingHeight+MiddleThickness - ConeHeight*2 ])
                    cylinder(r=0, r2=RodDiameter/2, h = ConeHeight * 2);

                translate([0,0,BearingHeight+MiddleThickness])
                    cylinder(r=RodDiameter/2, h = RodHeight);

                translate([0,0,BearingHeight+MiddleThickness+RodHeight])
                    cylinder(r=RodDiameter/2, r2=RimDiameter/2, h = RimHeight);
            }
        }
    }
}

// Rod: https://www.homedepot.com/p/Everbilt-1-2-in-x-36-in-Aluminum-Flat-Bar-800217/204604762
// Rod connect Bearing: https://www.amazon.com/gp/product/B00N4138LU/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
// Motor coupling bearing https://www.amazon.com/uxcell-KFL002-Aligning-Pillow-Bearing/dp/B073KTGZ1H/ref=sr_1_20?keywords=uxcell%2Bflange%2Bbearing&qid=1576645950&sr=8-20&th=1