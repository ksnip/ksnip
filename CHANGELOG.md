# Change log

## Release 1.3.2
* Fixed: When compositor is disabled, rect are capture shows only black screen. Fix for Qt4 Ksnip version ([#35](https://github.com/DamirPorobic/ksnip/issues/35))

## Release 1.3.1
* Fixed: Ksnip 1.3.0 fails to build - due to missing cmath library ([#29](https://github.com/DamirPorobic/ksnip/issues/29))

## Release 1.3.0
* New: Drawing two shapes, ellipse and rectangle, with and without fill. ([#21](https://github.com/DamirPorobic/ksnip/issues/21))
* New: Customizable color and size (thickness) for drawing tools via button on main tool bar. ([#25](https://github.com/DamirPorobic/ksnip/issues/25))
* New: Writing text on screenshots, with customizable font, size, color etc. ([#8](https://github.com/DamirPorobic/ksnip/issues/8))
* New: Undo/Redo for paint and crop operations. ([#5](https://github.com/DamirPorobic/ksnip/issues/5))
* New: Smooth out free hand pen and marker lines (can be disabled in settings). ([#16](https://github.com/DamirPorobic/ksnip/issues/16))
* New: Print screenshot or save is to prf/ps. ([#23](https://github.com/DamirPorobic/ksnip/issues/23))
* Fixed: Second and subsequent crops don't move painter items correctly ([#27](https://github.com/DamirPorobic/ksnip/issues/27))
* Fixed: Confirming crop via keyboard doesn't close crop panel ([28](https://github.com/DamirPorobic/ksnip/issues/28))

## Release 1.2.1
* Fixed: Ksnip 1.2.0 binary segfaults when compiled in x86_64 with -fPIC in gcc-5.4.0 ([#20](https://github.com/DamirPorobic/ksnip/issues/20))
* Fixed: Incorrect version number in "About" dialog.

## Release 1.2.0
* New: Added functionality to upload screenshots to Imgur.com in anonymous or account mode. ([#14](https://github.com/DamirPorobic/ksnip/issues/14))
* New: Capture mouse cursor on screenshot (feature can be enabled or disabled in settings). ([#18](https://github.com/DamirPorobic/ksnip/issues/18))
* New: In crop window the crop position, width and height can be entered in numeric values, to provide a more precise crop. ([#17](https://github.com/DamirPorobic/ksnip/issues/17))
* Changed: Settings Window Layout was changed and reorganized.
* Fixed: Paint cursor was visible when capturing new screenshot.
* Fixed: Crop could leave scene area.

## Release 1.1.0
* New: Cropping captured image to desired size. ([#4](https://github.com/DamirPorobic/ksnip/issues/4))
* New: Command line support, screenshotsa can be taken now from command line too. ([#11](https://github.com/DamirPorobic/ksnip/issues/11))
* New: Moving drawn lines to desired position by dragging. ([#2](https://github.com/DamirPorobic/ksnip/issues/2))
* New: Setting default save location, filename and format from settings window. ([#9](https://github.com/DamirPorobic/ksnip/issues/9))
* Changed: Capturing current screen captures now the screen where the mouse cursor is located.

## Release 1.0.0
* New: Screenshots from a custom drawn rectangular area.
* New: Screenshots from the screen where ksnip is currently located (for multi monitor environments).
* New: Screenshots from the whole screen, including all monitors.
* New: Screenshot of currently active (on top) window.
* New: Delayed captures.
* New: Drawing on the captured screenshot with Pen or Marker with changeable color and size.
* New: Saving ksnip location and selected tool and loading on startup.
