# ksnip

Version v1.1.0

Screenshot tool inspired by Windows Snipping Tool and made with Qt for Linux. 


### Building from source

1. Get latest release from GitHub by downloading either the zip or tar.gz package from https://github.com/damirporobic/ksnip/releases  
2. Change to download directory, unpack the package and go to new directory:  
    `> cd ~/Downloads`    
    `> unzip ksnip-1.x.x.zip`
    `> cd ksnip-1.x.x`
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
