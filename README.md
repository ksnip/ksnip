# ksnip [![Build Status](https://travis-ci.org/DamirPorobic/ksnip.svg?branch=master)](https://travis-ci.org/DamirPorobic/ksnip) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/94558bfc42d1466fae691a646cfe3f09)](https://www.codacy.com/app/DamirPorobic/ksnip?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DamirPorobic/ksnip&amp;utm_campaign=Badge_Grade) [![Weblate TRanslations](https://hosted.weblate.org/widgets/ksnip/-/svg-badge.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget)

Version v1.5.0 - alpha

Ksnip is a Qt based Linux screenshot tool that provides many annotation features 
for your screenshots.

![Ksnip](https://i.imgur.com/7FF2kkk.jpg "Ksnip with annotations")


### Features
Latest ksnip version contains following features:
* X11 and experimental KDE and Gnome Wayland support.
* Taking Screenshot of a custom rectangular area that can be drawn with mouse cursor (X11 and Gnome Wayland only).
* Taking screenshot of the screen/monitor where the mouse cursor is currently located.
* Taking screenshot of full screen, including all screens/monitors.
* Taking screenshot of window that currently has focus (X11 and Gnome Wayland only).
* Taking screenshot of window under mouse cursor (KDE Wayland only).
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


### AppImage
Starting with version 1.4.0 we provide an AppImage of Ksnip, which can be downloaded from the release page. 
Starting with version 1.5.0 we have a continues build AppImage which is build after every commit and is uploaded to the release page as Continues Build release. Continues Build AppImages are considered alpha versions and work in progress. 

In order to use AppImages, just download them from [here](https://github.com/damirporobic/ksnip/releases), make them executable and start using it, no installation required.  
`$ cd ~/Downloads`  
`$ chmod a+x ksnip*.AppImage`  
`$ ./ksnip*.AppImage`

More information about setting to executable can be found [here](https://discourse.appimage.org/t/how-to-make-an-appimage-executable/80).


### RPM and DEB Binaries
Starting with version 1.3.2 we provide ksnip as 32bit and 64bit DEB binariy and 64bit RPM binary. RPM and DEB binaries are created only at release of a version and currently we have no continues build that creates those binaries after every commit. RPM and DEB binaries can be downloaded from the relese page [here](https://github.com/DamirPorobic/ksnip/releases).

Installing RPM:  
`$ cd ~/Downloads`  
`$ rpm -Uvh ksnip*.rpm`  
`$ ksnip`  

Installing DEB:  
`$ cd ~/Downloads`  
`$ sudo dpkg -i ksnip*.deb`  
`$ ksnip`  


### Building from source
1. Get latest release from GitHub by downloading either the zip or tar.gz package from [here](https://github.com/damirporobic/ksnip/releases).  
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
6. Run the application:  
    `$ ksnip`  


### Translations
We are always looking for help with tranlsations, contributors are welcome!  
For translations we use [Weblate](https://weblate.org/en/)!  
<a href="https://hosted.weblate.org/engage/ksnip/?utm_source=widget">
<img src="https://hosted.weblate.org/widgets/ksnip/-/multi-green.svg" alt="Translation status" />
</a>

### Bug report
Please report any bugs or feature requests on the github page under the [issue section](https://github.com/DamirPorobic/ksnip/issues).
