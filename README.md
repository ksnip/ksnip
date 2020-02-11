# [ksnip](http://ksnip.org/) &middot; [![Build Status][travis-badge]][travis-url] [![GitHub commits (since latest release)][gh-comm-since-badge]][gh-comm-since-url] [![Translation status][weblate-badge]][weblate-url] [![GitHub total downloads][gh-dl-badge]][gh-dl-url] [![SourceForge total downloads][sf-dt-badge]][sf-dt-badge-url] 


Version v1.6.1

Ksnip is a Qt based cross-platform screenshot tool that provides many annotation features 
for your screenshots.

![Ksnip](https://i.imgur.com/TsDWwXC.png "Ksnip with annotations")


# Features
Latest ksnip version contains following features:
* Supports Linux (X11 and experimental KDE and Gnome Wayland support), Windows and MacOS.
* Taking screenshot of a custom rectangular area that can be drawn with mouse cursor.
* Taking screenshot of last selected rectangular area without selecting again.
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
* Global HotKeys for taking Screenshots (Currently only for Windows and X11).
* Many configuration options.


# Supported Screenshot Types
|              | Rect Area | Last Rect Area | Full Screen | Current Screen | Active Window | Window Under Cursor | Without Mouse Cursor |
| -------------|:---------:|:--------------:|:-----------:|:--------------:|:-------------:|:-------------------:|:--------------------:|
| X11          | X         | X              | X           | X              | X             |                     | X                    |
| KDE Wayland  |           |                | X           | X              |               | X                   |                      |
| Gnome Wayland| X         | X              | X           | X              | X             |                     | X                    |
| Windows      | X         | X              | X           | X              | X             |                     | X                    |
| MacOS        | X         | X              | X           | X              |               |                     |                      |


# Installing Binaries
Binaries can be downloaded from the release page [here](https://github.com/ksnip/ksnip/releases). Currently we 
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
ksnip depends on [kImageAnnotator](https://github.com/ksnip/kImageAnnotator) and [kColoPicker](https://github.com/DamirPorobic/kColorPicker) which needs
to be installed before building ksnip from source. Install instructions can be found on the github pages.


# Building from source
1. Get latest release from GitHub by cloning the repo:  
    `$ git clone https://github.com/ksnip/ksnip`  
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
1. Snipping Area with transparent background doesn't work, freeze background is always used. Issue [#151](https://github.com/ksnip/ksnip/issues/151)
2. Second activation of snipping area doesn't get focus, you need to switch to the right side in order to see the snipping area. Issue [#152](https://github.com/ksnip/ksnip/issues/152)
3. Mouse Cursor is always captured. Issue [#153](https://github.com/ksnip/ksnip/issues/153)


# Bug report
Please report any bugs or feature requests related to the annotation editor on the [kImageAnnotator](https://github.com/ksnip/kImageAnnotator/issues) github page under the issue section.
All other bugs or feature requests please report on the [ksnip](https://github.com/ksnip/ksnip/issues) github page under the issue section.

# Contribution
Any contribution, be it Code, Translation or other is always welcome. We are currently looking for someone to help produce a Snap [#147](https://github.com/ksnip/ksnip/issues/147) and Flatpak [#127](https://github.com/ksnip/ksnip/issues/127) 
version of ksnip and also help with setting up the CI/CD Pipeline for building both. Another area where help is wanted is MacOS support, we are currently looking for someone who
could help fix bugs under MacOS.

# Donate a Beer?
You would like to donate a Beer? Sure, you can do that [here](https://www.paypal.me/damirporobic), donations are always welcome :)

[travis-badge]:        https://img.shields.io/travis/ksnip/ksnip.svg?label=travis&logo=travis
[travis-url]:          https://travis-ci.org/ksnip/ksnip

[weblate-badge]:       https://hosted.weblate.org/widgets/ksnip/-/translations/svg-badge.svg
[weblate-url]:         https://hosted.weblate.org/engage/ksnip/?utm_source=widget

[gh-dl-badge]:         https://img.shields.io/github/downloads/damirporobic/ksnip/total.svg?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSI0MCIgaGVpZ2h0PSI0MCIgdmlld0JveD0iMTIgMTIgNDAgNDAiPjxwYXRoIGZpbGw9IiNmZmYiIGQ9Ik0zMiwxMy40Yy0xMC41LDAtMTksOC41LTE5LDE5YzAsOC40LDUuNSwxNS41LDEzLDE4YzEsMC4yLDEuMy0wLjQsMS4zLTAuOWMwLTAuNSwwLTEuNywwLTMuMiBjLTUuMywxLjEtNi40LTIuNi02LjQtMi42QzIwLDQxLjYsMTguOCw0MSwxOC44LDQxYy0xLjctMS4yLDAuMS0xLjEsMC4xLTEuMWMxLjksMC4xLDIuOSwyLDIuOSwyYzEuNywyLjksNC41LDIuMSw1LjUsMS42IGMwLjItMS4yLDAuNy0yLjEsMS4yLTIuNmMtNC4yLTAuNS04LjctMi4xLTguNy05LjRjMC0yLjEsMC43LTMuNywyLTUuMWMtMC4yLTAuNS0wLjgtMi40LDAuMi01YzAsMCwxLjYtMC41LDUuMiwyIGMxLjUtMC40LDMuMS0wLjcsNC44LTAuN2MxLjYsMCwzLjMsMC4yLDQuNywwLjdjMy42LTIuNCw1LjItMiw1LjItMmMxLDIuNiwwLjQsNC42LDAuMiw1YzEuMiwxLjMsMiwzLDIsNS4xYzAsNy4zLTQuNSw4LjktOC43LDkuNCBjMC43LDAuNiwxLjMsMS43LDEuMywzLjVjMCwyLjYsMCw0LjYsMCw1LjJjMCwwLjUsMC40LDEuMSwxLjMsMC45YzcuNS0yLjYsMTMtOS43LDEzLTE4LjFDNTEsMjEuOSw0Mi41LDEzLjQsMzIsMTMuNHoiLz48L3N2Zz4=
[gh-dl-url]:           https://github.com/ksnip/ksnip/releases

[sf-dt-badge]:         https://img.shields.io/sourceforge/dt/ksnip.svg?logo=data:image/svg+xml;base64,PCFET0NUWVBFIHN2ZyBQVUJMSUMgIi0vL1czQy8vRFREIFNWRyAyMDAxMDkwNC8vRU4iICJodHRwOi8vd3d3LnczLm9yZy9UUi8yMDAxL1JFQy1TVkctMjAwMTA5MDQvRFREL3N2ZzEwLmR0ZCI+PHN2ZyB2ZXJzaW9uPSIxLjAiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgd2lkdGg9IjMzMHB4IiBoZWlnaHQ9IjMzMHB4IiB2aWV3Qm94PSIwIDAgMzMwMCAzMzAwIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCBtZWV0Ij48ZyBpZD0ibGF5ZXIxMDEiIGZpbGw9IiNmZmYiIHN0cm9rZT0ibm9uZSI+IDxwYXRoIGQ9Ik0xNTI4IDMwMTkgYy0xMCAtNSAtMTggLTIwIC0xOCAtMzIgMCAtMTYgMTczIC0xOTUgNjA3IC02MjkgNTYyIC01NjIgNjA2IC02MDkgNjA1IC02MzkgLTEgLTI5IC00OSAtODEgLTQ4MSAtNTEzIC0zMjMgLTMyMyAtNDgxIC00ODggLTQ4MSAtNTAyIDAgLTIzIDE5OCAtMjI0IDIyMSAtMjI0IDE5IDAgMTIzOSAxMjIxIDEyMzkgMTI0MCAwIDggLTI5MSAzMDYgLTY0NyA2NjIgbC02NDggNjQ4IC0xOTAgMCBjLTExMCAwIC0xOTcgLTUgLTIwNyAtMTF6Ii8+IDxwYXRoIGQ9Ik02ODIgMjIwNiBjLTQwMSAtNDAwIC02MTMgLTYxOSAtNjExIC02MjkgNCAtMTggMTI2MiAtMTI4MiAxMjkxIC0xMjk4IDIzIC0xMyAzNzUgLTEyIDM5OSAxIDEwIDYgMTkgMjEgMTkgMzMgMCAxNSAtMTcyIDE5NCAtNjA0IDYyNyAtMzMzIDMzMyAtNjA1IDYxMiAtNjA2IDYyMCAtMiA4IC0yIDI0IC0xIDM1IDEgMTIgMTkzIDIxMiA0ODEgNTAwIDMwOCAzMDggNDgwIDQ4NyA0ODAgNTAwIDAgMjMgLTE5NyAyMjUgLTIyMCAyMjUgLTggMCAtMjkxIC0yNzYgLTYyOCAtNjE0eiIvPiA8cGF0aCBkPSJNMTU5MiAyMjM5IGMtMTM5IC0yMyAtMjY5IC0xMjMgLTMzNiAtMjYwIC00NiAtOTUgLTYwIC0xNjkgLTUyIC0yODkgMTAgLTE2MiA1MSAtMjU4IDE4NiAtNDMxIDEwOCAtMTM4IDEzOCAtMTk2IDE1MyAtMjg4IDEyIC04MyAyNiAtOTAgNzMgLTM4IDgxIDg2IDEzNyAxODYgMTc5IDMxNyA0MCAxMjYgNTUgMjE2IDY2IDQwMCA2IDkxIDE2IDE3NiAyMiAxOTAgMTggMzcgNTEgMzcgNzYgMSA0OCAtNjYgNTUgLTEwNiA1NSAtMjg0IDAgLTEwOSA0IC0xNjYgMTEgLTE2NCAxNiA1IDUzIDkxIDgwIDE4NCA5MSAzMTIgLTg3IDYyMCAtMzgxIDY2MyAtMzggNSAtNzEgOSAtNzQgOSAtMyAtMSAtMjkgLTUgLTU4IC0xMHoiLz4gPC9nPjwvc3ZnPg==
[sf-dt-badge-url]:     https://sourceforge.net/projects/ksnip

[gh-comm-since-badge]: https://img.shields.io/github/commits-since/damirporobic/ksnip/latest.svg?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSI0MCIgaGVpZ2h0PSI0MCIgdmlld0JveD0iMTIgMTIgNDAgNDAiPjxwYXRoIGZpbGw9IiNmZmYiIGQ9Ik0zMiwxMy40Yy0xMC41LDAtMTksOC41LTE5LDE5YzAsOC40LDUuNSwxNS41LDEzLDE4YzEsMC4yLDEuMy0wLjQsMS4zLTAuOWMwLTAuNSwwLTEuNywwLTMuMiBjLTUuMywxLjEtNi40LTIuNi02LjQtMi42QzIwLDQxLjYsMTguOCw0MSwxOC44LDQxYy0xLjctMS4yLDAuMS0xLjEsMC4xLTEuMWMxLjksMC4xLDIuOSwyLDIuOSwyYzEuNywyLjksNC41LDIuMSw1LjUsMS42IGMwLjItMS4yLDAuNy0yLjEsMS4yLTIuNmMtNC4yLTAuNS04LjctMi4xLTguNy05LjRjMC0yLjEsMC43LTMuNywyLTUuMWMtMC4yLTAuNS0wLjgtMi40LDAuMi01YzAsMCwxLjYtMC41LDUuMiwyIGMxLjUtMC40LDMuMS0wLjcsNC44LTAuN2MxLjYsMCwzLjMsMC4yLDQuNywwLjdjMy42LTIuNCw1LjItMiw1LjItMmMxLDIuNiwwLjQsNC42LDAuMiw1YzEuMiwxLjMsMiwzLDIsNS4xYzAsNy4zLTQuNSw4LjktOC43LDkuNCBjMC43LDAuNiwxLjMsMS43LDEuMywzLjVjMCwyLjYsMCw0LjYsMCw1LjJjMCwwLjUsMC40LDEuMSwxLjMsMC45YzcuNS0yLjYsMTMtOS43LDEzLTE4LjFDNTEsMjEuOSw0Mi41LDEzLjQsMzIsMTMuNHoiLz48L3N2Zz4=
[gh-comm-since-url]:   https://github.com/ksnip/ksnip/releases/tag/continuous
