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
            imp = fabs((-177.4 * adc + 327963)/(adc + -991.5));
            break;
        case 3:
            imp = fabs((-167.9 * adc + 350809)/(adc + -1026.3));
            break;
        case 4:
            imp = fabs((-188.4 * adc + 430471)/(adc + -946.5));
            break;
        case 5:
            imp = fabs((-292.8 * adc + 715406)/(adc + -535.8));
            break;
        case 6:
            imp = fabs((-454.6 * adc + 1171570)/(adc + 92.7));
            break;
        case 7:
            imp = fabs((-415.4 * adc + 1126990)/(adc + -147.8));
            break;
        case 8:
            imp = fabs((-305.8 * adc + 874825)/(adc + -671.9));
            break;
        case 9:
            imp = fabs((-373.0 * adc + 1109827)/(adc + -427.0));
            break;
        case 10:
            imp = fabs((-292.8 * adc + 921306)/(adc + -751.6));
            break;
        case 11:
            imp = fabs((-313.2 * adc + 1022744)/(adc + -704.3));
            break;
        case 12:
            imp = fabs((-207.1 * adc + 767415)/(adc + -943.9));
            break;
        case 13:
            imp = fabs((-227.8 * adc + 855186)/(adc + -916.8));
            break;
        case 14:
            imp = fabs((-250.4 * adc + 955105)/(adc + -879.9));
            break;
        case 15:
            imp = fabs((-274.3 * adc + 1059762)/(adc + -846.5));
            break;
        case 16:
            imp = fabs((-322.2 * adc + 1229249)/(adc + -767.9));
            break;
        case 17:
            imp = fabs((-248.8 * adc + 1051713)/(adc + -902.0));
            break;
        case 18:
            imp = fabs((-242.1 * adc + 1073692)/(adc + -901.7));
            break;
        case 19:
            imp = fabs((-232.3 * adc + 1078445)/(adc + -917.3));
            break;
        case 20:
            imp = fabs((-268.7 * adc + 1221124)/(adc + -874.6));
            break;
        case 21:
            imp = fabs((-270.5 * adc + 1259363)/(adc + -882.1));
            break;
        case 22:
            imp = fabs((-260.3 * adc + 1268816)/(adc + -891.8));
            break;
        case 23:
            imp = fabs((-193.3 * adc + 1121196)/(adc + -961.6));
            break;
        case 24:
            imp = fabs((-216.0 * adc + 1219090)/(adc + -944.5));
            break;
        case 25:
            imp = fabs((-216.9 * adc + 1256479)/(adc + -948.8));
            break;
        case 26:
            imp = fabs((-220.1 * adc + 1301628)/(adc + -946.4));
            break;
        case 27:
            imp = fabs((-215.7 * adc + 1327043)/(adc + -948.1));
            break;
        case 28:
            imp = fabs((-207.4 * adc + 1342391)/(adc + -953.8));
            break;
        case 29:
            imp = fabs((-221.9 * adc + 1415655)/(adc + -944.6));
            break;
        case 30:
            imp = fabs((-218.1 * adc + 1441652)/(adc + -950.1));
            break;
        case 31:
            imp = fabs((-246.9 * adc + 1557031)/(adc + -933.1));
            break;
        case 32:
            imp = fabs((-242.4 * adc + 1568224)/(adc + -930.6));
            break;
        case 33:
            imp = fabs((-222.2 * adc + 1549306)/(adc + -948.3));
            break;
        case 34:
            imp = fabs((-174.1 * adc + 1476210)/(adc + -959.7));
            break;
        case 35:
            imp = fabs((-275.9 * adc + 1757269)/(adc + -932.9));
            break;
        case 36:
            imp = fabs((-127.2 * adc + 1432180)/(adc + -973.3));
            break;
        case 37:
            imp = fabs((-217.2 * adc + 1700094)/(adc + -942.0));
            break;
        case 38:
            imp = fabs((-203.7 * adc + 1693412)/(adc + -953.1));
            break;
        case 39:
            imp = fabs((-147.8 * adc + 1583536)/(adc + -969.6));
            break;
        case 40:
            imp = fabs((-280.2 * adc + 1968879)/(adc + -923.6));
            break;
        case 41:
            imp = fabs((-171.3 * adc + 1716676)/(adc + -963.0));
            break;
        case 42:
            imp = fabs((-230.8 * adc + 1917308)/(adc + -941.4));
            break;
        case 43:
            imp = fabs((-250.8 * adc + 2008217)/(adc + -935.3));
            break;
        case 44:
            imp = fabs((-176.7 * adc + 1836664)/(adc + -962.8));
            break;
        case 45:
            imp = fabs((-258.1 * adc + 2092043)/(adc + -935.8));
            break;
        case 46:
            imp = fabs((-247.5 * adc + 2106878)/(adc + -935.3));
            break;
        case 47:
            imp = fabs((-177.3 * adc + 1942246)/(adc + -961.2));
            break;
        case 48:
            imp = fabs((-242.2 * adc + 2141083)/(adc + -944.6));
            break;
        case 49:
            imp = fabs((-236.2 * adc + 2171253)/(adc + -938.6));
            break;
        case 50:
            imp = fabs((-244.4 * adc + 2237985)/(adc + -934.0));
            break;
        case 51:
            imp = fabs((-292.3 * adc + 2391210)/(adc + -929.0));
            break;
        case 52:
            imp = fabs((-249.2 * adc + 2298438)/(adc + -943.2));
            break;
        case 53:
            imp = fabs((-157.7 * adc + 2106765)/(adc + -966.6));
            break;
        case 54:
            imp = fabs((-137.1 * adc + 2091030)/(adc + -970.8));
            break;
        case 55:
            imp = fabs((-293.9 * adc + 2529357)/(adc + -930.4));
            break;
        case 56:
            imp = fabs((-201.7 * adc + 2341241)/(adc + -951.0));
            break;
        case 57:
            imp = fabs((-111.3 * adc + 2144340)/(adc + -972.9));
            break;
        case 58:
            imp = fabs((-216.2 * adc + 2428894)/(adc + -953.8));
            break;
        case 59:
            imp = fabs((-270.7 * adc + 2636516)/(adc + -935.8));
            break;
        case 60:
            imp = fabs((-231.2 * adc + 2568331)/(adc + -944.9));
            break;
        case 61:
            imp = fabs((-236.1 * adc + 2594090)/(adc + -949.2));
            break;
        case 62:
            imp = fabs((-217.3 * adc + 2590554)/(adc + -953.2));
            break;
        case 63:
            imp = fabs((-267.3 * adc + 2772579)/(adc + -934.5));
            break;
        case 64:
            imp = fabs((-217.2 * adc + 2644639)/(adc + -948.7));
            break;
        case 65:
            imp = fabs((-247.7 * adc + 2781574)/(adc + -940.5));
            break;
        case 66:
            imp = fabs((-254.3 * adc + 2817956)/(adc + -946.2));
            break;
        case 67:
            imp = fabs((-191.6 * adc + 2691180)/(adc + -955.2));
            break;
        case 68:
            imp = fabs((-231.6 * adc + 2838118)/(adc + -943.6));
            break;
        case 69:
            imp = fabs((-306.9 * adc + 3098088)/(adc + -923.9));
            break;
        case 70:
            imp = fabs((-198.0 * adc + 2797702)/(adc + -959.3));
            break;
        case 71:
            imp = fabs((-190.5 * adc + 2812619)/(adc + -964.6));
            break;
        case 72:
            imp = fabs((-127.8 * adc + 2792661)/(adc + -955.5));
            break;
        case 73:
            imp = fabs((169.9 * adc + 2213183)/(adc + -984.8));
            break;
        case 74:
            imp = fabs((-1.7 * adc + 2605755)/(adc + -966.1));
            break;
        case 75:
            imp = fabs((-230.8 * adc + 3089171)/(adc + -949.5));
            break;
        case 76:
            imp = fabs((-398.5 * adc + 3452599)/(adc + -935.7));
            break;
        case 77:
            imp = fabs((-59.2 * adc + 2841849)/(adc + -960.5));
            break;
        case 78:
            imp = fabs((128.5 * adc + 2496868)/(adc + -975.6));
            break;
        case 79:
            imp = fabs((7.5 * adc + 2720793)/(adc + -973.2));
            break;
        case 80:
            imp = fabs((-80.6 * adc + 2953668)/(adc + -962.1));
            break;
        case 81:
            imp = fabs((-196.0 * adc + 3290571)/(adc + -943.0));
            break;
        case 82:
            imp = fabs((-26.0 * adc + 2946042)/(adc + -960.9));
            break;
        case 83:
            imp = fabs((-52.3 * adc + 3023906)/(adc + -958.5));
            break;
        case 84:
            imp = fabs((-182.0 * adc + 3340954)/(adc + -945.9));
            break;
        case 85:
            imp = fabs((-140.5 * adc + 3254623)/(adc + -963.6));
            break;
        case 86:
            imp = fabs((-194.3 * adc + 3408952)/(adc + -954.0));
            break;
        case 87:
            imp = fabs((65.3 * adc + 2940467)/(adc + -966.2));
            break;
        case 88:
            imp = fabs((50.2 * adc + 3019024)/(adc + -963.4));
            break;
        case 89:
            imp = fabs((-365.1 * adc + 3922116)/(adc + -930.9));
            break;
        case 90:
            imp = fabs((-281.9 * adc + 3786918)/(adc + -940.1));
            break;
        case 91:
            imp = fabs((-135.3 * adc + 3490731)/(adc + -954.2));
            break;
        case 92:
            imp = fabs((-155.3 * adc + 3579968)/(adc + -951.0));
            break;
        case 93:
            imp = fabs((-94.6 * adc + 3482275)/(adc + -955.7));
            break;
        case 94:
            imp = fabs((-288.2 * adc + 3974814)/(adc + -934.4));
            break;
        case 95:
            imp = fabs((-256.3 * adc + 3920263)/(adc + -942.6));
            break;
        case 96:
            imp = fabs((-291.6 * adc + 3992861)/(adc + -944.3));
            break;
        case 97:
            imp = fabs((97.8 * adc + 3136494)/(adc + -986.1));
            break;
        case 98:
            imp = fabs((30.2 * adc + 3369857)/(adc + -967.1));
            break;
        case 99:
            imp = fabs((-134.7 * adc + 3790267)/(adc + -950.1));
            break;
        case 100:
            imp = fabs((-316.6 * adc + 4240197)/(adc + -930.3));
            break;
        case 101:
            imp = fabs((-150.5 * adc + 3874956)/(adc + -954.3));
            break;
        case 102:
            imp = fabs((-63.2 * adc + 3726431)/(adc + -962.7));
            break;
        case 103:
            imp = fabs((95.4 * adc + 3394398)/(adc + -978.0));
            break;
        case 104:
            imp = fabs((-208.2 * adc + 4115161)/(adc + -945.5));
            break;
        case 105:
            imp = fabs((-283.5 * adc + 4319657)/(adc + -939.8));
            break;
        case 106:
            imp = fabs((-257.1 * adc + 4341628)/(adc + -939.1));
            break;
        case 107:
            imp = fabs((-82.4 * adc + 3973063)/(adc + -958.7));
            break;
        case 108:
            imp = fabs((-0.4 * adc + 3745582)/(adc + -975.3));
            break;
        case 109:
            imp = fabs((-26.5 * adc + 3843207)/(adc + -969.6));
            break;
        case 110:
            imp = fabs((-9.3 * adc + 3846058)/(adc + -973.9));
            break;
        case 111:
            imp = fabs((-312.2 * adc + 4660654)/(adc + -933.5));
            break;
        case 112:
            imp = fabs((-290.7 * adc + 4626091)/(adc + -934.4));
            break;
        case 113:
            imp = fabs((-330.0 * adc + 4740683)/(adc + -930.5));
            break;
        case 114:
            imp = fabs((33.1 * adc + 3892088)/(adc + -973.3));
            break;
        case 115:
            imp = fabs((86.8 * adc + 3769387)/(adc + -983.3));
            break;
        case 116:
            imp = fabs((28.1 * adc + 3905289)/(adc + -986.5));
            break;
        case 117:
            imp = fabs((-273.4 * adc + 4776051)/(adc + -937.4));
            break;
        case 118:
            imp = fabs((-297.3 * adc + 4867991)/(adc + -934.5));
            break;
        case 119:
            imp = fabs((-319.8 * adc + 4947717)/(adc + -930.8));
            break;
        case 120:
            imp = fabs((-178.0 * adc + 4651525)/(adc + -945.7));
            break;
        case 121:
            imp = fabs((12.2 * adc + 4191618)/(adc + -971.6));
            break;
        case 122:
            imp = fabs((-156.8 * adc + 4618798)/(adc + -958.4));
            break;
        case 123:
            imp = fabs((-255.7 * adc + 4889407)/(adc + -950.5));
            break;
        case 124:
            imp = fabs((-257.5 * adc + 4972765)/(adc + -943.1));
            break;
        case 125:
            imp = fabs((-257.3 * adc + 5038520)/(adc + -933.6));
            break;
        case 126:
            imp = fabs((-82.0 * adc + 4609251)/(adc + -956.6));
            break;
        case 127:
            imp = fabs((27.8 * adc + 4336963)/(adc + -976.8));
            break;
        case 128:
            imp = fabs((-211.9 * adc + 5014770)/(adc + -943.3));
            break;
        case 129:
            imp = fabs((-361.5 * adc + 5388090)/(adc + -933.3));
            break;
        case 130:
            imp = fabs((-178.3 * adc + 4893703)/(adc + -967.9));
            break;
        case 131:
            imp = fabs((-320.7 * adc + 5414422)/(adc + -929.6));
            break;
        case 132:
            imp = fabs((-53.6 * adc + 4738997)/(adc + -961.9));
            break;
        case 133:
            imp = fabs((-62.1 * adc + 4797826)/(adc + -959.2));
            break;
        case 134:
            imp = fabs((-360.8 * adc + 5638048)/(adc + -922.5));
            break;
        case 135:
            imp = fabs((-378.9 * adc + 5677353)/(adc + -929.6));
            break;
        case 136:
            imp = fabs((-305.0 * adc + 5502962)/(adc + -942.9));
            break;
        case 137:
            imp = fabs((-29.6 * adc + 4843143)/(adc + -970.0));
            break;
        case 138:
            imp = fabs((-138.3 * adc + 5164150)/(adc + -956.4));
            break;
        case 139:
            imp = fabs((-119.5 * adc + 5180774)/(adc + -951.3));
            break;
        case 140:
            imp = fabs((-221.4 * adc + 5470142)/(adc + -942.7));
            break;
        case 141:
            imp = fabs((-353.4 * adc + 5863986)/(adc + -925.1));
            break;
        case 142:
            imp = fabs((-193.1 * adc + 5431809)/(adc + -954.7));
            break;
        case 143:
            imp = fabs((-206.4 * adc + 5495354)/(adc + -956.6));
            break;
        case 144:
            imp = fabs((-41.1 * adc + 5043077)/(adc + -981.4));
            break;
        case 145:
            imp = fabs((2.6 * adc + 4984613)/(adc + -981.8));
            break;
        case 146:
            imp = fabs((-56.8 * adc + 5194148)/(adc + -970.1));
            break;
        case 147:
            imp = fabs((-306.2 * adc + 5937452)/(adc + -936.3));
            break;
        case 148:
            imp = fabs((-350.8 * adc + 6121724)/(adc + -925.4));
            break;
        case 149:
            imp = fabs((-470.2 * adc + 6481038)/(adc + -912.5));
            break;
        case 150:
            imp = fabs((-196.1 * adc + 5731472)/(adc + -954.1));
            break;
        case 151:
            imp = fabs((-158.5 * adc + 5660438)/(adc + -958.7));
            break;
        case 152:
            imp = fabs((-37.6 * adc + 5319059)/(adc + -980.6));
            break;
        case 153:
            imp = fabs((-212.8 * adc + 5898003)/(adc + -947.5));
            break;
        case 154:
            imp = fabs((-350.2 * adc + 6316641)/(adc + -931.3));
            break;
        case 155:
            imp = fabs((-505.3 * adc + 6870943)/(adc + -897.9));
            break;
        case 156:
            imp = fabs((-174.0 * adc + 5906128)/(adc + -949.8));
            break;
        case 157:
            imp = fabs((-150.0 * adc + 5863394)/(adc + -954.3));
            break;
        case 158:
            imp = fabs((-132.8 * adc + 5805378)/(adc + -966.1));
            break;
        case 159:
            imp = fabs((-179.0 * adc + 5957808)/(adc + -966.2));
            break;
        case 160:
            imp = fabs((-264.9 * adc + 6236141)/(adc + -951.7));
            break;
        case 161:
            imp = fabs((-249.0 * adc + 6261507)/(adc + -949.3));
            break;
        case 162:
            imp = fabs((-292.4 * adc + 6478883)/(adc + -934.1));
            break;
        case 163:
            imp = fabs((-433.6 * adc + 6953608)/(adc + -908.9));
            break;
        case 164:
            imp = fabs((-297.8 * adc + 6552816)/(adc + -931.7));
            break;
        case 165:
            imp = fabs((-291.4 * adc + 6585653)/(adc + -930.9));
            break;
        case 166:
            imp = fabs((36.6 * adc + 5575225)/(adc + -992.7));
            break;
        case 167:
            imp = fabs((-315.2 * adc + 6680141)/(adc + -939.3));
            break;
        case 168:
            imp = fabs((-392.1 * adc + 6969603)/(adc + -927.0));
            break;
        case 169:
            imp = fabs((-332.7 * adc + 6825468)/(adc + -933.0));
            break;
        case 170:
            imp = fabs((-238.6 * adc + 6583820)/(adc + -944.2));
            break;
        case 171:
            imp = fabs((-164.4 * adc + 6424068)/(adc + -948.6));
            break;
        case 172:
            imp = fabs((-220.2 * adc + 6636449)/(adc + -937.5));
            break;
        case 173:
            imp = fabs((-208.0 * adc + 6593542)/(adc + -950.2));
            break;
        case 174:
            imp = fabs((-409.0 * adc + 7265405)/(adc + -918.4));
            break;
        case 175:
            imp = fabs((-229.4 * adc + 6720479)/(adc + -952.3));
            break;
        case 176:
            imp = fabs((-255.5 * adc + 6785438)/(adc + -958.4));
            break;
        case 177:
            imp = fabs((-126.1 * adc + 6507835)/(adc + -962.0));
            break;
        case 178:
            imp = fabs((-186.6 * adc + 6665227)/(adc + -960.9));
            break;
        case 179:
            imp = fabs((-74.9 * adc + 6435290)/(adc + -960.6));
            break;
        case 180:
            imp = fabs((-40.8 * adc + 6434470)/(adc + -962.3));
            break;
        case 181:
            imp = fabs((-131.2 * adc + 6731786)/(adc + -951.5));
            break;
        case 182:
            imp = fabs((-335.6 * adc + 7267290)/(adc + -940.9));
            break;
        case 183:
            imp = fabs((-270.2 * adc + 7141215)/(adc + -944.5));
            break;
        case 184:
            imp = fabs((-283.1 * adc + 7206242)/(adc + -942.9));
            break;
        case 185:
            imp = fabs((-301.9 * adc + 7282798)/(adc + -944.0));
            break;
        case 186:
            imp = fabs((-219.2 * adc + 7080756)/(adc + -950.1));
            break;
        case 187:
            imp = fabs((-122.1 * adc + 6878248)/(adc + -958.0));
            break;
        case 188:
            imp = fabs((-38.3 * adc + 6684478)/(adc + -964.7));
            break;
        case 189:
            imp = fabs((-26.8 * adc + 6711921)/(adc + -965.5));
            break;
        case 190:
            imp = fabs((-141.2 * adc + 7055540)/(adc + -957.0));
            break;
        case 191:
            imp = fabs((-214.3 * adc + 7266616)/(adc + -952.6));
            break;
        case 192:
            imp = fabs((-353.3 * adc + 7672301)/(adc + -936.1));
            break;
        case 193:
            imp = fabs((-387.9 * adc + 7781622)/(adc + -937.3));
            break;
        case 194:
            imp = fabs((-206.6 * adc + 7365622)/(adc + -949.0));
            break;
        case 195:
            imp = fabs((-222.0 * adc + 7425037)/(adc + -950.5));
            break;
        case 196:
            imp = fabs((-106.5 * adc + 7097173)/(adc + -966.0));
            break;
        case 197:
            imp = fabs((-138.7 * adc + 7240538)/(adc + -959.7));
            break;
        case 198:
            imp = fabs((-84.2 * adc + 7184294)/(adc + -961.1));
            break;
        case 199:
            imp = fabs((-136.3 * adc + 7376208)/(adc + -953.8));
            break;
        case 200:
            imp = fabs((-128.6 * adc + 7362546)/(adc + -960.7));
            break;
        case 201:
            imp = fabs((-272.3 * adc + 7774911)/(adc + -947.9));
            break;
        case 202:
            imp = fabs((-443.8 * adc + 8239675)/(adc + -939.0));
            break;
        case 203:
            imp = fabs((-330.1 * adc + 8020319)/(adc + -939.9));
            break;
        case 204:
            imp = fabs((-287.4 * adc + 7918642)/(adc + -946.5));
            break;
        case 205:
            imp = fabs((-189.2 * adc + 7701562)/(adc + -948.8));
            break;
        case 206:
            imp = fabs((-194.3 * adc + 7813474)/(adc + -948.8));
            break;
        case 207:
            imp = fabs((6.5 * adc + 7250590)/(adc + -969.9));
            break;
        case 208:
            imp = fabs((65.8 * adc + 7121233)/(adc + -972.4));
            break;
        case 209:
            imp = fabs((-95.0 * adc + 7577218)/(adc + -959.6));
            break;
        case 210:
            imp = fabs((-161.5 * adc + 7777804)/(adc + -960.1));
            break;
        case 211:
            imp = fabs((-201.7 * adc + 7948244)/(adc + -951.7));
            break;
        case 212:
            imp = fabs((-295.4 * adc + 8207788)/(adc + -948.4));
            break;
        case 213:
            imp = fabs((-275.5 * adc + 8238965)/(adc + -945.5));
            break;
        case 214:
            imp = fabs((-229.2 * adc + 8154582)/(adc + -948.3));
            break;
        case 215:
            imp = fabs((-116.0 * adc + 7907117)/(adc + -953.3));
            break;
        case 216:
            imp = fabs((-160.9 * adc + 8042215)/(adc + -951.5));
            break;
        case 217:
            imp = fabs((-248.8 * adc + 8347738)/(adc + -941.5));
            break;
        case 218:
            imp = fabs((-185.4 * adc + 8154915)/(adc + -957.9));
            break;
        case 219:
            imp = fabs((-228.4 * adc + 8300233)/(adc + -954.1));
            break;
        case 220:
            imp = fabs((-270.7 * adc + 8410977)/(adc + -954.7));
            break;
        case 221:
            imp = fabs((-285.6 * adc + 8493592)/(adc + -953.5));
            break;
        case 222:
            imp = fabs((-186.0 * adc + 8257792)/(adc + -960.6));
            break;
        case 223:
            imp = fabs((-254.4 * adc + 8570410)/(adc + -945.2));
            break;
        case 224:
            imp = fabs((-229.3 * adc + 8543198)/(adc + -945.1));
            break;
        case 225:
            imp = fabs((-140.0 * adc + 8350663)/(adc + -946.7));
            break;
        case 226:
            imp = fabs((-109.9 * adc + 8291072)/(adc + -950.4));
            break;
        case 227:
            imp = fabs((-281.1 * adc + 8763711)/(adc + -945.3));
            break;
        case 228:
            imp = fabs((-266.2 * adc + 8729835)/(adc + -946.4));
            break;
        case 229:
            imp = fabs((-358.8 * adc + 8979079)/(adc + -947.1));
            break;
        case 230:
            imp = fabs((-252.7 * adc + 8770528)/(adc + -952.3));
            break;
        case 231:
            imp = fabs((-270.9 * adc + 8819716)/(adc + -955.5));
            break;
        case 232:
            imp = fabs((-214.6 * adc + 8739176)/(adc + -953.0));
            break;
        case 233:
            imp = fabs((-148.8 * adc + 8583593)/(adc + -960.4));
            break;
        case 234:
            imp = fabs((-158.2 * adc + 8617215)/(adc + -960.1));
            break;
        case 235:
            imp = fabs((-129.5 * adc + 8589599)/(adc + -957.7));
            break;
        case 236:
            imp = fabs((-103.1 * adc + 8609393)/(adc + -954.1));
            break;
        case 237:
            imp = fabs((-173.4 * adc + 8829916)/(adc + -948.9));
            break;
        case 238:
            imp = fabs((-223.5 * adc + 9015027)/(adc + -946.6));
            break;
        case 239:
            imp = fabs((-282.9 * adc + 9212849)/(adc + -945.0));
            break;
        case 240:
            imp = fabs((-326.6 * adc + 9323307)/(adc + -949.2));
            break;
        case 241:
            imp = fabs((-316.3 * adc + 9332939)/(adc + -950.5));
            break;
        case 242:
            imp = fabs((-319.5 * adc + 9391778)/(adc + -945.5));
            break;
        case 243:
            imp = fabs((-218.0 * adc + 9077188)/(adc + -958.2));
            break;
        case 244:
            imp = fabs((-188.3 * adc + 9032693)/(adc + -960.7));
            break;
        case 245:
            imp = fabs((-134.9 * adc + 8945801)/(adc + -962.1));
            break;
        case 246:
            imp = fabs((-110.7 * adc + 8931213)/(adc + -961.7));
            break;
        case 247:
            imp = fabs((-114.9 * adc + 9001895)/(adc + -960.5));
            break;
        case 248:
            imp = fabs((-343.4 * adc + 9704696)/(adc + -941.7));
            break;
        case 249:
            imp = fabs((-375.1 * adc + 9826237)/(adc + -940.0));
            break;
        case 250:
            imp = fabs((-432.0 * adc + 10064440)/(adc + -930.8));
            break;
        case 251:
            imp = fabs((4979.6 * adc + -2494553)/(adc + -1113.3));
            break;
        case 252:
            imp = fabs((70.4 * adc + 0)/(adc + -0.3));
            break;
        case 253:
            imp = fabs((5049.8 * adc + -2672913)/(adc + -1123.2));
            break;
        case 254:
            imp = fabs((4839.2 * adc + -2238383)/(adc + -1122.6));
            break;
       }
       return imp;
}
