# [ksnip](http://ksnip.org/) &middot; [![Build Status](https://travis-ci.org/DamirPorobic/ksnip.svg?branch=master)](https://travis-ci.org/DamirPorobic/ksnip) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/94558bfc42d1466fae691a646cfe3f09)](https://www.codacy.com/app/DamirPorobic/ksnip?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DamirPorobic/ksnip&amp;utm_campaign=Badge_Grade) [![Translation status](https://hosted.weblate.org/widgets/ksnip/-/translations/svg-badge.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget) [![ksnip Downloads](https://img.shields.io/github/downloads/damirporobic/ksnip/total.svg)](https://github.com/damirporobic/ksnip/releases)


Version v1.6.0 - alpha

Ksnip is a Qt based cross-platform screenshot tool that provides many annotation features 
for your screenshots.

![Ksnip](https://i.imgur.com/TsDWwXC.png "Ksnip with annotations")


# Features
Latest ksnip version contains following features:
* Supports Linux (X11 and experimental KDE and Gnome Wayland support), Windows and MacOS.
* Taking screenshot of a custom rectangular area that can be drawn with mouse cursor.
* Taking screenshot of the screen/monitor where the mouse cursor is currently located.
* Taking screenshot of full screen, including all screens/monitors.
* Taking screenshot of window that currently has focus.
* Taking screenshot of window under mouse cursor.
* Take screenshot with or without mouse cursor.
* Capture mouse cursor as annotation item that can be moved and deleted.
* Customizable capture delay for all capture options.
* Upload screenshots directly to imgur.com in anonymous or user mode.
* Command line support, for taking screenshot and saving it to default location, filename and format.
* Customizable default location, filename and format for saving new screenshots with wildcards for Year ($Y), Month ($M), Day ($D) and Time ($T).
* Print screenshot or save is to pdf/ps.
* Annotate screenshots with pen, marker, rectangles, ellipses, texts and other tools.
* Add watermarks to captured images.
* Many configuration options.


# Supported Screenshot Types
|              | Rect Area | Full Screen | Current Screen | Active Window | Window Under Cursor | Without Mouse Cursor |
| -------------|:---------:|:-----------:|:--------------:|:-------------:|:-------------------:|:--------------------:|
| X11          | X         | X           | X              | X             |                     | X                    |
| KDE Wayland  |           | X           | X              |               | X                   |                      |
| Gnome Wayland| X         | X           | X              | X             |                     | X                    |
| Windows      | X         | X           | X              | X             |                     | X                    |
| MacOS        | X         | X           | X              |               |                     |                      |


# Installing Binaries
Binaries can be downloaded from the release page [here](https://github.com/damirporobic/ksnip/releases). Currently we 
provide RPM, DEB and AppImage for Linux, zipped EXE for Windows and APP for MacOS in a DMG package.

### Continuous build
We build and provide all supported binaries for every pushed commit, those can be found at the top of the
release page. Continuous build artifacts are not fully tested and in most cases they are work in progress
so use them with caution.

### AppImage (Linux)
In order to use AppImages, make them executable and start using it, no installation required.  
`$ chmod a+x ksnip*.AppImage`  
`$ ./ksnip*.AppImage`

More information about setting to executable can be found [here](https://discourse.appimage.org/t/how-to-make-an-appimage-executable/80).

### RPM (Linux)
Just install them via rpm and start using.  
`$ rpm -Uvh ksnip*.rpm`  
`$ ksnip`  

### DEB (Linux)
Just install them via dpkg and start using.  
`$ sudo dpkg -i ksnip*.deb`  
`$ ksnip`  

### EXE (Windows)
The exe file with all required dependencies comes in a zipped package, which just need to be unzipped 
with your favorite zip tool. Ksnip can then be started by just double clicking ksnip.exe.

### APP (MacOS)
The app file comes in a dmg package which needs to be opened and the ksnip.app file needs to be dragged 
and dropped into the Application folder. After that the application can be started by double clicking ksnip.app


# Dependencies
ksnip depends on [kImageAnnotator](https://github.com/DamirPorobic/kImageAnnotator) and [kColoPicker](https://github.com/DamirPorobic/kColorPicker) which needs
to be installed before building ksnip from source. Install instructions can be found on the github pages.


# Building from source
1. Get latest release from GitHub by cloning the repo:  
    `$ git clone https://github.com/DamirPorobic/ksnip`  
2. Change to repo directory:  
    `$ cd ksnip`  
3. Make new build directory and enter it:  
    `$ mkdir build && cd build`  
4. Create the makefile and build the project:  
    `$ cmake .. && make`  
5. Now install the application, eventually you need to run it with sudo:  
    `$ sudo make install`  
6. Run the application:  
    `$ ksnip`  


# Translations
We are always looking for help with translations, contributors are welcome!  
For translations we use [Weblate](https://hosted.weblate.org/projects/ksnip/translations/)!  
[![Translation status](https://hosted.weblate.org/widgets/ksnip/-/translations/multi-green.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget)


# Known Issues

### X11
1. Snipping Area with transparent background doesn't work when Compositor is disabled, freeze background is used in that case.

### MacOs
1. Snipping Area with transparent background doesn't work, freeze background is always used. Issue [#151](https://github.com/DamirPorobic/ksnip/issues/151)
2. Second activation of snipping area doesn't get focus, you need to switch to the right side in order to see the snipping area. Issue [#152](https://github.com/DamirPorobic/ksnip/issues/152)
3. Mouse Cursor is always captured. Issue [#153](https://github.com/DamirPorobic/ksnip/issues/153)


# Bug report
Please report any bugs or feature requests related to the annotation editor on the [kImageAnnotator](https://github.com/DamirPorobic/kImageAnnotator/issues) github page under the issue section.
All other bugs or feature requests please report on the [ksnip](https://github.com/DamirPorobic/ksnip/issues) github page under the issue section.


# Donate a Beer?
You would like to donate a Beer? Sure, you can do that [here](https://paypal.com/paypalme2/damirporobic), donations are always welcome :)
