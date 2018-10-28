%define    packager           Damir Porobic <damir.porobic@gmx.com>
%define  __spec_install_post %{nil}
%define    debug_package     %{nil}
%define  __os_install_post   %{_dbpath}/brp-compress
%define  _signature           gpg
%define  _gpg_name            Ksnip


Name:    ksnip
Summary: Screenshot Tool
Version: 1.5.0
Release: 1
Source0: %{name}-%{version}.tar.gz
URL:     https://github.com/DamirPorobic/ksnip
License: GPLV2+
Group:   Application/Utility
BuildRequires: update-desktop-files


%description
Screenshot tool that provides many annotation features for your screenshots.

%prep
%setup

%build
cmake .
make

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
%suse_update_desktop_file -r %{name} Utility DesktopUtility

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root,-)
/bin/%{name}
%{_usr}/share/applications/%{name}.desktop
%{_usr}/share/applications/%{name}.desktop
%{_usr}/share/%{name}/translations/%{name}_*.qm
%{_usr}/share/metainfo/%{name}.appdata.xml

%changelog
* Sun Dec 17 2017 Damir Porobic <damir.porobic@gmx.com> 1.4.0
-- New: Info text (cursor position and selection area size) for snipping area cursor, can be enabled and disabled via settings.(#49)
-- New: Horizontal vertical guiding lines for snipping area cursor, can be enabled and disabled via settings. (#48)
-- New: Drop shadow for paint items, can be enabled and disabled via settings (#47)
-- New: Copy/past paint items. (#46)
-- New: Numbering paint item. (#45)
-- New: Arrow paint item. (#44)
-- New: Select multiple paint items and perform operation on all selected at once. (#42)
-- New: Run last or default capture on startup. (#40)
-- New: Run rect capture from command line. (#39)
-- New: Select between default and custom filename for saving screenshots. (#36)
-- New: Keyboard shortcuts for paint tools. (#43)
-- New: Bring to front and send to back paint items. (#31)
-- New: Configurable snipping cursor thickness and color. (#54)
-- Changed: Moving Ksnip from Qt4 to Qt5. (#22)
-- Fixed: Settings window left hand side menu is not correctly selected when opening first time. (#37)
-- Fixed: Snipping area not correctly shown when started on non-primary screen. (#52)
-- Fixed: Active window screenshot ignores delay. (#53)
-- Fixed: Rectangular area screenshot is shifted to the right of actual selected area. (#51)
-- Fixed: Snipping area not closing when pressing Esc on Ubuntu 16.04. (#57)

* Sat Dec 09 2017 Damir Porobic <damir.porobic@gmx.com> 1.3.2
-- Fixed: When compositor is disabled, rect are capture shows only black screen. Fix for Qt4 Ksnip version. (#35)

* Fri Mar 31 2017 Damir Porobic <damir.porobic@gmx.com> 1.3.1
-- Fixed bug #29 - Ksnip 1.3.0 fails to build - due to missing cmath library.

* Wed Mar 29 2017 Damir Porobic <damir.porobic@gmx.com> 1.3.0
-- New: Drawing two shapes, ellipse and rectangle, with and without fill.
-- New: Customizable color and size (thickness) for drawing tools via button on main tool bar.
-- New: Writing text on screenshots, with customizable font, size, color etc.
-- New: Undo/Redo for paint and crop operations.
-- New: Smooth out free hand pen and marker lines (can be disabled in settings).
-- New: Print screenshot or save is to prf/ps.
-- Fixed: Confirming crop via enter or return didn't close crop panel.
-- Fixed: Paint items not correctly positioned after second and subsequent crops.

* Fri Jan 20 2017 Damir Porobic <damir.porobic@gmx.com> 1.2.1
-- Fixed: Binary segfaults when compiled in x86_64 with -fPIC in gcc-5.4.0. (#20)
-- Fixed incorrect version number in "About" dialog.

* Mon Jan 16 2017 Damir Porobic <damir.porobic@gmx.com> 1.2.0
-- New: Added functionality to upload screenshots to Imgur.com in anonymous or account mode.
-- New: Capture mouse cursor on screenshot (feature can be enabled or disabled in settings).
-- New: In crop window the crop position, width and height can be entered in numeric values, to provide a more precise crop.
-- New: Settings Window Layout was changed and reorganized.
-- Fixed: Paint cursor was visible when capturing new screenshot.
-- Fixed: Crop could leave scene area.

* Sun Oct 23 2016 Damir Porobic <damir.porobic@gmx.com> 1.1.0
-- New: Cropping captured image to desired size.
-- New: Command line support, screenshots can be taken now from command line too.
-- New: Moving drawn lines to desired position by dragging.
-- New: Setting default save location, filename and format from settings window.

* Sun Oct 02 2016 Damir Porobic <damir.porobic@gmx.com> 1.0.0
-- New: Screenshots from a custom drawn rectangular area.
-- New: Screenshots from the screen where ksnip is currently located (for multi monitor environments).
-- New: Screenshots from the whole screen, including all monitors.
-- New: Screenshot of currently active (on top) window.
-- New: Delayed captures.
-- New: Drawing on the captured screenshot with Pen or Marker with changeable color and size.
-- New: Saving ksnip location and selected tool and loading on startup.
