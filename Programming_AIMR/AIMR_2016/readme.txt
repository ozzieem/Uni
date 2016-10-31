
============================================
1-Real robot
============================================
----------------------------
1.1-epuck-computer connection:
----------------------------
-Pairing computer with epuck:
system settings -> Bluetooth -> + (add) -> pin options.. -> custom PIN:
"write four digit number written on epuck" -> close -> continue
(NOTE: if pairing fail continuously then install blueman and pair through blueman)

-Turn on the robot

-Connecting epuck with robot:
-Open a terminal and write the following commands:

$sudo rfcomm release rfcommX    (where X is the port number which is also written on each epuck i.e 0,1,2..)
$sudo rfcomm connect rfcommX    (where X is the port number which is also written on each epuck i.e 0,1,2..)

-If everything works fine, the following message will appear on the terminal:
"Connected /dev/rfcommX to 10:00:E8:AD:75:AC on channel 1"

------------------------------------------
1.2-Compilie library and run sample program:
------------------------------------------
-Open a new terminal
-cd into AIMR_2016/real_robot/src
$make clean
$make
$cd ../../run/

-Open main.cpp

-In line 3 "ROBOT_NUMBER X" replace X with the robot number which is written on your epuck (e.g., 0,1,2 ...)

$make clean_real 
$make real 
$sudo ./real
(enter your login password)

-If everything works fine, the ring of leds on the epuck will trun on

-For more test examples remove the lines (/* remove this line , remove this line*/) from the main.cpp.
$make clean_real 
$make real
$sudo ./real

============================================
2-Simulator
============================================

------------------------------------------
2.1-Compilie the simulator:
------------------------------------------
-cd into AIMR_2016/simulator/src/
$make clean_lin
$make sim_lin

-Turn on the simulator:
$cd ../bin/
$./sim_lin
-Run the simulator by clicking "run" button
(simulator should be running while testing your code)

-Compilie and run sample program:

-Open a new terminal
-cd into AIMR_2016/run/

$make clean_sim 
$make sim
$./sim

============================================
3-Documentation of library related to the course: 
============================================

Go to AIMR_2014/doc/doxygen/html and double click on index.html
Documentation will appear in your browser (google chrome or firefox)
Click on "Files"
The files related to AIMR course are:
epuck.hpp
fuzzy.h
lists.h
maps.h

See the documentation and write your own code into:
AIMR_2014/main.cpp

============================================
4-Additional step
============================================
If you are working on a personal laptop then you have to do one extra step before connecting laptop to robot:
Open and copy all the data from file "AIMR_2016/edit_rfcomm.txt"
Edit and paste into the file "/etc/bluetooth/rfcomm.conf"

============================================
5-enjoy!
============================================
