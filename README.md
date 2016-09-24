# ksnip

Screenshot tool inspired by Windows Snipping Tool and made with Qt for Linux. 

*** CURRENTLY PROJECT IS WORK IN PROGRESS ***

### Building from source

1. Download the zip package from GitHub
2. Change to download directory, unpack the package and go to new directory:  
    `> cd ~/Downloads`  
    `> unzip ksnip-master.zip`  
    `> cd ksnip-master`  
3. Make new build directory and enter it:  
    `> mkdir build`  
    `> cd build`  
4. Create the makefile and build the project:  
    `> cmake ..`  
    `> make`  
5. Now install the application, eventually you need to run it with sudo:
    `> sudo make install`
5. Run the application:  
    `> ksnip`