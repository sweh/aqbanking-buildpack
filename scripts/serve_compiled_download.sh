#!/bin/bash

echo "Serving files from /app/download on $PORT"
cd /app/download
python -m SimpleHTTPServer $PORT &

while true
do
    sleep 1
    echo "."
done
