#!/bin/bash

gwenhywfar_tarball_url = 'http://www2.aquamaniac.de/sites/download/download.php?package=01&release=78&file=01&dummy=gwenhywfar-4.13.1.tar.gz'
aqbanking_tarball_url='http://www.aquamaniac.de/sites/download/download.php?package=03&release=118&file=01&dummy=aqbanking-5.5.1.tar.gz'

temp_dir=$(mktemp -d /tmp/aqbanking.XXXXXXXXXX)

echo "Serving files from /tmp on $PORT"
cd /tmp
python -m SimpleHTTPServer $PORT &

cd $temp_dir
echo "Temp dir: $temp_dir"

echo "Downloading $gwenhywfar_tarball_url"
curl -L $gwenhywfar_tarball_url | tar xzv

echo "Downloading $aqbanking_tarball_url"
curl -L $aqbanking_tarball_url | tar xzv

(
    cd /tmp/gwenhywfar-4.13.1
    ./configure --prefix=/tmp/gwenhywfar
    make
    make install
)

(
	cd /tmp/aqbanking-5.5.1
	./configure --prefix=/tmp/aqbanking --with-gwen-dir=/tmp/gwenhywfar
    make
	make install
)

while true
do
	sleep 1
	echo "."
done
