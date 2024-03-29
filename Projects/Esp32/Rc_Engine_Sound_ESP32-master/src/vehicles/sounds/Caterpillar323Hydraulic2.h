const unsigned int hydraulicPumpSampleRate = 22050;
const unsigned int hydraulicPumpSampleCount = 1932;
const signed char hydraulicPumpSamples[] = {//0
0, 1, 3, 7, 11, 16, 25, 31, 38, 42, 44, 46, 46, 46, 46, 44, //16
41, 36, 31, 26, 20, 15, 9, 0, -5, -11, -15, -19, -22, -25, -27, -27, //32
-28, -28, -28, -28, -28, -28, -28, -30, -31, -32, -33, -34, -36, -38, -38, -39, //48
-39, -39, -37, -36, -34, -32, -30, -27, -26, -22, -19, -16, -13, -11, -8, -5, //64
-3, -3, -1, -1, -2, -2, -4, -6, -7, -9, -13, -14, -16, -19, -21, -23, //80
-25, -26, -27, -25, -23, -19, -14, -9, -5, 0, 6, 16, 22, 29, 36, 43, //96
51, 62, 68, 74, 78, 82, 84, 84, 84, 82, 79, 74, 66, 60, 53, 46, //112
39, 33, 25, 20, 17, 15, 15, 17, 20, 22, 26, 30, 35, 41, 45, 48, //128
50, 52, 53, 53, 52, 50, 47, 42, 35, 28, 22, 16, 9, 4, -4, -9, //144
-13, -17, -22, -27, -31, -34, -36, -39, -41, -43, -42, -41, -39, -37, -34, -30, //160
-27, -24, -22, -19, -17, -17, -17, -19, -20, -23, -28, -30, -32, -33, -34, -34, //176
-31, -28, -24, -19, -13, 0, 9, 19, 29, 38, 48, 61, 69, 77, 84, 91, //192
97, 104, 107, 109, 110, 109, 105, 101, 96, 90, 83, 74, 62, 53, 45, 36, //208
28, 21, 11, 5, 1, -3, -5, -6, -5, -3, -1, 3, 7, 15, 21, 27, //224
34, 43, 51, 61, 67, 71, 73, 74, 72, 68, 61, 51, 40, 28, 8, -6, //240
-20, -34, -46, -57, -71, -79, -84, -88, -91, -92, -93, -92, -90, -87, -83, -75, //256
-70, -64, -57, -49, -42, -33, -27, -22, -18, -13, -9, -8, -6, -5, -5, -5, //272
-5, -5, -4, -3, -4, -5, -6, -7, -8, -10, -12, -16, -18, -20, -23, -23, //288
-23, -22, -19, -16, -12, -8, -4, -2, -2, -2, -3, -5, -9, -11, -13, -13, //304
-12, -11, -5, -1, 4, 10, 16, 24, 30, 34, 38, 42, 44, 44, 43, 40, //320
35, 29, 23, 12, 5, -4, -12, -21, -32, -39, -45, -51, -56, -60, -64, -64, //336
-62, -60, -56, -52, -45, -40, -35, -30, -26, -21, -19, -18, -16, -16, -17, -21, //352
-25, -29, -36, -43, -51, -65, -76, -86, -97, -106, -118, -123, -126, -127, -127, -124, //368
-116, -109, -100, -90, -79, -66, -46, -31, -16, -2, 11, 31, 43, 54, 63, 70, //384
75, 79, 79, 77, 74, 70, 64, 53, 44, 36, 26, 17, 6, -1, -7, -12, //400
-15, -17, -17, -17, -17, -17, -17, -17, -16, -15, -15, -14, -11, -6, -2, 3, //416
10, 16, 22, 32, 38, 43, 47, 51, 53, 55, 56, 54, 51, 47, 38, 30, //432
21, 10, -2, -15, -35, -48, -60, -71, -80, -90, -94, -96, -96, -93, -88, -78, //448
-68, -58, -46, -35, -22, -4, 7, 19, 30, 40, 53, 61, 67, 73, 77, 79, //464
81, 80, 80, 78, 75, 71, 63, 56, 47, 39, 29, 13, 3, -6, -12, -18, //480
-21, -23, -21, -18, -14, -8, -1, 11, 20, 29, 39, 47, 61, 69, 77, 84, //496
89, 95, 101, 103, 103, 103, 101, 97, 90, 83, 75, 66, 57, 43, 33, 25, //512
16, 9, 3, -6, -8, -10, -11, -12, -12, -10, -8, -7, -5, -4, -2, -1, //528
0, 0, -1, -4, -10, -15, -22, -31, -40, -50, -65, -76, -85, -93, -101, -109, //544
-112, -113, -113, -110, -106, -97, -90, -82, -72, -64, -54, -42, -35, -27, -19, -12, //560
-1, 4, 9, 14, 17, 18, 19, 18, 16, 13, 9, 6, 1, -1, -3, -4, //576
-5, -5, -5, -4, -3, -2, 0, 1, 2, 4, 7, 10, 16, 21, 27, 33, //592
39, 45, 52, 56, 60, 62, 63, 62, 61, 58, 54, 49, 43, 32, 25, 17, //608
8, 0, -8, -18, -25, -29, -31, -32, -33, -31, -30, -28, -25, -22, -18, -15, //624
-13, -12, -11, -11, -13, -15, -18, -22, -26, -30, -38, -43, -48, -54, -59, -67, //640
-71, -74, -76, -77, -75, -71, -67, -61, -55, -48, -40, -30, -23, -17, -10, -4, //656
2, 5, 8, 10, 11, 12, 12, 11, 10, 8, 5, 1, -2, -4, -7, -10, //672
-11, -13, -13, -13, -12, -11, -9, -5, -2, 2, 4, 6, 9, 14, 17, 21, //688
26, 31, 38, 43, 49, 53, 57, 61, 62, 63, 61, 57, 52, 46, 32, 21, //704
11, 0, -10, -25, -34, -41, -47, -52, -54, -54, -53, -48, -43, -38, -32, -20, //720
-13, -5, 3, 11, 21, 28, 34, 37, 39, 40, 36, 31, 24, 16, 8, -7, //736
-17, -28, -38, -47, -57, -70, -78, -83, -86, -89, -89, -86, -82, -76, -68, -59, //752
-45, -35, -25, -14, -5, 4, 16, 22, 28, 32, 36, 39, 45, 49, 52, 56, //768
60, 65, 67, 69, 70, 71, 71, 69, 67, 65, 63, 60, 57, 55, 52, 51, //784
52, 53, 56, 59, 63, 66, 70, 75, 80, 83, 84, 86, 87, 86, 83, 80, //800
77, 72, 67, 57, 50, 43, 36, 30, 24, 18, 14, 11, 8, 5, 3, -2, //816
-5, -9, -13, -16, -20, -22, -23, -24, -25, -24, -23, -23, -23, -23, -22, -23, //832
-23, -25, -26, -29, -32, -36, -38, -39, -39, -38, -36, -30, -27, -23, -19, -14, //848
-11, -7, -5, -4, -3, -1, -1, -1, -1, -1, -1, -1, 0, 1, 3, 7, //864
11, 16, 24, 29, 34, 40, 46, 53, 57, 61, 63, 64, 63, 60, 56, 51, //880
45, 39, 28, 21, 15, 10, 6, 3, 2, 3, 5, 8, 12, 17, 23, 27, //896
31, 36, 41, 48, 53, 56, 58, 61, 62, 61, 61, 59, 57, 54, 49, 42, //912
36, 29, 22, 14, 1, -7, -17, -26, -36, -47, -62, -71, -79, -86, -92, -98, //928
-102, -103, -102, -100, -98, -90, -84, -78, -69, -60, -50, -35, -26, -16, -7, 1, //944
6, 10, 11, 10, 6, 1, -10, -20, -29, -39, -48, -56, -66, -70, -73, -71, //960
-68, -64, -54, -44, -35, -24, -12, 7, 19, 31, 43, 55, 65, 78, 86, 92, //976
95, 96, 95, 89, 82, 74, 65, 56, 43, 35, 28, 21, 16, 12, 6, 2, //992
-3, -8, -11, -15, -19, -22, -24, -26, -28, -31, -35, -39, -43, -47, -52, -59, //1008
-62, -64, -66, -67, -66, -65, -63, -60, -56, -52, -48, -44, -41, -38, -35, -31, //1024
-29, -28, -28, -30, -31, -36, -40, -44, -48, -51, -54, -55, -58, -59, -59, -59, //1040
-59, -59, -57, -54, -50, -45, -35, -27, -19, -11, -4, 3, 11, 16, 20, 24, //1056
28, 30, 33, 35, 35, 35, 36, 36, 36, 36, 37, 38, 41, 44, 47, 49, //1072
50, 50, 50, 48, 44, 41, 38, 35, 34, 32, 32, 33, 35, 38, 43, 46, //1088
50, 53, 57, 59, 60, 60, 59, 58, 56, 51, 49, 46, 44, 43, 41, 39, //1104
38, 38, 37, 36, 35, 34, 33, 31, 29, 28, 27, 25, 23, 22, 18, 13, //1120
7, 1, -6, -15, -23, -32, -46, -53, -60, -64, -66, -67, -65, -62, -57, -51, //1136
-44, -36, -30, -24, -18, -12, -5, 3, 8, 13, 17, 21, 24, 24, 24, 24, //1152
21, 18, 13, 10, 6, 4, 2, 0, -1, -1, -1, 0, 1, 3, 5, 6, //1168
6, 6, 8, 10, 12, 14, 17, 19, 22, 23, 23, 23, 23, 22, 22, 22, //1184
22, 23, 24, 24, 24, 24, 24, 22, 18, 11, 5, -1, -8, -16, -24, -38, //1200
-46, -54, -61, -66, -71, -78, -83, -86, -89, -91, -93, -94, -93, -92, -89, -85, //1216
-77, -70, -62, -54, -46, -37, -27, -21, -15, -11, -6, 0, 2, 3, 4, 4, //1232
2, -2, -6, -12, -18, -24, -30, -38, -42, -46, -50, -53, -57, -59, -60, -60, //1248
-59, -58, -52, -47, -41, -33, -23, -14, 2, 13, 25, 37, 47, 61, 69, 74, //1264
78, 79, 79, 77, 73, 69, 64, 59, 53, 46, 39, 33, 27, 20, 11, 4, //1280
-2, -7, -11, -14, -16, -16, -14, -12, -9, -4, 3, 8, 14, 19, 24, 29, //1296
31, 32, 32, 29, 25, 16, 10, 4, -2, -8, -14, -20, -26, -31, -36, -42, //1312
-52, -57, -62, -68, -72, -74, -76, -76, -76, -74, -71, -67, -64, -61, -57, -55, //1328
-52, -49, -47, -44, -42, -41, -40, -39, -40, -41, -44, -47, -52, -55, -58, -60, //1344
-61, -62, -60, -59, -57, -54, -50, -46, -35, -27, -17, -7, 4, 22, 34, 45, //1360
57, 68, 77, 90, 98, 103, 107, 109, 110, 110, 107, 103, 98, 91, 81, 75, //1376
67, 59, 51, 43, 31, 24, 17, 10, 4, -2, -9, -12, -15, -16, -17, -20, //1392
-20, -20, -19, -17, -14, -6, 0, 8, 15, 22, 30, 39, 43, 46, 47, 47, //1408
43, 39, 33, 26, 19, 11, 0, -8, -16, -24, -32, -38, -49, -55, -59, -64, //1424
-66, -66, -64, -60, -54, -47, -39, -26, -16, -8, 1, 9, 16, 24, 29, 34, //1440
37, 41, 46, 49, 52, 54, 56, 58, 58, 58, 56, 55, 54, 53, 50, 48, //1456
46, 43, 42, 39, 38, 37, 37, 38, 38, 39, 40, 41, 42, 44, 44, 43, //1472
43, 42, 40, 39, 37, 37, 37, 38, 39, 39, 40, 41, 43, 44, 44, 43, //1488
42, 40, 37, 33, 27, 15, 8, 0, -9, -18, -27, -40, -46, -51, -55, -60, //1504
-65, -68, -69, -71, -73, -73, -73, -72, -70, -69, -67, -64, -59, -55, -51, -47, //1520
-45, -43, -42, -42, -44, -47, -51, -58, -63, -67, -71, -76, -80, -83, -84, -85, //1536
-84, -82, -77, -73, -68, -61, -54, -45, -30, -19, -7, 5, 18, 29, 47, 56, //1552
65, 73, 79, 84, 86, 86, 85, 82, 78, 71, 65, 57, 50, 42, 33, 21, //1568
15, 9, 4, -1, -5, -8, -9, -11, -13, -15, -18, -20, -21, -21, -21, -20, //1584
-20, -18, -16, -15, -12, -10, -8, -6, -6, -6, -7, -10, -13, -17, -21, -27, //1600
-34, -43, -50, -56, -63, -69, -78, -84, -89, -95, -99, -103, -108, -109, -109, -108, //1616
-105, -97, -90, -80, -71, -60, -50, -33, -21, -10, 0, 10, 20, 32, 39, 45, //1632
49, 54, 58, 60, 61, 61, 60, 57, 55, 50, 45, 40, 34, 28, 20, 16, //1648
11, 8, 5, 3, 4, 6, 7, 11, 16, 25, 32, 39, 47, 56, 63, 76, //1664
82, 88, 93, 97, 100, 102, 103, 102, 100, 97, 93, 88, 82, 75, 68, 60, //1680
48, 39, 30, 21, 12, 1, -6, -13, -19, -24, -27, -31, -32, -32, -33, -31, //1696
-29, -27, -25, -25, -24, -24, -23, -24, -25, -26, -27, -29, -31, -33, -35, -36, //1712
-39, -41, -44, -48, -51, -54, -57, -60, -60, -59, -58, -56, -51, -44, -39, -34, //1728
-28, -23, -18, -10, -5, 0, 6, 11, 21, 26, 32, 39, 44, 50, 59, 64, //1744
69, 73, 76, 79, 83, 84, 85, 84, 82, 78, 73, 69, 65, 61, 58, 53, //1760
51, 49, 48, 47, 46, 45, 45, 44, 42, 40, 37, 34, 31, 28, 23, 21, //1776
17, 14, 13, 12, 11, 13, 13, 14, 14, 14, 14, 13, 12, 10, 7, 4, //1792
-1, -10, -17, -26, -33, -41, -51, -57, -62, -65, -68, -69, -68, -65, -62, -57, //1808
-51, -44, -32, -24, -16, -9, -3, 7, 11, 15, 19, 21, 23, 23, 22, 20, //1824
17, 14, 11, 5, 2, 1, -2, -3, -2, -1, 1, 2, 3, 4, 6, 7, //1840
9, 12, 16, 20, 30, 36, 42, 49, 56, 65, 70, 74, 77, 78, 77, 74, //1856
70, 65, 59, 52, 46, 35, 28, 20, 13, 6, -7, -14, -21, -27, -32, -36, //1872
-40, -42, -44, -44, -44, -44, -43, -41, -39, -36, -33, -28, -25, -22, -20, -19, //1888
-18, -17, -17, -18, -21, -24, -28, -37, -43, -50, -58, -65, -76, -84, -91, -98, //1904
-103, -108, -113, -116, -119, -120, -120, -118, -115, -112, -106, -100, -94, -81, -73, -64, //1920
-56, -47, -37, -26, -19, -14, -10, -7, -3, -2, -1, 0, };
