#!/bin/sh

make test_pm

test_pm NGB/hypersheet.NGB res.off $1 tmp   
