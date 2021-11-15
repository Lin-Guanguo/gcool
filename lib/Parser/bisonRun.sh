#!/bin/bash

bison Parser.y && mv -f Parser.h ../../include/gcool/Parser/Parser.h