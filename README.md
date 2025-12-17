# Coil-O-Mat
Coil winding machine with integrated turn counter.

The main body of the coil winder is made primarly of 3D-printed parts and some of the shelf hardware.
The turn counter is based on a Rapberry Pi Pico reading two mechanical switches witch are actuated by a cam on the handle. A 2x16 character LCD screen is used to display the turn number and other information.

# PCB
The PCB can be ordered using the gerber and drill files. The neccessary files are bundled in a .zip for your convenience. This .zip can directly be used to order from manufacturers such as JLC PCB (tested) or PCB Way.
You can use the [bill of materials](empty link) or just look on the backside of the board to populate it. It is recommended to not only solder the LCD on with the pin header but also screw it down using washer of the appropriate thickness for your display and pin header. Stl files for the washers are not included, but i guess anyone can do their own from cylinders in the slicer if they really need to.
# Assembly 
Following parts are needed additional to the 3D-printed ones:

| Pcs. | Component                   |
|------|-----------------------------|
| 1    | M10 threaded rod            |
| 2    | Bearings 6000-2RS           |
| 3    | M10 Nut DIN 934             |
| 1    | M3x15 Bolt with Nut         |
| 4    | Wood screws                 |
| 2    | Micro switch with roller    |
| 2    | M5x20 Hex head screw DIN912 |
| 1    | M6x40 Hex head screw DIN912 |
| 4    | M2.5 x 10 to 20 screw       |
| 1    | <=3mm pin (optional)        |

The microswitches should have the dimensions 20x10x6mm with 2.5mm mounnting holes in a distance of ~9.5 mm and should look similar to [this one](https://www.neuhold-elektronik.at/micro-schalter/micro-schalter-5a-250v-mit-rollen-hebel).
An optional wood plate can be used as base for more sturdiness, the wood screws will be used to mount the coilwinder to that or a table.

For assembly first print the .stl files from the 3Dprints folder. It is recommended to print those parts from PETG. The 'clicker' can not be printed from PLA, because the integrated spring will creep over time and the ratched will stop working in a matter of days.

Press the bearings into place, cut the threaded rod to the length you desire and feed it through the bearings. Fix it with a M10 nut on both sides. Do not apply excessive force when tightening those nuts, otherwise the threaded rod will not rotate freely. Mount the clicker with two M5 screws, mount the micro switches onto the clicker and solder on wires. These wires need to be connected to J1 for one switch and J2 for the other switch. Changing which switch is connected to which port changes the direction for counting up / counting down. 

There are two versions of the handle, R and L. The ony differnce is the direction in which the ratchet allows movement, use whatever you prefer.
Assemble the handle using the M6x40 screw and screw it onto the threaded rod. make sure to push the micro-switch rollers and clicker out of the way while mounting the handle, so they can properly engage.
If your handle is not thight enough, you can fix it with the <= 3mm metal pin after drilling through the threaded rod in line with the hole in the handle. I do not recommend glueing on the handle, because the clicker is hard to exchange with a mounted handle and could need maintenace after some time.

Mount the carrier on the non-handle side of the threaded rod in your desired location. Drill through the threaded rod (3 mm - 3.5 mm) in line with the carriers mounting hole and fix it in place using the M3 screw and nut. One side of the carrier has a fitting recess for the hex nut. Depending on the coil you plan to wind you can put different carrier extensions on the carrier, a square one and a Cone are supplied with the .stl files. The other side of the coil carrier extension is pushed onto the threade rod after the coil carrier / bobbin you intend to wind onto. It is tightened against the coil by another M10 nut.

Happy winding!

# Software
The software is developed using the Arduino IDE with [Earl Philhower's Pi Pico Core](https://arduino-pico.readthedocs.io/en/latest/). You need to install this to compile the code provided in the [code folder](empty link).
Alternatively, you can put the .uf2 file onto the Pi Pico, just like pasting a file onto a flash drive. The .uf2 file contains the compiled code.
