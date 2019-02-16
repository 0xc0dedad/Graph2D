#!/bin/bash

BUILDIR=$PWD/build.Graph2D/
SRCDIR=$BUILDIR/..

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

fi

if [ "$1" == "distclean" ]
then
	rm -rf $BUILDIR
	rm -f build
fi
