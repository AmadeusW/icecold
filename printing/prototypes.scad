Gap = 0.2;
$fn = 72;

Helper(false, hide=true)
    FrameToBearing();

translate([-10,40,0])
    Helper(false, hide=true)
        RodToMotorCoupling();
    
intersection() {
    Helper(false, hide=true)
        Guide();
}

translate([0,-40,0])
    Helper(false, hide=false)
        RodToBearingCoupling();

// If debug is set, renders a cross section of the object
module Helper(debug, hide = false) {
    if (!hide)
    {
        if (debug) {
            intersection() {
                children();
                translate([0,-100,-100])
                    cube([200,200,200]);
            }
        } else {
            children();
        }
    }
}

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

module RodConnect() {
    RodThickness = 1.65; // 1/16 inch + 0.7mm gap
    RodDepth = 13.75; // 1/2 inch + 0.5mm gap
    
    BearingDiameter = 8.0;
    BearingLength = 15;
    
    ConnectorShift = 0.3;
    
    ConnectorWidth = RodThickness+6;
    ConnectorDepth = RodDepth+6;
    
    CornerRadius = 1;
    
    intersection() {
        translate([0,0,ConnectorShift])
            cube([200,200,BearingDiameter - 2 * ConnectorShift], center=true);
        difference() {
            union () {
                rotate([0,-90,0])
                    cylinder(r = BearingDiameter/2, h = BearingLength);
                
                rotate([0,-90,0])
                    cylinder(r = BearingDiameter/2,
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
                    cylinder(r=0, r2=RodDiameter/2, h = ConeHeight);

                translate([0,0,BearingHeight])
                    cylinder(r=RodDiameter/2, h = RodHeight);

                translate([0,0,BearingHeight+RodHeight])
                    cylinder(r=RodDiameter/2, r2=RimDiameter/2, h = RimHeight);
            }
        }
    }
}

// Rod: https://www.homedepot.com/p/Everbilt-1-2-in-x-36-in-Aluminum-Flat-Bar-800217/204604762
// Rod connect Bearing: https://www.amazon.com/gp/product/B00N4138LU/ref=ppx_yo_dt_b_search_asin_title?ie=UTF8&psc=1
// Motor coupling bearing https://www.amazon.com/uxcell-KFL002-Aligning-Pillow-Bearing/dp/B073KTGZ1H/ref=sr_1_20?keywords=uxcell%2Bflange%2Bbearing&qid=1576645950&sr=8-20&th=1