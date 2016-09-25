# ksnip

Currently in Beta!

Screenshot tool inspired by Windows Snipping Tool and made with Qt for Linux. 

### Building from source

1. Download the package from GitHub either by downloading the zip [here](https://github.com/damirporobic/ksnip/archive/master.zip) or by cloning the repository if you prefer git:  
    `> git clone https://github.com/damirporobic/ksnip.git  
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