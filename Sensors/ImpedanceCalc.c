/*
 * Created by Jared Brinkman
 * Date: 7/22/2022
 *
 * This file will change for every board calibrated.
 * It will hold 255 Impedance equations.
 */

#include "ImpedanceCalc.h"

float impedanceCalc(uint8_t tapNumber, uint16_t adc) {
    float imp = 0;
    switch(tapNumber) {
        default:
              imp = 49999;
                  break;
                          case 2:
                              imp = fabs((-187.0 * adc + 376711)/(adc + -955.5));
                              break;
                          case 3:
                              imp = fabs((-181.6 * adc + 402488)/(adc + -959.0));
                              break;
                          case 4:
                              imp = fabs((-182.5 * adc + 439050)/(adc + -953.4));
                              break;
                          case 5:
                              imp = fabs((-203.6 * adc + 522343)/(adc + -911.6));
                              break;
                          case 6:
                              imp = fabs((-227.3 * adc + 614465)/(adc + -865.5));
                              break;
                          case 7:
                              imp = fabs((-248.5 * adc + 704235)/(adc + -828.1));
                              break;
                          case 8:
                              imp = fabs((-210.4 * adc + 643596)/(adc + -920.4));
                              break;
                          case 9:
                              imp = fabs((-229.2 * adc + 726242)/(adc + -895.8));
                              break;
                          case 10:
                              imp = fabs((-208.8 * adc + 712537)/(adc + -933.9));
                              break;
                          case 11:
                              imp = fabs((-198.9 * adc + 733120)/(adc + -931.1));
                              break;
                          case 12:
                              imp = fabs((-199.1 * adc + 770069)/(adc + -923.9));
                              break;
                          case 13:
                              imp = fabs((-198.2 * adc + 797912)/(adc + -934.0));
                              break;
                          case 14:
                              imp = fabs((-206.3 * adc + 849149)/(adc + -937.9));
                              break;
                          case 15:
                              imp = fabs((-210.0 * adc + 884607)/(adc + -928.1));
                              break;
                          case 16:
                              imp = fabs((-232.2 * adc + 968851)/(adc + -919.2));
                              break;
                          case 17:
                              imp = fabs((-127.4 * adc + 787167)/(adc + -949.0));
                              break;
                          case 18:
                              imp = fabs((-203.7 * adc + 983175)/(adc + -925.9));
                              break;
                          case 19:
                              imp = fabs((-283.7 * adc + 1178979)/(adc + -912.7));
                              break;
                          case 20:
                              imp = fabs((-229.9 * adc + 1097013)/(adc + -930.8));
                              break;
                          case 21:
                              imp = fabs((-164.1 * adc + 992042)/(adc + -946.4));
                              break;
                          case 22:
                              imp = fabs((-165.0 * adc + 1030485)/(adc + -944.4));
                              break;
                          case 23:
                              imp = fabs((-154.4 * adc + 1063591)/(adc + -942.0));
                              break;
                          case 24:
                              imp = fabs((-291.9 * adc + 1384783)/(adc + -912.9));
                              break;
                          case 25:
                              imp = fabs((-231.2 * adc + 1294704)/(adc + -927.7));
                              break;
                          case 26:
                              imp = fabs((-248.0 * adc + 1370020)/(adc + -924.4));
                              break;
                          case 27:
                              imp = fabs((-231.3 * adc + 1364484)/(adc + -929.7));
                              break;
                          case 28:
                              imp = fabs((-193.3 * adc + 1319670)/(adc + -937.2));
                              break;
                          case 29:
                              imp = fabs((-114.8 * adc + 1178390)/(adc + -951.0));
                              break;
                          case 30:
                              imp = fabs((-230.3 * adc + 1478670)/(adc + -929.2));
                              break;
                          case 31:
                              imp = fabs((-212.9 * adc + 1469081)/(adc + -927.4));
                              break;
                          case 32:
                              imp = fabs((-293.1 * adc + 1690706)/(adc + -909.5));
                              break;
                          case 33:
                              imp = fabs((-274.8 * adc + 1647443)/(adc + -923.9));
                              break;
                          case 34:
                              imp = fabs((-92.8 * adc + 1351720)/(adc + -941.2));
                              break;
                          case 35:
                              imp = fabs((-186.7 * adc + 1568662)/(adc + -927.8));
                              break;
                          case 36:
                              imp = fabs((-228.1 * adc + 1681194)/(adc + -926.3));
                              break;
                          case 37:
                              imp = fabs((-248.5 * adc + 1765337)/(adc + -921.0));
                              break;
                          case 38:
                              imp = fabs((-229.4 * adc + 1754038)/(adc + -929.6));
                              break;
                          case 39:
                              imp = fabs((-162.3 * adc + 1656019)/(adc + -932.8));
                              break;
                          case 40:
                              imp = fabs((-287.6 * adc + 1952771)/(adc + -920.2));
                              break;
                          case 41:
                              imp = fabs((-101.5 * adc + 1597969)/(adc + -944.7));
                              break;
                          case 42:
                              imp = fabs((-163.4 * adc + 1764019)/(adc + -939.1));
                              break;
                          case 43:
                              imp = fabs((-200.7 * adc + 1869948)/(adc + -935.8));
                              break;
                          case 44:
                              imp = fabs((-202.8 * adc + 1904577)/(adc + -934.0));
                              break;
                          case 45:
                              imp = fabs((-140.3 * adc + 1821673)/(adc + -938.8));
                              break;
                          case 46:
                              imp = fabs((-231.3 * adc + 2051871)/(adc + -922.3));
                              break;
                          case 47:
                              imp = fabs((-241.8 * adc + 2083754)/(adc + -929.5));
                              break;
                          case 48:
                              imp = fabs((-235.8 * adc + 2125842)/(adc + -925.3));
                              break;
                          case 49:
                              imp = fabs((-282.0 * adc + 2258346)/(adc + -920.0));
                              break;
                          case 50:
                              imp = fabs((-322.0 * adc + 2397792)/(adc + -914.3));
                              break;
                          case 51:
                              imp = fabs((-262.8 * adc + 2233885)/(adc + -933.2));
                              break;
                          case 52:
                              imp = fabs((-401.0 * adc + 2554151)/(adc + -919.6));
                              break;
                          case 53:
                              imp = fabs((-51.9 * adc + 1954627)/(adc + -939.3));
                              break;
                          case 54:
                              imp = fabs((-209.9 * adc + 2260383)/(adc + -935.9));
                              break;
                          case 55:
                              imp = fabs((-169.5 * adc + 2242486)/(adc + -936.2));
                              break;
                          case 56:
                              imp = fabs((-331.6 * adc + 2596879)/(adc + -921.3));
                              break;
                          case 57:
                              imp = fabs((-252.2 * adc + 2490488)/(adc + -923.1));
                              break;
                          case 58:
                              imp = fabs((-238.0 * adc + 2495320)/(adc + -926.6));
                              break;
                          case 59:
                              imp = fabs((-141.7 * adc + 2307351)/(adc + -938.4));
                              break;
                          case 60:
                              imp = fabs((-159.6 * adc + 2425028)/(adc + -930.4));
                              break;
                          case 61:
                              imp = fabs((-248.1 * adc + 2634354)/(adc + -921.7));
                              break;
                          case 62:
                              imp = fabs((-108.0 * adc + 2384831)/(adc + -937.0));
                              break;
                          case 63:
                              imp = fabs((-115.8 * adc + 2425684)/(adc + -938.0));
                              break;
                          case 64:
                              imp = fabs((-254.2 * adc + 2729136)/(adc + -924.0));
                              break;
                          case 65:
                              imp = fabs((-77.2 * adc + 2419840)/(adc + -938.0));
                              break;
                          case 66:
                              imp = fabs((-203.7 * adc + 2709524)/(adc + -930.1));
                              break;
                          case 67:
                              imp = fabs((-316.9 * adc + 2950907)/(adc + -924.2));
                              break;
                          case 68:
                              imp = fabs((-137.2 * adc + 2612770)/(adc + -938.1));
                              break;
                          case 69:
                              imp = fabs((-173.4 * adc + 2766977)/(adc + -929.5));
                              break;
                          case 70:
                              imp = fabs((-308.6 * adc + 3025713)/(adc + -929.8));
                              break;
                          case 71:
                              imp = fabs((-66.9 * adc + 2612998)/(adc + -938.9));
                              break;
                          case 72:
                              imp = fabs((-190.6 * adc + 2883002)/(adc + -931.3));
                              break;
                          case 73:
                              imp = fabs((1493.3 * adc + 462118)/(adc + -949.1));
                              break;
                          case 74:
                              imp = fabs((-3.2 * adc + 2701828)/(adc + -929.3));
                              break;
                          case 75:
                              imp = fabs((1289.7 * adc + 831034)/(adc + -949.9));
                              break;
                          case 76:
                              imp = fabs((1197.3 * adc + 1007740)/(adc + -948.4));
                              break;
                          case 77:
                              imp = fabs((-967.5 * adc + 4259282)/(adc + -922.3));
                              break;
                          case 78:
                              imp = fabs((726.0 * adc + 1731300)/(adc + -943.7));
                              break;
                          case 79:
                              imp = fabs((-1703.2 * adc + 5450495)/(adc + -911.9));
                              break;
                          case 80:
                              imp = fabs((1195.5 * adc + 1084422)/(adc + -949.0));
                              break;
                          case 81:
                              imp = fabs((-545.5 * adc + 3753490)/(adc + -932.0));
                              break;
                          case 82:
                              imp = fabs((826.6 * adc + 1701362)/(adc + -943.5));
                              break;
                          case 83:
                              imp = fabs((100.3 * adc + 2846745)/(adc + -932.8));
                              break;
                          case 84:
                              imp = fabs((-1306.7 * adc + 5095905)/(adc + -914.3));
                              break;
                          case 85:
                              imp = fabs((833.3 * adc + 1781000)/(adc + -944.9));
                              break;
                          case 86:
                              imp = fabs((303.6 * adc + 2657666)/(adc + -936.5));
                              break;
                          case 87:
                              imp = fabs((1581.6 * adc + 673793)/(adc + -956.3));
                              break;
                          case 88:
                              imp = fabs((-334.8 * adc + 3703432)/(adc + -928.1));
                              break;
                          case 89:
                              imp = fabs((-1020.7 * adc + 4819066)/(adc + -920.3));
                              break;
                          case 90:
                              imp = fabs((619.2 * adc + 2232272)/(adc + -942.5));
                              break;
                          case 91:
                              imp = fabs((-1531.8 * adc + 5733961)/(adc + -913.0));
                              break;
                          case 92:
                              imp = fabs((-477.1 * adc + 3994551)/(adc + -933.5));
                              break;
                          case 93:
                              imp = fabs((281.1 * adc + 2917767)/(adc + -933.3));
                              break;
                          case 94:
                              imp = fabs((-1248.2 * adc + 5373563)/(adc + -918.5));
                              break;
                          case 95:
                              imp = fabs((-98.8 * adc + 3550593)/(adc + -937.7));
                              break;
                          case 96:
                              imp = fabs((-548.0 * adc + 4336950)/(adc + -925.6));
                              break;
                          case 97:
                              imp = fabs((-174.5 * adc + 3786245)/(adc + -927.8));
                              break;
                          case 98:
                              imp = fabs((-312.6 * adc + 4017260)/(adc + -935.1));
                              break;
                          case 99:
                              imp = fabs((813.4 * adc + 2193547)/(adc + -947.6));
                              break;
                          case 100:
                              imp = fabs((250.5 * adc + 3186843)/(adc + -937.9));
                              break;
                          case 101:
                              imp = fabs((-421.6 * adc + 4275824)/(adc + -933.5));
                              break;
                          case 102:
                              imp = fabs((952.3 * adc + 2045688)/(adc + -950.7));
                              break;
                          case 103:
                              imp = fabs((248.0 * adc + 3270598)/(adc + -939.4));
                              break;
                          case 104:
                              imp = fabs((-170.9 * adc + 4037441)/(adc + -928.2));
                              break;
                          case 105:
                              imp = fabs((90.3 * adc + 3601416)/(adc + -940.3));
                              break;
                          case 106:
                              imp = fabs((-851.4 * adc + 5297033)/(adc + -916.8));
                              break;
                          case 107:
                              imp = fabs((-225.8 * adc + 4162290)/(adc + -937.0));
                              break;
                          case 108:
                              imp = fabs((-908.7 * adc + 5458737)/(adc + -915.9));
                              break;
                          case 109:
                              imp = fabs((1310.6 * adc + 1671195)/(adc + -953.9));
                              break;
                          case 110:
                              imp = fabs((946.4 * adc + 2292424)/(adc + -951.3));
                              break;
                          case 111:
                              imp = fabs((-46.4 * adc + 4078498)/(adc + -928.2));
                              break;
                          case 112:
                              imp = fabs((-774.1 * adc + 5299561)/(adc + -925.5));
                              break;
                          case 113:
                              imp = fabs((366.0 * adc + 3387008)/(adc + -938.2));
                              break;
                          case 114:
                              imp = fabs((-191.2 * adc + 4363957)/(adc + -937.7));
                              break;
                          case 115:
                              imp = fabs((1034.9 * adc + 2270742)/(adc + -954.0));
                              break;
                          case 116:
                              imp = fabs((-527.2 * adc + 5060140)/(adc + -922.3));
                              break;
                          case 117:
                              imp = fabs((-614.3 * adc + 5203673)/(adc + -927.4));
                              break;
                          case 118:
                              imp = fabs((-113.9 * adc + 4366743)/(adc + -938.3));
                              break;
                          case 119:
                              imp = fabs((-919.7 * adc + 5883587)/(adc + -918.6));
                              break;
                          case 120:
                              imp = fabs((-1403.2 * adc + 6838766)/(adc + -906.2));
                              break;
                          case 121:
                              imp = fabs((-959.7 * adc + 6072239)/(adc + -912.9));
                              break;
                          case 122:
                              imp = fabs((-137.2 * adc + 4571247)/(adc + -932.0));
                              break;
                          case 123:
                              imp = fabs((223.0 * adc + 3940921)/(adc + -946.7));
                              break;
                          case 124:
                              imp = fabs((22.7 * adc + 4420721)/(adc + -931.7));
                              break;
                          case 125:
                              imp = fabs((95.1 * adc + 4244958)/(adc + -941.6));
                              break;
                          case 126:
                              imp = fabs((-148.2 * adc + 4748704)/(adc + -937.0));
                              break;
                          case 127:
                              imp = fabs((-575.4 * adc + 5595351)/(adc + -918.5));
                              break;
                          case 128:
                              imp = fabs((-481.4 * adc + 5513521)/(adc + -915.2));
                              break;
                          case 129:
                              imp = fabs((-203.7 * adc + 4976748)/(adc + -926.9));
                              break;
                          case 130:
                              imp = fabs((-1455.3 * adc + 7324476)/(adc + -905.6));
                              break;
                          case 131:
                              imp = fabs((-659.4 * adc + 5868119)/(adc + -925.3));
                              break;
                          case 132:
                              imp = fabs((-766.5 * adc + 6124055)/(adc + -920.6));
                              break;
                          case 133:
                              imp = fabs((-770.8 * adc + 6133454)/(adc + -921.5));
                              break;
                          case 134:
                              imp = fabs((413.6 * adc + 3991515)/(adc + -939.3));
                              break;
                          case 135:
                              imp = fabs((128.7 * adc + 4543044)/(adc + -939.6));
                              break;
                          case 136:
                              imp = fabs((403.6 * adc + 3986781)/(adc + -950.5));
                              break;
                          case 137:
                              imp = fabs((-257.6 * adc + 5353875)/(adc + -934.1));
                              break;
                          case 138:
                              imp = fabs((118.7 * adc + 4635089)/(adc + -945.1));
                              break;
                          case 139:
                              imp = fabs((-1341.3 * adc + 7608787)/(adc + -903.4));
                              break;
                          case 140:
                              imp = fabs((-705.5 * adc + 6372882)/(adc + -917.0));
                              break;
                          case 141:
                              imp = fabs((-545.6 * adc + 6081292)/(adc + -920.3));
                              break;
                          case 142:
                              imp = fabs((-20.9 * adc + 5063590)/(adc + -937.5));
                              break;
                          case 143:
                              imp = fabs((-618.6 * adc + 6233737)/(adc + -926.0));
                              break;
                          case 144:
                              imp = fabs((306.0 * adc + 4464219)/(adc + -944.7));
                              break;
                          case 145:
                              imp = fabs((1073.2 * adc + 2974793)/(adc + -966.5));
                              break;
                          case 146:
                              imp = fabs((1872.1 * adc + 1491962)/(adc + -977.8));
                              break;
                          case 147:
                              imp = fabs((-416.5 * adc + 6012153)/(adc + -928.8));
                              break;
                          case 148:
                              imp = fabs((-177.4 * adc + 5558656)/(adc + -935.0));
                              break;
                          case 149:
                              imp = fabs((-546.7 * adc + 6373488)/(adc + -921.1));
                              break;
                          case 150:
                              imp = fabs((-950.0 * adc + 7245550)/(adc + -911.4));
                              break;
                          case 151:
                              imp = fabs((123.4 * adc + 5076340)/(adc + -940.0));
                              break;
                          case 152:
                              imp = fabs((839.6 * adc + 3633545)/(adc + -963.5));
                              break;
                          case 153:
                              imp = fabs((-903.4 * adc + 7269015)/(adc + -913.2));
                              break;
                          case 154:
                              imp = fabs((-628.5 * adc + 6703828)/(adc + -921.8));
                              break;
                          case 155:
                              imp = fabs((-91.9 * adc + 5680570)/(adc + -929.7));
                              break;
                          case 156:
                              imp = fabs((-81.0 * adc + 5670574)/(adc + -936.1));
                              break;
                          case 157:
                              imp = fabs((77.8 * adc + 5367313)/(adc + -940.6));
                              break;
                          case 158:
                              imp = fabs((-1054.1 * adc + 7780897)/(adc + -909.8));
                              break;
                          case 159:
                              imp = fabs((-252.7 * adc + 6137379)/(adc + -931.5));
                              break;
                          case 160:
                              imp = fabs((-998.3 * adc + 7719138)/(adc + -913.4));
                              break;
                          case 161:
                              imp = fabs((-141.6 * adc + 5948575)/(adc + -936.3));
                              break;
                          case 162:
                              imp = fabs((-1607.5 * adc + 9137189)/(adc + -892.7));
                              break;
                          case 163:
                              imp = fabs((-832.2 * adc + 7556683)/(adc + -907.6));
                              break;
                          case 164:
                              imp = fabs((-95.6 * adc + 6005122)/(adc + -930.9));
                              break;
                          case 165:
                              imp = fabs((-129.1 * adc + 6037859)/(adc + -941.0));
                              break;
                          case 166:
                              imp = fabs((804.3 * adc + 4116390)/(adc + -961.3));
                              break;
                          case 167:
                              imp = fabs((60.9 * adc + 5757099)/(adc + -936.9));
                              break;
                          case 168:
                              imp = fabs((-877.9 * adc + 7831393)/(adc + -906.6));
                              break;
                          case 169:
                              imp = fabs((-1071.7 * adc + 8290979)/(adc + -904.0));
                              break;
                          case 170:
                              imp = fabs((-15.9 * adc + 6057919)/(adc + -935.9));
                              break;
                          case 171:
                              imp = fabs((-1200.3 * adc + 8700941)/(adc + -899.0));
                              break;
                          case 172:
                              imp = fabs((-347.4 * adc + 6827030)/(adc + -925.3));
                              break;
                          case 173:
                              imp = fabs((-556.2 * adc + 7305639)/(adc + -924.7));
                              break;
                          case 174:
                              imp = fabs((311.2 * adc + 5400595)/(adc + -951.5));
                              break;
                          case 175:
                              imp = fabs((-640.1 * adc + 7497480)/(adc + -921.8));
                              break;
                          case 176:
                              imp = fabs((-875.0 * adc + 8132394)/(adc + -906.7));
                              break;
                          case 177:
                              imp = fabs((2.8 * adc + 6231773)/(adc + -936.9));
                              break;
                          case 178:
                              imp = fabs((-924.4 * adc + 8249153)/(adc + -914.7));
                              break;
                          case 179:
                              imp = fabs((-795.2 * adc + 8042472)/(adc + -912.9));
                              break;
                          case 180:
                              imp = fabs((-1412.3 * adc + 9034480)/(adc + -914.5));
                              break;
                          case 181:
                              imp = fabs((256.9 * adc + 5788469)/(adc + -951.9));
                              break;
                          case 182:
                              imp = fabs((-1559.5 * adc + 9369174)/(adc + -915.2));
                              break;
                          case 183:
                              imp = fabs((568.8 * adc + 5336726)/(adc + -946.9));
                              break;
                          case 184:
                              imp = fabs((-1544.3 * adc + 9549695)/(adc + -902.9));
                              break;
                          case 185:
                              imp = fabs((-327.8 * adc + 7138087)/(adc + -933.7));
                              break;
                          case 186:
                              imp = fabs((985.9 * adc + 4520542)/(adc + -962.6));
                              break;
                          case 187:
                              imp = fabs((-530.0 * adc + 7679036)/(adc + -926.8));
                              break;
                          case 188:
                              imp = fabs((-231.0 * adc + 6932250)/(adc + -945.8));
                              break;
                          case 189:
                              imp = fabs((-1395.1 * adc + 9356839)/(adc + -918.7));
                              break;
                          case 190:
                              imp = fabs((-317.1 * adc + 7257696)/(adc + -934.3));
                              break;
                          case 191:
                              imp = fabs((607.2 * adc + 5541208)/(adc + -951.8));
                              break;
                          case 192:
                              imp = fabs((-931.6 * adc + 8891822)/(adc + -905.9));
                              break;
                          case 193:
                              imp = fabs((-867.3 * adc + 8514486)/(adc + -926.8));
                              break;
                          case 194:
                              imp = fabs((-794.3 * adc + 8717580)/(adc + -911.6));
                              break;
                          case 195:
                              imp = fabs((551.9 * adc + 5776249)/(adc + -945.5));
                              break;
                          case 196:
                              imp = fabs((561.8 * adc + 5757755)/(adc + -949.5));
                              break;
                          case 197:
                              imp = fabs((-275.7 * adc + 7306144)/(adc + -939.5));
                              break;
                          case 198:
                              imp = fabs((1447.3 * adc + 4128267)/(adc + -957.5));
                              break;
                          case 199:
                              imp = fabs((-1535.4 * adc + 10120412)/(adc + -903.5));
                              break;
                          case 200:
                              imp = fabs((-1265.0 * adc + 9875843)/(adc + -901.4));
                              break;
                          case 201:
                              imp = fabs((-1924.6 * adc + 11058911)/(adc + -897.0));
                              break;
                          case 202:
                              imp = fabs((-444.1 * adc + 7893520)/(adc + -932.3));
                              break;
                          case 203:
                              imp = fabs((853.7 * adc + 5518585)/(adc + -950.0));
                              break;
                          case 204:
                              imp = fabs((-572.3 * adc + 8576077)/(adc + -911.4));
                              break;
                          case 205:
                              imp = fabs((114.3 * adc + 7096532)/(adc + -939.4));
                              break;
                          case 206:
                              imp = fabs((-163.2 * adc + 7762872)/(adc + -919.2));
                              break;
                          case 207:
                              imp = fabs((-1818.1 * adc + 11132474)/(adc + -896.5));
                              break;
                          case 208:
                              imp = fabs((-832.0 * adc + 8971502)/(adc + -924.9));
                              break;
                          case 209:
                              imp = fabs((-2899.5 * adc + 13393094)/(adc + -881.7));
                              break;
                          case 210:
                              imp = fabs((-2762.4 * adc + 13167645)/(adc + -883.4));
                              break;
                          case 211:
                              imp = fabs((-245.2 * adc + 7921480)/(adc + -932.3));
                              break;
                          case 212:
                              imp = fabs((-2292.8 * adc + 12372595)/(adc + -890.1));
                              break;
                          case 213:
                              imp = fabs((-374.5 * adc + 8511161)/(adc + -923.6));
                              break;
                          case 214:
                              imp = fabs((412.1 * adc + 6654899)/(adc + -944.5));
                              break;
                          case 215:
                              imp = fabs((-1421.3 * adc + 10805993)/(adc + -899.0));
                              break;
                          case 216:
                              imp = fabs((1181.7 * adc + 5092122)/(adc + -966.4));
                              break;
                          case 217:
                              imp = fabs((-485.6 * adc + 8863700)/(adc + -924.5));
                              break;
                          case 218:
                              imp = fabs((-1845.0 * adc + 11569575)/(adc + -906.5));
                              break;
                          case 219:
                              imp = fabs((-375.1 * adc + 8360140)/(adc + -940.1));
                              break;
                          case 220:
                              imp = fabs((-2551.3 * adc + 13220953)/(adc + -886.5));
                              break;
                          case 221:
                              imp = fabs((-603.1 * adc + 9096364)/(adc + -928.0));
                              break;
                          case 222:
                              imp = fabs((-1202.4 * adc + 10712503)/(adc + -897.6));
                              break;
                          case 223:
                              imp = fabs((-2004.1 * adc + 12096780)/(adc + -901.4));
                              break;
                          case 224:
                              imp = fabs((580.7 * adc + 6634167)/(adc + -951.7));
                              break;
                          case 225:
                              imp = fabs((751.6 * adc + 6093385)/(adc + -962.5));
                              break;
                          case 226:
                              imp = fabs((-89.8 * adc + 8276376)/(adc + -936.0));
                              break;
                          case 227:
                              imp = fabs((-2511.1 * adc + 13414423)/(adc + -886.2));
                              break;
                          case 228:
                              imp = fabs((-2865.9 * adc + 14350784)/(adc + -878.8));
                              break;
                          case 229:
                              imp = fabs((632.9 * adc + 6741706)/(adc + -954.4));
                              break;
                          case 230:
                              imp = fabs((-1799.2 * adc + 12143762)/(adc + -895.2));
                              break;
                          case 231:
                              imp = fabs((-464.3 * adc + 9420568)/(adc + -920.2));
                              break;
                          case 232:
                              imp = fabs((1417.5 * adc + 5042757)/(adc + -968.1));
                              break;
                          case 233:
                              imp = fabs((952.7 * adc + 6023398)/(adc + -958.5));
                              break;
                          case 234:
                              imp = fabs((614.6 * adc + 6804219)/(adc + -959.5));
                              break;
                          case 235:
                              imp = fabs((-440.2 * adc + 9464495)/(adc + -923.7));
                              break;
                          case 236:
                              imp = fabs((-542.2 * adc + 9774497)/(adc + -916.9));
                              break;
                          case 237:
                              imp = fabs((-1924.4 * adc + 12632776)/(adc + -896.9));
                              break;
                          case 238:
                              imp = fabs((-3062.9 * adc + 15335707)/(adc + -872.5));
                              break;
                          case 239:
                              imp = fabs((-2226.7 * adc + 13280580)/(adc + -898.6));
                              break;
                          case 240:
                              imp = fabs((-3057.3 * adc + 15418927)/(adc + -871.4));
                              break;
                          case 241:
                              imp = fabs((-502.4 * adc + 9906635)/(adc + -918.4));
                              break;
                          case 242:
                              imp = fabs((12.2 * adc + 8556680)/(adc + -938.7));
                              break;
                          case 243:
                              imp = fabs((1123.1 * adc + 6149242)/(adc + -956.7));
                              break;
                          case 244:
                              imp = fabs((182.2 * adc + 8251382)/(adc + -941.8));
                              break;
                          case 245:
                              imp = fabs((467.8 * adc + 7550095)/(adc + -950.1));
                              break;
                          case 246:
                              imp = fabs((270.8 * adc + 8078690)/(adc + -937.6));
                              break;
                          case 247:
                              imp = fabs((1559.4 * adc + 5040922)/(adc + -978.3));
                              break;
                          case 248:
                              imp = fabs((-1835.9 * adc + 12859279)/(adc + -904.8));
                              break;
                          case 249:
                              imp = fabs((29.9 * adc + 8589081)/(adc + -953.9));
                              break;
                          case 250:
                              imp = fabs((-2466.1 * adc + 14563387)/(adc + -882.0));
                              break;
                          case 251:
                              imp = fabs((-726.3 * adc + 10586056)/(adc + -909.8));
                              break;
                          case 252:
                              imp = fabs((822.9 * adc + 7035554)/(adc + -960.2));
                              break;
                          case 253:
                              imp = fabs((46.8 * adc + 8931984)/(adc + -937.0));
                              break;
    }
                         return imp;
                  }
