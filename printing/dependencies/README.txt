                   .:                     :,                                          
,:::::::: ::`      :::                   :::                                          
,:::::::: ::`      :::                   :::                                          
.,,:::,,, ::`.:,   ... .. .:,     .:. ..`... ..`   ..   .:,    .. ::  .::,     .:,`   
   ,::    :::::::  ::, :::::::  `:::::::.,:: :::  ::: .::::::  ::::: ::::::  .::::::  
   ,::    :::::::: ::, :::::::: ::::::::.,:: :::  ::: :::,:::, ::::: ::::::, :::::::: 
   ,::    :::  ::: ::, :::  :::`::.  :::.,::  ::,`::`:::   ::: :::  `::,`   :::   ::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  :::::: ::::::::: ::`   :::::: ::::::::: 
   ,::    ::.  ::: ::, ::`  :::.::    ::.,::  .::::: ::::::::: ::`    ::::::::::::::: 
   ,::    ::.  ::: ::, ::`  ::: ::: `:::.,::   ::::  :::`  ,,, ::`  .::  :::.::.  ,,, 
   ,::    ::.  ::: ::, ::`  ::: ::::::::.,::   ::::   :::::::` ::`   ::::::: :::::::. 
   ,::    ::.  ::: ::, ::`  :::  :::::::`,::    ::.    :::::`  ::`   ::::::   :::::.  
                                ::,  ,::                               ``             
                                ::::::::                                              
                                 ::::::                                               
                                  `,,`


http://www.thingiverse.com/thing:16627
Parametric pulley - lots of tooth profiles by droftarts is licensed under the Creative Commons - Attribution - Share Alike license.
http://creativecommons.org/licenses/by-sa/3.0/

# Summary

This thing will create a range of metric and imperial tooth profile pulleys, with any number of teeth, specified in the Openscad file.
Tooth profiles currently supported are:
profile == 1 for MXL
profile == 2 for 40 D.P.
profile == 3 for XL 
profile == 4 for L
profile == 5 for T2.5
profile == 6 for T5
profile == 7 for T10
profile == 8 for AT5
profile == 9 for HTD 3mm
profile == 10 for HTD 5mm
profile == 11 for HTD 8mm
profile == 12 for GT2 2mm
profile == 13 for GT2 3mm
profile == 14 for GT2 5mm

NOTE: error in script regarding L and H pulleys spotted by OSTycoon (see comments) - the script says H, but actually it is L profile. 
There are a range of editable parameters for editing the fit of the tooth (to account for printer variation), the pulley base, captive nut(s) slot for the set screw, motor shaft diameter, pulley height and belt retainers.
The attached stls are reference pulleys, mostly around the size used on repraps.

Details
After creating the parametric pulley http://www.thingiverse.com/thing:11256 I realised this way of modelling them was only going to work for square-toothed pulleys, and a way of producing pulleys for belts with better characteristics for linear motion was required. I found dxf drawings of the relevant tooth profiles here http://oem.cadregister.com/asp/PPOW_Entry.asp?company=915217&elementID=07807803/METRIC/URETH/WV0025/F and modelled pulley diameter from data here http://www.sdp-si.com/D265/HTML/D265T016.html
There were a couple of possible approaches to importing the data, I chose to simplify the bezier curve dxf data in Inkscape, producing vertices with a resolution of around 0.05-0.1mm for each tooth. Another advantage is the the pulleys have the tooth ramp for smooth entry and exit of the belt tooth into the pulley. I'm not really sure 3D printers can take full advantage of this yet, but quality is improving all the time!
If other tooth profiles are required, or you model any, please pass them on to me and I will include them.

22 March 2012 - Updated for issue spotted by mfinn - see comments

# Instructions

1. Download openscad file, or use the Customiser (NOTE: I didn't create the customiser version, so I'm not sure what it does! There are some limits to it; see comments)
2. Tweak to make your perfect pulley
3. Print
3.1 If you get blobs and/or stringing, you may need to reduce the perimeter speed, perhaps as low as 10mm/s depending on your electronics/baud rate etc. The model is high resolution, and slicing software will produce lots of very short moves, that the comms may not be able to keep up with. Alternatively, print from SD card. Printing slow should improve the tooth shape, and fit of the belt.
4. Rejoice!