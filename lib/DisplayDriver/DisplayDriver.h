
void initDisplayDriver();

/*
** Write to a specific XY coordinate
*/
void putPixel(byte x, byte y, byte thebyte);

/*
** Update to a specific XY coordinate
*/
void addPixel(byte x, byte y, byte thebyte);

/*
** Write a value to all displays inside a square area
*/
void fillPixel(byte x1, byte y1, byte x2, byte y2, byte thebyte);

/*
** Clears the display and triggers a refresh.
*/
void clear ();
/*
** Displays a digit at the defined location
*/
void digits(byte place, byte value);

/*
**
*/
void letters(byte place, char letter);

/*
** Refresh display data
*/
void refreshDisplays();

/*
** Writes a value to all MAX7219 drivers
*/
void setDriverRegisters(uint8_t address, uint8_t value);

/*
** Sends values data for all display drivers
*/
void MAX7219Send(
    uint8_t address, uint8_t value,
    uint8_t addressb, uint8_t valueb,
    uint8_t addressc, uint8_t valuec,
    uint8_t addressd, uint8_t valued,
    uint8_t addresse, uint8_t valuee,
    uint8_t addressf, uint8_t valuef,
    uint8_t addressg, uint8_t valueg,
    uint8_t addressh, uint8_t valueh,
    uint8_t addressi, uint8_t valuei,
    uint8_t addressj, uint8_t valuej,
    uint8_t addressk, uint8_t valuek,
    uint8_t addressl, uint8_t valuel,
    uint8_t addressm, uint8_t valuem,
    uint8_t addressn, uint8_t valuen,
    uint8_t addresso, uint8_t valueo,
    uint8_t addressp, uint8_t valuep,
    uint8_t addressq, uint8_t valueq,
    uint8_t addressr, uint8_t valuer);
