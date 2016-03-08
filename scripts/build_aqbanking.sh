#!/bin/bash


AQBANKING_VERSION=${AQBANKING_VERSION-5.5.1}

aqbanking_tarball_url=http://www.aquamaniac.de/sites/download/download.php?package=03&release=118&file=01&dummy=aqbanking-5.5.1.tar.gz

temp_dir=$(mktemp -d /tmp/aqbanking.XXXXXXXXXX)

echo "Serving files from /tmp on $PORT"
cd /tmp
python -m SimpleHTTPServer $PORT &

cd $temp_dir
echo "Temp dir: $temp_dir"

echo "Downloading $aqbanking_tarball_url"
curl -L $aqbanking_tarball_url | tar xzv

(
	cd aqbanking-${NGINX_VERSION}
	./configure \
		--prefix=/tmp/aqbanking \
	make install
)

while true
do
	sleep 1
	echo "."
done
