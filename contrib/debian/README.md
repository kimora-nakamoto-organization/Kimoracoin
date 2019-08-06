
Debian
====================
This directory contains files used to package kimorad/kimora-qt
for Debian-based Linux systems. If you compile kimorad/kimora-qt yourself, there are some useful files here.

## kimora: URI support ##


kimora-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install kimora-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your kimora-qt binary to `/usr/bin`
and the `../../share/pixmaps/kimora128.png` to `/usr/share/pixmaps`

kimora-qt.protocol (KDE)

