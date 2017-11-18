
Debian
====================
This directory contains files used to package alisinabitd/alisinabit-qt
for Debian-based Linux systems. If you compile alisinabitd/alisinabit-qt yourself, there are some useful files here.

## alisinabit: URI support ##


alisinabit-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install alisinabit-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your alisinabit-qt binary to `/usr/bin`
and the `../../share/pixmaps/alisinabit128.png` to `/usr/share/pixmaps`

alisinabit-qt.protocol (KDE)

