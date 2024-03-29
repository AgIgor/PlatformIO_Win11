const unsigned int sampleRate = 22050;
const unsigned int sampleCount = 2971;
const signed char samples[] = {//0
0, -1, -1, -1, -1, -1, 0, 0, 1, 2, 2, 4, 6, 8, 11, 13, //16
15, 15, 15, 16, 18, 21, 22, 21, 20, 20, 20, 19, 17, 17, 17, 18, //32
20, 23, 29, 31, 34, 36, 38, 40, 41, 40, 40, 41, 42, 43, 42, 40, //48
39, 38, 37, 35, 32, 28, 25, 24, 21, 14, 9, 5, 2, -1, -6, -13, //64
-18, -22, -24, -27, -33, -38, -44, -48, -50, -49, -49, -52, -56, -60, -65, -70, //80
-77, -80, -82, -84, -86, -91, -95, -97, -98, -99, -100, -103, -103, -103, -102, -101, //96
-101, -101, -102, -103, -102, -101, -99, -99, -100, -101, -102, -102, -99, -96, -94, -94, //112
-95, -97, -98, -96, -92, -89, -87, -86, -86, -85, -81, -77, -71, -64, -58, -54, //128
-52, -47, -43, -34, -28, -22, -17, -13, -9, -5, -1, 3, 6, 11, 16, 18, //144
19, 21, 21, 26, 30, 35, 37, 38, 42, 52, 60, 64, 66, 67, 66, 66, //160
65, 65, 65, 65, 62, 61, 58, 55, 53, 51, 49, 45, 41, 37, 32, 27, //176
21, 18, 16, 15, 14, 13, 11, 8, 6, 4, 2, 1, -1, -3, -4, -4, //192
-6, -9, -11, -12, -14, -16, -18, -18, -18, -19, -19, -19, -18, -18, -18, -18, //208
-17, -16, -14, -13, -13, -13, -13, -10, -7, -7, -7, -7, -7, -3, 1, 3, //224
2, 2, 4, 7, 10, 10, 9, 9, 12, 16, 21, 24, 24, 27, 33, 37, //240
39, 39, 38, 39, 41, 43, 43, 42, 43, 49, 53, 55, 55, 55, 57, 61, //256
63, 64, 63, 59, 57, 55, 56, 58, 59, 60, 61, 64, 68, 71, 74, 77, //272
78, 78, 78, 79, 80, 81, 80, 81, 83, 86, 89, 94, 99, 103, 108, 112, //288
116, 122, 124, 123, 118, 114, 109, 106, 104, 102, 98, 96, 94, 95, 95, 94, //304
93, 90, 84, 78, 71, 65, 59, 49, 42, 34, 27, 22, 19, 15, 12, 10, //320
6, 4, 2, 0, -2, -2, -2, -4, -6, -7, -6, -5, -4, -4, -5, -6, //336
-7, -9, -9, -11, -14, -16, -19, -23, -29, -36, -37, -39, -40, -43, -47, -53, //352
-55, -57, -59, -61, -63, -64, -64, -62, -62, -63, -64, -63, -63, -62, -62, -63, //368
-66, -69, -72, -74, -78, -80, -81, -82, -82, -82, -82, -81, -81, -81, -81, -79, //384
-77, -74, -73, -71, -69, -69, -69, -67, -67, -66, -65, -64, -62, -62, -64, -65, //400
-64, -62, -58, -56, -56, -56, -57, -56, -55, -55, -54, -54, -56, -57, -57, -57, //416
-56, -55, -53, -51, -50, -49, -48, -48, -47, -45, -43, -41, -39, -38, -38, -38, //432
-36, -34, -31, -28, -26, -25, -25, -26, -26, -25, -22, -18, -16, -14, -14, -15, //448
-15, -14, -12, -11, -11, -12, -14, -15, -15, -15, -15, -15, -16, -18, -18, -19, //464
-20, -20, -21, -21, -22, -25, -30, -33, -32, -31, -30, -31, -33, -34, -36, -37, //480
-37, -37, -35, -32, -29, -28, -29, -31, -30, -28, -27, -24, -19, -19, -19, -19, //496
-18, -16, -13, -11, -9, -8, -7, -6, -5, -3, -1, 0, 3, 6, 8, 10, //512
12, 16, 19, 22, 23, 23, 21, 19, 18, 16, 17, 18, 20, 20, 20, 20, //528
22, 25, 28, 30, 32, 31, 31, 32, 35, 41, 47, 49, 51, 55, 61, 68, //544
70, 69, 67, 65, 61, 56, 50, 43, 37, 30, 25, 19, 15, 10, 6, 1, //560
-2, -5, -7, -11, -16, -19, -24, -27, -32, -37, -42, -45, -49, -51, -51, -52, //576
-54, -55, -52, -48, -46, -46, -47, -46, -43, -40, -38, -37, -39, -40, -39, -36, //592
-34, -31, -31, -33, -33, -31, -27, -24, -21, -19, -17, -15, -12, -5, -1, 2, //608
5, 8, 11, 13, 14, 15, 16, 18, 19, 22, 24, 26, 27, 29, 35, 40, //624
45, 48, 52, 54, 57, 61, 65, 69, 75, 79, 85, 89, 94, 99, 104, 109, //640
110, 111, 112, 113, 114, 112, 110, 108, 107, 106, 106, 106, 106, 107, 108, 110, //656
111, 113, 114, 115, 117, 117, 117, 117, 117, 118, 118, 117, 112, 108, 106, 103, //672
100, 98, 97, 97, 97, 95, 92, 88, 87, 87, 86, 83, 80, 75, 71, 66, //688
60, 53, 43, 37, 33, 31, 27, 23, 12, 6, 3, 2, 2, 1, 0, -2, //704
-5, -6, -8, -11, -14, -19, -24, -27, -31, -37, -42, -47, -52, -55, -58, -66, //720
-70, -73, -74, -74, -73, -72, -71, -72, -73, -76, -78, -78, -77, -77, -77, -77, //736
-79, -80, -81, -81, -82, -82, -83, -85, -88, -91, -94, -95, -95, -95, -95, -95, //752
-95, -93, -92, -89, -84, -79, -75, -75, -76, -76, -76, -74, -70, -70, -69, -67, //768
-66, -66, -66, -66, -64, -61, -56, -49, -45, -42, -39, -34, -31, -27, -24, -21, //784
-16, -13, -10, -8, -6, -4, -3, -2, 0, 3, 5, 9, 12, 15, 18, 19, //800
22, 24, 27, 29, 30, 32, 33, 33, 32, 31, 30, 28, 26, 23, 22, 23, //816
22, 20, 18, 17, 15, 15, 16, 16, 15, 14, 11, 10, 10, 10, 10, 7, //832
-1, -5, -10, -15, -20, -27, -30, -33, -37, -41, -45, -47, -49, -49, -51, -56, //848
-61, -66, -67, -66, -65, -67, -72, -73, -73, -73, -74, -75, -78, -81, -84, -87, //864
-90, -94, -98, -96, -91, -87, -85, -85, -84, -81, -77, -71, -64, -57, -54, -52, //880
-50, -46, -40, -35, -33, -31, -29, -26, -16, -10, -3, 3, 7, 12, 19, 26, //896
32, 38, 43, 48, 48, 49, 49, 50, 52, 56, 57, 59, 61, 63, 65, 68, //912
69, 69, 70, 72, 74, 75, 75, 73, 71, 69, 65, 64, 61, 57, 53, 51, //928
48, 44, 41, 39, 36, 35, 31, 27, 24, 19, 16, 10, 6, 4, 3, 1, //944
-2, -4, -5, -6, -7, -8, -9, -10, -12, -14, -17, -19, -21, -23, -24, -25, //960
-25, -24, -23, -22, -21, -20, -19, -16, -13, -10, -8, -7, -6, -4, -2, 1, //976
4, 7, 9, 14, 16, 17, 20, 22, 26, 28, 31, 35, 38, 42, 48, 52, //992
56, 59, 62, 65, 68, 70, 72, 73, 74, 74, 73, 74, 74, 74, 73, 72, //1008
73, 74, 75, 75, 74, 72, 71, 70, 69, 68, 67, 67, 64, 61, 57, 53, //1024
50, 47, 46, 44, 42, 37, 33, 32, 32, 32, 32, 31, 28, 24, 22, 21, //1040
21, 18, 14, 10, 7, 6, 5, 5, 3, 1, -3, -6, -8, -9, -9, -10, //1056
-13, -16, -22, -24, -24, -24, -25, -28, -30, -29, -27, -25, -22, -22, -22, -22, //1072
-22, -22, -21, -18, -17, -17, -19, -20, -20, -20, -19, -19, -17, -13, -5, -2, //1088
0, 0, 0, 2, 7, 10, 12, 11, 9, 7, 8, 10, 12, 11, 11, 10, //1104
10, 10, 9, 8, 7, 6, 7, 9, 11, 13, 13, 13, 12, 12, 12, 13, //1120
16, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 16, 15, 14, 14, 15, //1136
15, 15, 13, 13, 13, 14, 16, 16, 14, 12, 9, 7, 8, 6, 3, -2, //1152
-7, -11, -16, -18, -20, -23, -28, -32, -36, -39, -43, -46, -50, -54, -57, -61, //1168
-66, -69, -72, -75, -77, -80, -82, -83, -86, -87, -88, -88, -89, -91, -94, -94, //1184
-93, -92, -91, -90, -90, -90, -89, -88, -86, -81, -77, -75, -73, -72, -73, -75, //1200
-75, -72, -69, -68, -67, -68, -67, -64, -60, -55, -48, -43, -39, -36, -33, -29, //1216
-18, -13, -11, -7, -4, -1, 3, 6, 9, 12, 14, 20, 25, 31, 36, 39, //1232
40, 41, 42, 45, 47, 49, 50, 52, 54, 57, 58, 58, 56, 56, 54, 51, //1248
46, 42, 34, 28, 22, 17, 11, 8, 0, -5, -11, -15, -18, -26, -30, -34, //1264
-37, -40, -45, -53, -58, -61, -63, -64, -67, -74, -79, -82, -83, -83, -80, -80, //1280
-82, -82, -82, -81, -79, -79, -79, -79, -76, -74, -71, -70, -72, -73, -73, -69, //1296
-66, -63, -60, -58, -54, -45, -39, -34, -29, -24, -18, -9, -2, 5, 12, 19, //1312
26, 30, 35, 42, 47, 51, 57, 62, 66, 70, 75, 82, 87, 91, 96, 100, //1328
103, 107, 110, 113, 116, 119, 121, 124, 126, 126, 126, 126, 126, 126, 126, 126, //1344
126, 125, 119, 113, 109, 106, 104, 103, 98, 94, 88, 82, 79, 75, 73, 69, //1360
65, 62, 60, 58, 57, 54, 52, 50, 47, 43, 40, 39, 40, 39, 36, 32, //1376
28, 23, 20, 20, 20, 20, 19, 18, 17, 17, 18, 19, 21, 20, 17, 16, //1392
15, 14, 13, 12, 11, 12, 13, 12, 11, 11, 11, 16, 17, 16, 16, 16, //1408
19, 22, 25, 26, 28, 28, 29, 28, 28, 31, 33, 34, 32, 31, 31, 32, //1424
34, 36, 35, 34, 32, 32, 31, 29, 27, 26, 25, 24, 23, 23, 22, 21, //1440
19, 16, 10, 8, 5, 1, -3, -7, -11, -13, -16, -20, -23, -26, -30, -32, //1456
-36, -39, -41, -45, -47, -49, -50, -51, -51, -52, -53, -53, -54, -55, -57, -59, //1472
-60, -61, -63, -65, -70, -74, -76, -77, -78, -81, -84, -85, -85, -85, -85, -85, //1488
-85, -84, -80, -76, -73, -71, -71, -70, -66, -61, -55, -47, -43, -40, -38, -34, //1504
-27, -20, -15, -12, -11, -11, -9, -6, -3, 0, 2, 2, 3, 4, 6, 10, //1520
16, 22, 24, 24, 24, 23, 21, 17, 15, 13, 11, 10, 9, 5, 2, -1, //1536
-4, -6, -9, -11, -12, -16, -20, -25, -31, -34, -39, -44, -50, -56, -60, -62, //1552
-64, -66, -70, -75, -77, -78, -78, -76, -74, -72, -71, -70, -70, -68, -65, -60, //1568
-58, -57, -58, -57, -51, -45, -41, -39, -38, -38, -38, -36, -32, -27, -23, -21, //1584
-18, -15, -9, -3, 1, 4, 6, 11, 17, 26, 33, 42, 45, 49, 53, 59, //1600
65, 70, 71, 71, 70, 71, 74, 76, 79, 81, 82, 85, 89, 93, 99, 104, //1616
109, 112, 111, 108, 106, 105, 104, 97, 92, 86, 80, 73, 64, 54, 49, 44, //1632
38, 32, 24, 20, 16, 10, 4, -4, -13, -17, -22, -27, -34, -43, -57, -64, //1648
-70, -76, -83, -91, -96, -100, -104, -107, -109, -112, -114, -116, -116, -116, -116, -117, //1664
-115, -112, -109, -107, -105, -105, -104, -102, -99, -96, -93, -91, -87, -82, -79, -75, //1680
-69, -63, -55, -47, -38, -27, -20, -13, -5, 4, 12, 25, 34, 42, 51, 59, //1696
64, 69, 71, 74, 79, 85, 91, 91, 91, 92, 95, 101, 111, 116, 119, 121, //1712
125, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 125, 123, 120, 117, 114, //1728
109, 105, 102, 98, 96, 93, 90, 85, 76, 72, 69, 66, 63, 59, 54, 50, //1744
46, 42, 38, 34, 29, 26, 24, 22, 18, 12, 6, 1, -3, -5, -7, -11, //1760
-13, -16, -17, -17, -17, -16, -15, -15, -17, -20, -26, -28, -29, -29, -30, -31, //1776
-33, -32, -30, -28, -25, -23, -21, -19, -17, -15, -13, -10, -6, -3, -1, 1, //1792
3, 3, 4, 5, 7, 9, 10, 10, 9, 9, 10, 11, 14, 14, 12, 12, //1808
12, 12, 11, 10, 10, 9, 7, 4, 4, 4, 3, 0, -3, -6, -5, -2, //1824
1, 1, 0, -7, -11, -14, -16, -19, -24, -28, -31, -33, -33, -34, -38, -41, //1840
-43, -44, -45, -46, -50, -54, -57, -59, -60, -58, -58, -58, -58, -58, -58, -55, //1856
-53, -50, -46, -42, -39, -37, -37, -37, -38, -38, -36, -35, -35, -35, -36, -35, //1872
-33, -31, -28, -25, -22, -19, -15, -11, -7, -3, 0, 4, 6, 8, 11, 14, //1888
18, 25, 29, 31, 31, 32, 33, 35, 35, 36, 35, 35, 34, 33, 32, 31, //1904
30, 30, 31, 32, 33, 32, 31, 27, 23, 19, 15, 11, 6, 1, -1, -3, //1920
-7, -11, -16, -22, -25, -30, -37, -43, -52, -57, -60, -62, -63, -65, -71, -76, //1936
-80, -82, -85, -88, -91, -93, -95, -97, -99, -99, -98, -98, -99, -99, -98, -97, //1952
-95, -94, -94, -94, -92, -88, -87, -86, -85, -84, -80, -78, -76, -74, -70, -65, //1968
-57, -50, -46, -43, -38, -32, -24, -19, -14, -11, -8, -2, 3, 7, 8, 11, //1984
14, 21, 25, 28, 28, 30, 33, 39, 43, 46, 48, 51, 58, 58, 56, 55, //2000
56, 58, 61, 61, 59, 56, 53, 52, 51, 47, 42, 37, 31, 28, 26, 23, //2016
18, 12, 6, 0, -3, -6, -12, -18, -24, -31, -36, -42, -48, -53, -57, -57, //2032
-57, -59, -61, -64, -66, -65, -63, -63, -64, -65, -65, -65, -62, -58, -54, -45, //2048
-39, -35, -31, -28, -27, -22, -18, -13, -8, -4, 1, 5, 9, 14, 20, 25, //2064
34, 41, 48, 55, 62, 68, 75, 80, 85, 89, 93, 100, 105, 108, 112, 115, //2080
117, 120, 122, 124, 124, 125, 125, 125, 124, 122, 119, 117, 118, 119, 119, 117, //2096
115, 114, 115, 116, 115, 113, 110, 107, 103, 99, 93, 86, 78, 70, 68, 68, //2112
66, 63, 60, 55, 55, 54, 51, 48, 43, 33, 28, 26, 26, 25, 23, 20, //2128
19, 19, 19, 20, 20, 20, 20, 22, 22, 23, 22, 20, 19, 18, 19, 23, //2144
26, 31, 35, 39, 44, 49, 51, 52, 53, 54, 53, 52, 51, 49, 47, 44, //2160
42, 40, 39, 39, 40, 42, 44, 44, 45, 46, 47, 47, 45, 42, 40, 40, //2176
39, 36, 33, 29, 26, 24, 21, 16, 12, 6, 2, -1, -4, -10, -16, -22, //2192
-28, -32, -37, -39, -43, -47, -52, -57, -62, -65, -68, -73, -80, -89, -94, -98, //2208
-103, -107, -112, -118, -120, -123, -126, -127, -127, -127, -127, -127, -127, -127, -127, -127, //2224
-127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -127, -125, -120, //2240
-116, -113, -108, -102, -97, -92, -90, -89, -87, -82, -79, -73, -71, -69, -66, -64, //2256
-57, -51, -46, -42, -40, -38, -31, -25, -17, -11, -5, 0, 8, 14, 19, 24, //2272
29, 34, 36, 39, 42, 44, 46, 47, 47, 46, 45, 45, 44, 41, 37, 33, //2288
29, 26, 22, 19, 17, 15, 11, 8, 4, 2, 2, 2, 2, 1, -4, -9, //2304
-14, -18, -22, -28, -30, -33, -38, -43, -46, -50, -52, -54, -56, -57, -57, -56, //2320
-55, -55, -54, -54, -52, -50, -48, -47, -45, -43, -37, -31, -26, -23, -20, -17, //2336
-13, -11, -9, -5, 0, 4, 6, 7, 8, 10, 13, 19, 21, 24, 24, 24, //2352
29, 32, 36, 38, 39, 41, 44, 49, 53, 54, 54, 56, 61, 65, 67, 67, //2368
66, 68, 69, 69, 65, 59, 54, 46, 43, 41, 38, 32, 26, 17, 13, 9, //2384
7, 8, 11, 12, 13, 14, 15, 15, 16, 15, 13, 11, 10, 8, 5, 3, //2400
1, 0, -2, -5, -7, -8, -7, -6, -6, -8, -9, -10, -9, -9, -8, -6, //2416
-6, -4, -3, 0, 3, 3, 3, 3, 4, 9, 15, 19, 24, 26, 28, 30, //2432
35, 38, 39, 38, 37, 37, 38, 38, 36, 33, 32, 33, 35, 35, 37, 39, //2448
40, 42, 43, 46, 49, 51, 55, 56, 56, 54, 53, 55, 56, 58, 59, 60, //2464
58, 56, 55, 57, 59, 60, 59, 55, 50, 47, 46, 45, 44, 40, 38, 36, //2480
35, 35, 35, 37, 38, 40, 40, 40, 40, 40, 40, 38, 36, 34, 30, 28, //2496
27, 27, 26, 23, 20, 16, 12, 11, 11, 9, 7, 5, 3, 2, 2, 2, //2512
4, 6, 9, 9, 10, 10, 11, 13, 16, 20, 23, 23, 21, 21, 23, 26, //2528
28, 29, 28, 27, 28, 29, 27, 26, 25, 24, 24, 25, 25, 25, 25, 25, //2544
27, 30, 29, 29, 30, 32, 34, 33, 33, 33, 34, 36, 38, 39, 39, 38, //2560
37, 38, 40, 40, 39, 37, 33, 30, 30, 28, 26, 23, 19, 11, 6, 2, //2576
0, -3, -6, -9, -11, -14, -17, -21, -27, -32, -38, -44, -49, -53, -58, -62, //2592
-66, -69, -72, -75, -81, -85, -88, -90, -93, -101, -107, -112, -117, -119, -120, -122, //2608
-123, -126, -127, -127, -126, -122, -121, -120, -118, -115, -110, -107, -105, -103, -102, -102, //2624
-99, -97, -96, -93, -90, -87, -79, -75, -72, -69, -66, -59, -53, -48, -45, -42, //2640
-38, -32, -28, -24, -22, -21, -18, -15, -12, -8, -4, 0, 2, 3, 5, 10, //2656
14, 16, 16, 13, 12, 12, 14, 18, 21, 23, 23, 22, 22, 23, 25, 25, //2672
23, 19, 16, 8, 3, -2, -6, -9, -16, -21, -26, -30, -32, -33, -34, -35, //2688
-35, -35, -35, -33, -33, -33, -37, -41, -44, -45, -42, -40, -39, -38, -37, -36, //2704
-34, -32, -31, -30, -27, -24, -21, -19, -18, -17, -12, -9, -7, -6, -3, -1, //2720
1, 1, 0, 1, 4, 7, 10, 12, 15, 18, 20, 24, 28, 34, 39, 39, //2736
36, 36, 39, 41, 41, 39, 38, 40, 42, 42, 43, 43, 47, 48, 48, 46, //2752
44, 43, 42, 42, 41, 37, 32, 29, 27, 25, 22, 18, 14, 9, 3, -3, //2768
-8, -12, -15, -19, -24, -34, -42, -49, -54, -64, -71, -77, -81, -84, -88, -91, //2784
-94, -97, -99, -99, -101, -104, -108, -111, -111, -110, -108, -106, -105, -105, -105, -102, //2800
-100, -100, -102, -102, -102, -97, -93, -88, -83, -78, -70, -63, -55, -46, -36, -27, //2816
-16, -9, -1, 8, 17, 24, 35, 42, 49, 57, 65, 80, 89, 97, 103, 110, //2832
118, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, //2848
126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, 126, //2864
126, 126, 126, 126, 126, 126, 126, 126, 126, 123, 115, 108, 102, 96, 86, 79, //2880
73, 69, 66, 65, 61, 55, 48, 40, 34, 28, 19, 11, 4, -2, -8, -16, //2896
-22, -28, -32, -36, -41, -51, -58, -62, -66, -68, -71, -75, -77, -79, -81, -82, //2912
-81, -81, -82, -83, -83, -82, -80, -80, -80, -80, -81, -81, -79, -79, -79, -78, //2928
-76, -75, -75, -75, -75, -73, -71, -68, -64, -60, -56, -52, -48, -46, -46, -44, //2944
-42, -39, -35, -32, -29, -27, -26, -23, -20, -18, -16, -15, -14, -12, -11, -9, //2960
-8, -8, -7, -6, -5, -4, -3, -3, -2, -0, 0, };
