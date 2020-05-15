Gap = 0.2;
$fn = 72;

BarMount();

module BarMount() {
    RodThickness = 1.65; // 1/16 inch + 0.7mm gap
    RodDepth = 13.75; // 1/2 inch + 0.5mm gap
    
    BearingDiameter = 8.0;
    BearingLength = 15;
    
    ConnectorShift = 0.3;
    
    ConnectorWidth = RodThickness+8;
    ConnectorDepth = RodDepth+5;
    
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
            
            rotate([0,0,2])
                union () {
                    translate([ConnectorDepth/2,0,0])
                        cube([RodDepth, RodThickness, 100], center = true);
            }
        }
    }    
}