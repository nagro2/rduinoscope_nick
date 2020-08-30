# rduinoscope_nick

A fork of the terrific rDuinoscope telescope control project originally created by Dessislav Gouzgounov, with numerous additions and enhancements.
This project also includes code from other forks of rDuinoscope including by giacu92.

*Differences between this version and the original  
 *- Object filtering screen allows filtering of objects by object type, brightness, and angle in sky  
 *- object selection screens can show magnitude and size of each object. This can be turned on or off via boolean variables in the code  
 *- adjusts for USA and Europe DST / Summer, use DST_mode to set desired mode.
 *- sets time from gps clock if fix obtainbed, otherwise RTC module
 *- gps skip button loads last valid gps fix from SD card
 *- color coded indication of alignment quality in 1 star alignment screen
 *- easily configure RA and Dec motor direction using RA_reverse and DEC_reverse variables
 *- message on main screen indicates when the scope is slewing
 *- autoguiding feature (still under development and untested)
 *- Uses ILI9488 spi display with xpi_2046 spi touch
 *- gps module connects at 4800 baud
 *- Some Arduino pin definitions are different from the main version
 *- Sound 3 notes at startup plus a warble if any startup errors
 
 Some time ago I stopped developing and using this code. The code runs well but may still have bugs. I am posting it in hopes that it will be helpful to others.
