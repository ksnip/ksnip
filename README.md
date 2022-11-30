# [ksnip](http://ksnip.org/) 
[![Linux build status][github-linux-badge]][github-linux-url] [![Windows build status][github-windows-badge]][github-windows-url] [![MacOS build status][github-macos-badge]][github-macos-url] [![GitHub commits (since latest release)][gh-comm-since-badge]][gh-comm-since-url]  
[![Translation status][weblate-badge]][weblate-url] [![GitHub total downloads][gh-dl-badge]][gh-dl-url] [![SourceForge total downloads][sf-dt-badge]][sf-dt-badge-url] [![Discord][discord-badge]][discord-badge-url]
[![IRC: #ksnip on libera.chat][libera-badge]][libera-badge-url]
[![GitHub license](https://img.shields.io/github/license/ksnip/ksnip?color=lightgrey)](https://github.com/ksnip/ksnip/blob/master/LICENSE.txt)

Version v1.10.1

Ksnip is a Qt-based cross-platform screenshot tool that provides many annotation features
for your screenshots.

![ksnip](https://i.imgur.com/0oP6i1H.png "Ksnip with annotations")

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
* Upload screenshots via FTP in anonymous or user mode.
* Upload screenshots via custom user defined scripts.
* Command-line support, for capturing screenshots and saving to default location, filename and format.
* Filename wildcards for Year ($Y), Month ($M), Day ($D), Time ($T) and Counter (multiple # characters for number with zero-leading padding).
* Print screenshot or save it to PDF/PS.
* Annotate screenshots with pen, marker, rectangles, ellipses, texts and other tools.
* Annotate screenshots with stickers and add custom stickers.
* Crop and cut out vertical/horizontal slices of images.
* Obfuscate image regions with blur and pixelate.
* Add effects to image (Drop Shadow, Grayscale, invert color or Border).
* Add watermarks to captured images.
* Global hotkeys for capturing screenshots (currently only for Windows and X11).
* Tabs for screenshots and images.
* Open existing images via dialog, drag-and-drop or paste from clipboard.
* Run as single instance application (secondary instances send cli parameter to primary instance).
* Pin screenshots in frameless windows that stay atop other windows.
* User-defined actions for taking screenshot and post-processing.
* OCR support through plugin (Window and Linux/Unix).
* Many configuration options.

# Supported Screenshot Types
|                     | Rect Area | Last Rect Area | Full Screen | Current Screen | Active Window | Window Under Cursor | Without Mouse Cursor | Screenshot Portal |
| --------------------|:---------:|:--------------:|:-----------:|:--------------:|:-------------:|:-------------------:|:--------------------:|:-----------------:|
| X11                 | X         | X              | X           | X              | X             |                     | X                    |                   |
| Plasma Wayland      |           |                | X           | X              |               | X                   |                      |                   |
| Gnome Wayland `< 41`| X         | X              | X           | X              | X             |                     | X                    |                   |
| xdg-desktop-portal* |           |                |             |                |               |                     |                      | X                 |
| Windows             | X         | X              | X           | X              | X             |                     | X                    |                   |
| macOS               | X         | X              | X           | X              |               |                     |                      |                   |

&ast; xdg-desktop-portal screenshots are screenshots taken by the compositor and passed to ksnip, you will see a popup dialog that required additional confirmation,
    the implementation can vary depending on the compositor. Currently, Snaps and Gnome Wayland `>= 41` only support xdg-desktop-portal screenshots, this is a
    limitation coming from the Gnome and Snaps, non-native screenshot tools are not allowed to take screenshots in any other way except through the xdg-desktop-portal.
    
# Installing Binaries
Binaries can be downloaded from the [Releases page](https://github.com/ksnip/ksnip/releases). 
Currently, RPM, DEB, APT, Snap, Flatpak and AppImage for Linux, 
zipped EXE for Windows and 
APP for macOS in a DMG package are available.

### Continuous build
All supported binaries are built for every pushed commit, to be found at the top of the
release page. Continuous build artifacts are not fully tested and in most cases they are work in progress,
so use them with caution.

## Linux

*Click on the item, to expand information.*

<details>
  <summary>AppImage</summary>

To use AppImages, make them executable and run them, no installation required.
```
$ chmod a+x ksnip*.AppImage
$ ./ksnip*.AppImage
```

More info about setting to executable can be found [here](https://discourse.appimage.org/t/how-to-make-an-appimage-executable/80).
</details>

<details>
  <summary>RPM</summary>

Just install them via RPM and use.
```
$ rpm -Uvh ksnip*.rpm
$ ksnip
```
</details>

<details>
  <summary>DEB</summary>

Just install them via apt and start using.
```
$ sudo apt install ./ksnip*.deb
$ ksnip
```
</details>

<details>
  <summary>APT</summary>

Starting with Ubuntu 21.04 Hirsute Hippo, you can install from the [official package](https://launchpad.net/ubuntu/+source/ksnip):
```
$ sudo apt install ksnip
```

For older Ubuntu versions, you can use [@nemonein](https://github.com/nemonein)'s unofficial [PPA](url):
```
sudo add-apt-repository ppa:nemonein/ksnip
sudo apt update
sudo apt install ksnip
```

For Debian 11 and later releases, you can install from the [official package](https://tracker.debian.org/pkg/ksnip):
```
$ sudo apt install ksnip
```

For Debian 10 and Debian 9, ksnip is available via [Debian Backports](https://backports.debian.org/).
Please enable `bullseye-backports` and `buster-backports` repo for Debian 10 and Debian 9 respectively before installing using `sudo apt install ksnip`.
</details>

<details>
  <summary>ArchLinux</summary>

Ksnip is in the [Community repository](https://archlinux.org/packages/community/x86_64/ksnip/), so you can install it directly via pacman.
```
$ sudo pacman -S ksnip
```

If you want to build from the GIT repository, you can use the [AUR package](https://aur.archlinux.org/packages/ksnip-git/) (make sure you build the necessary dependencies too).
```
$ yay -S ksnip-git kimageannotator-git kcolorpicker-git
```
</details>

<details>
  <summary>Snap</summary>

The usual method for Snaps, will install the latest version:
```
$ sudo snap install ksnip
```

The continuous build version is also available as edge, in order to install it you need to provide the edge flag:
```
$ sudo snap install ksnip --edge
```

Snap startup time can be sped up and console output cleaned up from following error `Could not create AF_NETLINK socket (Permission denied)` by running the following commands:
```
$ snap connect ksnip:network-observe
$ snap connect ksnip:network-manager-observe
```

If you need to save screenshots to a removable media, the following additional connection is required:
```
$ snap connect ksnip:removable-media
```

This only needs to be done once and connects some Snap plugs which are currently not auto-connected.

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/ksnip)
</Details>

<details>
  <summary>Flatpak</summary>

The usual method for Flatpaks will install the latest version:
```
$ flatpak install flathub org.ksnip.ksnip
```

Then just start it:
```
$ flatpak run org.ksnip.ksnip
```

<a href='https://flathub.org/apps/details/org.ksnip.ksnip'><img width='220' alt='Download on Flathub' src='https://flathub.org/assets/badges/flathub-badge-en.png'/></a>
</details>

## Windows

<details>
  <summary>MSI</summary>

The MSI installer installs ksnip on your system and is the preferred way for installing ksnip under Windows.
</details>

<details>
  <summary>EXE</summary>

The EXE file with all required dependencies comes in a zipped package, which just need to be unzipped
with your favorite unpacking tool. Ksnip can then be started by just double-clicking ksnip.exe.
</details>

## macOS

<details>
  <summary>APP</summary>

The app file comes in a DMG package which needs to be opened, and the ksnip.app file needs to be dragged
and dropped into the "Application" folder. After that the application can be started by double clicking ksnip.app
</details>

<details>
  <summary>Homebrew Cask</summary>

Just install via Homebrew and start using from your "Applications" folder.
```
$ brew install --cask ksnip
```
</details>

# Plugins
ksnip functionality can be extended by using plugins that need to be downloaded separately and installed or unpacked,
depending on the environment. Currently, under `Options > Settings > Plugins` a plugin detection can be triggered either
in the default location(s) or by providing a search path where to look for plugins. After clicking on "Detect", ksnip 
searches for known plugins and when found will list the name and version. 

### Default search locations  
Windows: `plugins` directory, next to `ksnip.exe`  
Linux/Unix: `/usr/local/lib`, `/usr/local/lib64`, `/usr/lib`, `/usr/lib64`  

### Version selection
The plugin must match the Qt version and build type of ksnip. If you have a ksnip version that uses Qt 15.5.X and was
build in `DEBUG` then the plugin must match the same criteria. In most cases the latest ksnip and plugin version will
be using the same Qt version, the only think that you need to watch out for is to not mix `DEBUG` and `RELEASE` build.

## OCR (Window and Linux/Unix)
ksnip supports OCR by using the [ksnip-plugin-ocr](https://github.com/ksnip/ksnip-plugin-ocr) which utilizes Tesseract
to convert Image to text. When the OCR plugin was loaded, the OCR option becomes available under `Options > OCR`.
The latest plugin version can be found [here](https://github.com/ksnip/ksnip-plugin-ocr/releases).


# Dependencies
ksnip depends on [kImageAnnotator](https://github.com/ksnip/kImageAnnotator) and [kColorPicker](https://github.com/DamirPorobic/kColorPicker) which needs
to be installed before building ksnip from source. Installation instructions can be found on the Github pages.

# Building from source
1. Get the latest release from GitHub by cloning the repo:
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

If you are using Archlinux, you may prefer to [build ksnip through AUR](https://github.com/ksnip/ksnip#archlinux).

# Known Issues

<details>
  <summary>Expand</summary>

### X11
1. Snipping area with transparent background doesn't work when compositor is turned off, freeze background is used in that case.

### macOS
1. Snipping area with transparent background doesn't work, freeze background is always used. Issue [#151](https://github.com/ksnip/ksnip/issues/151)
2. Second activation of snipping area doesn't get focus, you need to switch to the right side in order to see the snipping area. Issue [#152](https://github.com/ksnip/ksnip/issues/152)
3. Mouse cursor is always captured. Issue [#153](https://github.com/ksnip/ksnip/issues/153)

### Wayland
1. Portal and Native Screenshots not working under KDE Plasma `>= 5.80`. The issue is coming from a recent change in KDE 
Plasma that prevents access to DBUS Interfaces responsible for taking screenshots. This issue is going to be fixed in 
future Plasma releases for the Portal Screenshots. Workaround for making the Portal Screenshots work is adding the string 
`X-KDE-DBUS-Restricted-Interfaces=org.kde.kwin.Screenshot` to the 
`/usr/share/applications/org.freedesktop.impl.portal.desktop.kde.desktop` file and then restarting. Don't forget to 
enforce Portal screenshots in settings. Issue [#424](https://github.com/ksnip/ksnip/issues/424)
2. Under Gnome Wayland copying images to clipboard and then pasting them somewhere might not work. This happens currently
with native Wayland. A workaround is using XWayland by starting ksnip like this `QT_QPA_PLATFORM=xcb /usr/bin/ksnip` or
switch to XWayland completely by exporting that variable `export QT_QPA_PLATFORM=xcb`. Issue [#416](https://github.com/ksnip/ksnip/issues/416)
3. Native Wayland screenshots are no longer possible with Gnome `>= 41`. The Gnome developers have forbidden
access to the DBus interface that provides Screenshots under Wayland and leave non Gnome application only the possibility
to use xdg-desktop-portal screenshots. Security comes before usability for the Gnome developers. There is an open feature 
request to only grant screenshot permission once instead of for every screenshot, help us raise awareness for such feature 
[here](https://github.com/flatpak/xdg-desktop-portal/issues/649).
4. Global Hotkeys don't work under Wayland, this is due to the secure nature of Wayland. As long as compositor developers
don't provide an interface for us to work with Global Hotkeys, does won't be supported.

### Screen Scaling (HiDPI)
1. Qt is having issues with screen scaling, it can occur that the Snipping area is incorrectly positioned. As a workaround
the Snipping Area position or offset can be configured so that it's placed correctly. Issue [#276]
</details>

### Snap
1. Drag and Drop might not be working when ksnip or the application that you drag and drop from/to is installed as snap.
the reason being that the image is shared via the temp directory which in case of snaps are restricted and every 
application can only see their own files or files of the user. The workaround for this is to change the temp directory 
location to a user owned directory like home, document or download directory via `Options > Settings > Application > 
Temp Directory`.

# Discussion & Community
If you have general questions, ideas or just want to talk about ksnip, please join our [Discord][discord-badge-url] 
or [IRC][libera-badge-url] server. 

# Contribution
Any contribution is welcome, be it code, translations or other things. Currently, we need:
* Developers for writing code and fixing bugs for linux, windows and macOS. We have **only one developer** and the feature requests and bugs are pilling up.
* Testers for testing releases on different OS and Distros.
* Docu writers, there are a lot of features that the casual users don't know about.
* Bug reporting, Please report any bugs or feature requests related to the annotation editor on the [kImageAnnotator](https://github.com/ksnip/kImageAnnotator/issues) GitHub page under the "Issue" section.
All other bugs or feature requests can be reported on the [ksnip](https://github.com/ksnip/ksnip/issues) GitHub page under the "Issue" section.
* Translations - [Weblate](https://hosted.weblate.org/projects/ksnip/translations/) is used for translations. For translating annotator-related texts, please refer to [kImageAnnotator](https://github.com/ksnip/kImageAnnotator)
<details>
  <summary>Translation status</summary>

[![Translation status](https://hosted.weblate.org/widgets/ksnip/-/translations/multi-green.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget)
</details>

# Donation 
ksnip is a non-profitable copylefted libre software project, and still has some costs that need to be covered, like domain costs or hardware costs for cross-platform support.
If you want to help or just want to appreciate the work being done by treating developers to a beer or coffee,
you can do that [here](https://www.paypal.me/damirporobic), donations are always welcome :)

Also in crypto:  
BTC: bc1q6cke457fk8qhxxacl4nu5q2keudtdukrqe2gx0  
ETH: 0xbde87a83427D61072055596e7a746CeC5316253C   
BNB: bnb1fmy0vupsv23s36sejp07jetj6exj3hqeewkj6d  


[github-linux-badge]:  https://github.com/ksnip/ksnip/actions/workflows/linux.yml/badge.svg
[github-linux-url]:    https://github.com/ksnip/ksnip/actions/workflows/linux.yml

[github-windows-badge]:https://github.com/ksnip/ksnip/actions/workflows/windows.yml/badge.svg
[github-windows-url]:  https://github.com/ksnip/ksnip/actions/workflows/windows.yml

[github-macos-badge]:  https://github.com/ksnip/ksnip/actions/workflows/macos.yml/badge.svg
[github-macos-url]:    https://github.com/ksnip/ksnip/actions/workflows/macos.yml

[weblate-badge]:       https://hosted.weblate.org/widgets/ksnip/-/translations/svg-badge.svg
[weblate-url]:         https://hosted.weblate.org/engage/ksnip/?utm_source=widget

[gh-dl-badge]:         https://img.shields.io/github/downloads/damirporobic/ksnip/total.svg?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSI0MCIgaGVpZ2h0PSI0MCIgdmlld0JveD0iMTIgMTIgNDAgNDAiPjxwYXRoIGZpbGw9IiNmZmYiIGQ9Ik0zMiwxMy40Yy0xMC41LDAtMTksOC41LTE5LDE5YzAsOC40LDUuNSwxNS41LDEzLDE4YzEsMC4yLDEuMy0wLjQsMS4zLTAuOWMwLTAuNSwwLTEuNywwLTMuMiBjLTUuMywxLjEtNi40LTIuNi02LjQtMi42QzIwLDQxLjYsMTguOCw0MSwxOC44LDQxYy0xLjctMS4yLDAuMS0xLjEsMC4xLTEuMWMxLjksMC4xLDIuOSwyLDIuOSwyYzEuNywyLjksNC41LDIuMSw1LjUsMS42IGMwLjItMS4yLDAuNy0yLjEsMS4yLTIuNmMtNC4yLTAuNS04LjctMi4xLTguNy05LjRjMC0yLjEsMC43LTMuNywyLTUuMWMtMC4yLTAuNS0wLjgtMi40LDAuMi01YzAsMCwxLjYtMC41LDUuMiwyIGMxLjUtMC40LDMuMS0wLjcsNC44LTAuN2MxLjYsMCwzLjMsMC4yLDQuNywwLjdjMy42LTIuNCw1LjItMiw1LjItMmMxLDIuNiwwLjQsNC42LDAuMiw1YzEuMiwxLjMsMiwzLDIsNS4xYzAsNy4zLTQuNSw4LjktOC43LDkuNCBjMC43LDAuNiwxLjMsMS43LDEuMywzLjVjMCwyLjYsMCw0LjYsMCw1LjJjMCwwLjUsMC40LDEuMSwxLjMsMC45YzcuNS0yLjYsMTMtOS43LDEzLTE4LjFDNTEsMjEuOSw0Mi41LDEzLjQsMzIsMTMuNHoiLz48L3N2Zz4=
[gh-dl-url]:           https://github.com/ksnip/ksnip/releases

[sf-dt-badge]:         https://img.shields.io/sourceforge/dt/ksnip.svg?logo=data:image/svg+xml;base64,PCFET0NUWVBFIHN2ZyBQVUJMSUMgIi0vL1czQy8vRFREIFNWRyAyMDAxMDkwNC8vRU4iICJodHRwOi8vd3d3LnczLm9yZy9UUi8yMDAxL1JFQy1TVkctMjAwMTA5MDQvRFREL3N2ZzEwLmR0ZCI+PHN2ZyB2ZXJzaW9uPSIxLjAiIHhtbG5zPSJodHRwOi8vd3d3LnczLm9yZy8yMDAwL3N2ZyIgd2lkdGg9IjMzMHB4IiBoZWlnaHQ9IjMzMHB4IiB2aWV3Qm94PSIwIDAgMzMwMCAzMzAwIiBwcmVzZXJ2ZUFzcGVjdFJhdGlvPSJ4TWlkWU1pZCBtZWV0Ij48ZyBpZD0ibGF5ZXIxMDEiIGZpbGw9IiNmZmYiIHN0cm9rZT0ibm9uZSI+IDxwYXRoIGQ9Ik0xNTI4IDMwMTkgYy0xMCAtNSAtMTggLTIwIC0xOCAtMzIgMCAtMTYgMTczIC0xOTUgNjA3IC02MjkgNTYyIC01NjIgNjA2IC02MDkgNjA1IC02MzkgLTEgLTI5IC00OSAtODEgLTQ4MSAtNTEzIC0zMjMgLTMyMyAtNDgxIC00ODggLTQ4MSAtNTAyIDAgLTIzIDE5OCAtMjI0IDIyMSAtMjI0IDE5IDAgMTIzOSAxMjIxIDEyMzkgMTI0MCAwIDggLTI5MSAzMDYgLTY0NyA2NjIgbC02NDggNjQ4IC0xOTAgMCBjLTExMCAwIC0xOTcgLTUgLTIwNyAtMTF6Ii8+IDxwYXRoIGQ9Ik02ODIgMjIwNiBjLTQwMSAtNDAwIC02MTMgLTYxOSAtNjExIC02MjkgNCAtMTggMTI2MiAtMTI4MiAxMjkxIC0xMjk4IDIzIC0xMyAzNzUgLTEyIDM5OSAxIDEwIDYgMTkgMjEgMTkgMzMgMCAxNSAtMTcyIDE5NCAtNjA0IDYyNyAtMzMzIDMzMyAtNjA1IDYxMiAtNjA2IDYyMCAtMiA4IC0yIDI0IC0xIDM1IDEgMTIgMTkzIDIxMiA0ODEgNTAwIDMwOCAzMDggNDgwIDQ4NyA0ODAgNTAwIDAgMjMgLTE5NyAyMjUgLTIyMCAyMjUgLTggMCAtMjkxIC0yNzYgLTYyOCAtNjE0eiIvPiA8cGF0aCBkPSJNMTU5MiAyMjM5IGMtMTM5IC0yMyAtMjY5IC0xMjMgLTMzNiAtMjYwIC00NiAtOTUgLTYwIC0xNjkgLTUyIC0yODkgMTAgLTE2MiA1MSAtMjU4IDE4NiAtNDMxIDEwOCAtMTM4IDEzOCAtMTk2IDE1MyAtMjg4IDEyIC04MyAyNiAtOTAgNzMgLTM4IDgxIDg2IDEzNyAxODYgMTc5IDMxNyA0MCAxMjYgNTUgMjE2IDY2IDQwMCA2IDkxIDE2IDE3NiAyMiAxOTAgMTggMzcgNTEgMzcgNzYgMSA0OCAtNjYgNTUgLTEwNiA1NSAtMjg0IDAgLTEwOSA0IC0xNjYgMTEgLTE2NCAxNiA1IDUzIDkxIDgwIDE4NCA5MSAzMTIgLTg3IDYyMCAtMzgxIDY2MyAtMzggNSAtNzEgOSAtNzQgOSAtMyAtMSAtMjkgLTUgLTU4IC0xMHoiLz4gPC9nPjwvc3ZnPg==
[sf-dt-badge-url]:     https://sourceforge.net/projects/ksnip

[gh-comm-since-badge]: https://img.shields.io/github/commits-since/damirporobic/ksnip/latest.svg?logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSI0MCIgaGVpZ2h0PSI0MCIgdmlld0JveD0iMTIgMTIgNDAgNDAiPjxwYXRoIGZpbGw9IiNmZmYiIGQ9Ik0zMiwxMy40Yy0xMC41LDAtMTksOC41LTE5LDE5YzAsOC40LDUuNSwxNS41LDEzLDE4YzEsMC4yLDEuMy0wLjQsMS4zLTAuOWMwLTAuNSwwLTEuNywwLTMuMiBjLTUuMywxLjEtNi40LTIuNi02LjQtMi42QzIwLDQxLjYsMTguOCw0MSwxOC44LDQxYy0xLjctMS4yLDAuMS0xLjEsMC4xLTEuMWMxLjksMC4xLDIuOSwyLDIuOSwyYzEuNywyLjksNC41LDIuMSw1LjUsMS42IGMwLjItMS4yLDAuNy0yLjEsMS4yLTIuNmMtNC4yLTAuNS04LjctMi4xLTguNy05LjRjMC0yLjEsMC43LTMuNywyLTUuMWMtMC4yLTAuNS0wLjgtMi40LDAuMi01YzAsMCwxLjYtMC41LDUuMiwyIGMxLjUtMC40LDMuMS0wLjcsNC44LTAuN2MxLjYsMCwzLjMsMC4yLDQuNywwLjdjMy42LTIuNCw1LjItMiw1LjItMmMxLDIuNiwwLjQsNC42LDAuMiw1YzEuMiwxLjMsMiwzLDIsNS4xYzAsNy4zLTQuNSw4LjktOC43LDkuNCBjMC43LDAuNiwxLjMsMS43LDEuMywzLjVjMCwyLjYsMCw0LjYsMCw1LjJjMCwwLjUsMC40LDEuMSwxLjMsMC45YzcuNS0yLjYsMTMtOS43LDEzLTE4LjFDNTEsMjEuOSw0Mi41LDEzLjQsMzIsMTMuNHoiLz48L3N2Zz4=
[gh-comm-since-url]:   https://github.com/ksnip/ksnip/releases/tag/continuous

[discord-badge]:       https://img.shields.io/discord/812295724837371955.svg?label=&logo=discord&logoColor=ffffff&color=7389D8&labelColor=6A7EC2
[discord-badge-url]:   http://discord.ksnip.org

[libera-badge]:        https://img.shields.io/badge/libera.chat-%23ksnip-brightgreen.svg
[libera-badge-url]:    https://web.libera.chat/?channels=#ksnip
