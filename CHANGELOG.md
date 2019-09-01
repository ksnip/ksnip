# Change log

## Release 1.6.0
* New: Make captured cursor an item which can be moved and deleted. ([#86](https://github.com/DamirPorobic/kImageAnnotator/issues/86))
* New: Add watermarks to annotated image. ([#199](https://github.com/DamirPorobic/kImageAnnotator/issues/199))
* New kImageAnnotator: Edit text box content. ([#51](https://github.com/DamirPorobic/kImageAnnotator/issues/51))
* Fixed: Translations not working for Windows and MacOS. ([#164](https://github.com/DamirPorobic/ksnip/issues/164))
* Fixed: AppImage update fails with "None of the artifacts matched the pattern in the update information". ([#166](https://github.com/DamirPorobic/ksnip/issues/166))
* Fixed: Wildcards in path are not resolved. ([#168](https://github.com/DamirPorobic/ksnip/issues/168))
* Fixed: CLI arg --rectarea doesn't work. ([#170](https://github.com/DamirPorobic/ksnip/issues/170))
* Fixed: Imgur Uploader on windows issue. ([#173](https://github.com/DamirPorobic/ksnip/issues/173))
* Fixed: Add shortcut for File Menu in Main Menu. ([#192](https://github.com/DamirPorobic/ksnip/issues/192))
* Fixed: Prompt to save before exit enabled now by default. ([#193](https://github.com/DamirPorobic/ksnip/issues/193))
* Fixed kImageAnnotator: Unable to select number annotation when clicking on the number without background. ([#46](https://github.com/DamirPorobic/kImageAnnotator/issues/46))
* Fixed kImageAnnotator: Ctrl Modifier stuck on second or third screenshot with Ctrl-N. ([#58](https://github.com/DamirPorobic/kImageAnnotator/issues/58))
* Fixed kImageAnnotator: Undo/Redo is now disabled during crop and scale operation. ([#56](https://github.com/DamirPorobic/kImageAnnotator/issues/56))

## Release 1.5.0
* New: Added Continues Build with Travis-CI that creates AppImages for every commit. ([#63](https://github.com/DamirPorobic/ksnip/issues/63))
* New: Added option to open image from file via GUI. ([#60](https://github.com/DamirPorobic/ksnip/issues/60))
* New: Added option to set next number for Numbering Paint Items via popup settings. ([#59](https://github.com/DamirPorobic/ksnip/issues/59))
* New: Added experimental Wayland support for KDE and Gnome DEs. ([#56](https://github.com/DamirPorobic/ksnip/issues/56))
* New: Metadata info for ksnip is now installed in the /usr/share/metainfo directory. ([#66](https://github.com/DamirPorobic/ksnip/issues/66))
* New: Added option to open image from file via CLI. ([#71](https://github.com/DamirPorobic/ksnip/issues/71))
* New: Instant saving captures without prompting for save location. ([#61](https://github.com/DamirPorobic/ksnip/issues/61))
* New: Scaling/resizing screenshots and items. ([#79](https://github.com/DamirPorobic/ksnip/issues/79))
* New: Added translation support. ([#94](https://github.com/DamirPorobic/ksnip/issues/94))
* New: Added Spanish, German, Dutch Norwegian and Polish translation. ([#94](https://github.com/DamirPorobic/ksnip/issues/94))
* New: Option to switch between dynamic and default painter cursor size. ([#77](https://github.com/DamirPorobic/ksnip/issues/77))
* New: Added RPM and DEB binaries to continues build.
* New: Added blur annotation tool. ([#109](https://github.com/DamirPorobic/ksnip/issues/109))
* New: Added Windows support. ([#113](https://github.com/DamirPorobic/ksnip/issues/113))
* New: Added Continues build for Windows binaries. ([#114](https://github.com/DamirPorobic/ksnip/issues/114))
* New: Place time delay settings on Toolbar. ([#91](https://github.com/DamirPorobic/ksnip/issues/91))
* New: Add qt style switcher to configuration. ([#137](https://github.com/DamirPorobic/ksnip/issues/137))
* New: Add icons for dark theme. ([#142](https://github.com/DamirPorobic/ksnip/issues/142))
* New: Store imgur delete links. ([#74](https://github.com/DamirPorobic/ksnip/issues/74))
* New: Freeze image while selecting rectangular area. ([#136](https://github.com/DamirPorobic/ksnip/issues/136))
* New: Magnifying glass for snipping area. ([#62](https://github.com/DamirPorobic/ksnip/issues/62))
* New: Add MacOS support. ([#125](https://github.com/DamirPorobic/ksnip/issues/125))
* New: CI support for MacOS. ([#126](https://github.com/DamirPorobic/ksnip/issues/126))
* New kImageAnnotator: Keep number tool sequence consecutive after deleting item. ([#7](https://github.com/DamirPorobic/kImageAnnotator/issues/7))
* New kImageAnnotator: Added control for setting first number for numbering tool. ([#7](https://github.com/DamirPorobic/kImageAnnotator/issues/7))
* New kImageAnnotator: Text and Number tool have now noBorderAndNoFill type. ([#22](https://github.com/DamirPorobic/kImageAnnotator/issues/22))
* New kImageAnnotator: Double Arrow annotation tool. ([#23](https://github.com/DamirPorobic/kImageAnnotator/issues/23))
* New kImageAnnotator: Marker Rectangle and Ellipse annotation tool. ([#26](https://github.com/DamirPorobic/kImageAnnotator/issues/26))
* New kImageAnnotator: Add config option to setup blur radius. ([#25](https://github.com/DamirPorobic/kImageAnnotator/issues/25))
* Changed: Move and select operation are now combined under single tool. ([#72](https://github.com/DamirPorobic/ksnip/issues/72))
* Changed: Item selection is now based on item shape and not on item bounding rect. ([#83](https://github.com/DamirPorobic/ksnip/issues/83))
* Changed: Imgur upload now asks for confirmation before uploading. This can be disabled in setting. ([#73](https://github.com/DamirPorobic/ksnip/issues/73))
* Changed: CLI screenshots open now in editor when triggered without -s flag. ([#103](https://github.com/DamirPorobic/ksnip/issues/103))
* Changed: Default filename features now a more fine-grained time placeholder. ([#110](https://github.com/DamirPorobic/ksnip/issues/110))
* Changed: Console version output doesn't show build. ([#121](https://github.com/DamirPorobic/ksnip/issues/121))
* Changed kImageAnnotator: Blur tool is now preciser and fits the rect. ([#28](https://github.com/DamirPorobic/kImageAnnotator/issues/28))
* Changed kImageAnnotator: Enter finishes text input and shift-enter adds new line in Text Tool. ([#30](https://github.com/DamirPorobic/kImageAnnotator/issues/30))
* Changed kImageAnnotator: Text item draws border around the text when in text edit mode. ([#34](https://github.com/DamirPorobic/kImageAnnotator/issues/34))
* Fixed: Crash on Ubuntu 17.10 caused by null painterPath pointer in smoothOut method. ([#67](https://github.com/DamirPorobic/ksnip/issues/67))
* Fixed: Default filename for screenshot had one $ sign too many. ([#68](https://github.com/DamirPorobic/ksnip/issues/68))
* Fixed: Cancel on browse to save directory in settings dialog clears save path. ([#69](https://github.com/DamirPorobic/ksnip/issues/69))
* Fixed: About dialog not closing when close button is clicked. ([#76](https://github.com/DamirPorobic/ksnip/issues/76))
* Fixed: Undo move operation returns item to wrong location. ([#84](https://github.com/DamirPorobic/ksnip/issues/84))
* Fixed: Crash when adding an item after another item was moved and undone ([#85](https://github.com/DamirPorobic/ksnip/issues/85))
* Fixed: Crop tool not marking screenshot as unsaved after cropping ([#99](https://github.com/DamirPorobic/ksnip/issues/99))
* Fixed: Scale tool not marking screenshot as unsaved after scaling ([#100](https://github.com/DamirPorobic/ksnip/issues/100))
* Fixed: Running ksnip with -e flag and enabled capture screenshot on startup starts new screenshot. ([#105](https://github.com/DamirPorobic/ksnip/issues/105))
* Fixed: Triggering new capture discards unsaved changes. ([#89](https://github.com/DamirPorobic/ksnip/issues/89))
* Fixed: Text tool cannot be resized. ([#111](https://github.com/DamirPorobic/ksnip/issues/111))
* Fixed: Exe file not showing icon on windows. ([#122](https://github.com/DamirPorobic/ksnip/issues/122))
* Fixed: Buttons for text bold, italic and underlined are not correctly shown under windows. ([#118](https://github.com/DamirPorobic/ksnip/issues/118))
* Fixed: ksnip not running on windows when qt not installed. ([#145](https://github.com/DamirPorobic/ksnip/issues/145))
* Fixed: Imgur upload not working under windows. ([#144](https://github.com/DamirPorobic/ksnip/issues/144))
* Fixed: Snipping area with freezed background image not working. ([#149](https://github.com/DamirPorobic/ksnip/issues/149))
* Fixed: Snipping area cursor included in screenshot. ([#148](https://github.com/DamirPorobic/ksnip/issues/148))
* Fixed kImageAnnotator: Double-click on annotation area causes SIGSEGV crash. ([#29](https://github.com/DamirPorobic/kImageAnnotator/issues/29))
* Fixed kImageAnnotator: CAPS LOCK doesnt work on image editor. ([#27](https://github.com/DamirPorobic/kImageAnnotator/issues/27))
* Fixed kImageAnnotator: Unable to select text item when clicking on text. ([#32](https://github.com/DamirPorobic/kImageAnnotator/issues/32))
* Fixed kImageAnnotator: Some blurs get removed when losing focus. ([#35](https://github.com/DamirPorobic/kImageAnnotator/issues/35))
* Fixed kImageAnnotator: Right click on annotation items selects item but doesn't switch tool. ([#40](https://github.com/DamirPorobic/kImageAnnotator/issues/40))
* Fixed kImageAnnotator: Copy number annotation item doesn't increment number. ([#41](https://github.com/DamirPorobic/kImageAnnotator/issues/41))
* Fixed kImageAnnotator: Crash on startup after adding Blur Radius Picker. ([#43](https://github.com/DamirPorobic/kImageAnnotator/issues/43))

## Release 1.4.0
* New: Info text (cursor position and selection area size) for snipping area cursor, can be enabled and disabled via settings.([#49](https://github.com/DamirPorobic/ksnip/issues/49))
* New: Horizontal vertical guiding lines for snipping area cursor, can be enabled and disabled via settings. ([#48](https://github.com/DamirPorobic/ksnip/issues/48))
* New: Drop shadow for paint items, can be enabled and disabled via settings ([#47](https://github.com/DamirPorobic/ksnip/issues/47))
* New: Copy/past paint items. ([#46](https://github.com/DamirPorobic/ksnip/issues/46))
* New: Numbering paint item. ([#45](https://github.com/DamirPorobic/ksnip/issues/45))
* New: Arrow paint item. ([#44](https://github.com/DamirPorobic/ksnip/issues/44))
* New: Select multiple paint items and perform operation on all selected at once. ([#42](https://github.com/DamirPorobic/ksnip/issues/42))
* New: Run last or default capture on startup. ([#40](https://github.com/DamirPorobic/ksnip/issues/40))
* New: Run rect capture from command line. ([#39](https://github.com/DamirPorobic/ksnip/issues/39))
* New: Select between default and custom filename for saving screenshots. ([#36](https://github.com/DamirPorobic/ksnip/issues/36))
* New: Keyboard shortcuts for paint tools. ([#43](https://github.com/DamirPorobic/ksnip/issues/43))
* New: Bring to front and send to back paint items. ([#31](https://github.com/DamirPorobic/ksnip/issues/31))
* New: Configurable snipping cursor thickness and color. ([#54](https://github.com/DamirPorobic/ksnip/issues/54))
* Changed: Moving Ksnip from Qt4 to Qt5. ([#22](https://github.com/DamirPorobic/ksnip/issues/22))
* Fixed: Settings window left hand side menu is not correctly selected when opening first time. ([#37](https://github.com/DamirPorobic/ksnip/issues/37))
* Fixed: Snipping area not correctly shown when started on non-primary screen. ([#52](https://github.com/DamirPorobic/ksnip/issues/52))
* Fixed: Active window screenshot ignores delay. ([#53](https://github.com/DamirPorobic/ksnip/issues/53))
* Fixed: Rectangular area screenshot is shifted to the right of actual selected area. ([#51](https://github.com/DamirPorobic/ksnip/issues/51))
* Fixed: Snipping area not closing when pressing Esc on Ubuntu 16.04. ([#57](https://github.com/DamirPorobic/ksnip/issues/57))

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
