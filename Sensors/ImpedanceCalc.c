/*
 * Created by Jared Brinkman
 * Date: 7/22/2022
 *
 * This file will change for every board that is calibrated.
 * Will hold 255 Impedance equations
 */

#include "ImpedanceCalc.h"

float ImpedanceCalc(uint8_t tapNumber, uint16_t adc) {
    float imp = 0;
    switch(tapNumber) {
        default:
              imp = 49999;
                  break;
        case 2:
           imp = fabs((-171.2 * adc + 356707)/(adc + -987.6));
               break;
       case 3:
           imp = fabs((-177.1 * adc + 402791)/(adc + -991.1));
           break;
       case 4:
           imp = fabs((-178.2 * adc + 439904)/(adc + -986.7));
           break;
       case 5:
           imp = fabs((-228.2 * adc + 594493)/(adc + -856.5));
           break;
       case 6:
           imp = fabs((-242.7 * adc + 666269)/(adc + -844.3));
           break;
       case 7:
           imp = fabs((-261.9 * adc + 753943)/(adc + -798.2));
           break;
       case 8:
           imp = fabs((-211.3 * adc + 659112)/(adc + -956.6));
           break;
       case 9:
           imp = fabs((-180.0 * adc + 620132)/(adc + -977.8));
           break;
       case 10:
           imp = fabs((-186.9 * adc + 669927)/(adc + -984.0));
           break;
       case 11:
           imp = fabs((-194.8 * adc + 741771)/(adc + -955.1));
           break;
       case 12:
           imp = fabs((-179.2 * adc + 739116)/(adc + -965.7));
           break;
       case 13:
           imp = fabs((-212.4 * adc + 850439)/(adc + -945.5));
           break;
       case 14:
           imp = fabs((-236.2 * adc + 936899)/(adc + -942.0));
           break;
       case 15:
           imp = fabs((-153.1 * adc + 796705)/(adc + -960.9));
           break;
       case 16:
           imp = fabs((-173.6 * adc + 864671)/(adc + -964.5));
           break;
       case 17:
           imp = fabs((-43.4 * adc + 629764)/(adc + -996.2));
           break;
       case 18:
           imp = fabs((-109.0 * adc + 804619)/(adc + -968.2));
           break;
       case 19:
           imp = fabs((-132.1 * adc + 866572)/(adc + -984.4));
           break;
       case 20:
           imp = fabs((-217.0 * adc + 1116522)/(adc + -934.6));
           break;
       case 21:
           imp = fabs((-281.2 * adc + 1281746)/(adc + -936.4));
           break;
       case 22:
           imp = fabs((-112.0 * adc + 993273)/(adc + -959.3));
           break;
       case 23:
           imp = fabs((-226.6 * adc + 1237125)/(adc + -937.9));
           break;
       case 24:
           imp = fabs((-189.7 * adc + 1198751)/(adc + -957.2));
           break;
       case 25:
           imp = fabs((-285.2 * adc + 1432551)/(adc + -935.3));
           break;
       case 26:
           imp = fabs((9.3 * adc + 846578)/(adc + -990.4));
           break;
       case 27:
           imp = fabs((-118.7 * adc + 1161835)/(adc + -962.7));
           break;
       case 28:
           imp = fabs((-176.6 * adc + 1313138)/(adc + -956.8));
           break;
       case 29:
           imp = fabs((-131.4 * adc + 1235505)/(adc + -971.7));
           break;
       case 30:
           imp = fabs((-200.8 * adc + 1435623)/(adc + -959.8));
           break;
       case 31:
           imp = fabs((-22.7 * adc + 1046295)/(adc + -997.7));
           break;
       case 32:
           imp = fabs((-215.6 * adc + 1506317)/(adc + -954.3));
           break;
       case 33:
           imp = fabs((-315.7 * adc + 1770823)/(adc + -936.9));
           break;
       case 34:
           imp = fabs((64.4 * adc + 1048633)/(adc + -984.0));
           break;
       case 35:
           imp = fabs((-248.9 * adc + 1748921)/(adc + -932.3));
           break;
       case 36:
           imp = fabs((-213.6 * adc + 1637295)/(adc + -968.7));
           break;
       case 37:
           imp = fabs((40.5 * adc + 1224864)/(adc + -978.0));
           break;
       case 38:
           imp = fabs((59.9 * adc + 1193705)/(adc + -980.4));
           break;
       case 39:
           imp = fabs((-340.6 * adc + 2049494)/(adc + -944.4));
           break;
       case 40:
           imp = fabs((-149.4 * adc + 1679551)/(adc + -966.5));
           break;
       case 41:
           imp = fabs((-413.9 * adc + 2323307)/(adc + -915.8));
           break;
       case 42:
           imp = fabs((98.4 * adc + 1262980)/(adc + -992.3));
           break;
       case 43:
           imp = fabs((-206.4 * adc + 1864416)/(adc + -973.4));
           break;
       case 44:
           imp = fabs((-380.2 * adc + 2339504)/(adc + -935.6));
           break;
       case 45:
           imp = fabs((-328.5 * adc + 2260187)/(adc + -934.9));
           break;
       case 46:
           imp = fabs((7.1 * adc + 1541137)/(adc + -989.2));
           break;
       case 47:
           imp = fabs((74.1 * adc + 1472078)/(adc + -989.9));
           break;
       case 48:
           imp = fabs((-458.5 * adc + 2713356)/(adc + -911.2));
           break;
       case 49:
           imp = fabs((-83.7 * adc + 1855235)/(adc + -960.4));
           break;
       case 50:
           imp = fabs((419.1 * adc + 1114068)/(adc + -978.2));
           break;
       case 51:
           imp = fabs((-523.6 * adc + 2725745)/(adc + -946.5));
           break;
       case 52:
           imp = fabs((-558.1 * adc + 2864753)/(adc + -943.4));
           break;
       case 53:
           imp = fabs((-425.2 * adc + 2689495)/(adc + -929.4));
           break;
       case 54:
           imp = fabs((-171.3 * adc + 2260109)/(adc + -963.9));
           break;
       case 55:
           imp = fabs((-27.9 * adc + 2078777)/(adc + -949.9));
           break;
       case 56:
           imp = fabs((-325.0 * adc + 2618991)/(adc + -950.7));
           break;
       case 57:
           imp = fabs((-619.5 * adc + 3215093)/(adc + -924.4));
           break;
       case 58:
           imp = fabs((-579.1 * adc + 3228841)/(adc + -923.8));
           break;
       case 59:
           imp = fabs((-271.0 * adc + 2553238)/(adc + -961.1));
           break;
       case 60:
           imp = fabs((-540.5 * adc + 3243686)/(adc + -925.3));
           break;
       case 61:
           imp = fabs((-437.0 * adc + 3087179)/(adc + -929.9));
           break;
       case 62:
           imp = fabs((-68.2 * adc + 2342868)/(adc + -951.1));
           break;
       case 63:
           imp = fabs((-111.8 * adc + 2563719)/(adc + -938.8));
           break;
       case 64:
           imp = fabs((-162.3 * adc + 2687181)/(adc + -934.6));
           break;
       case 65:
           imp = fabs((-186.8 * adc + 2627619)/(adc + -958.2));
           break;
       case 66:
           imp = fabs((-271.0 * adc + 2926954)/(adc + -952.8));
           break;
       case 67:
           imp = fabs((2.6 * adc + 2440490)/(adc + -960.0));
           break;
       case 68:
           imp = fabs((-599.1 * adc + 3692531)/(adc + -921.6));
           break;
       case 69:
           imp = fabs((175.0 * adc + 2471930)/(adc + -939.2));
           break;
       case 70:
           imp = fabs((-805.5 * adc + 3891639)/(adc + -944.3));
           break;
       case 71:
           imp = fabs((-2316.7 * adc + 6000648)/(adc + -932.8));
           break;
       case 72:
           imp = fabs((-1144.3 * adc + 4540788)/(adc + -926.5));
           break;
       case 73:
           imp = fabs((-3698.6 * adc + 8256667)/(adc + -907.6));
           break;
       case 74:
           imp = fabs((3241.6 * adc + -2034709)/(adc + -985.7));
           break;
       case 75:
           imp = fabs((4730.8 * adc + -4231753)/(adc + -1006.5));
           break;
       case 76:
           imp = fabs((149.3 * adc + 2611013)/(adc + -954.2));
           break;
       case 77:
           imp = fabs((-3753.4 * adc + 8639044)/(adc + -906.1));
           break;
       case 78:
           imp = fabs((-893.8 * adc + 4288005)/(adc + -941.9));
           break;
       case 79:
           imp = fabs((2318.7 * adc + -605449)/(adc + -978.6));
           break;
       case 80:
           imp = fabs((4109.0 * adc + -3296637)/(adc + -1003.8));
           break;
       case 81:
           imp = fabs((-239.2 * adc + 3260287)/(adc + -965.6));
           break;
       case 82:
           imp = fabs((-1417.0 * adc + 5354846)/(adc + -920.8));
           break;
       case 83:
           imp = fabs((4336.6 * adc + -3634021)/(adc + -1010.3));
           break;
       case 84:
           imp = fabs((-2523.8 * adc + 7182588)/(adc + -915.1));
           break;
       case 85:
           imp = fabs((-4348.5 * adc + 10003710)/(adc + -891.2));
           break;
       case 86:
           imp = fabs((1933.0 * adc + 206011)/(adc + -971.9));
           break;
       case 87:
           imp = fabs((-1793.7 * adc + 6165401)/(adc + -917.2));
           break;
       case 88:
           imp = fabs((2211.7 * adc + -371477)/(adc + -994.5));
           break;
       case 89:
           imp = fabs((183.2 * adc + 2810613)/(adc + -973.9));
           break;
       case 90:
           imp = fabs((-511.7 * adc + 4262854)/(adc + -929.2));
           break;
       case 91:
           imp = fabs((582.9 * adc + 2351867)/(adc + -973.7));
           break;
       case 92:
           imp = fabs((1223.4 * adc + 1415037)/(adc + -981.6));
           break;
       case 93:
           imp = fabs((-120.7 * adc + 3713817)/(adc + -935.2));
           break;
       case 94:
           imp = fabs((816.0 * adc + 1988772)/(adc + -982.8));
           break;
       case 95:
           imp = fabs((-1604.3 * adc + 6223576)/(adc + -931.2));
           break;
       case 96:
           imp = fabs((3481.9 * adc + -2144989)/(adc + -1006.7));
           break;
       case 97:
           imp = fabs((482.2 * adc + 2696376)/(adc + -976.3));
           break;
       case 98:
           imp = fabs((-841.9 * adc + 5106572)/(adc + -939.3));
           break;
       case 99:
           imp = fabs((1410.9 * adc + 1098439)/(adc + -990.7));
           break;
       case 100:
           imp = fabs((-884.9 * adc + 5247712)/(adc + -927.4));
           break;
       case 101:
           imp = fabs((1497.3 * adc + 1205680)/(adc + -975.4));
           break;
       case 102:
           imp = fabs((-2294.0 * adc + 7650423)/(adc + -924.5));
           break;
       case 103:
           imp = fabs((-3542.1 * adc + 9972959)/(adc + -893.1));
           break;
       case 104:
           imp = fabs((-2041.0 * adc + 7550328)/(adc + -904.9));
           break;
       case 105:
           imp = fabs((1078.0 * adc + 1854738)/(adc + -985.2));
           break;
       case 106:
           imp = fabs((3315.6 * adc + -1756551)/(adc + -1009.4));
           break;
       case 107:
           imp = fabs((-2937.7 * adc + 9149508)/(adc + -904.3));
           break;
       case 108:
           imp = fabs((4186.2 * adc + -3174017)/(adc + -1020.5));
           break;
       case 109:
           imp = fabs((-1517.9 * adc + 6582678)/(adc + -935.6));
           break;
       case 110:
           imp = fabs((2635.7 * adc + -541059)/(adc + -1000.2));
           break;
       case 111:
           imp = fabs((-921.9 * adc + 5572324)/(adc + -951.8));
           break;
       case 112:
           imp = fabs((2528.4 * adc + -331139)/(adc + -992.7));
           break;
       case 113:
           imp = fabs((-64.6 * adc + 4111183)/(adc + -967.1));
           break;
       case 114:
           imp = fabs((1962.9 * adc + 582531)/(adc + -994.5));
           break;
       case 115:
           imp = fabs((2676.9 * adc + -599179)/(adc + -1003.3));
           break;
       case 116:
           imp = fabs((3694.2 * adc + -2354432)/(adc + -1020.5));
           break;
       case 117:
           imp = fabs((-2989.5 * adc + 9891675)/(adc + -893.8));
           break;
       case 118:
           imp = fabs((-1375.3 * adc + 6703048)/(adc + -944.1));
           break;
       case 119:
           imp = fabs((819.9 * adc + 2907253)/(adc + -962.2));
           break;
       case 120:
           imp = fabs((1457.1 * adc + 1797453)/(adc + -979.1));
           break;
       case 121:
           imp = fabs((-334.9 * adc + 5149829)/(adc + -930.2));
           break;
       case 122:
           imp = fabs((-872.7 * adc + 5889662)/(adc + -949.2));
           break;
       case 123:
           imp = fabs((-2090.7 * adc + 8260499)/(adc + -923.3));
           break;
       case 124:
           imp = fabs((-3310.5 * adc + 10823474)/(adc + -884.3));
           break;
       case 125:
           imp = fabs((-3461.4 * adc + 11297525)/(adc + -878.4));
           break;
       case 126:
           imp = fabs((-292.4 * adc + 5018548)/(adc + -958.0));
           break;
       case 127:
           imp = fabs((2159.3 * adc + 600918)/(adc + -992.3));
           break;
       case 128:
           imp = fabs((1551.8 * adc + 1661925)/(adc + -993.4));
           break;
       case 129:
           imp = fabs((-316.3 * adc + 5428005)/(adc + -926.8));
           break;
       case 130:
           imp = fabs((-894.5 * adc + 6386018)/(adc + -948.7));
           break;
       case 131:
           imp = fabs((237.8 * adc + 4449123)/(adc + -951.2));
           break;
       case 132:
           imp = fabs((-2179.4 * adc + 8991975)/(adc + -916.9));
           break;
       case 133:
           imp = fabs((250.8 * adc + 4186826)/(adc + -978.6));
           break;
       case 134:
           imp = fabs((734.8 * adc + 3463918)/(adc + -973.5));
           break;
       case 135:
           imp = fabs((-1037.2 * adc + 6809873)/(adc + -949.0));
           break;
       case 136:
           imp = fabs((-3068.3 * adc + 10869113)/(adc + -889.4));
           break;
       case 137:
           imp = fabs((1029.2 * adc + 2985463)/(adc + -984.3));
           break;
       case 138:
           imp = fabs((2866.0 * adc + -543350)/(adc + -1014.8));
           break;
       case 139:
           imp = fabs((1303.8 * adc + 2608126)/(adc + -972.2));
           break;
       case 140:
           imp = fabs((2490.8 * adc + 279462)/(adc + -1007.1));
           break;
       case 141:
           imp = fabs((-584.8 * adc + 6304186)/(adc + -928.1));
           break;
       case 142:
           imp = fabs((-412.6 * adc + 6067288)/(adc + -937.2));
           break;
       case 143:
           imp = fabs((2432.2 * adc + 331150)/(adc + -1010.2));
           break;
       case 144:
           imp = fabs((-1918.8 * adc + 9139366)/(adc + -905.2));
           break;
       case 145:
           imp = fabs((-293.7 * adc + 5715563)/(adc + -959.5));
           break;
       case 146:
           imp = fabs((2736.4 * adc + -182435)/(adc + -1017.5));
           break;
       case 147:
           imp = fabs((-2108.2 * adc + 9679955)/(adc + -900.1));
           break;
       case 148:
           imp = fabs((2801.2 * adc + -263064)/(adc + -1021.5));
           break;
       case 149:
           imp = fabs((706.5 * adc + 3983242)/(adc + -961.6));
           break;
       case 150:
           imp = fabs((508.1 * adc + 4324331)/(adc + -981.1));
           break;
       case 151:
           imp = fabs((1632.9 * adc + 2213031)/(adc + -985.7));
           break;
       case 152:
           imp = fabs((359.4 * adc + 4692788)/(adc + -962.4));
           break;
       case 153:
           imp = fabs((-1790.0 * adc + 9435650)/(adc + -904.6));
           break;
       case 154:
           imp = fabs((861.1 * adc + 3896970)/(adc + -965.2));
           break;
       case 155:
           imp = fabs((1830.1 * adc + 1802446)/(adc + -1002.0));
           break;
       case 156:
           imp = fabs((-328.5 * adc + 6254013)/(adc + -958.5));
           break;
       case 157:
           imp = fabs((308.7 * adc + 5180561)/(adc + -947.6));
           break;
       case 158:
           imp = fabs((1641.7 * adc + 2260147)/(adc + -993.5));
           break;
       case 159:
           imp = fabs((-2724.6 * adc + 11502425)/(adc + -886.4));
           break;
       case 160:
           imp = fabs((74.2 * adc + 5659638)/(adc + -947.4));
           break;
       case 161:
           imp = fabs((2419.1 * adc + 716965)/(adc + -1013.0));
           break;
       case 162:
           imp = fabs((-521.5 * adc + 6831208)/(adc + -964.0));
           break;
       case 163:
           imp = fabs((2826.1 * adc + -7943)/(adc + -1025.8));
           break;
       case 164:
           imp = fabs((-410.0 * adc + 6987077)/(adc + -927.6));
           break;
       case 165:
           imp = fabs((841.5 * adc + 4340298)/(adc + -962.4));
           break;
       case 166:
           imp = fabs((-598.7 * adc + 7258681)/(adc + -949.6));
           break;
       case 167:
           imp = fabs((-1971.9 * adc + 10408867)/(adc + -896.8));
           break;
       case 168:
           imp = fabs((-91.6 * adc + 6444869)/(adc + -931.3));
           break;
       case 169:
           imp = fabs((-2121.0 * adc + 10825491)/(adc + -896.3));
           break;
       case 170:
           imp = fabs((2115.0 * adc + 1621096)/(adc + -1005.5));
           break;
       case 171:
           imp = fabs((-326.6 * adc + 7031332)/(adc + -932.3));
           break;
       case 172:
           imp = fabs((-1018.0 * adc + 8142326)/(adc + -937.9));
           break;
       case 173:
           imp = fabs((111.6 * adc + 6024030)/(adc + -944.1));
           break;
       case 174:
           imp = fabs((-27.0 * adc + 6628011)/(adc + -942.6));
           break;
       case 175:
           imp = fabs((628.3 * adc + 4916553)/(adc + -978.5));
           break;
       case 176:
           imp = fabs((-597.9 * adc + 7576373)/(adc + -947.4));
           break;
       case 177:
           imp = fabs((-963.2 * adc + 8494563)/(adc + -936.9));
           break;
       case 178:
           imp = fabs((-1478.9 * adc + 9258011)/(adc + -936.2));
           break;
       case 179:
           imp = fabs((-4084.2 * adc + 14768645)/(adc + -881.3));
           break;
       case 180:
           imp = fabs((-2535.6 * adc + 11861751)/(adc + -898.9));
           break;
       case 181:
           imp = fabs((-1313.8 * adc + 9432870)/(adc + -914.4));
           break;
       case 182:
           imp = fabs((946.1 * adc + 4473316)/(adc + -976.6));
           break;
       case 183:
           imp = fabs((1732.2 * adc + 2807008)/(adc + -1002.7));
           break;
       case 184:
           imp = fabs((-125.6 * adc + 6695679)/(adc + -974.9));
           break;
       case 185:
           imp = fabs((-1020.0 * adc + 8627255)/(adc + -937.2));
           break;
       case 186:
           imp = fabs((-260.3 * adc + 7233554)/(adc + -955.4));
           break;
       case 187:
           imp = fabs((-2382.4 * adc + 11496289)/(adc + -909.1));
           break;
       case 188:
           imp = fabs((1238.1 * adc + 4366521)/(adc + -968.1));
           break;
       case 189:
           imp = fabs((-1482.3 * adc + 10199842)/(adc + -910.0));
           break;
       case 190:
           imp = fabs((1412.5 * adc + 4140733)/(adc + -966.2));
           break;
       case 191:
           imp = fabs((1400.2 * adc + 4179995)/(adc + -971.9));
           break;
       case 192:
           imp = fabs((-4312.8 * adc + 15820536)/(adc + -873.2));
           break;
       case 193:
           imp = fabs((-2705.8 * adc + 12731166)/(adc + -893.9));
           break;
       case 194:
           imp = fabs((-352.3 * adc + 8035336)/(adc + -930.5));
           break;
       case 195:
           imp = fabs((-1907.4 * adc + 11014069)/(adc + -923.9));
           break;
       case 196:
           imp = fabs((-3270.9 * adc + 13852010)/(adc + -890.7));
           break;
       case 197:
           imp = fabs((-2862.1 * adc + 13452543)/(adc + -888.0));
           break;
       case 198:
           imp = fabs((1077.8 * adc + 4744808)/(adc + -991.2));
           break;
       case 199:
           imp = fabs((1055.3 * adc + 4936473)/(adc + -971.9));
           break;
       case 200:
           imp = fabs((-1636.3 * adc + 10465953)/(adc + -939.4));
           break;
       case 201:
           imp = fabs((-3118.6 * adc + 13780446)/(adc + -891.5));
           break;
       case 202:
           imp = fabs((1897.8 * adc + 3269676)/(adc + -992.2));
           break;
       case 203:
           imp = fabs((-1607.6 * adc + 10730214)/(adc + -927.1));
           break;
       case 204:
           imp = fabs((-4251.7 * adc + 16434154)/(adc + -880.4));
           break;
       case 205:
           imp = fabs((2673.9 * adc + 1436468)/(adc + -1027.2));
           break;
       case 206:
           imp = fabs((-3251.0 * adc + 14485825)/(adc + -884.3));
           break;
       case 207:
           imp = fabs((-1304.2 * adc + 10302016)/(adc + -928.7));
           break;
       case 208:
           imp = fabs((-1851.7 * adc + 11322263)/(adc + -930.6));
           break;
       case 209:
           imp = fabs((682.6 * adc + 5679198)/(adc + -987.4));
           break;
       case 210:
           imp = fabs((-1687.4 * adc + 11219138)/(adc + -934.6));
           break;
       case 211:
           imp = fabs((-1761.7 * adc + 11406509)/(adc + -933.3));
           break;
       case 212:
           imp = fabs((-3610.3 * adc + 15389288)/(adc + -881.9));
           break;
       case 213:
           imp = fabs((-2238.6 * adc + 12920536)/(adc + -892.3));
           break;
       case 214:
           imp = fabs((-202.8 * adc + 8500965)/(adc + -936.7));
           break;
       case 215:
           imp = fabs((-3060.4 * adc + 14328319)/(adc + -888.9));
           break;
       case 216:
           imp = fabs((-1663.4 * adc + 11802823)/(adc + -905.8));
           break;
       case 217:
           imp = fabs((673.4 * adc + 6678786)/(adc + -948.1));
           break;
       case 218:
           imp = fabs((231.1 * adc + 7056469)/(adc + -982.9));
           break;
       case 219:
           imp = fabs((-350.7 * adc + 8827106)/(adc + -947.8));
           break;
       case 220:
           imp = fabs((-509.7 * adc + 9215692)/(adc + -940.0));
           break;
       case 221:
           imp = fabs((1411.9 * adc + 4823988)/(adc + -989.7));
           break;
       case 222:
           imp = fabs((1151.8 * adc + 5761897)/(adc + -963.0));
           break;
       case 223:
           imp = fabs((-2974.5 * adc + 14834492)/(adc + -895.2));
           break;
       case 224:
           imp = fabs((-1148.0 * adc + 10599594)/(adc + -942.8));
           break;
       case 225:
           imp = fabs((-2206.7 * adc + 13059722)/(adc + -905.5));
           break;
       case 226:
           imp = fabs((-405.9 * adc + 9399233)/(adc + -942.9));
           break;
       case 227:
           imp = fabs((95.1 * adc + 8141376)/(adc + -943.8));
           break;
       case 228:
           imp = fabs((-1693.8 * adc + 12430097)/(adc + -906.5));
           break;
       case 229:
           imp = fabs((-171.7 * adc + 8497489)/(adc + -973.3));
           break;
       case 230:
           imp = fabs((1915.1 * adc + 4087193)/(adc + -993.3));
           break;
       case 231:
           imp = fabs((-2371.7 * adc + 13617667)/(adc + -897.1));
           break;
       case 232:
           imp = fabs((-1771.3 * adc + 12188883)/(adc + -928.7));
           break;
       case 233:
           imp = fabs((347.1 * adc + 7704377)/(adc + -977.4));
           break;
       case 234:
           imp = fabs((-931.3 * adc + 10862427)/(adc + -912.9));
           break;
       case 235:
           imp = fabs((-4155.2 * adc + 18008252)/(adc + -867.8));
           break;
       case 236:
           imp = fabs((-615.5 * adc + 10143825)/(adc + -924.9));
           break;
       case 237:
           imp = fabs((338.6 * adc + 7915185)/(adc + -968.1));
           break;
       case 238:
           imp = fabs((-3832.3 * adc + 17353341)/(adc + -881.5));
           break;
       case 239:
           imp = fabs((191.7 * adc + 8199234)/(adc + -952.5));
           break;
       case 240:
           imp = fabs((1212.2 * adc + 6031703)/(adc + -977.0));
           break;
       case 241:
           imp = fabs((-773.9 * adc + 10579411)/(adc + -931.8));
           break;
       case 242:
           imp = fabs((689.7 * adc + 7190853)/(adc + -976.4));
           break;
       case 243:
           imp = fabs((-844.7 * adc + 10663431)/(adc + -949.3));
           break;
       case 244:
           imp = fabs((-1059.2 * adc + 11109697)/(adc + -942.8));
           break;
       case 245:
           imp = fabs((877.2 * adc + 6845547)/(adc + -980.4));
           break;
       case 246:
           imp = fabs((104.9 * adc + 9242524)/(adc + -944.1));
           break;
       case 247:
           imp = fabs((30.2 * adc + 1)/(adc + 0.1));
           break;
       case 248:
           imp = fabs((1608.7 * adc + 5810006)/(adc + -976.4));
           break;
       case 249:
           imp = fabs((-1080.9 * adc + 11422120)/(adc + -920.2));
           break;
       case 250:
           imp = fabs((-2140.2 * adc + 13773266)/(adc + -909.7));
           break;
       case 251:
           imp = fabs((-532.7 * adc + 10169310)/(adc + -956.2));
           break;
       case 252:
           imp = fabs((2233.3 * adc + 5335052)/(adc + -968.9));
           break;
       case 253:
           imp = fabs((-562.2 * adc + 10432675)/(adc + -945.8));
           break;
    }
    return imp;
}




