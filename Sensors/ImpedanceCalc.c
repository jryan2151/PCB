/*
 * Created by Jared Brinkman
 * Date: 7/22/2022
 *
 * This file should be completely changed for every board calibrated
 * It will hold 255 impedance equations
*/

#include "ImpedanceCalc.h"

float impedanceCalc(uint8_t tapNumber, uint16_t adc) {
    float imp = 0;
    switch(tapNumber) {
        default:
              imp = 49999;
                  break;
        case 2:
            imp = fabs((-506.3 * adc + 732123)/(adc + 4404.9));
            break;
        case 3:
            imp = fabs((-797.0 * adc + 1988496)/(adc + 6311.3));
            break;
        case 4:
            imp = fabs((-1070.7 * adc + 3143571)/(adc + 6879.6));
            break;
        case 5:
            imp = fabs((-1130.2 * adc + 3673593)/(adc + 5974.0));
            break;
        case 6:
            imp = fabs((-782.3 * adc + 2870405)/(adc + 3412.9));
            break;
        case 7:
            imp = fabs((-1595.2 * adc + 5756979)/(adc + 6330.1));
            break;
        case 8:
            imp = fabs((-348.2 * adc + 1983894)/(adc + 1579.1));
            break;
        case 9:
            imp = fabs((-1397.7 * adc + 5587411)/(adc + 4461.0));
            break;
        case 10:
            imp = fabs((-2127.8 * adc + 8348564)/(adc + 6142.5));
            break;
        case 11:
            imp = fabs((259.4 * adc + 749658)/(adc + 186.5));
            break;
        case 12:
            imp = fabs((49.9 * adc + 1343105)/(adc + 367.2));
            break;
        case 13:
            imp = fabs((-172.8 * adc + 2051658)/(adc + 584.1));
            break;
        case 14:
            imp = fabs((-416.7 * adc + 2896672)/(adc + 842.3));
            break;
        case 15:
            imp = fabs((-665.6 * adc + 3807593)/(adc + 1121.5));
            break;
        case 16:
            imp = fabs((995.4 * adc + -15861)/(adc + -41.3));
            break;
        case 17:
            imp = fabs((998.0 * adc + -18954)/(adc + -41.9));
            break;
        case 18:
            imp = fabs((998.3 * adc + -17318)/(adc + -41.4));
            break;
        case 19:
            imp = fabs((996.2 * adc + -9691)/(adc + -39.6));
            break;
        case 20:
            imp = fabs((992.0 * adc + 3746)/(adc + -36.7));
            break;
        case 21:
            imp = fabs((981.2 * adc + 36884)/(adc + -29.7));
            break;
        case 22:
            imp = fabs((954.7 * adc + 118809)/(adc + -13.0));
            break;
        case 23:
            imp = fabs((1914.8 * adc + -2956452)/(adc + -799.7));
            break;
        case 24:
            imp = fabs((2134.9 * adc + -83170)/(adc + -44.9));
            break;
        case 25:
            imp = fabs((2148.1 * adc + -73917)/(adc + -43.3));
            break;
        case 26:
            imp = fabs((2168.1 * adc + -76926)/(adc + -44.0));
            break;
        case 27:
            imp = fabs((2173.9 * adc + -74280)/(adc + -43.6));
            break;
        case 28:
            imp = fabs((2168.5 * adc + -62321)/(adc + -41.7));
            break;
        case 29:
            imp = fabs((2161.0 * adc + -47697)/(adc + -39.7));
            break;
        case 30:
            imp = fabs((2135.7 * adc + -6806)/(adc + -33.8));
            break;
        case 31:
            imp = fabs((2097.5 * adc + 57127)/(adc + -25.0));
            break;
        case 32:
            imp = fabs((2842.0 * adc + -1130987)/(adc + -236.9));
            break;
        case 33:
            imp = fabs((1792.1 * adc + 628942)/(adc + 57.6));
            break;
        case 34:
            imp = fabs((3845.0 * adc + -159968)/(adc + -45.3));
            break;
        case 35:
            imp = fabs((3872.7 * adc + -161772)/(adc + -45.3));
            break;
        case 36:
            imp = fabs((3863.2 * adc + -146441)/(adc + -43.6));
            break;
        case 37:
            imp = fabs((3876.7 * adc + -150070)/(adc + -44.0));
            break;
        case 38:
            imp = fabs((3889.9 * adc + -158120)/(adc + -45.0));
            break;
        case 39:
            imp = fabs((3888.1 * adc + -154789)/(adc + -45.0));
            break;
        case 40:
            imp = fabs((3889.7 * adc + -151504)/(adc + -44.5));
            break;
        case 41:
            imp = fabs((3883.7 * adc + -139956)/(adc + -43.3));
            break;
        case 42:
            imp = fabs((3878.5 * adc + -128419)/(adc + -42.2));
            break;
        case 43:
            imp = fabs((3859.5 * adc + -93415)/(adc + -38.5));
            break;
        case 44:
            imp = fabs((3848.8 * adc + -71304)/(adc + -36.6));
            break;
        case 45:
            imp = fabs((4761.1 * adc + -1801390)/(adc + -242.7));
            break;
        case 46:
            imp = fabs((4903.9 * adc + -2179846)/(adc + -290.0));
            break;
        case 47:
            imp = fabs((5051.6 * adc + -2594087)/(adc + -343.0));
            break;
        case 48:
            imp = fabs((3606.4 * adc + 438664)/(adc + 12.8));
            break;
        case 49:
            imp = fabs((3378.7 * adc + 953394)/(adc + 63.3));
            break;
        case 50:
            imp = fabs((3047.2 * adc + 1746488)/(adc + 141.2));
            break;
        case 51:
            imp = fabs((2647.2 * adc + 2777744)/(adc + 243.8));
            break;
        case 52:
            imp = fabs((2239.4 * adc + 3894764)/(adc + 354.2));
            break;
        case 53:
            imp = fabs((1814.9 * adc + 5123807)/(adc + 475.7));
            break;
        case 54:
            imp = fabs((1337.6 * adc + 6570930)/(adc + 619.2));
            break;
        case 55:
            imp = fabs((878.4 * adc + 8019312)/(adc + 762.4));
            break;
        case 56:
            imp = fabs((410.0 * adc + 9552933)/(adc + 914.5));
            break;
        case 57:
            imp = fabs((-164.6 * adc + 11475938)/(adc + 1104.9));
            break;
        case 58:
            imp = fabs((-772.2 * adc + 13568961)/(adc + 1311.8));
            break;
        case 59:
            imp = fabs((-1397.1 * adc + 15793439)/(adc + 1531.8));
            break;
        case 60:
            imp = fabs((-2086.6 * adc + 18266267)/(adc + 1775.6));
            break;
        case 61:
            imp = fabs((-2845.4 * adc + 21046858)/(adc + 2049.6));
            break;
        case 62:
            imp = fabs((-3663.2 * adc + 24093549)/(adc + 2348.5));
            break;
        case 63:
            imp = fabs((-4518.3 * adc + 27329839)/(adc + 2666.5));
            break;
        case 64:
            imp = fabs((-5430.8 * adc + 30792295)/(adc + 3006.2));
            break;
        case 65:
            imp = fabs((-6536.9 * adc + 35037924)/(adc + 3418.9));
            break;
        case 66:
            imp = fabs((-7712.7 * adc + 39634230)/(adc + 3865.4));
            break;
        case 67:
            imp = fabs((-9002.3 * adc + 44676953)/(adc + 4350.7));
            break;
        case 68:
            imp = fabs((-10387.7 * adc + 50138713)/(adc + 4870.8));
            break;
        case 69:
            imp = fabs((-11623.7 * adc + 55096373)/(adc + 5329.6));
            break;
        case 70:
            imp = fabs((-12709.4 * adc + 59486063)/(adc + 5710.5));
            break;
        case 71:
            imp = fabs((-13437.9 * adc + 62465389)/(adc + 5937.5));
            break;
        case 72:
            imp = fabs((-13798.4 * adc + 64021835)/(adc + 6013.9));
            break;
        case 73:
            imp = fabs((-13950.4 * adc + 64799752)/(adc + 6000.9));
            break;
        case 74:
            imp = fabs((-14196.7 * adc + 65915759)/(adc + 6019.4));
            break;
        case 75:
            imp = fabs((-14440.1 * adc + 67041576)/(adc + 6039.0));
            break;
        case 76:
            imp = fabs((-14561.7 * adc + 67675826)/(adc + 6012.0));
            break;
        case 77:
            imp = fabs((-14857.8 * adc + 68973339)/(adc + 6048.2));
            break;
        case 78:
            imp = fabs((-14994.5 * adc + 69664153)/(adc + 6024.9));
            break;
        case 79:
            imp = fabs((-15279.2 * adc + 70932337)/(adc + 6062.2));
            break;
        case 80:
            imp = fabs((-15432.2 * adc + 71655962)/(adc + 6052.4));
            break;
        case 81:
            imp = fabs((-15682.6 * adc + 72788312)/(adc + 6069.4));
            break;
        case 82:
            imp = fabs((-15755.6 * adc + 73232939)/(adc + 6025.5));
            break;
        case 83:
            imp = fabs((3281.0 * adc + 4723155)/(adc + 96.8));
            break;
        case 84:
            imp = fabs((3116.6 * adc + 5157607)/(adc + 109.5));
            break;
        case 85:
            imp = fabs((82.5 * adc + 4)/(adc + -50.5));
            break;
        case 86:
            imp = fabs((82.8 * adc + 3)/(adc + -50.9));
            break;
        case 87:
            imp = fabs((2619.3 * adc + 6522643)/(adc + 150.3));
            break;
        case 88:
            imp = fabs((82.8 * adc + 3)/(adc + -50.9));
            break;
        case 89:
            imp = fabs((2282.6 * adc + 7483073)/(adc + 178.4));
            break;
        case 90:
            imp = fabs((2111.1 * adc + 7989018)/(adc + 193.6));
            break;
        case 91:
            imp = fabs((82.9 * adc + 4)/(adc + -51.5));
            break;
        case 92:
            imp = fabs((82.6 * adc + 3)/(adc + -51.3));
            break;
        case 93:
            imp = fabs((83.3 * adc + 4)/(adc + -51.7));
            break;
        case 94:
            imp = fabs((83.2 * adc + 7)/(adc + -51.3));
            break;
        case 95:
            imp = fabs((82.6 * adc + 2)/(adc + -51.3));
            break;
        case 96:
            imp = fabs((83.0 * adc + 7)/(adc + -51.1));
            break;
        case 97:
            imp = fabs((926.2 * adc + 11687406)/(adc + 303.4));
            break;
        case 98:
            imp = fabs((758.5 * adc + 12243135)/(adc + 319.7));
            break;
        case 99:
            imp = fabs((586.5 * adc + 12812503)/(adc + 335.9));
            break;
        case 100:
            imp = fabs((414.4 * adc + 13402013)/(adc + 354.2));
            break;
        case 101:
            imp = fabs((82.4 * adc + 3)/(adc + -51.1));
            break;
        case 102:
            imp = fabs((83.9 * adc + 2)/(adc + -52.1));
            break;
        case 103:
            imp = fabs((83.4 * adc + 6)/(adc + -51.9));
            break;
        case 104:
            imp = fabs((-297.1 * adc + 15828632)/(adc + 426.0));
            break;
        case 105:
            imp = fabs((83.8 * adc + 6)/(adc + -52.1));
            break;
        case 106:
            imp = fabs((83.7 * adc + 3)/(adc + -52.1));
            break;
        case 107:
            imp = fabs((83.2 * adc + 3)/(adc + -51.9));
            break;
        case 108:
            imp = fabs((-1024.0 * adc + 18428941)/(adc + 504.2));
            break;
        case 109:
            imp = fabs((83.7 * adc + 3)/(adc + -52.5));
            break;
        case 110:
            imp = fabs((83.5 * adc + 4)/(adc + -52.1));
            break;
        case 111:
            imp = fabs((83.4 * adc + 3)/(adc + -51.7));
            break;
        case 112:
            imp = fabs((83.7 * adc + 4)/(adc + -52.1));
            break;
        case 113:
            imp = fabs((83.9 * adc + 2)/(adc + -51.7));
            break;
        case 114:
            imp = fabs((83.7 * adc + 2)/(adc + -51.7));
            break;
        case 115:
            imp = fabs((-2318.3 * adc + 23228493)/(adc + 646.0));
            break;
        case 116:
            imp = fabs((83.8 * adc + 2)/(adc + -51.9));
            break;
        case 117:
            imp = fabs((84.1 * adc + 11)/(adc + -52.3));
            break;
        case 118:
            imp = fabs((8240.7 * adc + -136814)/(adc + -43.3));
            break;
        case 119:
            imp = fabs((13205.8 * adc + -10325267)/(adc + -269.2));
            break;
        case 120:
            imp = fabs((8256.3 * adc + -164023)/(adc + -44.0));
            break;
        case 121:
            imp = fabs((13480.3 * adc + -11113938)/(adc + -286.6));
            break;
        case 122:
            imp = fabs((8252.9 * adc + -149864)/(adc + -43.6));
            break;
        case 123:
            imp = fabs((13333.3 * adc + -11052365)/(adc + -285.4));
            break;
        case 124:
            imp = fabs((73.7 * adc + 1)/(adc + -52.1));
            break;
        case 125:
            imp = fabs((8238.9 * adc + -110431)/(adc + -42.7));
            break;
        case 126:
            imp = fabs((13279.4 * adc + -11283051)/(adc + -290.6));
            break;
        case 127:
            imp = fabs((8264.9 * adc + -164540)/(adc + -44.0));
            break;
        case 128:
            imp = fabs((13393.3 * adc + -11744385)/(adc + -301.0));
            break;
        case 129:
            imp = fabs((74.1 * adc + 1)/(adc + -47.9));
            break;
        case 130:
            imp = fabs((13500.1 * adc + -12206054)/(adc + -311.4));
            break;
        case 131:
            imp = fabs((8268.9 * adc + -163130)/(adc + -43.8));
            break;
        case 132:
            imp = fabs((8258.8 * adc + -139570)/(adc + -43.5));
            break;
        case 133:
            imp = fabs((8265.3 * adc + -152267)/(adc + -43.8));
            break;
        case 134:
            imp = fabs((13544.5 * adc + -12740486)/(adc + -323.2));
            break;
        case 135:
            imp = fabs((13478.9 * adc + -12686476)/(adc + -322.1));
            break;
        case 136:
            imp = fabs((8262.5 * adc + -139802)/(adc + -43.5));
            break;
        case 137:
            imp = fabs((8258.2 * adc + -127232)/(adc + -43.3));
            break;
        case 138:
            imp = fabs((8237.9 * adc + -70143)/(adc + -41.6));
            break;
        case 139:
            imp = fabs((8254.7 * adc + -114715)/(adc + -43.1));
            break;
        case 140:
            imp = fabs((8250.4 * adc + -100493)/(adc + -42.7));
            break;
        case 141:
            imp = fabs((8251.4 * adc + -100552)/(adc + -42.7));
            break;
        case 142:
            imp = fabs((13802.2 * adc + -14189237)/(adc + -356.0));
            break;
        case 143:
            imp = fabs((8248.0 * adc + -86387)/(adc + -42.3));
            break;
        case 144:
            imp = fabs((8259.0 * adc + -113332)/(adc + -42.9));
            break;
        case 145:
            imp = fabs((13562.8 * adc + -13871069)/(adc + -348.8));
            break;
        case 146:
            imp = fabs((8240.6 * adc + -62946)/(adc + -42.0));
            break;
        case 147:
            imp = fabs((8246.5 * adc + -72333)/(adc + -41.8));
            break;
        case 148:
            imp = fabs((8257.1 * adc + -100912)/(adc + -42.7));
            break;
        case 149:
            imp = fabs((13415.2 * adc + -13842299)/(adc + -348.2));
            break;
        case 150:
            imp = fabs((8253.8 * adc + -88402)/(adc + -42.5));
            break;
        case 151:
            imp = fabs((8259.4 * adc + -99401)/(adc + -42.5));
            break;
        case 152:
            imp = fabs((8260.0 * adc + -101096)/(adc + -42.7));
            break;
        case 153:
            imp = fabs((8260.7 * adc + -97835)/(adc + -42.3));
            break;
        case 154:
            imp = fabs((13854.0 * adc + -15458739)/(adc + -384.6));
            break;
        case 155:
            imp = fabs((8252.6 * adc + -76024)/(adc + -42.2));
            break;
        case 156:
            imp = fabs((8262.7 * adc + -101263)/(adc + -42.7));
            break;
        case 157:
            imp = fabs((8282.0 * adc + -153280)/(adc + -43.8));
            break;
        case 158:
            imp = fabs((8259.4 * adc + -88758)/(adc + -42.5));
            break;
        case 159:
            imp = fabs((14167.9 * adc + -16767304)/(adc + -414.0));
            break;
        case 160:
            imp = fabs((8274.3 * adc + -128229)/(adc + -43.3));
            break;
        case 161:
            imp = fabs((8284.0 * adc + -156713)/(adc + -44.2));
            break;
        case 162:
            imp = fabs((14038.1 * adc + -16666150)/(adc + -411.5));
            break;
        case 163:
            imp = fabs((13877.7 * adc + -16291167)/(adc + -403.4));
            break;
        case 164:
            imp = fabs((8271.9 * adc + -115788)/(adc + -43.1));
            break;
        case 165:
            imp = fabs((8280.3 * adc + -142364)/(adc + -44.0));
            break;
        case 166:
            imp = fabs((8269.6 * adc + -106835)/(adc + -43.0));
            break;
        case 167:
            imp = fabs((8264.5 * adc + -89079)/(adc + -42.5));
            break;
        case 168:
            imp = fabs((8270.5 * adc + -106894)/(adc + -43.0));
            break;
        case 169:
            imp = fabs((8249.1 * adc + -39897)/(adc + -41.4));
            break;
        case 170:
            imp = fabs((8266.1 * adc + -93309)/(adc + -43.0));
            break;
        case 171:
            imp = fabs((70.8 * adc + 1)/(adc + -47.0));
            break;
        case 172:
            imp = fabs((9823.3 * adc + -211493)/(adc + -43.5));
            break;
        case 173:
            imp = fabs((9868.7 * adc + -205301)/(adc + -43.4));
            break;
        case 174:
            imp = fabs((9911.0 * adc + -196417)/(adc + -43.0));
            break;
        case 175:
            imp = fabs((71.3 * adc + 1)/(adc + -47.0));
            break;
        case 176:
            imp = fabs((71.1 * adc + 2)/(adc + -47.5));
            break;
        case 177:
            imp = fabs((9335.8 * adc + -103727)/(adc + -41.9));
            break;
        case 178:
            imp = fabs((9618.5 * adc + -175390)/(adc + -43.1));
            break;
        case 179:
            imp = fabs((72.1 * adc + 1)/(adc + -53.1));
            break;
        case 180:
            imp = fabs((71.4 * adc + 1)/(adc + -47.0));
            break;
        case 181:
            imp = fabs((69789602.6 * adc + -198589847483)/(adc + -3748724.4));
            break;
        case 182:
            imp = fabs((89187823.8 * adc + -255076235156)/(adc + -4815349.5));
            break;
        case 183:
            imp = fabs((10226.2 * adc + -207364)/(adc + -42.9));
            break;
        case 184:
            imp = fabs((9621.4 * adc + -175551)/(adc + -43.1));
            break;
        case 185:
            imp = fabs((71.3 * adc + 2)/(adc + -47.4));
            break;
        case 186:
            imp = fabs((71.6 * adc + 2)/(adc + -47.5));
            break;
        case 187:
            imp = fabs((128679128.1 * adc + -375820007288)/(adc + -7096363.6));
            break;
        case 188:
            imp = fabs((83984010.5 * adc + -246283448728)/(adc + -4650874.7));
            break;
        case 189:
            imp = fabs((9654.3 * adc + -104827)/(adc + -41.6));
            break;
        case 190:
            imp = fabs((9654.9 * adc + -104858)/(adc + -41.6));
            break;
        case 191:
            imp = fabs((9918.6 * adc + -196854)/(adc + -43.0));
            break;
        case 192:
            imp = fabs((71.6 * adc + 1)/(adc + -47.4));
            break;
        case 193:
            imp = fabs((9583.0 * adc + -122625)/(adc + -42.4));
            break;
        case 194:
            imp = fabs((9725.2 * adc + -91744)/(adc + -41.4));
            break;
        case 195:
            imp = fabs((85452198.4 * adc + -257692357293)/(adc + -4868157.8));
            break;
        case 196:
            imp = fabs((71.6 * adc + 2)/(adc + -47.0));
            break;
        case 197:
            imp = fabs((10112.8 * adc + -156245)/(adc + -42.4));
            break;
        case 198:
            imp = fabs((73950852.8 * adc + -225502032192)/(adc + -4260329.4));
            break;
        case 199:
            imp = fabs((71.7 * adc + 2)/(adc + -47.2));
            break;
        case 200:
            imp = fabs((71.5 * adc + 2)/(adc + -47.2));
            break;
        case 201:
            imp = fabs((71.4 * adc + 1)/(adc + -47.5));
            break;
        case 202:
            imp = fabs((9926.5 * adc + -44832)/(adc + -40.7));
            break;
        case 203:
            imp = fabs((9655.6 * adc + 22130)/(adc + -39.8));
            break;
        case 204:
            imp = fabs((10169.2 * adc + -27145)/(adc + -40.4));
            break;
        case 205:
            imp = fabs((71.5 * adc + 1)/(adc + -47.2));
            break;
        case 206:
            imp = fabs((10270.9 * adc + -6391)/(adc + -39.9));
            break;
        case 207:
            imp = fabs((10252.9 * adc + 13412)/(adc + -39.5));
            break;
        case 208:
            imp = fabs((10220.8 * adc + 61810)/(adc + -38.8));
            break;
        case 209:
            imp = fabs((10233.2 * adc + 89793)/(adc + -38.5));
            break;
        case 210:
            imp = fabs((29535.1 * adc + -1591304)/(adc + -51.0));
            break;
        case 211:
            imp = fabs((72.3 * adc + 1)/(adc + -46.9));
            break;
        case 212:
            imp = fabs((72.5 * adc + 1)/(adc + -47.2));
            break;
        case 213:
            imp = fabs((10096.0 * adc + 274768)/(adc + -35.7));
            break;
        case 214:
            imp = fabs((72.0 * adc + 2)/(adc + -47.2));
            break;
        case 215:
            imp = fabs((72.6 * adc + 2)/(adc + -48.7));
            break;
        case 216:
            imp = fabs((10085.3 * adc + 472493)/(adc + -32.4));
            break;
        case 217:
            imp = fabs((73.1 * adc + 2)/(adc + -49.2));
            break;
        case 218:
            imp = fabs((9939.6 * adc + 639765)/(adc + -29.7));
            break;
        case 219:
            imp = fabs((9899.4 * adc + 712411)/(adc + -29.0));
            break;
        case 220:
            imp = fabs((27672.8 * adc + -1626843)/(adc + -53.3));
            break;
        case 221:
            imp = fabs((73.4 * adc + 2)/(adc + -48.9));
            break;
        case 222:
            imp = fabs((9838.2 * adc + 1054231)/(adc + -23.3));
            break;
        case 223:
            imp = fabs((73.2 * adc + 1)/(adc + -47.7));
            break;
        case 224:
            imp = fabs((73.2 * adc + 1)/(adc + -46.9));
            break;
        case 225:
            imp = fabs((73.6 * adc + 1)/(adc + -49.2));
            break;
        case 226:
            imp = fabs((73.6 * adc + 1)/(adc + -49.2));
            break;
        case 227:
            imp = fabs((269370269.1 * adc + -891845444557)/(adc + -16758880.4));
            break;
        case 228:
            imp = fabs((99.0 * adc + 0)/(adc + -105.7));
            break;
        case 229:
            imp = fabs((9219.9 * adc + 2656962)/(adc + 1.5));
            break;
        case 230:
            imp = fabs((75.1 * adc + 1)/(adc + -50.1));
            break;
        case 231:
            imp = fabs((26192.3 * adc + -1912384)/(adc + -59.5));
            break;
        case 232:
            imp = fabs((8838.6 * adc + 3927168)/(adc + 22.1));
            break;
        case 233:
            imp = fabs((75.4 * adc + 1)/(adc + -50.1));
            break;
        case 234:
            imp = fabs((8468.4 * adc + 5027229)/(adc + 39.2));
            break;
        case 235:
            imp = fabs((75.1 * adc + 1)/(adc + -47.3));
            break;
        case 236:
            imp = fabs((25167.7 * adc + -2053927)/(adc + -62.6));
            break;
        case 237:
            imp = fabs((7908.3 * adc + 6857084)/(adc + 68.3));
            break;
        case 238:
            imp = fabs((7693.5 * adc + 7545770)/(adc + 79.3));
            break;
        case 239:
            imp = fabs((7513.9 * adc + 8160917)/(adc + 89.2));
            break;
        case 240:
            imp = fabs((75.0 * adc + 1)/(adc + -47.7));
            break;
        case 241:
            imp = fabs((24451.1 * adc + -2158922)/(adc + -65.1));
            break;
        case 242:
            imp = fabs((75.8 * adc + 1)/(adc + -47.5));
            break;
        case 243:
            imp = fabs((6692.5 * adc + 10939957)/(adc + 133.7));
            break;
        case 244:
            imp = fabs((6387.9 * adc + 11828642)/(adc + 147.7));
            break;
        case 245:
            imp = fabs((24401.2 * adc + -2361391)/(adc + -68.4));
            break;
        case 246:
            imp = fabs((76.1 * adc + 1)/(adc + -50.7));
            break;
        case 247:
            imp = fabs((5798.1 * adc + 13936868)/(adc + 181.7));
            break;
        case 248:
            imp = fabs((71.8 * adc + 1)/(adc + -47.0));
            break;
        case 249:
            imp = fabs((72.2 * adc + 1)/(adc + -47.4));
            break;
        case 250:
            imp = fabs((688030011.0 * adc + -343607180430)/(adc + -3802873.9));
            break;
        case 251:
            imp = fabs((71.9 * adc + 1)/(adc + -47.4));
            break;
        case 252:
            imp = fabs((71.9 * adc + 2)/(adc + -46.8));
            break;
        case 253:
            imp = fabs((36206.5 * adc + -1617421)/(adc + -46.3));
            break;
        case 254:
            imp = fabs((72.4 * adc + 2)/(adc + -47.4));
            break;
       }
       return imp;
}
