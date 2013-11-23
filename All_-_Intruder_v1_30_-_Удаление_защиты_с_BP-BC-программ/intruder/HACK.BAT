@echo off
intruder %1 
del dump?.dat > nul
del %1 > nul
ren cracked.exe %1 > nul
