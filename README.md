# Byrd

A simple and easy terminal for linux written in C.


### Installation

1. `git clone https://github.com/Flyken271/Byrd.git`
2. `cd Byrd`
3. `sudo mkdir /opt/Byrd/ && mkdir /usr/bin/Byrd/`
4. `sudo cp Byrd /opt/Byrd/`
5. `sudo cp -s /opt/Byrd/Byrd /usr/bin/Byrd/`
6. `add "export PATH=$PATH:/opt/Byrd/Byrd" to .bashrc or something that applies to you`
7. `cp the Byrd.conf file to where the binary will be ran, the conf file needs to be in the same directory as the binary; all of the values and settings in the conf are documented.`

## Configuration
The configuration file needs to be in the directory where Byrd binary is, you can compile from source and change where the conf file is needed to be; the configuration file is pre-loaded with a single option for alpha, it uses floats, 0-1, 1 being fully visible, 0 being fully transparent.

### Dependencies
`libconfig vte-2.91`


### Tips
[Buy Me A Coffee](https://www.buymeacoffee.com/DFLhquo)
