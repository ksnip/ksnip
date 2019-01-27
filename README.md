<div align="center">
  <p>
    <h1>
      <a href="https://github.com/DamirPorobic/ksnip">
        <img src="icons/ksnip.svg" alt="ksnip" height="64" width="64"/>
      </a>
      <br />
      ksnip
    </h1>
    <h4>
      Version v1.5.0 - alpha
  </h4>
  </p>
    <p>
    <a href="https://travis-ci.org/DamirPorobic/ksnip">
      <img src="https://travis-ci.org/DamirPorobic/ksnip.svg?branch=master" alt="Build Status" />
    </a>
    <a href="https://www.codacy.com/app/DamirPorobic/ksnip?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=DamirPorobic/ksnip&amp;utm_campaign=Badge_Grade">
      <img src="https://api.codacy.com/project/badge/Grade/94558bfc42d1466fae691a646cfe3f09" alt="Codacy Badge" />
    </a>
    <a href="https://hosted.weblate.org/engage/ksnip/?utm_source=widget">
      <img src="https://hosted.weblate.org/widgets/ksnip/-/translations/svg-badge.svg" alt="Translation Status" />
    </a>
    <a href="https://github.com/damirporobic/ksnip/releases">
      <img src="https://img.shields.io/github/downloads/damirporobic/ksnip/total.svg" alt="Total Downloads" />
    </a>
  </p>
</div>

![Ksnip](https://imgur.com/cB2zfKW.png "Ksnip with annotations")

Ksnip is a Qt based cross-platform screenshot tool that provides many annotation features 
for your screenshots.

### Features
Latest ksnip version contains following features:
* Supports Linux and Windows.
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

### Continues build
We provide deb, rpm and AppImage binaries for every pushed commit, those can be found at the top of the
release page. Continues build artifacts are not fully tested and in most cases they are work in progress
so use them with caution.

### Dependencies

ksnip depends on [kImageAnnotator](https://github.com/DamirPorobic/kImageAnnotator) and [kColoPicker](https://github.com/DamirPorobic/kColorPicker) which needs
to be installed before building ksnip from source. Install instructions can be found on the github pages.

### Building from source

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


### Translations
We are always looking for help with translations, contributors are welcome!  
For translations we use [Weblate](https://hosted.weblate.org/projects/ksnip/translations/)!  
[![Translation status](https://hosted.weblate.org/widgets/ksnip/-/translations/multi-green.svg)](https://hosted.weblate.org/engage/ksnip/?utm_source=widget)

### Bug report
Please report any bugs or feature requests related to the annotation editor on the [kImageAnnotator](https://github.com/DamirPorobic/kImageAnnotator/issues) github page under the issue section.
All other bugs or feature requests please report on the [ksnip](https://github.com/DamirPorobic/ksnip/issues) github page under the issue section.
