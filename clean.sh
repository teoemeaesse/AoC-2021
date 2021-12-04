#!/bin/sh
for D in */; do make -C "${D}" clean; done
