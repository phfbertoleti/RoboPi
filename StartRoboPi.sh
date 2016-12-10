#!/bin/bash

gcc ControleRobo.c -o ControleRobo -l wiringPi
python WebCamView.py &  sudo ./ControleRobo

