const unsigned int revSampleRate = 22050;
const unsigned int revSampleCount = 3751;
const signed char revSamples[] = {//0
0, -1, -1, -1, -1, -2, -2, -3, -4, -4, -4, -4, -4, -3, -3, -3, //16
-3, -3, -3, -4, -4, -4, -4, -4, -4, -4, -3, -3, -2, -1, 0, 1, //32
2, 2, 3, 3, 3, 2, 1, 0, -1, -2, -3, -3, -4, -6, -4, -4, //48
-2, -1, 1, 6, 8, 11, 13, 16, 18, 20, 21, 21, 20, 19, 17, 13, //64
12, 10, 9, 8, 7, 6, 6, 6, 7, 7, 8, 9, 9, 10, 10, 10, //80
11, 11, 10, 10, 9, 7, 4, 1, -1, -3, -7, -9, -11, -12, -12, -13, //96
-13, -12, -11, -10, -8, -6, -3, -1, 0, 1, 1, 2, 1, 1, 0, -1, //112
-1, -2, -2, -2, -1, 0, 1, 3, 4, 7, 8, 9, 9, 9, 9, 8, //128
7, 6, 3, 2, 1, 0, -1, -2, -3, -4, -6, -7, -8, -9, -11, -12, //144
-14, -17, -19, -22, -25, -27, -29, -30, -31, -32, -33, -33, -32, -32, -31, -30, //160
-29, -28, -27, -27, -26, -26, -25, -23, -22, -20, -17, -13, -10, -7, -2, 1, //176
6, 9, 11, 14, 17, 20, 23, 27, 30, 33, 38, 45, 49, 53, 58, 61, //192
65, 69, 71, 74, 75, 76, 77, 79, 80, 81, 82, 84, 85, 85, 84, 84, //208
82, 81, 78, 77, 75, 72, 70, 67, 64, 61, 58, 55, 51, 47, 43, 40, //224
37, 35, 31, 28, 25, 22, 20, 18, 16, 14, 13, 12, 12, 12, 13, 14, //240
17, 18, 20, 21, 23, 25, 26, 27, 27, 29, 30, 31, 33, 35, 37, 40, //256
42, 45, 46, 47, 47, 47, 47, 47, 47, 47, 49, 50, 52, 53, 56, 58, //272
61, 64, 66, 68, 69, 69, 69, 69, 68, 68, 67, 66, 66, 65, 64, 64, //288
62, 62, 62, 62, 62, 62, 64, 64, 65, 65, 66, 66, 65, 64, 61, 59, //304
58, 56, 52, 50, 48, 46, 45, 42, 42, 41, 41, 41, 41, 41, 40, 39, //320
38, 36, 33, 29, 27, 25, 21, 19, 17, 16, 14, 13, 13, 13, 13, 12, //336
12, 11, 10, 8, 4, 2, -1, -3, -6, -10, -12, -13, -16, -17, -18, -20, //352
-20, -21, -21, -21, -22, -22, -23, -25, -25, -26, -25, -25, -23, -22, -21, -20, //368
-19, -19, -19, -20, -21, -22, -25, -27, -28, -29, -31, -32, -32, -33, -33, -33, //384
-33, -33, -33, -33, -32, -32, -33, -35, -36, -37, -39, -41, -45, -47, -50, -53, //400
-56, -59, -61, -63, -63, -65, -65, -66, -66, -67, -67, -67, -68, -69, -70, -71, //416
-74, -75, -77, -80, -81, -84, -85, -87, -88, -90, -91, -92, -92, -94, -94, -92, //432
-92, -92, -94, -94, -94, -94, -95, -95, -95, -94, -94, -94, -94, -94, -94, -94, //448
-92, -91, -89, -87, -85, -82, -80, -79, -77, -77, -75, -75, -74, -74, -74, -74, //464
-75, -75, -76, -77, -78, -79, -81, -84, -86, -88, -91, -95, -97, -99, -100, -101, //480
-101, -101, -100, -99, -98, -96, -95, -92, -90, -89, -87, -87, -86, -86, -87, -88, //496
-89, -91, -92, -92, -92, -92, -91, -89, -86, -84, -80, -78, -75, -72, -70, -69, //512
-68, -68, -68, -68, -69, -69, -69, -69, -69, -67, -66, -62, -60, -57, -52, -49, //528
-46, -43, -41, -40, -37, -36, -33, -32, -31, -29, -27, -25, -21, -19, -17, -12, //544
-10, -8, -6, -3, -1, 1, 2, 2, 2, 1, 1, 0, 0, -1, -1, -1, //560
-1, -2, -2, -3, -4, -4, -7, -7, -8, -9, -10, -10, -10, -10, -9, -9, //576
-8, -6, -4, -3, -2, -1, 0, 0, -1, -1, -2, -2, -1, -1, 0, 1, //592
2, 4, 6, 8, 9, 10, 11, 11, 11, 10, 9, 8, 7, 6, 6, 6, //608
6, 7, 8, 9, 9, 10, 10, 9, 8, 6, 3, 0, -2, -4, -7, -8, //624
-8, -7, -6, -4, -2, 0, 2, 6, 8, 11, 16, 18, 21, 23, 26, 29, //640
32, 35, 37, 40, 42, 47, 50, 53, 57, 61, 65, 70, 72, 76, 78, 80, //656
84, 86, 88, 90, 91, 94, 97, 99, 101, 104, 106, 108, 110, 111, 113, 114, //672
114, 114, 113, 113, 111, 111, 111, 113, 113, 114, 114, 114, 114, 114, 114, 113, //688
111, 111, 109, 108, 107, 106, 104, 102, 100, 100, 99, 99, 98, 98, 98, 98, //704
98, 98, 98, 97, 97, 96, 96, 95, 95, 94, 94, 94, 95, 96, 97, 99, //720
100, 101, 102, 102, 102, 104, 104, 104, 104, 104, 104, 104, 102, 102, 101, 101, //736
100, 100, 99, 99, 98, 97, 97, 97, 97, 98, 98, 97, 97, 96, 95, 94, //752
90, 89, 87, 85, 82, 81, 79, 78, 78, 77, 78, 78, 78, 79, 79, 78, //768
78, 75, 72, 70, 68, 65, 62, 58, 56, 52, 50, 48, 46, 42, 40, 38, //784
35, 32, 28, 25, 22, 19, 16, 13, 10, 8, 6, 3, 2, 0, -3, -7, //800
-9, -12, -16, -20, -22, -25, -27, -29, -31, -33, -35, -37, -38, -39, -40, -41, //816
-42, -43, -45, -46, -47, -48, -49, -50, -50, -51, -52, -53, -53, -55, -55, -56, //832
-56, -55, -55, -53, -52, -51, -50, -49, -49, -49, -49, -50, -50, -51, -52, -53, //848
-53, -55, -55, -53, -53, -53, -53, -53, -55, -57, -59, -62, -68, -72, -76, -79, //864
-81, -85, -88, -90, -91, -94, -95, -97, -98, -99, -101, -104, -105, -109, -111, -114, //880
-117, -119, -121, -123, -124, -125, -124, -124, -121, -119, -117, -116, -114, -113, -111, -110, //896
-109, -108, -108, -107, -106, -105, -105, -105, -104, -104, -102, -102, -101, -101, -100, -100, //912
-100, -99, -99, -99, -97, -96, -95, -92, -90, -89, -87, -86, -86, -86, -86, -86, //928
-86, -85, -85, -85, -85, -85, -86, -86, -87, -87, -88, -88, -87, -86, -85, -82, //944
-80, -76, -72, -70, -67, -65, -61, -60, -58, -57, -56, -56, -55, -55, -55, -55, //960
-53, -52, -51, -49, -48, -46, -45, -41, -39, -37, -33, -31, -29, -27, -26, -26, //976
-26, -26, -26, -26, -26, -26, -26, -26, -23, -22, -21, -19, -17, -16, -12, -11, //992
-10, -9, -8, -7, -7, -7, -8, -9, -10, -12, -14, -17, -19, -21, -23, -27, //1008
-29, -30, -31, -32, -32, -32, -31, -31, -30, -29, -28, -28, -28, -27, -27, -27, //1024
-27, -27, -28, -29, -29, -30, -30, -30, -30, -29, -28, -25, -22, -20, -18, -16, //1040
-12, -9, -7, -4, -2, 0, 1, 2, 3, 4, 6, 7, 9, 11, 12, 14, //1056
17, 19, 21, 23, 26, 28, 30, 32, 35, 37, 39, 41, 42, 46, 48, 49, //1072
51, 53, 56, 59, 60, 62, 65, 68, 71, 74, 76, 78, 81, 84, 87, 89, //1088
91, 94, 96, 98, 100, 101, 102, 102, 102, 101, 100, 99, 98, 96, 95, 91, //1104
89, 87, 85, 84, 82, 80, 79, 78, 76, 74, 70, 68, 65, 61, 58, 55, //1120
49, 46, 42, 39, 36, 32, 29, 27, 25, 23, 23, 22, 23, 23, 25, 27, //1136
28, 31, 35, 37, 40, 43, 46, 50, 52, 55, 57, 59, 62, 65, 68, 70, //1152
74, 77, 81, 86, 89, 92, 96, 99, 105, 107, 109, 111, 114, 116, 117, 118, //1168
118, 119, 119, 120, 120, 121, 123, 124, 125, 126, 126, 127, 127, 127, 127, 127, //1184
127, 126, 125, 125, 124, 123, 123, 123, 121, 120, 119, 118, 116, 114, 110, 106, //1200
104, 100, 97, 94, 91, 88, 87, 86, 85, 86, 86, 87, 87, 88, 88, 89, //1216
89, 89, 89, 89, 89, 88, 87, 87, 86, 86, 86, 85, 85, 85, 84, 82, //1232
81, 80, 78, 76, 74, 70, 67, 60, 55, 50, 45, 40, 32, 28, 23, 19, //1248
16, 11, 7, 3, 0, -3, -7, -10, -14, -18, -20, -23, -26, -30, -32, -36, //1264
-38, -41, -43, -48, -50, -53, -56, -58, -60, -63, -65, -67, -68, -69, -70, -71, //1280
-72, -72, -74, -75, -75, -75, -76, -76, -76, -76, -76, -76, -77, -77, -77, -78, //1296
-79, -80, -80, -81, -81, -81, -81, -80, -80, -80, -79, -78, -78, -77, -76, -75, //1312
-74, -72, -71, -70, -69, -67, -66, -65, -63, -63, -63, -63, -65, -65, -66, -66, //1328
-67, -68, -69, -70, -71, -72, -74, -76, -77, -78, -79, -81, -84, -86, -88, -90, //1344
-92, -95, -98, -99, -100, -101, -101, -102, -102, -102, -104, -104, -105, -106, -108, -109, //1360
-110, -113, -115, -117, -118, -119, -119, -120, -120, -119, -119, -118, -117, -116, -114, -114, //1376
-113, -113, -113, -114, -114, -115, -115, -116, -116, -116, -115, -114, -113, -111, -110, -108, //1392
-107, -106, -105, -102, -100, -97, -95, -91, -89, -87, -85, -81, -79, -77, -75, -72, //1408
-70, -68, -67, -66, -63, -62, -60, -58, -56, -52, -50, -47, -42, -39, -37, -33, //1424
-31, -28, -27, -25, -23, -23, -22, -21, -21, -21, -21, -20, -20, -19, -18, -17, //1440
-16, -16, -14, -14, -13, -14, -14, -16, -18, -19, -19, -20, -20, -20, -19, -19, //1456
-19, -19, -19, -19, -20, -20, -21, -21, -22, -22, -21, -20, -19, -17, -12, -9, //1472
-7, -3, -1, 1, 2, 3, 4, 4, 3, 3, 2, 1, 0, -1, -2, -3, //1488
-4, -7, -8, -10, -12, -14, -16, -18, -19, -20, -21, -23, -23, -25, -25, -25, //1504
-25, -25, -25, -26, -26, -26, -26, -25, -25, -23, -22, -20, -17, -14, -11, -8, //1520
-4, 2, 6, 10, 16, 20, 25, 30, 35, 38, 42, 45, 48, 52, 55, 58, //1536
61, 65, 69, 71, 75, 78, 81, 85, 90, 94, 98, 101, 105, 108, 113, 115, //1552
117, 119, 120, 121, 121, 120, 120, 118, 117, 115, 114, 111, 110, 109, 108, 106, //1568
105, 104, 102, 100, 97, 95, 91, 88, 86, 82, 78, 75, 72, 70, 68, 66, //1584
62, 60, 59, 57, 56, 56, 57, 58, 59, 61, 64, 67, 70, 72, 76, 78, //1600
81, 86, 88, 90, 94, 96, 99, 101, 104, 106, 108, 110, 113, 114, 115, 116, //1616
117, 118, 119, 119, 119, 119, 118, 118, 117, 116, 116, 115, 114, 111, 109, 107, //1632
105, 102, 99, 98, 96, 92, 90, 88, 86, 84, 82, 81, 81, 80, 77, 75, //1648
72, 69, 67, 62, 59, 57, 55, 53, 51, 49, 48, 48, 47, 45, 43, 41, //1664
40, 39, 37, 36, 35, 33, 32, 31, 30, 30, 29, 29, 29, 29, 29, 29, //1680
28, 28, 27, 27, 26, 25, 25, 23, 23, 23, 22, 22, 21, 21, 20, 20, //1696
19, 18, 17, 16, 14, 13, 10, 8, 6, 3, 1, -1, -4, -7, -9, -11, //1712
-13, -17, -20, -22, -25, -26, -28, -30, -31, -32, -33, -36, -37, -41, -43, -47, //1728
-50, -53, -57, -61, -66, -69, -74, -77, -82, -86, -89, -92, -95, -97, -101, -104, //1744
-106, -108, -109, -110, -111, -111, -110, -110, -109, -108, -107, -106, -104, -102, -101, -98, //1760
-97, -95, -94, -91, -89, -87, -85, -84, -81, -80, -78, -77, -76, -75, -72, -71, //1776
-69, -68, -67, -65, -62, -60, -58, -56, -55, -53, -51, -50, -50, -49, -49, -49, //1792
-49, -50, -50, -51, -51, -51, -52, -52, -52, -52, -52, -52, -52, -52, -52, -52, //1808
-53, -53, -55, -56, -57, -58, -59, -60, -62, -63, -65, -67, -68, -70, -71, -71, //1824
-72, -72, -72, -72, -72, -72, -72, -72, -72, -72, -72, -72, -72, -71, -69, -68, //1840
-66, -63, -61, -59, -55, -51, -49, -46, -42, -39, -36, -33, -31, -29, -27, -23, //1856
-21, -19, -18, -17, -17, -16, -17, -17, -17, -18, -18, -19, -20, -21, -21, -22, //1872
-23, -23, -23, -22, -22, -21, -20, -19, -18, -17, -16, -13, -13, -12, -12, -12, //1888
-12, -12, -13, -13, -12, -12, -11, -10, -9, -9, -8, -8, -7, -6, -4, -3, //1904
-2, 0, 3, 4, 6, 8, 8, 9, 9, 8, 8, 8, 8, 8, 8, 8, //1920
8, 8, 8, 9, 9, 10, 11, 12, 13, 14, 16, 17, 18, 18, 19, 19, //1936
20, 20, 20, 20, 21, 21, 21, 21, 21, 22, 22, 22, 22, 23, 23, 25, //1952
25, 25, 25, 26, 26, 25, 25, 25, 23, 22, 22, 21, 21, 21, 21, 21, //1968
21, 22, 23, 25, 25, 26, 27, 27, 28, 28, 28, 28, 28, 27, 25, 22, //1984
20, 17, 14, 12, 11, 10, 10, 10, 11, 12, 13, 16, 18, 19, 20, 21, //2000
22, 23, 25, 25, 25, 25, 25, 25, 23, 23, 22, 22, 21, 21, 21, 21, //2016
21, 21, 20, 20, 20, 21, 21, 22, 22, 23, 23, 23, 23, 22, 21, 20, //2032
19, 17, 16, 14, 13, 13, 12, 12, 13, 13, 14, 14, 16, 16, 16, 17, //2048
18, 19, 20, 21, 22, 23, 25, 26, 26, 26, 27, 28, 29, 30, 32, 33, //2064
37, 38, 40, 41, 43, 45, 47, 49, 50, 52, 53, 56, 57, 58, 59, 60, //2080
62, 64, 66, 67, 68, 68, 69, 69, 70, 70, 70, 71, 71, 71, 71, 70, //2096
69, 67, 65, 61, 59, 58, 56, 55, 53, 53, 52, 52, 51, 49, 48, 47, //2112
46, 45, 43, 41, 41, 40, 40, 39, 39, 38, 37, 36, 35, 33, 31, 30, //2128
28, 27, 26, 25, 23, 23, 22, 22, 21, 21, 20, 20, 20, 20, 20, 20, //2144
20, 20, 20, 20, 20, 20, 20, 19, 18, 18, 17, 17, 18, 18, 19, 20, //2160
23, 25, 27, 28, 29, 30, 30, 29, 28, 27, 25, 23, 20, 19, 18, 17, //2176
16, 16, 14, 14, 13, 13, 12, 12, 11, 11, 11, 10, 10, 9, 8, 8, //2192
7, 7, 6, 4, 3, 3, 2, 1, 0, 0, -1, -1, -2, -3, -3, -4, //2208
-4, -4, -4, -3, -3, -3, -3, -3, -3, -3, -2, -2, -3, -3, -6, -7, //2224
-8, -10, -11, -12, -13, -14, -16, -17, -18, -19, -21, -22, -23, -25, -26, -27, //2240
-28, -29, -29, -30, -30, -30, -30, -30, -30, -30, -30, -31, -32, -32, -33, -35, //2256
-36, -36, -37, -37, -37, -38, -39, -40, -42, -45, -46, -48, -51, -53, -55, -57, //2272
-58, -60, -61, -61, -62, -62, -63, -66, -67, -69, -71, -72, -75, -78, -79, -80, //2288
-81, -82, -84, -85, -85, -85, -85, -85, -85, -85, -85, -85, -85, -86, -86, -86, //2304
-86, -87, -87, -87, -87, -86, -85, -84, -82, -79, -78, -77, -76, -76, -76, -76, //2320
-76, -76, -76, -76, -76, -76, -75, -75, -74, -74, -74, -74, -72, -72, -71, -71, //2336
-69, -68, -67, -66, -65, -63, -62, -63, -63, -63, -65, -67, -68, -69, -70, -72, //2352
-74, -75, -76, -77, -78, -79, -80, -81, -84, -85, -87, -88, -91, -92, -95, -96, //2368
-98, -99, -100, -100, -100, -99, -99, -97, -96, -94, -91, -89, -87, -82, -79, -76, //2384
-72, -69, -65, -61, -59, -57, -53, -51, -48, -46, -43, -40, -38, -36, -32, -30, //2400
-29, -27, -25, -22, -20, -19, -18, -17, -16, -13, -11, -10, -9, -8, -7, -7, //2416
-8, -8, -9, -11, -12, -13, -13, -14, -14, -14, -13, -13, -13, -12, -10, -9, //2432
-6, -4, -2, 0, 1, 3, 3, 4, 4, 4, 3, 2, 2, 2, 2, 2, //2448
3, 4, 7, 8, 10, 12, 16, 17, 19, 20, 21, 22, 22, 22, 22, 22, //2464
22, 22, 22, 23, 25, 26, 27, 29, 30, 31, 31, 31, 31, 32, 32, 32, //2480
32, 32, 31, 30, 29, 28, 27, 25, 23, 21, 20, 19, 18, 17, 16, 16, //2496
14, 16, 16, 17, 18, 19, 21, 23, 26, 29, 30, 31, 32, 33, 35, 38, //2512
40, 42, 46, 49, 53, 58, 61, 65, 68, 71, 76, 78, 80, 82, 85, 87, //2528
90, 94, 96, 99, 101, 106, 108, 109, 110, 111, 111, 111, 110, 110, 109, 109, //2544
109, 108, 108, 108, 109, 109, 110, 111, 114, 115, 117, 118, 119, 120, 120, 120, //2560
119, 118, 116, 115, 114, 114, 114, 114, 114, 115, 115, 115, 114, 114, 113, 111, //2576
110, 109, 108, 107, 106, 106, 106, 106, 107, 107, 108, 109, 109, 110, 110, 111, //2592
111, 111, 110, 109, 106, 104, 100, 98, 96, 94, 92, 92, 92, 92, 92, 94, //2608
95, 96, 96, 96, 96, 94, 92, 90, 88, 85, 80, 78, 75, 72, 69, 67, //2624
64, 62, 60, 59, 57, 55, 52, 50, 49, 47, 45, 42, 41, 40, 39, 38, //2640
38, 37, 36, 33, 32, 31, 29, 28, 26, 23, 22, 20, 17, 16, 14, 12, //2656
11, 9, 7, 6, 3, 1, -1, -4, -7, -9, -10, -12, -13, -16, -17, -19, //2672
-21, -22, -25, -29, -31, -33, -36, -38, -40, -41, -42, -43, -43, -45, -45, -45, //2688
-46, -46, -47, -47, -48, -49, -50, -51, -53, -56, -58, -60, -62, -65, -67, -70, //2704
-72, -75, -77, -78, -79, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, -80, //2720
-81, -82, -84, -85, -86, -87, -89, -90, -91, -94, -95, -96, -97, -98, -98, -98, //2736
-99, -99, -100, -100, -101, -101, -101, -100, -100, -100, -100, -100, -101, -102, -104, -104, //2752
-106, -107, -108, -109, -110, -111, -111, -111, -111, -110, -110, -109, -107, -105, -102, -100, //2768
-99, -98, -97, -97, -96, -96, -97, -97, -97, -97, -97, -97, -97, -97, -97, -97, //2784
-96, -96, -96, -96, -95, -94, -92, -90, -89, -87, -85, -84, -82, -81, -80, -78, //2800
-77, -76, -75, -74, -72, -71, -70, -69, -69, -68, -68, -68, -68, -68, -67, -66, //2816
-65, -62, -60, -58, -56, -53, -51, -49, -48, -47, -46, -45, -45, -43, -42, -41, //2832
-39, -36, -33, -31, -29, -26, -23, -18, -16, -12, -9, -7, -2, 0, 1, 3, //2848
4, 4, 7, 7, 8, 9, 9, 10, 10, 10, 10, 10, 9, 9, 8, 7, //2864
6, 4, 3, 1, 1, 1, 1, 1, 2, 3, 4, 4, 6, 6, 6, 6, //2880
6, 4, 3, 2, -1, -3, -6, -8, -10, -11, -13, -14, -14, -16, -16, -17, //2896
-18, -19, -19, -20, -21, -22, -23, -25, -26, -27, -28, -30, -31, -31, -31, -31, //2912
-30, -29, -27, -26, -23, -20, -17, -13, -10, -6, -2, 2, 8, 12, 17, 21, //2928
26, 31, 35, 38, 41, 43, 47, 51, 53, 57, 60, 65, 70, 75, 78, 81, //2944
85, 88, 91, 92, 94, 95, 96, 96, 96, 96, 96, 96, 97, 97, 97, 97, //2960
96, 96, 95, 91, 90, 88, 85, 82, 80, 76, 74, 71, 69, 68, 66, 65, //2976
64, 62, 61, 60, 58, 57, 55, 52, 50, 49, 45, 42, 40, 38, 36, 32, //2992
31, 31, 31, 31, 32, 33, 35, 35, 36, 37, 39, 41, 43, 46, 48, 50, //3008
53, 57, 60, 64, 67, 70, 76, 78, 81, 85, 87, 90, 95, 97, 100, 104, //3024
106, 110, 113, 115, 117, 118, 119, 121, 123, 123, 123, 123, 123, 123, 123, 121, //3040
121, 120, 118, 117, 116, 115, 114, 114, 113, 113, 113, 113, 113, 113, 113, 113, //3056
111, 111, 110, 107, 105, 102, 99, 97, 95, 90, 88, 86, 84, 81, 79, 76, //3072
75, 74, 72, 71, 71, 71, 71, 71, 71, 70, 69, 67, 66, 65, 64, 61, //3088
59, 58, 57, 55, 53, 51, 49, 48, 47, 46, 45, 43, 42, 41, 40, 38, //3104
36, 35, 33, 31, 30, 28, 25, 21, 18, 14, 11, 8, 3, 1, -2, -4, //3120
-7, -10, -12, -14, -16, -18, -20, -22, -25, -27, -29, -30, -32, -36, -38, -40, //3136
-43, -46, -49, -52, -55, -57, -59, -61, -65, -68, -70, -72, -74, -76, -78, -79, //3152
-81, -84, -85, -88, -90, -92, -94, -95, -96, -97, -98, -99, -99, -100, -100, -101, //3168
-101, -102, -101, -101, -100, -98, -97, -95, -92, -90, -87, -86, -85, -84, -84, -84, //3184
-84, -85, -86, -87, -88, -89, -89, -89, -88, -87, -86, -85, -82, -81, -80, -79, //3200
-78, -77, -77, -77, -76, -76, -76, -76, -77, -77, -77, -78, -78, -78, -78, -78, //3216
-78, -78, -78, -79, -79, -79, -80, -80, -80, -80, -80, -80, -79, -79, -79, -78, //3232
-79, -79, -81, -82, -85, -87, -89, -90, -94, -95, -96, -97, -98, -98, -98, -97, //3248
-97, -97, -97, -97, -97, -98, -99, -100, -101, -104, -105, -106, -106, -106, -106, -104, //3264
-102, -101, -99, -97, -95, -92, -91, -90, -88, -87, -85, -82, -80, -78, -77, -75, //3280
-71, -70, -68, -67, -65, -62, -60, -58, -56, -53, -50, -47, -45, -41, -39, -37, //3296
-33, -31, -29, -28, -27, -26, -23, -23, -22, -22, -22, -22, -23, -23, -25, -25, //3312
-26, -26, -26, -25, -25, -25, -23, -23, -22, -22, -22, -21, -20, -19, -18, -17, //3328
-16, -16, -13, -12, -10, -9, -7, -4, -3, -1, 0, 1, 2, 3, 4, 7, //3344
8, 9, 10, 12, 13, 14, 16, 16, 16, 14, 14, 13, 12, 11, 10, 9, //3360
8, 7, 6, 4, 4, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, //3376
4, 4, 6, 6, 7, 8, 9, 10, 12, 14, 17, 20, 23, 27, 31, 35, //3392
39, 46, 50, 53, 58, 62, 67, 70, 74, 76, 78, 81, 85, 87, 89, 91, //3408
94, 96, 100, 102, 106, 109, 111, 116, 118, 119, 121, 121, 123, 123, 123, 123, //3424
121, 121, 120, 118, 116, 115, 113, 110, 107, 105, 102, 100, 98, 97, 95, 94, //3440
92, 91, 89, 87, 84, 82, 80, 78, 76, 72, 71, 69, 69, 68, 68, 68, //3456
68, 69, 70, 71, 74, 76, 78, 79, 81, 85, 88, 90, 91, 94, 95, 96, //3472
97, 97, 98, 98, 99, 99, 100, 100, 101, 102, 104, 106, 108, 109, 111, 114, //3488
115, 117, 118, 118, 118, 118, 117, 116, 115, 114, 113, 110, 108, 105, 102, 99, //3504
96, 92, 87, 82, 79, 76, 72, 69, 65, 61, 58, 56, 52, 48, 46, 42, //3520
39, 36, 32, 28, 25, 22, 20, 18, 14, 13, 12, 11, 10, 10, 9, 8, //3536
8, 8, 8, 8, 8, 9, 9, 9, 8, 8, 7, 7, 6, 4, 3, 2, //3552
1, 0, -1, -2, -3, -4, -6, -7, -8, -9, -10, -10, -11, -11, -12, -12, //3568
-13, -13, -14, -14, -16, -17, -19, -21, -23, -25, -27, -28, -28, -28, -28, -28, //3584
-28, -28, -29, -30, -32, -35, -37, -42, -46, -50, -55, -58, -63, -68, -71, -75, //3600
-78, -80, -85, -87, -88, -90, -91, -92, -94, -95, -96, -97, -99, -101, -104, -106, //3616
-108, -110, -111, -114, -114, -115, -116, -117, -117, -118, -118, -118, -118, -117, -116, -115, //3632
-115, -114, -114, -113, -110, -108, -106, -104, -101, -99, -97, -95, -94, -92, -92, -92, //3648
-92, -91, -91, -91, -90, -89, -88, -87, -87, -86, -84, -81, -80, -77, -75, -72, //3664
-69, -67, -66, -63, -63, -62, -61, -60, -60, -59, -59, -57, -56, -55, -53, -51, //3680
-50, -48, -46, -45, -42, -41, -39, -38, -36, -35, -35, -33, -32, -31, -31, -30, //3696
-30, -31, -32, -32, -33, -35, -35, -33, -32, -31, -30, -29, -29, -30, -30, -31, //3712
-32, -33, -35, -37, -37, -38, -39, -40, -40, -40, -39, -38, -37, -36, -35, -33, //3728
-32, -31, -30, -28, -26, -23, -21, -18, -16, -13, -11, -9, -8, -7, -7, -4, //3744
-3, -3, -2, -1, -1, -1, 0, };
