acdb_get
========

This binary dload the stock audio hal and dump the acdb table

WARNING: SOCs <8974 aren't supported

0. Generate the acdb_data header
   -> ./generate_acdb_data.sh $stock_audio_hal.so
0. Build and push this binary
0. Push stock 32bit audio hal and dependencies to /system/lib
0. Run the binary
0. Enjoy your acdb table
