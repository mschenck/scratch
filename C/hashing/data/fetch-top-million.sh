#!/bin/bash

DATADIR=$(dirname "${BASH_SOURCE[0]}")
TOPMILLIONZIP="$DATADIR/top-million.zip"
TOPMILLIONREPORT="$DATADIR/Quantcast-Top-Million.txt"
TOPMILLIONFILE="$DATADIR/top-million.txt"

echo "Pulling down Quantcast Top Million list"
wget -O $TOPMILLIONZIP https://ak.quantcast.com/quantcast-top-million.zip

if [[ -f $TOPMILLIONZIP ]]
then
  echo "Extracting the FQDNs"
  unzip -c $TOPMILLIONZIP > $TOPMILLIONREPORT
  egrep '^[0-9]' $TOPMILLIONREPORT | awk '{print $2}' | sed -e 's///g' > $TOPMILLIONFILE
else
  echo "Failed to retrieve list"
  exit 1
fi
