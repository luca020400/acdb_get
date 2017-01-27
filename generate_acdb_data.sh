#!/bin/bash

devices=$(strings $1 |  egrep "SND_DEVICE_OUT|SND_DEVICE_IN")

echo -ne "" > acdb_data.h

echo "#define LIB_AUDIO_HAL \"$(basename $1)\"" >> acdb_data.h
echo >> acdb_data.h

echo "enum {" >> acdb_data.h

for device in $devices; do
    echo "    $device," >> acdb_data.h
done

echo "    SND_DEVICE_MAX," >> acdb_data.h
echo "};" >> acdb_data.h

echo >> acdb_data.h

echo "static char * device_table[SND_DEVICE_MAX] = {" >> acdb_data.h
for device in $devices; do
    echo "    [$device] = \"$device\"," >> acdb_data.h
done
echo "};" >> acdb_data.h
