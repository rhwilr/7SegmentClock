# 7SegmentClock

![Cover](../assets/Cover.jpeg)

This is my 7 Segment display clock. The project started out as a rebuild of a
project by [Frugha on Hackaday][1]. The display is built using 144 7 Segment
displays controlled by an arduino nano.

I initially built the project exectly acording to the original schema, but
quickly came up with several extensions and improvements to make make the clock
more usefull to me.


## Added Features

- DHT22 temparature/humidity sensor
  - Displays the room teparature once a minute.
- ESP-01 Wi-Fi Module
  - Fetch the current time on boot-up from NTP.
  - Re-sync the ntp time perodically.

![Demo Animation](../assets/Demo.gif?raw=true)


## Planned Features

- Display outside temparature, fetched from weather services.
- Display stock price for stocks in my portfolio.
- Add Home Assistant integration to turn of the display.


[1]: https://hackaday.io/project/169632-7-segment-display-array-clock