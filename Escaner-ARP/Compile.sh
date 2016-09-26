#!/bin/bash

#
# Compiling script for the ARP Scanner
#
# This script compiles the ScannerARP.c sourcecode into an executable
# however, a few packages you need in order to compile appropiately this
# script:
#
#   - MySQL Client API 
#   - C++ Compiler (Due to OOP migration in future)
#   - A Linux-based box, this won't work on MacOS due to Networking libraries
#     used on the program. Use a Linux installation instead.
#
# You also need to run the resulting binary as root so it can properly run 
# since it uses sockets and some other tricky things which require some
# root permissions.
#
# 2016 - Humberto Alcocer

echo "Compiling..."
g++ *.c -o ARPScanner.out `mysql_config --libs`
echo "Success!"
echo ""