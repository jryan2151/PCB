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
            imp = fabs((-175.0 * adc + 324400)/(adc + -992.5));
            break;
        case 3:
            imp = fabs((-168.4 * adc + 352892)/(adc + -1019.9));
            break;
        case 4:
            imp = fabs((-196.9 * adc + 451380)/(adc + -911.6));
            break;
        case 5:
            imp = fabs((-291.7 * adc + 715049)/(adc + -551.4));
            break;
        case 6:
            imp = fabs((-443.4 * adc + 1146304)/(adc + 26.2));
            break;
        case 7:
            imp = fabs((-374.6 * adc + 1021250)/(adc + -346.5));
            break;
        case 8:
            imp = fabs((-266.7 * adc + 767665)/(adc + -879.6));
            break;
        case 9:
            imp = fabs((-376.0 * adc + 1123310)/(adc + -435.7));
            break;
        case 10:
            imp = fabs((-303.6 * adc + 955691)/(adc + -730.8));
            break;
        case 11:
            imp = fabs((-327.1 * adc + 1067989)/(adc + -679.2));
            break;
        case 12:
            imp = fabs((-234.0 * adc + 845261)/(adc + -902.4));
            break;
        case 13:
            imp = fabs((-253.5 * adc + 932748)/(adc + -876.9));
            break;
        case 14:
            imp = fabs((-275.7 * adc + 1032206)/(adc + -846.2));
            break;
        case 15:
            imp = fabs((-289.3 * adc + 1110037)/(adc + -826.3));
            break;
        case 16:
            imp = fabs((-216.4 * adc + 936700)/(adc + -933.5));
            break;
        case 17:
            imp = fabs((-228.4 * adc + 1003919)/(adc + -924.0));
            break;
        case 18:
            imp = fabs((-236.0 * adc + 1060289)/(adc + -918.4));
            break;
        case 19:
            imp = fabs((-249.5 * adc + 1132719)/(adc + -905.9));
            break;
        case 20:
            imp = fabs((-259.5 * adc + 1197609)/(adc + -897.4));
            break;
        case 21:
            imp = fabs((-268.7 * adc + 1261163)/(adc + -888.8));
            break;
        case 22:
            imp = fabs((-278.6 * adc + 1330178)/(adc + -878.0));
            break;
        case 23:
            imp = fabs((-204.3 * adc + 1163916)/(adc + -952.3));
            break;
        case 24:
            imp = fabs((-204.6 * adc + 1200887)/(adc + -953.3));
            break;
        case 25:
            imp = fabs((-208.3 * adc + 1247560)/(adc + -952.3));
            break;
        case 26:
            imp = fabs((-217.5 * adc + 1307906)/(adc + -948.2));
            break;
        case 27:
            imp = fabs((-222.1 * adc + 1358089)/(adc + -946.9));
            break;
        case 28:
            imp = fabs((-227.5 * adc + 1408253)/(adc + -944.9));
            break;
        case 29:
            imp = fabs((-236.0 * adc + 1466171)/(adc + -942.0));
            break;
        case 30:
            imp = fabs((-240.3 * adc + 1513263)/(adc + -941.2));
            break;
        case 31:
            imp = fabs((-245.9 * adc + 1566074)/(adc + -937.8));
            break;
        case 32:
            imp = fabs((-245.3 * adc + 1588436)/(adc + -937.7));
            break;
        case 33:
            imp = fabs((-191.3 * adc + 1498620)/(adc + -955.0));
            break;
        case 34:
            imp = fabs((-190.2 * adc + 1532106)/(adc + -956.3));
            break;
        case 35:
            imp = fabs((-196.3 * adc + 1583054)/(adc + -953.6));
            break;
        case 36:
            imp = fabs((-200.1 * adc + 1628521)/(adc + -953.5));
            break;
        case 37:
            imp = fabs((-203.3 * adc + 1674319)/(adc + -952.0));
            break;
        case 38:
            imp = fabs((-191.0 * adc + 1680330)/(adc + -955.1));
            break;
        case 39:
            imp = fabs((-200.5 * adc + 1741038)/(adc + -953.6));
            break;
        case 40:
            imp = fabs((-184.1 * adc + 1731918)/(adc + -960.5));
            break;
        case 41:
            imp = fabs((-190.7 * adc + 1786261)/(adc + -957.8));
            break;
        case 42:
            imp = fabs((-202.7 * adc + 1852988)/(adc + -954.4));
            break;
        case 43:
            imp = fabs((-206.5 * adc + 1900073)/(adc + -954.0));
            break;
        case 44:
            imp = fabs((-217.6 * adc + 1967800)/(adc + -949.6));
            break;
        case 45:
            imp = fabs((-206.3 * adc + 1966811)/(adc + -956.3));
            break;
        case 46:
            imp = fabs((-232.6 * adc + 2079233)/(adc + -946.0));
            break;
        case 47:
            imp = fabs((-219.1 * adc + 2076283)/(adc + -951.3));
            break;
        case 48:
            imp = fabs((-221.0 * adc + 2104600)/(adc + -950.8));
            break;
        case 49:
            imp = fabs((-209.5 * adc + 2105682)/(adc + -956.6));
            break;
        case 50:
            imp = fabs((-221.8 * adc + 2179033)/(adc + -951.4));
            break;
        case 51:
            imp = fabs((-218.3 * adc + 2214528)/(adc + -950.4));
            break;
        case 52:
            imp = fabs((-217.6 * adc + 2248571)/(adc + -950.7));
            break;
        case 53:
            imp = fabs((-227.9 * adc + 2308885)/(adc + -949.6));
            break;
        case 54:
            imp = fabs((-217.8 * adc + 2321184)/(adc + -952.0));
            break;
        case 55:
            imp = fabs((-224.5 * adc + 2374361)/(adc + -950.9));
            break;
        case 56:
            imp = fabs((-216.9 * adc + 2393123)/(adc + -952.5));
            break;
        case 57:
            imp = fabs((-215.8 * adc + 2427650)/(adc + -952.7));
            break;
        case 58:
            imp = fabs((-224.4 * adc + 2486418)/(adc + -951.3));
            break;
        case 59:
            imp = fabs((-218.8 * adc + 2515648)/(adc + -950.9));
            break;
        case 60:
            imp = fabs((-229.5 * adc + 2577537)/(adc + -949.6));
            break;
        case 61:
            imp = fabs((-227.1 * adc + 2603107)/(adc + -951.1));
            break;
        case 62:
            imp = fabs((-218.4 * adc + 2620740)/(adc + -952.4));
            break;
        case 63:
            imp = fabs((-220.0 * adc + 2656759)/(adc + -953.0));
            break;
        case 64:
            imp = fabs((-230.8 * adc + 2713174)/(adc + -949.7));
            break;
        case 65:
            imp = fabs((-238.4 * adc + 2771177)/(adc + -947.4));
            break;
        case 66:
            imp = fabs((-221.1 * adc + 2760706)/(adc + -951.4));
            break;
        case 67:
            imp = fabs((-230.2 * adc + 2821663)/(adc + -949.3));
            break;
        case 68:
            imp = fabs((-229.0 * adc + 2852706)/(adc + -951.6));
            break;
        case 69:
            imp = fabs((-233.2 * adc + 2904735)/(adc + -949.0));
            break;
        case 70:
            imp = fabs((-234.6 * adc + 2946339)/(adc + -949.0));
            break;
        case 71:
            imp = fabs((-182.9 * adc + 2887791)/(adc + -953.1));
            break;
        case 72:
            imp = fabs((-157.6 * adc + 2870051)/(adc + -955.8));
            break;
        case 73:
            imp = fabs((-206.1 * adc + 3000835)/(adc + -953.2));
            break;
        case 74:
            imp = fabs((-190.2 * adc + 3011056)/(adc + -953.5));
            break;
        case 75:
            imp = fabs((-127.4 * adc + 2914699)/(adc + -960.9));
            break;
        case 76:
            imp = fabs((-191.9 * adc + 3090271)/(adc + -952.9));
            break;
        case 77:
            imp = fabs((-78.4 * adc + 2888467)/(adc + -963.8));
            break;
        case 78:
            imp = fabs((-177.9 * adc + 3139142)/(adc + -953.1));
            break;
        case 79:
            imp = fabs((-151.3 * adc + 3118803)/(adc + -956.5));
            break;
        case 80:
            imp = fabs((-78.6 * adc + 2990152)/(adc + -963.5));
            break;
        case 81:
            imp = fabs((-181.5 * adc + 3248869)/(adc + -953.6));
            break;
        case 82:
            imp = fabs((-95.9 * adc + 3106165)/(adc + -960.9));
            break;
        case 83:
            imp = fabs((-173.4 * adc + 3304723)/(adc + -954.5));
            break;
        case 84:
            imp = fabs((-179.1 * adc + 3361294)/(adc + -952.5));
            break;
        case 85:
            imp = fabs((-84.3 * adc + 3185927)/(adc + -963.0));
            break;
        case 86:
            imp = fabs((-142.2 * adc + 3357773)/(adc + -956.0));
            break;
        case 87:
            imp = fabs((-133.4 * adc + 3380491)/(adc + -956.0));
            break;
        case 88:
            imp = fabs((-182.0 * adc + 3515530)/(adc + -952.7));
            break;
        case 89:
            imp = fabs((-118.6 * adc + 3416714)/(adc + -958.5));
            break;
        case 90:
            imp = fabs((-139.2 * adc + 3499664)/(adc + -956.6));
            break;
        case 91:
            imp = fabs((-155.0 * adc + 3562103)/(adc + -957.3));
            break;
        case 92:
            imp = fabs((-174.8 * adc + 3648959)/(adc + -954.2));
            break;
        case 93:
            imp = fabs((-90.7 * adc + 3508851)/(adc + -960.7));
            break;
        case 94:
            imp = fabs((-160.5 * adc + 3700604)/(adc + -953.8));
            break;
        case 95:
            imp = fabs((-91.6 * adc + 3573532)/(adc + -962.1));
            break;
        case 96:
            imp = fabs((-110.2 * adc + 3640215)/(adc + -960.5));
            break;
        case 97:
            imp = fabs((-164.3 * adc + 3797351)/(adc + -954.1));
            break;
        case 98:
            imp = fabs((-222.6 * adc + 3978075)/(adc + -947.0));
            break;
        case 99:
            imp = fabs((-86.2 * adc + 3690693)/(adc + -963.8));
            break;
        case 100:
            imp = fabs((-108.3 * adc + 3779063)/(adc + -960.8));
            break;
        case 101:
            imp = fabs((-143.2 * adc + 3904457)/(adc + -955.6));
            break;
        case 102:
            imp = fabs((-141.3 * adc + 3927287)/(adc + -957.7));
            break;
        case 103:
            imp = fabs((-85.4 * adc + 3839008)/(adc + -961.8));
            break;
        case 104:
            imp = fabs((-124.4 * adc + 3956256)/(adc + -960.9));
            break;
        case 105:
            imp = fabs((-72.4 * adc + 3869301)/(adc + -966.5));
            break;
        case 106:
            imp = fabs((-149.5 * adc + 4096515)/(adc + -956.6));
            break;
        case 107:
            imp = fabs((-176.7 * adc + 4192213)/(adc + -954.9));
            break;
        case 108:
            imp = fabs((-163.8 * adc + 4209111)/(adc + -954.1));
            break;
        case 109:
            imp = fabs((-122.9 * adc + 4138032)/(adc + -960.3));
            break;
        case 110:
            imp = fabs((-165.8 * adc + 4282104)/(adc + -954.3));
            break;
        case 111:
            imp = fabs((-141.0 * adc + 4252591)/(adc + -959.0));
            break;
        case 112:
            imp = fabs((-178.5 * adc + 4377287)/(adc + -952.7));
            break;
        case 113:
            imp = fabs((-94.8 * adc + 4192582)/(adc + -965.2));
            break;
        case 114:
            imp = fabs((-146.0 * adc + 4357698)/(adc + -958.9));
            break;
        case 115:
            imp = fabs((-194.7 * adc + 4526673)/(adc + -950.6));
            break;
        case 116:
            imp = fabs((-183.0 * adc + 4532060)/(adc + -952.0));
            break;
        case 117:
            imp = fabs((-185.0 * adc + 4572079)/(adc + -953.2));
            break;
        case 118:
            imp = fabs((-166.7 * adc + 4561536)/(adc + -954.8));
            break;
        case 119:
            imp = fabs((-187.8 * adc + 4658830)/(adc + -951.5));
            break;
        case 120:
            imp = fabs((-198.9 * adc + 4719039)/(adc + -951.5));
            break;
        case 121:
            imp = fabs((-166.0 * adc + 4669142)/(adc + -955.8));
            break;
        case 122:
            imp = fabs((-226.7 * adc + 4868416)/(adc + -946.8));
            break;
        case 123:
            imp = fabs((-228.2 * adc + 4909734)/(adc + -947.8));
            break;
        case 124:
            imp = fabs((-157.0 * adc + 4762861)/(adc + -956.8));
            break;
        case 125:
            imp = fabs((-215.8 * adc + 4943174)/(adc + -952.1));
            break;
        case 126:
            imp = fabs((-208.4 * adc + 4967626)/(adc + -949.9));
            break;
        case 127:
            imp = fabs((-205.7 * adc + 4997710)/(adc + -950.5));
            break;
        case 128:
            imp = fabs((-212.3 * adc + 5030581)/(adc + -951.6));
            break;
        case 129:
            imp = fabs((-168.6 * adc + 4941578)/(adc + -958.9));
            break;
        case 130:
            imp = fabs((-210.0 * adc + 5104807)/(adc + -951.4));
            break;
        case 131:
            imp = fabs((-161.7 * adc + 5005727)/(adc + -958.3));
            break;
        case 132:
            imp = fabs((-224.1 * adc + 5218832)/(adc + -948.2));
            break;
        case 133:
            imp = fabs((-175.4 * adc + 5118819)/(adc + -955.6));
            break;
        case 134:
            imp = fabs((-268.7 * adc + 5401719)/(adc + -945.7));
            break;
        case 135:
            imp = fabs((-240.4 * adc + 5388218)/(adc + -944.6));
            break;
        case 136:
            imp = fabs((-195.8 * adc + 5290889)/(adc + -952.2));
            break;
        case 137:
            imp = fabs((-191.0 * adc + 5308465)/(adc + -954.6));
            break;
        case 138:
            imp = fabs((-258.4 * adc + 5541116)/(adc + -943.6));
            break;
        case 139:
            imp = fabs((-209.4 * adc + 5435911)/(adc + -951.6));
            break;
        case 140:
            imp = fabs((-136.9 * adc + 5265329)/(adc + -963.4));
            break;
        case 141:
            imp = fabs((-211.1 * adc + 5518302)/(adc + -951.5));
            break;
        case 142:
            imp = fabs((-182.4 * adc + 5469657)/(adc + -955.7));
            break;
        case 143:
            imp = fabs((-186.8 * adc + 5515127)/(adc + -957.0));
            break;
        case 144:
            imp = fabs((-141.8 * adc + 5413509)/(adc + -961.6));
            break;
        case 145:
            imp = fabs((-165.2 * adc + 5515469)/(adc + -958.5));
            break;
        case 146:
            imp = fabs((-220.4 * adc + 5700340)/(adc + -953.1));
            break;
        case 147:
            imp = fabs((-225.1 * adc + 5755939)/(adc + -950.7));
            break;
        case 148:
            imp = fabs((-205.3 * adc + 5747299)/(adc + -951.5));
            break;
        case 149:
            imp = fabs((-194.9 * adc + 5744681)/(adc + -954.8));
            break;
        case 150:
            imp = fabs((-195.8 * adc + 5776475)/(adc + -956.3));
            break;
        case 151:
            imp = fabs((-218.1 * adc + 5890913)/(adc + -951.1));
            break;
        case 152:
            imp = fabs((-235.3 * adc + 5982119)/(adc + -947.6));
            break;
        case 153:
            imp = fabs((-216.1 * adc + 5957038)/(adc + -952.4));
            break;
        case 154:
            imp = fabs((-218.0 * adc + 5994975)/(adc + -952.6));
            break;
        case 155:
            imp = fabs((-248.3 * adc + 6133016)/(adc + -946.3));
            break;
        case 156:
            imp = fabs((-206.9 * adc + 6046108)/(adc + -952.6));
            break;
        case 157:
            imp = fabs((-179.6 * adc + 5992265)/(adc + -957.7));
            break;
        case 158:
            imp = fabs((-234.7 * adc + 6196026)/(adc + -950.7));
            break;
        case 159:
            imp = fabs((-267.7 * adc + 6342616)/(adc + -943.1));
            break;
        case 160:
            imp = fabs((-194.3 * adc + 6126755)/(adc + -956.7));
            break;
        case 161:
            imp = fabs((-265.4 * adc + 6389962)/(adc + -944.0));
            break;
        case 162:
            imp = fabs((-233.5 * adc + 6329858)/(adc + -949.0));
            break;
        case 163:
            imp = fabs((-276.1 * adc + 6500423)/(adc + -941.4));
            break;
        case 164:
            imp = fabs((-238.8 * adc + 6405202)/(adc + -950.8));
            break;
        case 165:
            imp = fabs((-225.2 * adc + 6403455)/(adc + -953.0));
            break;
        case 166:
            imp = fabs((-234.6 * adc + 6480451)/(adc + -950.1));
            break;
        case 167:
            imp = fabs((-285.3 * adc + 6682935)/(adc + -939.6));
            break;
        case 168:
            imp = fabs((-281.9 * adc + 6701654)/(adc + -943.4));
            break;
        case 169:
            imp = fabs((-247.5 * adc + 6627781)/(adc + -948.8));
            break;
        case 170:
            imp = fabs((-249.3 * adc + 6673510)/(adc + -948.2));
            break;
        case 171:
            imp = fabs((-234.6 * adc + 6665653)/(adc + -950.3));
            break;
        case 172:
            imp = fabs((-267.6 * adc + 6809279)/(adc + -944.5));
            break;
        case 173:
            imp = fabs((-261.3 * adc + 6818411)/(adc + -946.8));
            break;
        case 174:
            imp = fabs((-285.0 * adc + 6946890)/(adc + -940.2));
            break;
        case 175:
            imp = fabs((-175.1 * adc + 6668866)/(adc + -955.4));
            break;
        case 176:
            imp = fabs((-194.4 * adc + 6728853)/(adc + -955.4));
            break;
        case 177:
            imp = fabs((-176.1 * adc + 6732431)/(adc + -954.4));
            break;
        case 178:
            imp = fabs((-193.7 * adc + 6808185)/(adc + -954.9));
            break;
        case 179:
            imp = fabs((-205.0 * adc + 6888415)/(adc + -952.0));
            break;
        case 180:
            imp = fabs((-178.9 * adc + 6858829)/(adc + -953.4));
            break;
        case 181:
            imp = fabs((-249.9 * adc + 7067581)/(adc + -950.0));
            break;
        case 182:
            imp = fabs((-191.7 * adc + 6969840)/(adc + -953.0));
            break;
        case 183:
            imp = fabs((-225.5 * adc + 7081568)/(adc + -951.5));
            break;
        case 184:
            imp = fabs((-188.9 * adc + 7018789)/(adc + -955.3));
            break;
        case 185:
            imp = fabs((-202.9 * adc + 7079615)/(adc + -956.5));
            break;
        case 186:
            imp = fabs((-240.1 * adc + 7231943)/(adc + -951.6));
            break;
        case 187:
            imp = fabs((-192.7 * adc + 7150639)/(adc + -953.0));
            break;
        case 188:
            imp = fabs((-215.6 * adc + 7228764)/(adc + -954.8));
            break;
        case 189:
            imp = fabs((-190.4 * adc + 7205430)/(adc + -955.0));
            break;
        case 190:
            imp = fabs((-188.2 * adc + 7241810)/(adc + -955.2));
            break;
        case 191:
            imp = fabs((-227.6 * adc + 7378546)/(adc + -952.9));
            break;
        case 192:
            imp = fabs((-188.1 * adc + 7312871)/(adc + -952.5));
            break;
        case 193:
            imp = fabs((-183.0 * adc + 7337085)/(adc + -953.2));
            break;
        case 194:
            imp = fabs((-238.1 * adc + 7503167)/(adc + -951.9));
            break;
        case 195:
            imp = fabs((-215.0 * adc + 7492122)/(adc + -951.6));
            break;
        case 196:
            imp = fabs((-216.4 * adc + 7530468)/(adc + -952.2));
            break;
        case 197:
            imp = fabs((-205.9 * adc + 7531846)/(adc + -953.4));
            break;
        case 198:
            imp = fabs((-184.6 * adc + 7513809)/(adc + -956.0));
            break;
        case 199:
            imp = fabs((-177.0 * adc + 7532986)/(adc + -955.9));
            break;
        case 200:
            imp = fabs((-166.7 * adc + 7544113)/(adc + -955.8));
            break;
        case 201:
            imp = fabs((-216.1 * adc + 7695543)/(adc + -955.2));
            break;
        case 202:
            imp = fabs((-218.6 * adc + 7756464)/(adc + -953.5));
            break;
        case 203:
            imp = fabs((-229.2 * adc + 7819558)/(adc + -952.4));
            break;
        case 204:
            imp = fabs((-209.8 * adc + 7814501)/(adc + -953.2));
            break;
        case 205:
            imp = fabs((-250.3 * adc + 7960766)/(adc + -949.9));
            break;
        case 206:
            imp = fabs((-221.8 * adc + 7925682)/(adc + -951.3));
            break;
        case 207:
            imp = fabs((-194.0 * adc + 7882071)/(adc + -953.0));
            break;
        case 208:
            imp = fabs((-209.2 * adc + 7929265)/(adc + -955.6));
            break;
        case 209:
            imp = fabs((-211.4 * adc + 7983495)/(adc + -952.9));
            break;
        case 210:
            imp = fabs((-216.4 * adc + 8039623)/(adc + -952.2));
            break;
        case 211:
            imp = fabs((-223.9 * adc + 8090756)/(adc + -952.6));
            break;
        case 212:
            imp = fabs((-206.1 * adc + 8081673)/(adc + -953.8));
            break;
        case 213:
            imp = fabs((-270.7 * adc + 8291841)/(adc + -950.0));
            break;
        case 214:
            imp = fabs((-228.7 * adc + 8211243)/(adc + -952.5));
            break;
        case 215:
            imp = fabs((-231.0 * adc + 8246651)/(adc + -953.8));
            break;
        case 216:
            imp = fabs((-211.5 * adc + 8245934)/(adc + -953.0));
            break;
        case 217:
            imp = fabs((-191.8 * adc + 8230348)/(adc + -954.4));
            break;
        case 218:
            imp = fabs((-241.2 * adc + 8408692)/(adc + -951.9));
            break;
        case 219:
            imp = fabs((-205.6 * adc + 8342958)/(adc + -954.0));
            break;
        case 220:
            imp = fabs((-272.0 * adc + 8555537)/(adc + -950.3));
            break;
        case 221:
            imp = fabs((-177.2 * adc + 8327033)/(adc + -957.0));
            break;
        case 222:
            imp = fabs((-204.8 * adc + 8438771)/(adc + -955.3));
            break;
        case 223:
            imp = fabs((-220.1 * adc + 8534724)/(adc + -952.0));
            break;
        case 224:
            imp = fabs((-247.4 * adc + 8630474)/(adc + -950.9));
            break;
        case 225:
            imp = fabs((-207.1 * adc + 8556451)/(adc + -952.6));
            break;
        case 226:
            imp = fabs((-192.1 * adc + 8546386)/(adc + -955.4));
            break;
        case 227:
            imp = fabs((-217.2 * adc + 8645660)/(adc + -954.5));
            break;
        case 228:
            imp = fabs((-236.5 * adc + 8754213)/(adc + -950.5));
            break;
        case 229:
            imp = fabs((-229.3 * adc + 8765809)/(adc + -951.6));
            break;
        case 230:
            imp = fabs((-195.0 * adc + 8703013)/(adc + -955.2));
            break;
        case 231:
            imp = fabs((-211.7 * adc + 8787530)/(adc + -953.0));
            break;
        case 232:
            imp = fabs((-219.5 * adc + 8851916)/(adc + -952.8));
            break;
        case 233:
            imp = fabs((-254.1 * adc + 8989380)/(adc + -950.2));
            break;
        case 234:
            imp = fabs((-230.1 * adc + 8952957)/(adc + -953.4));
            break;
        case 235:
            imp = fabs((-276.5 * adc + 9119719)/(adc + -950.1));
            break;
        case 236:
            imp = fabs((-230.5 * adc + 9042607)/(adc + -950.5));
            break;
        case 237:
            imp = fabs((-249.2 * adc + 9114696)/(adc + -950.3));
            break;
        case 238:
            imp = fabs((-210.1 * adc + 9030317)/(adc + -956.1));
            break;
        case 239:
            imp = fabs((-244.3 * adc + 9171573)/(adc + -952.4));
            break;
        case 240:
            imp = fabs((-239.3 * adc + 9179623)/(adc + -953.0));
            break;
        case 241:
            imp = fabs((-242.5 * adc + 9239591)/(adc + -951.1));
            break;
        case 242:
            imp = fabs((-202.0 * adc + 9135697)/(adc + -956.6));
            break;
        case 243:
            imp = fabs((-223.4 * adc + 9254021)/(adc + -953.0));
            break;
        case 244:
            imp = fabs((-241.8 * adc + 9335864)/(adc + -953.1));
            break;
        case 245:
            imp = fabs((-220.5 * adc + 9319053)/(adc + -953.8));
            break;
        case 246:
            imp = fabs((-235.2 * adc + 9397354)/(adc + -953.8));
            break;
        case 247:
            imp = fabs((-265.1 * adc + 9521566)/(adc + -950.3));
            break;
        case 248:
            imp = fabs((-214.5 * adc + 9451345)/(adc + -951.9));
            break;
        case 249:
            imp = fabs((-219.8 * adc + 9457164)/(adc + -954.7));
            break;
        case 250:
            imp = fabs((-17.0 * adc + 9055774)/(adc + -958.9));
            break;
        case 251:
            imp = fabs((85.9 * adc + 8857559)/(adc + -961.5));
            break;
        case 252:
            imp = fabs((37.4 * adc + 8981620)/(adc + -963.2));
            break;
        case 253:
            imp = fabs((-409.3 * adc + 10071326)/(adc + -948.2));
            break;
        case 254:
            imp = fabs((-192.9 * adc + 9587759)/(adc + -956.0));
            break;
       }
       return imp;
}
