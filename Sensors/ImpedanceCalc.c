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
            imp = fabs((-169.7 * adc + 316758)/(adc + -1015.2));
            break;
        case 3:
            imp = fabs((-158.7 * adc + 335582)/(adc + -1060.9));
            break;
        case 4:
            imp = fabs((-186.3 * adc + 431309)/(adc + -961.0));
            break;
        case 5:
            imp = fabs((-283.8 * adc + 701918)/(adc + -589.3));
            break;
        case 6:
            imp = fabs((-418.0 * adc + 1091547)/(adc + -59.9));
            break;
        case 7:
            imp = fabs((-346.7 * adc + 956344)/(adc + -449.1));
            break;
        case 8:
            imp = fabs((-387.5 * adc + 1113928)/(adc + -364.2));
            break;
        case 9:
            imp = fabs((-361.3 * adc + 1092925)/(adc + -479.3));
            break;
        case 10:
            imp = fabs((-298.3 * adc + 951700)/(adc + -743.2));
            break;
        case 11:
            imp = fabs((-320.9 * adc + 1062929)/(adc + -694.8));
            break;
        case 12:
            imp = fabs((-218.4 * adc + 811519)/(adc + -932.2));
            break;
        case 13:
            imp = fabs((-257.0 * adc + 954543)/(adc + -876.5));
            break;
        case 14:
            imp = fabs((-273.0 * adc + 1039308)/(adc + -854.0));
            break;
        case 15:
            imp = fabs((-270.4 * adc + 1068780)/(adc + -859.8));
            break;
        case 16:
            imp = fabs((-205.1 * adc + 919151)/(adc + -951.6));
            break;
        case 17:
            imp = fabs((-229.1 * adc + 1021336)/(adc + -927.8));
            break;
        case 18:
            imp = fabs((-251.4 * adc + 1118712)/(adc + -904.0));
            break;
        case 19:
            imp = fabs((-257.1 * adc + 1167924)/(adc + -905.2));
            break;
        case 20:
            imp = fabs((-248.6 * adc + 1182190)/(adc + -915.9));
            break;
        case 21:
            imp = fabs((-254.1 * adc + 1237041)/(adc + -910.2));
            break;
        case 22:
            imp = fabs((-199.3 * adc + 1129011)/(adc + -961.0));
            break;
        case 23:
            imp = fabs((-202.8 * adc + 1174305)/(adc + -959.9));
            break;
        case 24:
            imp = fabs((-211.5 * adc + 1235801)/(adc + -956.4));
            break;
        case 25:
            imp = fabs((-229.8 * adc + 1319964)/(adc + -949.1));
            break;
        case 26:
            imp = fabs((-225.0 * adc + 1345802)/(adc + -951.1));
            break;
        case 27:
            imp = fabs((-229.8 * adc + 1396146)/(adc + -951.7));
            break;
        case 28:
            imp = fabs((-218.8 * adc + 1400376)/(adc + -958.3));
            break;
        case 29:
            imp = fabs((-228.8 * adc + 1468521)/(adc + -951.8));
            break;
        case 30:
            imp = fabs((-238.9 * adc + 1529962)/(adc + -948.6));
            break;
        case 31:
            imp = fabs((-242.6 * adc + 1575451)/(adc + -948.8));
            break;
        case 32:
            imp = fabs((-201.3 * adc + 1508135)/(adc + -958.7));
            break;
        case 33:
            imp = fabs((-189.5 * adc + 1513156)/(adc + -963.7));
            break;
        case 34:
            imp = fabs((-184.6 * adc + 1537325)/(adc + -966.1));
            break;
        case 35:
            imp = fabs((-181.6 * adc + 1567973)/(adc + -965.3));
            break;
        case 36:
            imp = fabs((-212.3 * adc + 1685941)/(adc + -956.0));
            break;
        case 37:
            imp = fabs((-221.3 * adc + 1739427)/(adc + -954.2));
            break;
        case 38:
            imp = fabs((-203.8 * adc + 1734643)/(adc + -960.8));
            break;
        case 39:
            imp = fabs((-205.4 * adc + 1775510)/(adc + -962.1));
            break;
        case 40:
            imp = fabs((-211.9 * adc + 1830595)/(adc + -958.0));
            break;
        case 41:
            imp = fabs((-189.7 * adc + 1815839)/(adc + -963.8));
            break;
        case 42:
            imp = fabs((-185.4 * adc + 1833742)/(adc + -967.4));
            break;
        case 43:
            imp = fabs((-208.8 * adc + 1931889)/(adc + -960.5));
            break;
        case 44:
            imp = fabs((-215.4 * adc + 1989225)/(adc + -958.3));
            break;
        case 45:
            imp = fabs((-187.5 * adc + 1944270)/(adc + -968.9));
            break;
        case 46:
            imp = fabs((-195.2 * adc + 1993980)/(adc + -970.3));
            break;
        case 47:
            imp = fabs((-221.3 * adc + 2112448)/(adc + -957.5));
            break;
        case 48:
            imp = fabs((-223.0 * adc + 2139459)/(adc + -958.3));
            break;
        case 49:
            imp = fabs((-220.3 * adc + 2164098)/(adc + -961.6));
            break;
        case 50:
            imp = fabs((-195.4 * adc + 2146860)/(adc + -964.3));
            break;
        case 51:
            imp = fabs((-179.4 * adc + 2149759)/(adc + -967.7));
            break;
        case 52:
            imp = fabs((-184.4 * adc + 2194495)/(adc + -967.6));
            break;
        case 53:
            imp = fabs((-224.9 * adc + 2351161)/(adc + -954.3));
            break;
        case 54:
            imp = fabs((-231.9 * adc + 2396793)/(adc + -954.5));
            break;
        case 55:
            imp = fabs((-205.0 * adc + 2357782)/(adc + -963.7));
            break;
        case 56:
            imp = fabs((-260.6 * adc + 2539748)/(adc + -950.3));
            break;
        case 57:
            imp = fabs((-221.3 * adc + 2483997)/(adc + -958.5));
            break;
        case 58:
            imp = fabs((-214.9 * adc + 2511677)/(adc + -958.1));
            break;
        case 59:
            imp = fabs((-248.8 * adc + 2632494)/(adc + -951.5));
            break;
        case 60:
            imp = fabs((-176.7 * adc + 2473043)/(adc + -971.0));
            break;
        case 61:
            imp = fabs((-216.7 * adc + 2598020)/(adc + -965.6));
            break;
        case 62:
            imp = fabs((-221.6 * adc + 2664593)/(adc + -960.5));
            break;
        case 63:
            imp = fabs((-255.5 * adc + 2805686)/(adc + -950.1));
            break;
        case 64:
            imp = fabs((-212.2 * adc + 2696081)/(adc + -964.2));
            break;
        case 65:
            imp = fabs((-246.3 * adc + 2836678)/(adc + -951.7));
            break;
        case 66:
            imp = fabs((-200.4 * adc + 2750309)/(adc + -963.8));
            break;
        case 67:
            imp = fabs((-234.3 * adc + 2880688)/(adc + -956.3));
            break;
        case 68:
            imp = fabs((-245.7 * adc + 2945422)/(adc + -953.7));
            break;
        case 69:
            imp = fabs((-239.9 * adc + 2976433)/(adc + -954.4));
            break;
        case 70:
            imp = fabs((-349.4 * adc + 3228100)/(adc + -944.8));
            break;
        case 71:
            imp = fabs((-120.1 * adc + 2794570)/(adc + -969.3));
            break;
        case 72:
            imp = fabs((-26.6 * adc + 2646833)/(adc + -976.8));
            break;
        case 73:
            imp = fabs((-164.3 * adc + 2965866)/(adc + -964.4));
            break;
        case 74:
            imp = fabs((-185.7 * adc + 3056938)/(adc + -961.8));
            break;
        case 75:
            imp = fabs((-373.0 * adc + 3459930)/(adc + -947.7));
            break;
        case 76:
            imp = fabs((21.2 * adc + 2686400)/(adc + -981.7));
            break;
        case 77:
            imp = fabs((-98.7 * adc + 2979453)/(adc + -969.8));
            break;
        case 78:
            imp = fabs((-126.5 * adc + 3088964)/(adc + -965.7));
            break;
        case 79:
            imp = fabs((-182.4 * adc + 3249397)/(adc + -959.4));
            break;
        case 80:
            imp = fabs((-159.0 * adc + 3203863)/(adc + -964.5));
            break;
        case 81:
            imp = fabs((-152.8 * adc + 3253459)/(adc + -960.3));
            break;
        case 82:
            imp = fabs((-171.3 * adc + 3308263)/(adc + -962.5));
            break;
        case 83:
            imp = fabs((-99.9 * adc + 3209462)/(adc + -967.1));
            break;
        case 84:
            imp = fabs((-193.1 * adc + 3422340)/(adc + -961.7));
            break;
        case 85:
            imp = fabs((-115.4 * adc + 3319222)/(adc + -966.3));
            break;
        case 86:
            imp = fabs((-211.0 * adc + 3553748)/(adc + -957.9));
            break;
        case 87:
            imp = fabs((-34.5 * adc + 3219224)/(adc + -972.1));
            break;
        case 88:
            imp = fabs((-328.9 * adc + 3894320)/(adc + -945.4));
            break;
        case 89:
            imp = fabs((-88.3 * adc + 3415274)/(adc + -968.2));
            break;
        case 90:
            imp = fabs((-219.5 * adc + 3725646)/(adc + -958.1));
            break;
        case 91:
            imp = fabs((-139.7 * adc + 3624780)/(adc + -959.5));
            break;
        case 92:
            imp = fabs((-142.4 * adc + 3612125)/(adc + -967.7));
            break;
        case 93:
            imp = fabs((-58.0 * adc + 3475581)/(adc + -974.5));
            break;
        case 94:
            imp = fabs((-165.7 * adc + 3777354)/(adc + -960.0));
            break;
        case 95:
            imp = fabs((-137.8 * adc + 3746621)/(adc + -963.7));
            break;
        case 96:
            imp = fabs((-150.3 * adc + 3801159)/(adc + -962.1));
            break;
        case 97:
            imp = fabs((-141.2 * adc + 3790300)/(adc + -965.9));
            break;
        case 98:
            imp = fabs((-127.3 * adc + 3807583)/(adc + -968.4));
            break;
        case 99:
            imp = fabs((-79.2 * adc + 3733848)/(adc + -972.5));
            break;
        case 100:
            imp = fabs((-392.4 * adc + 4549487)/(adc + -931.0));
            break;
        case 101:
            imp = fabs((-159.9 * adc + 4000896)/(adc + -962.7));
            break;
        case 102:
            imp = fabs((-148.4 * adc + 4002961)/(adc + -966.8));
            break;
        case 103:
            imp = fabs((-162.7 * adc + 4077438)/(adc + -963.7));
            break;
        case 104:
            imp = fabs((-281.5 * adc + 4429055)/(adc + -944.8));
            break;
        case 105:
            imp = fabs((-89.3 * adc + 3979911)/(adc + -971.5));
            break;
        case 106:
            imp = fabs((-105.6 * adc + 4046060)/(adc + -969.8));
            break;
        case 107:
            imp = fabs((-203.7 * adc + 4350411)/(adc + -955.2));
            break;
        case 108:
            imp = fabs((-199.1 * adc + 4360722)/(adc + -957.3));
            break;
        case 109:
            imp = fabs((-132.4 * adc + 4236861)/(adc + -966.0));
            break;
        case 110:
            imp = fabs((-219.0 * adc + 4489340)/(adc + -956.8));
            break;
        case 111:
            imp = fabs((-109.7 * adc + 4250313)/(adc + -969.5));
            break;
        case 112:
            imp = fabs((-195.3 * adc + 4494291)/(adc + -959.4));
            break;
        case 113:
            imp = fabs((-172.5 * adc + 4483799)/(adc + -959.3));
            break;
        case 114:
            imp = fabs((-213.5 * adc + 4614368)/(adc + -954.0));
            break;
        case 115:
            imp = fabs((-243.7 * adc + 4712935)/(adc + -954.8));
            break;
        case 116:
            imp = fabs((-142.7 * adc + 4482840)/(adc + -969.0));
            break;
        case 117:
            imp = fabs((-348.3 * adc + 5033569)/(adc + -944.9));
            break;
        case 118:
            imp = fabs((-160.2 * adc + 4641633)/(adc + -961.7));
            break;
        case 119:
            imp = fabs((-256.7 * adc + 4891641)/(adc + -953.5));
            break;
        case 120:
            imp = fabs((-183.0 * adc + 4772187)/(adc + -960.1));
            break;
        case 121:
            imp = fabs((-174.6 * adc + 4765138)/(adc + -962.6));
            break;
        case 122:
            imp = fabs((-251.2 * adc + 5015916)/(adc + -951.9));
            break;
        case 123:
            imp = fabs((-165.6 * adc + 4823882)/(adc + -963.2));
            break;
        case 124:
            imp = fabs((-241.9 * adc + 5062592)/(adc + -955.1));
            break;
        case 125:
            imp = fabs((-211.1 * adc + 5005846)/(adc + -962.5));
            break;
        case 126:
            imp = fabs((-215.6 * adc + 5060360)/(adc + -959.5));
            break;
        case 127:
            imp = fabs((-197.8 * adc + 5071374)/(adc + -957.2));
            break;
        case 128:
            imp = fabs((-229.9 * adc + 5134154)/(adc + -961.0));
            break;
        case 129:
            imp = fabs((-306.9 * adc + 5450564)/(adc + -940.4));
            break;
        case 130:
            imp = fabs((-267.9 * adc + 5347496)/(adc + -949.6));
            break;
        case 131:
            imp = fabs((-154.4 * adc + 5052146)/(adc + -967.5));
            break;
        case 132:
            imp = fabs((-279.2 * adc + 5489570)/(adc + -944.3));
            break;
        case 133:
            imp = fabs((-173.2 * adc + 5166844)/(adc + -967.8));
            break;
        case 134:
            imp = fabs((-248.9 * adc + 5462646)/(adc + -952.4));
            break;
        case 135:
            imp = fabs((-176.7 * adc + 5289770)/(adc + -964.2));
            break;
        case 136:
            imp = fabs((-105.0 * adc + 5086098)/(adc + -979.6));
            break;
        case 137:
            imp = fabs((-269.6 * adc + 5664121)/(adc + -943.5));
            break;
        case 138:
            imp = fabs((-171.9 * adc + 5348197)/(adc + -969.8));
            break;
        case 139:
            imp = fabs((-200.0 * adc + 5498815)/(adc + -961.9));
            break;
        case 140:
            imp = fabs((-269.6 * adc + 5759297)/(adc + -948.7));
            break;
        case 141:
            imp = fabs((-188.5 * adc + 5537976)/(adc + -962.3));
            break;
        case 142:
            imp = fabs((-333.3 * adc + 6017064)/(adc + -937.3));
            break;
        case 143:
            imp = fabs((-236.8 * adc + 5769585)/(adc + -953.4));
            break;
        case 144:
            imp = fabs((-185.0 * adc + 5606410)/(adc + -966.9));
            break;
        case 145:
            imp = fabs((-354.3 * adc + 6172197)/(adc + -936.0));
            break;
        case 146:
            imp = fabs((-140.0 * adc + 5582643)/(adc + -968.1));
            break;
        case 147:
            imp = fabs((-341.9 * adc + 6227793)/(adc + -936.0));
            break;
        case 148:
            imp = fabs((-263.8 * adc + 6000972)/(adc + -953.2));
            break;
        case 149:
            imp = fabs((-171.2 * adc + 5778465)/(adc + -965.7));
            break;
        case 150:
            imp = fabs((-438.1 * adc + 6603486)/(adc + -923.2));
            break;
        case 151:
            imp = fabs((-124.0 * adc + 5710139)/(adc + -972.0));
            break;
        case 152:
            imp = fabs((-272.7 * adc + 6194394)/(adc + -950.9));
            break;
        case 153:
            imp = fabs((-197.4 * adc + 5989833)/(adc + -963.2));
            break;
        case 154:
            imp = fabs((-136.2 * adc + 5808380)/(adc + -980.8));
            break;
        case 155:
            imp = fabs((-381.7 * adc + 6630612)/(adc + -934.8));
            break;
        case 156:
            imp = fabs((-205.6 * adc + 6151956)/(adc + -959.3));
            break;
        case 157:
            imp = fabs((-191.8 * adc + 6122955)/(adc + -965.8));
            break;
        case 158:
            imp = fabs((-211.7 * adc + 6224679)/(adc + -963.0));
            break;
        case 159:
            imp = fabs((-252.4 * adc + 6365784)/(adc + -956.2));
            break;
        case 160:
            imp = fabs((-269.1 * adc + 6480073)/(adc + -950.1));
            break;
        case 161:
            imp = fabs((-253.6 * adc + 6468575)/(adc + -953.8));
            break;
        case 162:
            imp = fabs((-367.0 * adc + 6850794)/(adc + -934.9));
            break;
        case 163:
            imp = fabs((-260.5 * adc + 6531227)/(adc + -959.1));
            break;
        case 164:
            imp = fabs((-183.1 * adc + 6336720)/(adc + -968.1));
            break;
        case 165:
            imp = fabs((-321.2 * adc + 6832006)/(adc + -940.6));
            break;
        case 166:
            imp = fabs((-293.5 * adc + 6784463)/(adc + -945.8));
            break;
        case 167:
            imp = fabs((-223.1 * adc + 6627572)/(adc + -953.1));
            break;
        case 168:
            imp = fabs((-384.3 * adc + 7126607)/(adc + -934.1));
            break;
        case 169:
            imp = fabs((-321.3 * adc + 6985957)/(adc + -941.2));
            break;
        case 170:
            imp = fabs((-229.8 * adc + 6733638)/(adc + -958.2));
            break;
        case 171:
            imp = fabs((-171.9 * adc + 6603086)/(adc + -965.7));
            break;
        case 172:
            imp = fabs((-169.2 * adc + 6630287)/(adc + -965.7));
            break;
        case 173:
            imp = fabs((-280.4 * adc + 6962575)/(adc + -957.1));
            break;
        case 174:
            imp = fabs((365.3 * adc + 5631702)/(adc + -974.9));
            break;
        case 175:
            imp = fabs((189.2 * adc + 6043316)/(adc + -969.1));
            break;
        case 176:
            imp = fabs((-31.8 * adc + 6558606)/(adc + -963.3));
            break;
        case 177:
            imp = fabs((-186.2 * adc + 6941628)/(adc + -957.8));
            break;
        case 178:
            imp = fabs((-80.8 * adc + 6770983)/(adc + -961.6));
            break;
        case 179:
            imp = fabs((-137.1 * adc + 6818395)/(adc + -963.8));
            break;
        case 180:
            imp = fabs((301.3 * adc + 5966367)/(adc + -974.1));
            break;
        case 181:
            imp = fabs((-6.3 * adc + 6593898)/(adc + -968.8));
            break;
        case 182:
            imp = fabs((-270.0 * adc + 7193958)/(adc + -963.8));
            break;
        case 183:
            imp = fabs((-571.9 * adc + 7847163)/(adc + -956.4));
            break;
        case 184:
            imp = fabs((-406.9 * adc + 7606865)/(adc + -957.4));
            break;
        case 185:
            imp = fabs((-245.8 * adc + 7258930)/(adc + -962.2));
            break;
        case 186:
            imp = fabs((-419.9 * adc + 7656490)/(adc + -959.9));
            break;
        case 187:
            imp = fabs((-285.1 * adc + 7425608)/(adc + -962.8));
            break;
        case 188:
            imp = fabs((-205.3 * adc + 7281634)/(adc + -965.9));
            break;
        case 189:
            imp = fabs((-322.6 * adc + 7618738)/(adc + -959.8));
            break;
        case 190:
            imp = fabs((-304.4 * adc + 7634949)/(adc + -958.1));
            break;
        case 191:
            imp = fabs((-356.1 * adc + 7788220)/(adc + -955.8));
            break;
        case 192:
            imp = fabs((-334.3 * adc + 7730340)/(adc + -958.9));
            break;
        case 193:
            imp = fabs((228.1 * adc + 6604798)/(adc + -970.0));
            break;
        case 194:
            imp = fabs((462.8 * adc + 6163216)/(adc + -974.8));
            break;
        case 195:
            imp = fabs((25.8 * adc + 7063499)/(adc + -968.4));
            break;
        case 196:
            imp = fabs((55.4 * adc + 7099585)/(adc + -964.8));
            break;
        case 197:
            imp = fabs((-360.3 * adc + 8004613)/(adc + -958.4));
            break;
        case 198:
            imp = fabs((-99.5 * adc + 7514394)/(adc + -963.0));
            break;
        case 199:
            imp = fabs((346.4 * adc + 6648797)/(adc + -969.5));
            break;
        case 200:
            imp = fabs((-47.7 * adc + 7490438)/(adc + -962.4));
            break;
        case 201:
            imp = fabs((-582.8 * adc + 8548130)/(adc + -956.7));
            break;
        case 202:
            imp = fabs((-9.8 * adc + 7335209)/(adc + -970.6));
            break;
        case 203:
            imp = fabs((-421.1 * adc + 8295284)/(adc + -961.2));
            break;
        case 204:
            imp = fabs((-78.0 * adc + 7667057)/(adc + -963.5));
            break;
        case 205:
            imp = fabs((-257.9 * adc + 8103452)/(adc + -958.6));
            break;
        case 206:
            imp = fabs((-256.0 * adc + 8174255)/(adc + -957.6));
            break;
        case 207:
            imp = fabs((64.3 * adc + 7477667)/(adc + -966.0));
            break;
        case 208:
            imp = fabs((-82.5 * adc + 7764590)/(adc + -966.3));
            break;
        case 209:
            imp = fabs((332.5 * adc + 6942958)/(adc + -975.0));
            break;
        case 210:
            imp = fabs((-319.3 * adc + 8353124)/(adc + -963.0));
            break;
        case 211:
            imp = fabs((-163.7 * adc + 8059755)/(adc + -965.6));
            break;
        case 212:
            imp = fabs((-268.6 * adc + 8370538)/(adc + -958.6));
            break;
        case 213:
            imp = fabs((-700.8 * adc + 9383855)/(adc + -947.9));
            break;
        case 214:
            imp = fabs((-745.2 * adc + 9435217)/(adc + -951.7));
            break;
        case 215:
            imp = fabs((3.4 * adc + 7927907)/(adc + -963.4));
            break;
        case 216:
            imp = fabs((-361.5 * adc + 8669581)/(adc + -960.0));
            break;
        case 217:
            imp = fabs((-237.5 * adc + 8459351)/(adc + -964.4));
            break;
        case 218:
            imp = fabs((-121.7 * adc + 8209099)/(adc + -968.9));
            break;
        case 219:
            imp = fabs((-149.5 * adc + 8304423)/(adc + -966.2));
            break;
        case 220:
            imp = fabs((-265.2 * adc + 8729056)/(adc + -954.2));
            break;
        case 221:
            imp = fabs((-231.2 * adc + 8629811)/(adc + -959.8));
            break;
        case 222:
            imp = fabs((-239.6 * adc + 8716226)/(adc + -955.9));
            break;
        case 223:
            imp = fabs((-199.0 * adc + 8601369)/(adc + -966.0));
            break;
        case 224:
            imp = fabs((-229.4 * adc + 8682540)/(adc + -963.0));
            break;
        case 225:
            imp = fabs((-228.7 * adc + 8756876)/(adc + -961.2));
            break;
        case 226:
            imp = fabs((-379.3 * adc + 9222801)/(adc + -949.6));
            break;
        case 227:
            imp = fabs((-307.0 * adc + 9052416)/(adc + -953.8));
            break;
        case 228:
            imp = fabs((-128.4 * adc + 8599878)/(adc + -966.3));
            break;
        case 229:
            imp = fabs((-217.5 * adc + 8835824)/(adc + -963.4));
            break;
        case 230:
            imp = fabs((-80.3 * adc + 8543609)/(adc + -966.9));
            break;
        case 231:
            imp = fabs((-160.4 * adc + 8786434)/(adc + -965.5));
            break;
        case 232:
            imp = fabs((-297.4 * adc + 9203548)/(adc + -957.6));
            break;
        case 233:
            imp = fabs((-172.9 * adc + 8909259)/(adc + -962.8));
            break;
        case 234:
            imp = fabs((-291.1 * adc + 9276041)/(adc + -956.7));
            break;
        case 235:
            imp = fabs((-295.4 * adc + 9305117)/(adc + -958.0));
            break;
        case 236:
            imp = fabs((-166.0 * adc + 9013388)/(adc + -963.2));
            break;
        case 237:
            imp = fabs((-182.4 * adc + 9074857)/(adc + -964.2));
            break;
        case 238:
            imp = fabs((-315.1 * adc + 9457079)/(adc + -960.6));
            break;
        case 239:
            imp = fabs((-143.0 * adc + 9046697)/(adc + -967.7));
            break;
        case 240:
            imp = fabs((-155.9 * adc + 9085550)/(adc + -963.7));
            break;
        case 241:
            imp = fabs((-264.5 * adc + 9486485)/(adc + -955.1));
            break;
        case 242:
            imp = fabs((-15.5 * adc + 8887218)/(adc + -967.8));
            break;
        case 243:
            imp = fabs((-59.2 * adc + 9017385)/(adc + -965.5));
            break;
        case 244:
            imp = fabs((-591.6 * adc + 10312779)/(adc + -953.1));
            break;
        case 245:
            imp = fabs((-745.8 * adc + 10670213)/(adc + -947.4));
            break;
        case 246:
            imp = fabs((-497.6 * adc + 10166667)/(adc + -952.8));
            break;
        case 247:
            imp = fabs((-200.3 * adc + 9556324)/(adc + -961.5));
            break;
        case 248:
            imp = fabs((126.3 * adc + 8732230)/(adc + -974.6));
            break;
        case 249:
            imp = fabs((11.1 * adc + 9065538)/(adc + -969.7));
            break;
        case 250:
            imp = fabs((-393.0 * adc + 10042038)/(adc + -960.2));
            break;
        case 251:
            imp = fabs((-266.3 * adc + 9765330)/(adc + -963.6));
            break;
        case 252:
            imp = fabs((-25.8 * adc + 9303874)/(adc + -967.7));
            break;
        case 253:
            imp = fabs((-467.9 * adc + 10344711)/(adc + -956.0));
            break;
        case 254:
            imp = fabs((-586.9 * adc + 10699349)/(adc + -949.6));
            break;
       }
       return imp;
}
