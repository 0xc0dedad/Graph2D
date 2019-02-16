#!/bin/bash

BUILDIR=$PWD/build.Graph2D/
SRCDIR=$BUILDIR/..

copy()
{
	cd $SRCDIR
	rm -rf $BUILDIR/images
	mkdir $BUILDIR/images
	cp -R $PWD/images/ $BUILDIR/
}

if [ "$1" == "build" ]
then
	if ! [ -e $BUILDIR ]
	then
		mkdir $BUILDIR
		cd $BUILDIR
		qmake ../Graph2D.pro -spec linux-g++ CONFIG+=debug
		make -f Makefile
	fi

	cd $SRCDIR

	if ! [ -e $PWD/build ]
	then
		ln -s $BUILDIR/ build
	fi

	copy
fi

if [ "$1" == "copy" ]
then
	
	if [ -e $PWD/build.Graph2D ]
	then
		copy
	fi
fi

if [ "$1" == "distclean" ]
then
	rm -rf $BUILDIR
	rm -f build
fi
