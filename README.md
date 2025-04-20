# Smart DSMR P1 Splitter - 4 ports

Device that splits the P1 port into three individually functioning P1 ports (P2, P3 and P4).
It will let three devices communicate with the DSMR P1 port at different intervals.
In my case I use this device to connect a HomeWizard P1 meter, an Alfen EV Charger load balancer and a Sessy Meter for a Sessy Battery.

## Schematics
![Schema](/media/Schematic_Active-P1-DSMR-Switch_2025-04-20.png?raw=true "Schema")

+ [EasyEda Schematic](/hardware/schematics/SCH_Active-P1-DSMR-Switch_2025-04-20.json? "EasyEda Schematic")

+ [EasyEda PCB](/hardware/pcb/PCB_PCB_Smart-DSMR-Splitter_2025-04-20.json? "EasyEda PCB")

## PCB images
![PCB top](/media/PCB_top_view.png?raw=true "PCB top")

![PCB bottom](/media/PCB_bottom_view.png?raw=true "PCB bottom")

## Libraries Used

+ [Arduino Dutch Smart meter (DSMR) parser](https://github.com/matthijskooijman/arduino-dsmr) (slightly modified)

License
-------
All of the code in this project is licensed under the GNU General Public License v3.0 (GNU GPLv3) license.
