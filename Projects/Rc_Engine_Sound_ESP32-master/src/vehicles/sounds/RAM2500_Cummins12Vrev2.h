const unsigned int revSampleRate = 22050;
const unsigned int revSampleCount = 3439;
const signed char revSamples[] = {//0
0, -1, -1, 0, 0, 0, 0, 1, 1, 2, 3, 4, 8, 11, 14, 17, //16
21, 27, 30, 34, 37, 40, 42, 45, 47, 48, 49, 50, 50, 51, 52, 53, //32
54, 54, 55, 56, 57, 58, 59, 60, 62, 64, 67, 69, 71, 73, 76, 77, //48
78, 79, 79, 79, 79, 79, 78, 78, 78, 78, 80, 81, 82, 84, 85, 87, //64
89, 90, 91, 92, 93, 94, 96, 97, 98, 101, 103, 105, 106, 108, 109, 110, //80
112, 113, 114, 116, 117, 120, 122, 123, 124, 126, 127, 127, 127, 127, 126, 125, //96
123, 121, 119, 118, 116, 115, 113, 112, 111, 110, 109, 108, 107, 106, 106, 105, //112
105, 104, 102, 102, 102, 102, 103, 104, 106, 107, 109, 111, 112, 114, 115, 116, //128
116, 116, 115, 114, 113, 112, 111, 110, 109, 108, 107, 106, 105, 105, 103, 102, //144
102, 100, 99, 96, 94, 93, 90, 89, 88, 85, 84, 83, 82, 81, 79, 75, //160
72, 69, 66, 64, 59, 57, 54, 51, 49, 47, 44, 43, 42, 41, 40, 39, //176
38, 37, 35, 34, 33, 32, 31, 29, 28, 27, 26, 23, 22, 20, 19, 19, //192
18, 19, 19, 20, 21, 23, 25, 25, 27, 28, 29, 30, 30, 29, 28, 27, //208
26, 25, 23, 22, 22, 22, 23, 23, 25, 25, 24, 25, 26, 25, 23, 21, //224
19, 17, 15, 12, 11, 8, 6, 4, 1, -2, -5, -7, -9, -10, -11, -12, //240
-13, -14, -14, -14, -14, -14, -15, -16, -15, -14, -15, -15, -16, -17, -17, -17, //256
-18, -19, -20, -19, -20, -19, -18, -19, -20, -21, -22, -23, -25, -26, -27, -28, //272
-30, -30, -30, -31, -31, -32, -32, -33, -34, -34, -36, -36, -37, -38, -38, -38, //288
-37, -36, -36, -35, -34, -34, -33, -32, -32, -32, -33, -35, -35, -36, -36, -36, //304
-37, -36, -36, -35, -35, -34, -33, -32, -31, -30, -30, -29, -29, -28, -27, -27, //320
-26, -25, -26, -25, -24, -23, -24, -24, -23, -22, -22, -22, -23, -23, -25, -24, //336
-25, -27, -28, -30, -32, -33, -34, -35, -35, -38, -39, -40, -41, -41, -43, -45, //352
-46, -47, -48, -49, -51, -52, -52, -53, -54, -54, -55, -55, -54, -54, -54, -55, //368
-55, -55, -55, -53, -53, -53, -50, -48, -46, -44, -42, -39, -37, -36, -34, -34, //384
-34, -34, -35, -35, -35, -37, -37, -40, -41, -42, -42, -42, -42, -41, -40, -39, //400
-38, -36, -35, -35, -34, -34, -34, -35, -38, -40, -43, -46, -49, -55, -59, -62, //416
-65, -68, -70, -73, -75, -75, -75, -76, -76, -75, -75, -74, -73, -73, -73, -74, //432
-74, -74, -74, -74, -75, -75, -75, -74, -73, -73, -72, -72, -71, -70, -68, -67, //448
-65, -63, -61, -58, -56, -53, -52, -51, -49, -49, -47, -46, -46, -46, -47, -47, //464
-48, -49, -50, -50, -50, -50, -50, -50, -51, -52, -53, -55, -57, -59, -62, -64, //480
-65, -68, -70, -72, -75, -77, -79, -85, -88, -91, -95, -99, -103, -106, -108, -109, //496
-109, -107, -105, -102, -98, -94, -90, -85, -79, -76, -73, -71, -69, -67, -66, -64, //512
-63, -61, -59, -55, -52, -49, -46, -43, -41, -39, -39, -40, -42, -44, -48, -51, //528
-53, -55, -57, -58, -59, -59, -61, -62, -64, -66, -67, -69, -71, -71, -72, -73, //544
-73, -73, -73, -73, -73, -74, -74, -74, -74, -74, -74, -73, -71, -69, -67, -65, //560
-60, -56, -51, -46, -42, -37, -31, -26, -23, -20, -18, -17, -15, -14, -14, -14, //576
-14, -14, -13, -13, -13, -11, -10, -7, -4, -2, 0, 2, 5, 7, 9, 10, //592
12, 13, 14, 14, 15, 16, 17, 18, 19, 21, 24, 27, 29, 32, 34, 35, //608
36, 37, 37, 38, 38, 38, 38, 38, 37, 37, 36, 36, 36, 36, 36, 36, //624
36, 36, 36, 38, 39, 40, 41, 42, 44, 46, 48, 49, 50, 51, 52, 52, //640
53, 54, 56, 58, 60, 64, 68, 72, 76, 79, 83, 88, 90, 92, 93, 93, //656
92, 91, 90, 90, 90, 91, 92, 94, 95, 97, 99, 100, 101, 101, 101, 101, //672
100, 97, 95, 93, 90, 89, 87, 85, 85, 85, 86, 87, 88, 91, 93, 95, //688
96, 98, 98, 99, 99, 99, 99, 98, 96, 95, 95, 95, 94, 94, 94, 94, //704
94, 94, 94, 93, 92, 90, 89, 88, 86, 83, 80, 78, 76, 73, 71, 68, //720
66, 63, 61, 59, 56, 55, 53, 53, 52, 51, 50, 50, 51, 51, 52, 52, //736
53, 53, 53, 54, 54, 54, 54, 54, 54, 54, 55, 55, 56, 57, 59, 61, //752
63, 64, 65, 67, 68, 69, 71, 71, 71, 71, 71, 71, 70, 69, 68, 67, //768
65, 63, 63, 62, 61, 60, 58, 56, 55, 53, 51, 49, 48, 45, 43, 41, //784
39, 38, 37, 36, 34, 33, 33, 32, 32, 32, 31, 31, 30, 30, 29, 29, //800
28, 27, 26, 28, 28, 28, 28, 30, 30, 31, 30, 29, 30, 29, 29, 28, //816
26, 25, 23, 22, 20, 19, 18, 17, 16, 16, 16, 16, 16, 16, 16, 16, //832
16, 16, 16, 15, 13, 11, 10, 7, 6, 3, 1, -2, -4, -5, -6, -7, //848
-7, -6, -5, -4, -4, -4, -3, -3, -3, -4, -5, -5, -4, -3, -3, -3, //864
-1, 1, 5, 7, 9, 13, 14, 18, 20, 22, 23, 24, 25, 25, 25, 24, //880
23, 21, 18, 17, 16, 15, 13, 11, 11, 11, 11, 11, 11, 11, 11, 11, //896
11, 9, 7, 4, 2, 1, 0, -2, -3, -4, -4, -5, -5, -5, -6, -6, //912
-6, -7, -8, -9, -10, -11, -12, -12, -13, -14, -14, -14, -14, -13, -13, -12, //928
-10, -9, -8, -7, -7, -7, -7, -6, -5, -5, -5, -5, -6, -7, -8, -10, //944
-13, -18, -21, -25, -29, -32, -37, -40, -42, -43, -43, -43, -43, -41, -39, -38, //960
-35, -34, -33, -33, -34, -34, -36, -38, -40, -40, -40, -39, -38, -36, -34, -31, //976
-28, -26, -24, -24, -26, -28, -31, -36, -46, -53, -60, -67, -74, -79, -86, -89, //992
-91, -92, -93, -93, -94, -95, -95, -95, -95, -94, -92, -91, -88, -84, -81, -74, //1008
-70, -66, -63, -59, -57, -55, -55, -55, -56, -59, -63, -67, -71, -74, -76, -78, //1024
-81, -82, -83, -83, -83, -82, -82, -81, -81, -80, -78, -77, -77, -76, -76, -76, //1040
-76, -78, -79, -80, -82, -84, -88, -91, -94, -97, -100, -101, -104, -105, -106, -107, //1056
-106, -105, -104, -104, -105, -107, -109, -111, -113, -114, -116, -116, -117, -117, -115, -113, //1072
-111, -108, -104, -99, -97, -95, -93, -93, -94, -95, -97, -100, -103, -104, -105, -105, //1088
-104, -101, -98, -95, -89, -86, -81, -77, -74, -70, -67, -65, -64, -64, -63, -61, //1104
-61, -59, -57, -54, -51, -47, -44, -42, -40, -39, -37, -36, -36, -35, -35, -34, //1120
-33, -31, -29, -27, -25, -22, -18, -15, -12, -9, -8, -5, -4, -4, -3, -2, //1136
-1, 0, 2, 4, 5, 8, 10, 13, 15, 16, 17, 18, 19, 19, 19, 18, //1152
19, 18, 18, 19, 21, 23, 25, 28, 31, 35, 38, 42, 46, 51, 55, 59, //1168
62, 66, 68, 73, 75, 78, 80, 82, 85, 86, 87, 87, 87, 87, 84, 83, //1184
82, 80, 79, 78, 76, 75, 74, 74, 74, 74, 75, 75, 75, 76, 76, 77, //1200
77, 78, 78, 78, 78, 79, 79, 79, 81, 83, 85, 88, 90, 92, 95, 97, //1216
101, 103, 106, 108, 110, 111, 112, 112, 112, 111, 111, 109, 109, 108, 107, 106, //1232
105, 103, 102, 100, 100, 98, 97, 95, 94, 94, 93, 93, 92, 91, 91, 90, //1248
90, 90, 90, 90, 90, 91, 91, 91, 91, 90, 90, 90, 90, 89, 89, 89, //1264
90, 90, 90, 90, 90, 90, 90, 90, 90, 88, 86, 85, 84, 81, 80, 78, //1280
77, 76, 75, 75, 75, 75, 75, 75, 75, 75, 74, 73, 72, 72, 71, 70, //1296
69, 68, 68, 67, 67, 66, 65, 65, 64, 64, 62, 60, 59, 57, 55, 53, //1312
50, 48, 46, 45, 44, 42, 41, 39, 38, 37, 36, 35, 34, 32, 31, 29, //1328
28, 27, 26, 25, 24, 23, 24, 26, 26, 27, 28, 30, 32, 33, 34, 34, //1344
34, 34, 33, 32, 30, 28, 26, 24, 20, 17, 14, 10, 7, 2, -1, -4, //1360
-7, -9, -11, -11, -12, -12, -12, -12, -12, -10, -9, -9, -9, -9, -7, -6, //1376
-6, -5, -5, -5, -2, -1, 0, 1, 2, 4, 6, 8, 10, 11, 11, 12, //1392
12, 12, 12, 10, 10, 8, 7, 6, 5, 3, 2, 0, -2, -4, -7, -10, //1408
-14, -16, -18, -21, -22, -24, -25, -25, -26, -25, -26, -27, -28, -28, -30, -30, //1424
-32, -34, -35, -36, -37, -38, -38, -38, -37, -36, -36, -35, -34, -33, -31, -30, //1440
-29, -28, -27, -26, -26, -25, -25, -26, -28, -29, -29, -31, -33, -36, -38, -39, //1456
-41, -41, -42, -42, -41, -40, -39, -38, -37, -37, -35, -34, -33, -33, -33, -32, //1472
-32, -31, -31, -31, -31, -31, -30, -30, -30, -30, -31, -32, -33, -33, -35, -38, //1488
-40, -43, -45, -46, -49, -52, -54, -55, -55, -56, -56, -56, -56, -55, -55, -55, //1504
-53, -52, -51, -50, -48, -46, -44, -43, -42, -41, -40, -39, -39, -38, -38, -37, //1520
-36, -35, -35, -35, -34, -34, -33, -33, -33, -33, -32, -32, -32, -32, -32, -32, //1536
-34, -34, -36, -38, -40, -42, -43, -44, -46, -48, -49, -49, -49, -49, -49, -49, //1552
-49, -49, -47, -46, -45, -44, -43, -42, -40, -39, -38, -38, -38, -38, -40, -41, //1568
-43, -45, -46, -48, -48, -49, -49, -48, -47, -47, -45, -45, -45, -46, -46, -47, //1584
-50, -53, -56, -58, -61, -66, -69, -72, -75, -78, -80, -83, -85, -87, -90, -91, //1600
-92, -93, -94, -95, -95, -95, -94, -93, -93, -92, -91, -90, -87, -85, -83, -82, //1616
-80, -77, -76, -75, -75, -76, -78, -81, -83, -86, -90, -93, -95, -97, -98, -98, //1632
-98, -97, -95, -93, -91, -90, -89, -89, -88, -88, -87, -87, -87, -87, -84, -82, //1648
-80, -78, -76, -71, -68, -64, -60, -57, -54, -51, -49, -46, -45, -43, -41, -37, //1664
-35, -34, -34, -34, -35, -36, -37, -39, -40, -42, -43, -43, -43, -43, -43, -43, //1680
-41, -40, -39, -39, -41, -42, -44, -46, -48, -50, -51, -54, -55, -55, -55, -55, //1696
-53, -49, -46, -44, -43, -41, -39, -38, -36, -35, -34, -32, -31, -28, -26, -24, //1712
-22, -21, -19, -17, -15, -14, -13, -11, -11, -10, -10, -11, -12, -13, -14, -16, //1728
-18, -20, -21, -23, -25, -25, -25, -25, -24, -23, -22, -21, -20, -19, -17, -17, //1744
-15, -13, -13, -12, -10, -9, -8, -6, -5, -2, 1, 3, 6, 9, 11, 15, //1760
19, 22, 25, 28, 32, 35, 37, 40, 42, 44, 47, 49, 51, 53, 54, 55, //1776
57, 59, 61, 62, 64, 66, 66, 67, 68, 69, 68, 67, 65, 64, 62, 61, //1792
60, 58, 58, 59, 60, 61, 61, 62, 63, 63, 64, 63, 61, 60, 58, 58, //1808
57, 56, 56, 56, 58, 59, 61, 64, 65, 67, 68, 69, 70, 71, 71, 72, //1824
74, 76, 78, 81, 83, 85, 88, 91, 95, 96, 97, 98, 98, 98, 97, 97, //1840
97, 98, 99, 100, 102, 104, 106, 109, 111, 114, 115, 115, 116, 117, 118, 120, //1856
120, 120, 119, 119, 119, 118, 117, 116, 115, 114, 113, 111, 109, 106, 104, 102, //1872
99, 98, 96, 96, 95, 96, 96, 96, 96, 96, 96, 96, 95, 94, 92, 90, //1888
89, 87, 85, 83, 81, 80, 80, 80, 80, 80, 80, 80, 81, 80, 79, 77, //1904
75, 74, 71, 69, 67, 66, 65, 63, 64, 64, 63, 62, 62, 60, 59, 57, //1920
55, 53, 51, 48, 46, 45, 44, 43, 43, 43, 43, 42, 41, 41, 40, 39, //1936
38, 37, 37, 37, 38, 39, 40, 42, 43, 46, 47, 48, 49, 49, 49, 49, //1952
49, 48, 47, 46, 44, 43, 42, 41, 40, 39, 37, 36, 34, 32, 30, 28, //1968
24, 21, 18, 15, 12, 9, 4, 2, -1, -4, -6, -9, -11, -12, -13, -14, //1984
-15, -16, -16, -16, -16, -17, -17, -17, -17, -16, -16, -15, -15, -13, -12, -10, //2000
-10, -9, -6, -4, -2, 1, 2, 4, 5, 7, 8, 8, 9, 8, 8, 8, //2016
8, 8, 7, 5, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 4, 3, //2032
1, -1, -2, -4, -7, -9, -11, -12, -13, -16, -17, -18, -19, -20, -20, -22, //2048
-24, -23, -24, -25, -26, -28, -28, -28, -27, -26, -25, -24, -23, -22, -21, -20, //2064
-21, -20, -21, -20, -19, -18, -17, -17, -16, -14, -13, -10, -10, -10, -8, -8, //2080
-7, -8, -9, -10, -11, -12, -13, -14, -16, -17, -18, -19, -21, -22, -23, -24, //2096
-25, -25, -27, -28, -29, -29, -29, -28, -28, -28, -28, -27, -26, -28, -29, -29, //2112
-29, -29, -28, -29, -29, -30, -30, -30, -30, -31, -32, -32, -34, -34, -33, -33, //2128
-32, -30, -28, -26, -23, -22, -21, -22, -21, -22, -24, -26, -28, -31, -33, -36, //2144
-38, -39, -42, -43, -43, -44, -45, -47, -50, -54, -57, -62, -66, -70, -73, -74, //2160
-76, -77, -77, -77, -77, -78, -78, -78, -79, -81, -81, -82, -84, -85, -86, -86, //2176
-85, -84, -82, -81, -79, -78, -77, -73, -72, -71, -70, -70, -70, -71, -72, -72, //2192
-73, -74, -76, -77, -78, -80, -80, -81, -83, -84, -85, -88, -89, -93, -95, -97, //2208
-99, -100, -100, -100, -99, -98, -98, -98, -96, -94, -93, -90, -89, -89, -86, -85, //2224
-84, -84, -84, -84, -83, -83, -83, -83, -83, -83, -83, -83, -83, -84, -84, -85, //2240
-85, -86, -86, -87, -88, -89, -89, -89, -90, -90, -90, -91, -91, -91, -91, -91, //2256
-91, -91, -90, -89, -88, -87, -84, -81, -78, -74, -70, -66, -62, -58, -56, -53, //2272
-51, -48, -46, -45, -44, -42, -42, -39, -37, -35, -33, -32, -31, -30, -29, -28, //2288
-27, -27, -27, -26, -25, -24, -23, -21, -19, -18, -16, -15, -14, -13, -12, -12, //2304
-12, -11, -10, -8, -6, -4, 0, 4, 8, 13, 18, 22, 26, 30, 34, 40, //2320
42, 46, 49, 51, 54, 56, 58, 61, 63, 64, 66, 68, 68, 69, 69, 70, //2336
70, 71, 71, 72, 74, 76, 77, 80, 81, 83, 85, 87, 89, 91, 92, 93, //2352
95, 96, 96, 97, 98, 98, 99, 99, 100, 101, 102, 103, 106, 107, 109, 110, //2368
111, 112, 112, 111, 110, 109, 107, 104, 102, 100, 97, 95, 93, 91, 89, 89, //2384
88, 88, 88, 88, 88, 89, 89, 90, 91, 92, 93, 94, 95, 96, 98, 99, //2400
101, 102, 104, 106, 108, 110, 112, 114, 115, 118, 119, 120, 121, 121, 121, 121, //2416
120, 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 108, 106, 103, 101, 99, //2432
94, 92, 89, 85, 83, 79, 77, 75, 74, 73, 72, 72, 71, 71, 70, 70, //2448
69, 69, 68, 67, 66, 65, 64, 64, 63, 62, 61, 61, 60, 60, 59, 60, //2464
59, 58, 56, 55, 54, 52, 50, 49, 47, 46, 45, 43, 40, 37, 34, 31, //2480
29, 27, 24, 22, 20, 18, 16, 15, 14, 13, 12, 12, 12, 11, 10, 9, //2496
9, 9, 8, 8, 9, 10, 10, 11, 13, 14, 15, 16, 17, 18, 17, 17, //2512
17, 15, 13, 11, 8, 5, 3, 1, -2, -3, -6, -7, -8, -8, -9, -9, //2528
-9, -9, -9, -9, -9, -9, -9, -9, -8, -8, -9, -9, -9, -10, -11, -12, //2544
-13, -13, -14, -14, -15, -15, -16, -16, -17, -18, -19, -21, -22, -23, -25, -26, //2560
-28, -30, -33, -35, -36, -37, -39, -42, -43, -44, -46, -48, -49, -50, -51, -52, //2576
-52, -53, -53, -54, -54, -53, -53, -53, -52, -51, -50, -49, -48, -48, -46, -44, //2592
-42, -41, -40, -39, -38, -36, -35, -34, -33, -33, -32, -31, -30, -29, -29, -28, //2608
-27, -26, -25, -25, -24, -25, -26, -26, -27, -28, -30, -31, -32, -32, -31, -31, //2624
-30, -28, -26, -24, -22, -21, -19, -17, -17, -16, -16, -17, -19, -20, -22, -23, //2640
-24, -27, -28, -28, -29, -29, -31, -31, -32, -33, -33, -34, -36, -37, -37, -37, //2656
-36, -36, -36, -36, -36, -35, -35, -35, -36, -37, -37, -37, -37, -37, -36, -35, //2672
-34, -33, -31, -31, -30, -30, -29, -28, -30, -31, -32, -33, -35, -36, -39, -41, //2688
-43, -44, -46, -48, -50, -53, -55, -57, -60, -64, -68, -72, -75, -78, -82, -86, //2704
-88, -89, -89, -89, -89, -86, -84, -82, -80, -77, -73, -70, -66, -62, -59, -55, //2720
-48, -44, -41, -37, -34, -31, -28, -27, -27, -26, -25, -27, -28, -29, -31, -34, //2736
-36, -40, -42, -45, -49, -53, -57, -62, -66, -70, -75, -80, -86, -89, -92, -93, //2752
-94, -94, -93, -93, -92, -92, -92, -90, -87, -84, -82, -79, -75, -71, -68, -65, //2768
-63, -62, -62, -61, -62, -61, -60, -60, -58, -56, -55, -53, -53, -53, -52, -53, //2784
-53, -54, -57, -60, -65, -69, -73, -77, -80, -86, -88, -91, -93, -95, -98, -101, //2800
-103, -104, -106, -108, -109, -110, -110, -110, -109, -109, -107, -106, -104, -101, -99, -97, //2816
-92, -89, -87, -84, -82, -80, -77, -75, -73, -72, -70, -69, -69, -68, -69, -69, //2832
-69, -70, -71, -71, -71, -70, -69, -68, -67, -65, -62, -60, -57, -55, -52, -49, //2848
-46, -43, -40, -37, -34, -32, -31, -28, -25, -23, -21, -19, -17, -15, -14, -12, //2864
-10, -8, -8, -6, -6, -6, -7, -7, -7, -10, -11, -12, -13, -14, -15, -15, //2880
-15, -15, -15, -15, -13, -12, -10, -7, -4, -2, 2, 4, 5, 8, 11, 13, //2896
16, 18, 21, 24, 26, 31, 34, 37, 41, 44, 47, 51, 54, 57, 59, 62, //2912
64, 66, 69, 70, 72, 74, 74, 75, 76, 76, 76, 77, 77, 78, 78, 78, //2928
79, 79, 80, 80, 81, 81, 81, 81, 80, 80, 80, 80, 80, 80, 80, 81, //2944
81, 81, 82, 82, 83, 83, 83, 83, 83, 83, 84, 85, 87, 89, 91, 92, //2960
94, 95, 96, 97, 98, 98, 99, 100, 101, 102, 103, 103, 104, 105, 104, 104, //2976
103, 104, 103, 102, 101, 100, 100, 99, 100, 101, 101, 102, 104, 105, 106, 107, //2992
108, 107, 108, 107, 107, 107, 107, 106, 107, 106, 105, 105, 105, 104, 104, 104, //3008
104, 104, 103, 102, 101, 100, 98, 97, 96, 95, 95, 95, 95, 94, 94, 94, //3024
94, 93, 92, 91, 90, 88, 87, 87, 86, 85, 84, 84, 84, 83, 82, 81, //3040
80, 79, 78, 77, 75, 74, 72, 71, 70, 69, 68, 67, 68, 68, 68, 67, //3056
66, 65, 64, 63, 62, 60, 58, 56, 54, 51, 49, 48, 46, 44, 42, 40, //3072
39, 38, 35, 34, 31, 29, 27, 24, 22, 20, 18, 18, 17, 16, 15, 13, //3088
13, 12, 12, 12, 12, 13, 14, 15, 15, 16, 17, 18, 19, 20, 21, 22, //3104
22, 22, 23, 22, 23, 22, 21, 22, 21, 22, 22, 21, 20, 20, 19, 19, //3120
18, 16, 15, 15, 14, 13, 12, 10, 9, 9, 9, 8, 8, 8, 9, 10, //3136
10, 10, 9, 8, 7, 6, 3, 0, -3, -5, -7, -8, -9, -11, -11, -11, //3152
-10, -10, -10, -9, -9, -9, -9, -9, -10, -11, -11, -11, -12, -12, -12, -13, //3168
-13, -12, -12, -12, -10, -9, -8, -7, -5, -3, -2, -1, 0, 1, 1, 1, //3184
1, 1, 1, 0, -1, -3, -4, -6, -7, -8, -10, -11, -12, -13, -14, -15, //3200
-16, -19, -21, -24, -27, -29, -35, -38, -40, -43, -46, -48, -51, -52, -52, -51, //3216
-50, -48, -44, -41, -37, -34, -30, -25, -22, -19, -15, -13, -11, -7, -5, -4, //3232
-2, 0, 1, 2, 2, 3, 2, 2, 0, -3, -6, -8, -11, -15, -20, -24, //3248
-27, -30, -34, -39, -43, -46, -48, -50, -51, -53, -54, -55, -55, -55, -55, -54, //3264
-53, -50, -49, -46, -42, -39, -36, -34, -30, -26, -21, -18, -16, -14, -13, -12, //3280
-11, -10, -10, -10, -11, -12, -15, -18, -21, -24, -26, -31, -33, -37, -40, -42, //3296
-44, -46, -48, -50, -52, -53, -56, -58, -60, -61, -62, -63, -63, -63, -64, -65, //3312
-65, -66, -65, -66, -65, -66, -66, -66, -66, -67, -69, -70, -71, -73, -74, -75, //3328
-75, -75, -76, -76, -77, -78, -78, -79, -81, -82, -84, -86, -87, -90, -94, -97, //3344
-100, -102, -104, -105, -105, -106, -105, -104, -105, -103, -102, -102, -101, -99, -97, -92, //3360
-89, -87, -84, -81, -78, -74, -72, -71, -70, -69, -69, -68, -67, -68, -69, -69, //3376
-71, -71, -72, -74, -74, -76, -76, -76, -76, -76, -76, -76, -76, -76, -77, -77, //3392
-77, -78, -78, -78, -79, -79, -79, -78, -77, -77, -76, -76, -75, -73, -72, -72, //3408
-72, -71, -71, -70, -69, -67, -66, -64, -62, -60, -58, -57, -55, -53, -52, -49, //3424
-48, -46, -46, -44, -43, -42, -41, -39, -36, -32, -28, -24, -19, -9, 0, };
