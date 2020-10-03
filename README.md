# [ksnip](http://ksnip.org/) &middot; [![Build Status][travis-badge]][travis-url] [![GitHub commits (since latest release)][gh-comm-since-badge]][gh-comm-since-url] [![Translation status][weblate-badge]][weblate-url] [![GitHub total downloads][gh-dl-badge]][gh-dl-url] [![SourceForge total downloads][sf-dt-badge]][sf-dt-badge-url]

Version v1.8.0 - Work in Progress

Ksnip is a Qt-based cross-platform screenshot tool that provides many annotation features
for your screenshots.

![Ksnip](https://imgur.com/cogRcTo.png "Ksnip with annotations")

# Features
Latest ksnip version contains following features:
* Supports Linux (X11, Plasma Wayland, GNOME Wayland and xdg-desktop-portal Wayland), Windows and macOS.
* Screenshot of a custom rectangular area that can be drawn with mouse cursor.
* Screenshot of last selected rectangular area without selecting again.
* Screenshot of the screen/monitor where the mouse cursor is currently located.
* Screenshot of full-screen, including all screens/monitors.
* Screenshot of window that currently has focus.
* Screenshot of window under mouse cursor.
* Screenshot with or without mouse cursor.
* Capture mouse cursor as annotation item that can be moved and deleted.
* Customizable capture delay for all capture options.
* Upload screenshots directly to imgur.com in anonymous or user mode.
* Upload screenshots via custom user defined scripts.
* Command-line support, for capturing screenshots and saving to default location, filename and format.
* Filename wildcards for Year ($Y), Month ($M), Day ($D), Time ($T) and Counter (multiple # characters for number with zero-leading padding).
* Print screenshot or save it to PDF/PS.
* Annotate screenshots with pen, marker, rectangles, ellipses, texts and other tools.
* Annotate screenshots with stickers and add custom stickers.
* Obfuscate image regions with blur and pixelate.
* Add watermarks to captured images.
* Global hotkeys for capturing screenshots (currently only for Windows and X11).
* Tabs for screenshots and images.
* Open existing images via dialog, drag-and-drop or paste from clipboard.
* Run as single instance application (secondary instances send cli parameter to primary instance).
* Pin screenshots in frameless windows that stay atop other windows.
* Many configuration options.

# Supported Screenshot Types
|                    | Rect Area | Last Rect Area | Full Screen | Current Screen | Active Window | Window Under Cursor | Without Mouse Cursor | Screenshot Portal |
| -------------------|:---------:|:--------------:|:-----------:|:--------------:|:-------------:|:-------------------:|:--------------------:|:-----------------:|
| X11                | X         | X              | X           | X              | X             |                     | X                    |                   |
| Plasma Wayland     |           |                | X           | X              |               | X                   |                      |                   |
| Gnome Wayland      | X         | X              | X           | X              | X             |                     | X                    |                   |
| xdg-desktop-portal |           |                |             |                |               |                     |                      | X                 |
| Windows            | X         | X              | X           | X              | X             |                     | X                    |                   |
| macOS              | X         | X              | X           | X              |               |                     |                      |                   |

# Installing Binaries
Binaries can be downloaded from the release page [here](https://github.com/ksnip/ksnip/releases). Currently
RPM, DEB and AppImage for Linux, zipped EXE for Windows and APP for macOS in a DMG package is available.

### Continuous build
All supported binaries are built for every pushed commit, to be found at the top of the
release page. Continuous build artifacts are not fully tested and in most cases they are work in progress,
so use them with caution.

### AppImage (Linux)
To use AppImages, make them executable and run them, no installation required.
`$ chmod a+x ksnip*.AppImage`
`$ ./ksnip*.AppImage`

More info about setting to executable can be found [here](https://discourse.appimage.org/t/how-to-make-an-appimage-executable/80).

### RPM (Linux)
Just install them via RPM and use.
`$ rpm -Uvh ksnip*.rpm`
`$ ksnip`

### DEB (Linux)
Just install them via dpkg and start using.
`$ sudo dpkg -i ksnip*.deb`
`$ ksnip`

### Snap (Linux)
The usual method for Snaps, will install the latest version:
`$ sudo snap install ksnip`

The continuous build version is also available as edge, in order to install it you need to provide the edge flag:
`$ sudo snap install ksnip --edge`

Snap startup time can be sped up and console output cleaned up from following error `Could not create AF_NETLINK socket (Permission denied)` by running the following commands:
`$ snap connect ksnip:network-observe`
`$ snap connect ksnip:network-manager-observe`

If you need to save screenshots to a removable media, the following additional connection is required:
`$ snap connect ksnip:removable-media`

This only needs to be done once and connects some Snap plugs which are currently not auto-connected.

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/ksnip)

### Flatpak (Linux)
The usual method for Flatpaks will install the latest version:
`$ flatpak install flathub org.ksnip.ksnip`

Then just start it:
`$ flatpak run org.ksnip.ksnip`

<a href='https://flathub.org/apps/details/org.ksnip.ksnip'><img width='220' alt='Download on Flathub' src='https://flathub.org/assets/badges/flathub-badge-en.png'/></a>

### EXE (Windows)
The EXE file with all required dependencies comes in a zipped package, which just need to be unzipped
with your favorite unpacking tool. Ksnip can then be started by just double-clicking ksnip.exe.

### APP (macOS)
The app file comes in a DMG package which needs to be opened and the ksnip.app file needs to be dragged
and dropped into the "Application" folder. After that the application can be started by double clicking ksnip.app

### Homebrew Cask (macOS)
Just install via Homebrew and start using from your "Applications" folder.
`$ brew cask install ksnip`

# Dependencies
ksnip depends on [kImageAnnotator](https://github.com/ksnip/kImageAnnotator) and [kColorPicker](https://github.com/DamirPorobic/kColorPicker) which needs
to be installed before building ksnip from source. Installation instructions can be found on the Github pages.

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
As with all continuous translations, contributors are always welcome!
For translations [Weblate](https://hosted.weblate.org/projects/ksnip/translations/) is used.
[![Translation status](https://hosted.weblate.org/widgets/ksnip/-/translations/multi-green.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget)

For translations of annotator-related texts, please refer to [kImageAnnotator](https://github.com/ksnip/kImageAnnotator)

# Known Issues

### X11
1. Snipping area with transparent background doesn't work when compositor is turned off, freeze background is used in that case.

### macOS
1. Snipping area with transparent background doesn't work, freeze background is always used. Issue [#151](https://github.com/ksnip/ksnip/issues/151)
2. Second activation of snipping area doesn't get focus, you need to switch to the right side in order to see the snipping area. Issue [#152](https://github.com/ksnip/ksnip/issues/152)
3. Mouse cursor is always captured. Issue [#153](https://github.com/ksnip/ksnip/issues/153)

# Bug report
Please report any bugs or feature requests related to the annotation editor on the [kImageAnnotator](https://github.com/ksnip/kImageAnnotator/issues) GitHub page under the "Issue" section.
All other bugs or feature requests can be reported on the [ksnip](https://github.com/ksnip/ksnip/issues) GitHub page under the "Issue" section.

# Contribution
Any contribution welcome, be it code, translations or other things. Currently this is needed:
* Write code and fix bugs for macOS.
* Write wiki entries and documentation for ksnip.
* Package ksnip for different operating systems and distros.

# Donation 

ksnip is a non-profitable copylefted libre software project, and still has some costs that need to be covered, like domain costs or hardware costs for cross-platform support.
If you want to help or just want appreciate the work being done by treating developers to a beer or coffee,
you can do that [here](https://www.paypal.me/damirporobic), donations are always welcome :)

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
