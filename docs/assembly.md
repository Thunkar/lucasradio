# Wiring

## Preparation

Space is at a premium, so it is recommended to either desolder or cut all pins and connectors from the ESP32 A1S board. Every connection is going to be soldered on!

<img src="./img/esp32a1sdiagram.png" width="800">

Switches should be in the following configuration: **ON | ON | ON | OFF | OFF**

## Battery

The battery cables should be long enough to run underneath the ESP32 when mounted to the base. The switch should interrupt one of them:

<img src="./img/battery-connection.png" width="500">

## Hall effect sensor

The hall effect sensor *MUST* be mounted with the beveled side facing **UP**. Only one magnet orientation is going to trigger it, so it is recommended to test this before finalizing the assembly.

## NFC
Make sure the PN532 is in I2C mode!

<img src="./img/pn532-i2c.png" width="500">

After that, connect it as follows:

<img src="./img/nfg-connection.png" width="500">

# Assembly

Check out the diagram below to understand how it all fits together. It is recommended to do the wiring first! <br/>
<img src="./img/diagram.jpg" width="500">
