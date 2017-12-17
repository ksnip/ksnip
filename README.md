# ksnip

Version v1.4.0

Ksnip is a Qt based Linux screenshot tool inspired by Microsoft's Snipping Tool.

### Features
Latest ksnip version contains following features:
* Taking Screenshot of a custom rectangular area that can be drawn with mouse cursor.
* Taking screenshot of the screen/monitor where the mouse cursor is currently located.
* Taking screenshot of full screen, including all screens/monitors.
* Taking screenshot of window that currently has focus.
* Take screenshot with or without mouse cursor.
* Customizable capture delay for all capture options.
* Upload screenshots directly to imgur.com in anonymous or user mode.
* Drawing on captured screenshot with two different tools, pen (opaque) and maker (semi-transparent).
* Drawing two shapes ellipse and rectangle, with and without fill.
* Drawing lines and arrows.
* Customizable color and size (thickness) for all drawing tools.
* Writing text on screenshots, with customizable font, size, color etc.
* Numbering tool with customizable font and color.
* Any drawing (or multiple selection) can be moved around without deleting it by simply dragging it to new location.
* Ordering paint items (bring to front, send to back).
* Cropping captured screensshot, including any drawing on the captured image.
* Command line support, for taking screenshot and saving it to default location, filename and format.
* Customizable default location, filename and format for saving new screenshots with wildcards for Year ($Y), Month ($M), Day ($D) and Time ($T).
* Print screenshot or save is to pdf/ps.
* Undo/Redo for paint and crop operations.
* Smooth out free hand pen and marker lines (can be disabled in settings).
* Drop shadow for paint items (can be disabled in settings).
* And other configuration options.


### Building from source

1. Get latest release from GitHub by downloading either the zip or tar.gz package from https://github.com/damirporobic/ksnip/releases  
2. Change to download directory, unpack the package and go to new directory:  
    `$ cd ~/Downloads`    
    `$ unzip ksnip-1.x.x.zip`
    `$ cd ksnip-1.x.x`
3. Make new build directory and enter it:  
    `$ mkdir build`  
    `$ cd build`  
4. Create the makefile and build the project:  
    `$ cmake ..`  
    `$ make`  
5. Now install the application, eventually you need to run it with sudo:  
    `$ sudo make install`  
5. Run the application:  
    `$ ksnip`  


### Bug report
Please report any bugs or feature requests on the github page under the issue section https://github.com/DamirPorobic/ksnip/issues.


### Other
For Gentoo, check out this link https://github.com/mrbitt/mrbit-overlay/blob/master/x11-apps/ksnip/ksnip-1.3.1.ebuild
