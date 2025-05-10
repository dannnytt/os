#!/bin/bash

LIB_FILE=lib/liblist.so

readelf -s $LIB_FILE

echo -e "\nСписок экспортируемых функций (для работы со списком):"
nm -D --defined-only $LIB_FILE | awk '{print $1,$3}'

echo -e "\nСписок имен секций:"
eu-readelf -S $LIB_FILE | grep -F "["
