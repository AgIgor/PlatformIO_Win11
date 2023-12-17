const unsigned int knockSampleRate = 22050;
const unsigned int knockSampleCount = 415;
const signed char knockSamples[] = {//0
0, 0, 6, 16, 27, 36, 48, 56, 63, 71, 78, 85, 102, 109, 110, 107, //16
108, 108, 107, 107, 106, 105, 106, 114, 114, 112, 114, 109, 98, 101, 102, 103, //32
96, 79, 57, 37, 22, 17, 15, 12, 14, 23, 35, 38, 43, 54, 55, 54, //48
46, 42, 44, 41, 44, 48, 55, 65, 70, 86, 99, 103, 103, 104, 104, 84, //64
67, 65, 69, 66, 61, 60, 63, 66, 64, 69, 69, 68, 75, 73, 67, 58, //80
36, 36, 28, 7, -2, -16, -38, -53, -70, -85, -92, -103, -102, -100, -103, -99, //96
-85, -71, -60, -42, -26, -12, -3, -6, -4, -6, -22, -43, -83, -103, -105, -106, //112
-108, -107, -105, -109, -111, -108, -113, -113, -111, -115, -110, -106, -103, 8, 73, 97, //128
115, 121, 125, 117, 117, 116, 112, 113, 112, 113, 113, 114, 113, 112, 106, 105, //144
104, 100, 99, 96, 91, 69, 41, 8, -29, -57, -93, -108, -104, -115, -119, -119, //160
-122, -125, -127, -122, -118, -118, -116, -113, -110, -108, -108, -97, -59, -21, 0, 44, //176
109, 113, 119, 121, 118, 118, 119, 117, 108, 106, 105, 102, 104, 104, 109, 107, //192
109, 83, 35, 31, 35, 15, -4, -9, -19, -8, 27, 41, 66, 94, 110, 116, //208
92, 67, 83, 49, 7, 7, 10, -8, -22, -38, -63, -82, -76, -107, -120, -120, //224
-124, -121, -108, -81, -91, -99, -89, -96, -104, -86, -63, -59, -59, -38, -29, -30, //240
-27, -19, -24, -48, -78, -109, -120, -118, -119, -121, -119, -116, -116, -111, -108, -104, //256
-99, -83, -55, -25, 22, 92, 98, 95, 105, 112, 110, 108, 106, 107, 108, 106, //272
107, 92, 79, 73, 78, 76, 52, 48, 41, 51, 55, 50, 34, 25, 53, 51, //288
24, 11, 8, 21, 30, 35, 19, 8, 15, 2, -20, -23, 1, 18, 24, 43, //304
78, 102, 111, 111, 110, 111, 107, 108, 112, 112, 113, 114, 110, 107, 104, 105, //320
105, 99, 106, 85, 40, 4, 3, 9, -32, -36, -37, -34, -13, -1, -3, -13, //336
-29, -38, -54, -90, -107, -107, -109, -106, -109, -106, -101, -105, -106, -105, -105, -104, //352
-104, -107, -112, -112, -114, -116, -116, -115, -111, -108, -103, -103, -106, -93, -58, -25, //368
21, 53, 89, 112, 109, 107, 109, 107, 110, 115, 119, 120, 118, 115, 114, 112, //384
110, 114, 115, 115, 110, 108, 102, 72, 55, 43, 33, 17, -42, -86, -99, -99, //400
-103, -106, -111, -113, -113, -113, -112, -113, -115, -113, -105, -87, -70, -23, 0, };
