#! /bin/sh
### Building-Script for third-party libraries

echo "Building third party libraries"

## Building LibDash

echo "Building LibDash.."

BOOST_DIR="./libdash"
if [ ! -d "$BOOST_DIR" ]; then
	echo "Fetching LibDash"
    git clone git://github.com/bitmovin/libdash.git
    cd libdash/libdash
	mkdir build
	cd build
	cmake ../
	make
	echo "Building LibDash finished."
else
	echo "LibDash already existing."
	echo "To build LibDash again please delete ./libdash"
	echo "Press [Enter] key to continue.."
	read dummy < /dev/tty
fi

## End LibDash

echo "Install-Script finished."
