#pragma once

void initWifi();

void setupWifi(const char* ssid, const char* passphrase);

bool reconnectWifi(const char* ssid, const char* passphrase);