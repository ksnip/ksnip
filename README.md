# ksnip [![Build Status](https://travis-ci.org/DamirPorobic/ksnip.svg?branch=master)](https://travis-ci.org/DamirPorobic/ksnip) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/94558bfc42d1466fae691a646cfe3f09)](https://www.codacy.com/app/DamirPorobic/ksnip?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DamirPorobic/ksnip&amp;utm_campaign=Badge_Grade) [![Translation status](https://hosted.weblate.org/widgets/ksnip/-/translations/svg-badge.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget) [![ksnip Downloads](https://img.shields.io/github/downloads/damirporobic/ksnip/total.svg)](https://github.com/damirporobic/ksnip/releases)

Version v1.5.0 - alpha

Ksnip is a Qt based Linux screenshot tool that provides many annotation features 
for your screenshots.

![Ksnip](https://i.imgur.com/Zvnl8PT.png "Ksnip with annotations")


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
* Annotate image with pen, marker, rectangles, ellipses, text and other.
* Command line support, for taking screenshot and saving it to default location, filename and format.
* Customizable default location, filename and format for saving new screenshots with wildcards for Year ($Y), Month ($M), Day ($D) and Time ($T).
* Print screenshot or save is to pdf/ps.
* Undo/Redo for paint and crop operations.
* Smooth out free hand pen and marker lines (can be disabled in settings).
* Drop shadow for paint items (can be disabled in settings).
* And other configuration options.


### AppImage
In order to use AppImages, just download them from [here](https://github.com/damirporobic/ksnip/releases), make them executable and start using it, no installation required.  
`$ chmod a+x ksnip*.AppImage`  
`$ ./ksnip*.AppImage`

More information about setting to executable can be found [here](https://discourse.appimage.org/t/how-to-make-an-appimage-executable/80).


### RPM and DEB Binaries
RPM and DEB binaries can be downloaded from the release page [here](https://github.com/DamirPorobic/ksnip/releases).

Installing RPM:  
`$ rpm -Uvh ksnip*.rpm`  
`$ ksnip`  

Installing DEB:  
`$ sudo dpkg -i ksnip*.deb`  
`$ ksnip`  


### Building from source

1. Get latest release from GitHub by cloning the repo:  
    `$ git clone https://github.com/DamirPorobic/ksnip`  
2. Change to repo directory:  
    `$ cd ksnip`  
3. Resolve dependencies by fetching git submodules:  
    `$ git submodule update --init --recursive`  
4. Make new build directory and enter it:  
    `$ mkdir build && cd build`  
5. Create the makefile and build the project:  
    `$ cmake .. && make`  
6. Now install the application, eventually you need to run it with sudo:  
    `$ sudo make install`  
6. Run the application:  
    `$ ksnip`  


### Translations
We are always looking for help with translations, contributors are welcome!  
For translations we use [Weblate](https://hosted.weblate.org/projects/ksnip/translations/)!  
[![Translation status](https://hosted.weblate.org/widgets/ksnip/-/translations/multi-green.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget)

### Bug report
Please report any bugs or feature requests on the github page under the [issue section](https://github.com/DamirPorobic/ksnip/issues).
