@echo off

REM Valid URLs
set URL1=http://www.example.com:8080/index.html
set URL2=https://example.org/
set URL3=ftp://ftp.example.net

REM Invalid URLs
set URL4=htt://invalid-url.com
set URL5=://missing-protocol.com
set URL6=ftp://missing-host-port:

REM Run the program for each URL
echo Testing Valid URL 1: %URL1%
ParseURL.exe %URL1%

echo Testing Valid URL 2: %URL2%
ParseURL.exe %URL2%

echo Testing Valid URL 3: %URL3%
ParseURL.exe %URL3%

echo Testing Invalid URL 4: %URL4%
ParseURL.exe %URL4%

echo Testing Invalid URL 5: %URL5%
ParseURL.exe %URL5%

echo Testing Invalid URL 6: %URL6%
ParseURL.exe %URL6%

echo All tests completed.
pause
