@echo off
test_generator > input
solution < input > output
correct_solution < input > correct_output
fc output correct_output
if errorlevel 1 exit
test
