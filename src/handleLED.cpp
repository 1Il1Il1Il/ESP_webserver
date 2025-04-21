#include "header.h"

const int Line1[] = {
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    151,
    152,
    153,
    154,
    155,
    156,
    157,
    200,
    201,
    202,
    203,
    217,
    221,
    222,
    223,
    224,
    238,
    305,
    307,
    306,
};
const int Line2[] = {
    7, 8, 9, 41, 40, 39,
    56, 57, 58, 90, 89, 88,
    109, 110, 111, 143, 142, 141,
    158, 159, 160, 192, 191, 190,
    204, 205, 215, 216,
    225, 226, 236, 237,
    301, 304, 303, 302};
const int Line3[] = {
    11, 10, 12, 37, 38, 36,
    60, 59, 61, 86, 87, 85,
    113, 112, 114, 139, 140, 138,
    162, 161, 163, 188, 189, 187,
    206, 207, 213, 214, 220, 218, 219,
    227, 228, 234, 235, 241, 239, 240,
    100, 101,
    299, 300};
const int Line4[] = {
    34, 35, 14, 13, 43, 44, 45, 46, 47, 48,
    83, 84, 63, 62, 92, 93, 94, 95, 96, 97,
    136, 137, 116, 115, 145, 146, 147, 148, 149, 150,
    185, 186, 165, 164, 194, 195, 196, 197, 198, 199,
    208, 212, 211, 210, 209,
    229, 233, 232, 231, 230,
    242, 243, 244, 245, 259,
    266, 263, 264, 265, 280,
    296, 298, 297};
const int Line5[] = {
    11 + 5, 10 + 5, 12 + 5,
    37 - 5, 38 - 5, 36 - 5,
    60 + 5, 59 + 5, 61 + 5,
    86 - 5, 87 - 5, 85 - 5,
    113 + 5, 112 + 5, 114 + 5,
    139 - 5, 140 - 5, 138 - 5,
    162 + 5, 161 + 5, 163 + 5,
    188 - 5, 189 - 5, 187 - 5,
    204 + 42, 205 + 42, 215 + 42, 216 + 42,
    225 + 42, 226 + 42, 236 + 42, 237 + 42,
    241 + 42, 239 + 42, 240 + 42,
    220 + 42, 218 + 42, 219 + 42,
    98, 99,
    291, 286, 285, 284};
const int Line6[] = {
    11 + 8, 10 + 8, 12 + 8,
    37 - 8, 38 - 8, 36 - 8,
    60 + 8, 59 + 8, 61 + 8,
    86 - 8, 87 - 8, 85 - 8,
    113 + 8, 112 + 8, 114 + 8,
    139 - 8, 140 - 8, 138 - 8,
    162 + 8, 161 + 8, 163 + 8,
    188 - 8, 189 - 8, 187 - 8,
    204 + 44, 205 + 44, 215 + 40, 216 + 40,
    225 + 44, 226 + 44, 236 + 40, 237 + 40,
    294, 293, 292, 290, 288, 287};
const int Line7[] = {
    0 + 21, 1 + 21, 2 + 21, 3 + 21, 4 + 21, 5 + 21, 6 + 21,
    49 + 21, 50 + 21, 51 + 21, 52 + 21, 53 + 21, 54 + 21, 55 + 21,
    102 + 21, 103 + 21, 104 + 21, 105 + 21, 106 + 21, 107 + 21, 108 + 21,
    151 + 21, 152 + 21, 153 + 21, 154 + 21, 155 + 21, 156 + 21, 157 + 21,
    254 - 4, 255 - 4, 256 - 4, 257 - 4, 258 - 4,
    275 - 4, 276 - 4, 277 - 4, 278 - 4, 279 - 4,
    295, 289};

#define STEPS 3000

#define POINTAPP 98

const int addNums[] = {0, 49, 102, 151, 200, 221, 242, 263};

const float tonlist[] = {0.0, 5.0, 55.0, 65.0, 85.0, 95.0, 145.0, 155.0, 178.0, 180.0, 185.0, 190.0, 230.0, 240.0, 295.0, 305.0, 355.0, 360.0}; //  0 500 700 1400 1500 1550 1950 2450 2600

const int nums[] = {
    1, 1, 1, 1, 1, 1, 0,
    0, 1, 1, 0, 0, 0, 0,
    1, 1, 0, 1, 1, 0, 1,
    1, 1, 1, 1, 0, 0, 1,
    0, 1, 1, 0, 0, 1, 1,
    1, 0, 1, 1, 0, 1, 1,
    1, 0, 1, 1, 1, 1, 1,
    1, 1, 1, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 0, 1, 1,
    0, 0, 0, 0, 0, 0, 0};

CRGB leds[NUMPIXELS];
chngNum ChngNum(STEPS, UPDATERATE - 1);
chngNum ChngPoint(2, 1000);
long chngColortimer = 1000;
long long chngColorlt;

const byte maincolors[] = {
    255, 0, 0,
    255, 0, 125,
    255, 0, 255,
    75, 20, 255,
    30, 99, 255,
    0, 255, 255,
    0, 255, 125,
    0, 255, 0,
    125, 255, 0,
    255, 255, 0,
    255, 125, 0,
    255, 75, 0};
byte currentcolor = 0;

const int endspart[] = {
    200, 42,
    242, 42,
    284, 12,
    296, 12};

float col[3];
int Speed = 100;

void fillLine(byte num, byte r, byte g, byte b);
void fillColor(byte mode, byte index1, byte index2, CRGB rgb);
void applyNum(byte num, byte value);
void applyPoint();
float rectifier(float value);
float *hsv2rgb(float h, float s, float b, float *rgb);
CRGB hex2rgb(uint32_t hex);
void fillEnd(byte index1, CRGB color1);

float rectifier(float value)
{
    byte len = sizeof(tonlist) / sizeof(float) - 1;
    int numseg = (int)(value * len);
    float part = (value * len - numseg);
    return tonlist[numseg] / tonlist[len] + (double)(tonlist[numseg + 1] - tonlist[numseg]) / (double)tonlist[len] * part;
}

float *hsv2rgb(float h, float s, float b, float *rgb)
{
    rgb[0] = b * mix(1.0, constrain(abs(fract(h + 1.0) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
    rgb[1] = b * mix(1.0, constrain(abs(fract(h + 0.6666666) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
    rgb[2] = b * mix(1.0, constrain(abs(fract(h + 0.3333333) * 6.0 - 3.0) - 1.0, 0.0, 1.0), s);
    return rgb;
}

float fract(float x) { return x - int(x); }

float mix(float a, float b, float t) { return a + (b - a) * t; }

handleLED::handleLED()
{
    chngColorlt = millis();
}

void handleLED::begin()
{
    FastLED.addLeds<WS2811, PIN, RGB>(leds, NUMPIXELS);
    FastLED.clear();
    FastLED.show();
}

void handleLED::tick()
{
    FastLED.clear();

    if (Data.storedStaticCheckbox)
        fillColor(1, 0, 0, hex2rgb(Data.storedStaticColor));

    if (Data.storedSpectrumCheckbox)
    {
        if (Speed != Data.storedSpectrumSpeed)
        {
            Speed = Data.storedSpectrumSpeed;
            ChngNum.Max((int)((float)STEPS / (Speed / 100)));
        }

        fillColor(0, 0, 0, CRGB(0, 0, 0));
    }

    if (Data.storedGradientCheckbox)
    {
        fillColor(2, Data.storedGradientShift, Data.storedGradientSize, CRGB(0, 0, 0));
    }

    if (Data.storedPeriodCheckbox)
    {
        bool flag = 0;
        for (byte i = 0; i < sizeof(Data.storedFlagTable) / sizeof(bool) / 3; i++)
            if (Data.storedFlagTable[i])
                flag = 1;
        if (!flag)
            return;

        if (chngColortimer != Data.storedPeriodHour * 3600 * 1000)
        {
            chngColortimer = Data.storedPeriodHour * 3600 * 1000;
            chngColorlt = millis();
            currentcolor = 0;
        }

        if (millis() - chngColorlt >= chngColortimer || !Data.storedFlagTable[currentcolor])
        {
            chngColorlt = millis();
            currentcolor++;
            if (currentcolor >= sizeof(maincolors) / sizeof(byte) / 3)
                currentcolor = 0;

            while (!Data.storedFlagTable[currentcolor])
            {
                currentcolor++;
                if (currentcolor >= sizeof(maincolors) / sizeof(byte) / 3)
                    currentcolor = 0;
            }
        }

        fillColor(3, currentcolor, 0, CRGB(0, 0, 0));
    }

    if (Data.storedCelsiusColorCheckbox)
    {
        fillEnd(0, hex2rgb(Data.storedCelsiusColor));
        fillEnd(3, hex2rgb(Data.storedCelsiusColor));
    }

    if (Data.storedPercentageColorCheckbox)
    {
        fillEnd(1, hex2rgb(Data.storedPercentageColor));
        fillEnd(2, hex2rgb(Data.storedPercentageColor));
    }

    if (Data.storedBlinkPointCheckbox)
        applyPoint();

    show(0, Leddata.Hour, 1);
    show(1, Leddata.Minutes, 1);
    show(2, Leddata.Temp, 1);
    show(3, Leddata.Humidity, 1);

    FastLED.show();
}

void handleLED::show(byte ind, byte num, bool zero)
{
    if (num / 10 != 0)
        applyNum(ind * 2, num / 10);
    else if (zero)
        applyNum(ind * 2, 0);
    else
        applyNum(ind * 2, 10);

    applyNum(ind * 2 + 1, num % 10);
}

void clearSegment(int add, int size)
{
    for (int i = add; i < add + size; i++)
        leds[i] = CRGB(0, 0, 0);
}

void applyNum(byte num, byte value)
{
    for (byte i = 0; i < 7; i++)
    {
        if (nums[i + 7 * value] == 0)
            clearSegment(addNums[num] + (num > 3 ? 3 : 7) * i, num > 3 ? 3 : 7);
    }
}

void applyPoint()
{
    if (!ChngPoint.value())
        for (byte i = POINTAPP; i < 4 + POINTAPP; i++)
            leds[i] = CRGB(0, 0, 0);
}

void fillColor(byte mode, byte index1, byte index2, CRGB rgb)
{
    float k = (float)Data.storedBrightnessRange / 100.0;
    float *color1;

    switch (mode)
    {
    case 0:
        color1 = hsv2rgb(rectifier((float)ChngNum.value() / ((float)STEPS / (Speed / 100))), 1.0, 1.0, col);
        for (int i = 0; i < NUMPIXELS; i++)
        {
            leds[i] = CRGB((int)((1.0 - color1[0]) * 255 * k), (int)((1.0 - color1[1]) * 255 * k), (int)((1.0 - color1[2]) * 255 * k));
        }
        break;

    case 1:
        for (int i = 0; i < NUMPIXELS; i++)
        {

            leds[i] = rgb;
        }
        break;

    case 2:
        for (int i = 0; i < 7; i++)
        {
            color1 = hsv2rgb(rectifier((float)index1 / 100.0 + ((float)(index2 - index1) / 100.0 / 7.0 * (float)i)), 1.0, 1.0, col);
            fillLine(i, (int)((1.0 - color1[0]) * 255 * k), (int)((1.0 - color1[1]) * 255 * k), (int)((1.0 - color1[2]) * 255 * k));
        }
        break;

    case 3:
        for (int i = 0; i < NUMPIXELS; i++)
        {
            leds[i] = CRGB(maincolors[index1 * 3 + 1], maincolors[index1 * 3], maincolors[index1 * 3 + 2]);
        }
        break;

    default:
        break;
    }
}

void fillLine(byte num, byte r, byte g, byte b)
{
    switch (num)
    {
    case 0:
        for (int i = 0; i < (byte)sizeof(Line1) / (byte)sizeof(int); i++)
            leds[Line1[i]] = CRGB(r, g, b);
        break;

    case 1:
        for (int i = 0; i < (byte)sizeof(Line2) / (byte)sizeof(int); i++)
            leds[Line2[i]] = CRGB(r, g, b);
        break;

    case 2:
        for (int i = 0; i < (byte)sizeof(Line3) / (byte)sizeof(int); i++)
            leds[Line3[i]] = CRGB(r, g, b);
        break;

    case 3:
        for (int i = 0; i < (byte)sizeof(Line4) / (byte)sizeof(int); i++)
            leds[Line4[i]] = CRGB(r, g, b);
        leds[42] = CRGB(r, g, b);
        leds[91] = CRGB(r, g, b);
        leds[144] = CRGB(r, g, b);
        leds[193] = CRGB(r, g, b);
        break;

    case 4:
        for (int i = 0; i < (byte)sizeof(Line5) / (byte)sizeof(int); i++)
            leds[Line5[i]] = CRGB(r, g, b);
        break;

    case 5:
        for (int i = 0; i < (byte)sizeof(Line6) / (byte)sizeof(int); i++)
            leds[Line6[i]] = CRGB(r, g, b);
        break;

    case 6:
        for (int i = 0; i < (byte)sizeof(Line7) / (byte)sizeof(int); i++)
            leds[Line7[i]] = CRGB(r, g, b);
        break;

    default:
        break;
    }
}

void fillEnd(byte index1, CRGB color1)
{
    for (int i = endspart[index1 * 2]; i < endspart[index1 * 2] + endspart[index1 * 2 + 1]; i++)
    {
        leds[i] = color1;
    }
}

CRGB hex2rgb(uint32_t hex)
{
    return CRGB((hex >> 8) & 0xFF, (hex >> 16) & 0xFF, hex & 0xFF);
}