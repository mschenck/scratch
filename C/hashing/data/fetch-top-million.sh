#!/bin/bash

DATADIR=$(dirname "${BASH_SOURCE[0]}")
TOPMILLIONZIP="$DATADIR/top-million.zip"
TOPMILLIONREPORT="$DATADIR/Quantcast-Top-Million.txt"
TOPMILLIONFILE="$DATADIR/top-million.txt"

wget -O $TOPMILLIONZIP https://ak.quantcast.com/quantcast-top-million.zip

if [[ -f $TOPMILLIONZIP ]]
then
  unzip -c $TOPMILLIONZIP > $TOPMILLIONREPORT
  egrep '^[0-9]' $TOPMILLIONREPORT | awk '{print $2}' > $TOPMILLIONFILE
fi
