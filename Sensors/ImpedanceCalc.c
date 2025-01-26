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
            imp = fabs((-175.4 * adc + 312205)/(adc + -969.8));
            break;
        case 3:
            imp = fabs((-165.2 * adc + 331738)/(adc + -1006.6));
            break;
        case 4:
            imp = fabs((-167.4 * adc + 369435)/(adc + -991.9));
            break;
        case 5:
            imp = fabs((-224.7 * adc + 533888)/(adc + -779.1));
            break;
        case 6:
            imp = fabs((-375.3 * adc + 942013)/(adc + -190.3));
            break;
        case 7:
            imp = fabs((-413.0 * adc + 1090845)/(adc + -90.7));
            break;
        case 8:
            imp = fabs((-291.2 * adc + 810784)/(adc + -706.0));
            break;
        case 9:
            imp = fabs((-400.9 * adc + 1156525)/(adc + -304.8));
            break;
        case 10:
            imp = fabs((-358.6 * adc + 1087018)/(adc + -464.9));
            break;
        case 11:
            imp = fabs((-305.7 * adc + 973056)/(adc + -695.3));
            break;
        case 12:
            imp = fabs((-327.7 * adc + 1079248)/(adc + -641.4));
            break;
        case 13:
            imp = fabs((-233.5 * adc + 848569)/(adc + -874.2));
            break;
        case 14:
            imp = fabs((-251.1 * adc + 931201)/(adc + -850.4));
            break;
        case 15:
            imp = fabs((-265.1 * adc + 1004570)/(adc + -834.1));
            break;
        case 16:
            imp = fabs((-286.2 * adc + 1087807)/(adc + -805.9));
            break;
        case 17:
            imp = fabs((-210.9 * adc + 921567)/(adc + -912.5));
            break;
        case 18:
            imp = fabs((-216.7 * adc + 971952)/(adc + -908.4));
            break;
        case 19:
            imp = fabs((-231.3 * adc + 1044762)/(adc + -894.5));
            break;
        case 20:
            imp = fabs((-242.3 * adc + 1109551)/(adc + -884.5));
            break;
        case 21:
            imp = fabs((-250.6 * adc + 1167421)/(adc + -876.7));
            break;
        case 22:
            imp = fabs((-258.9 * adc + 1226871)/(adc + -870.9));
            break;
        case 23:
            imp = fabs((-268.7 * adc + 1292833)/(adc + -859.7));
            break;
        case 24:
            imp = fabs((-196.7 * adc + 1134292)/(adc + -929.5));
            break;
        case 25:
            imp = fabs((-201.9 * adc + 1183137)/(adc + -927.2));
            break;
        case 26:
            imp = fabs((-204.1 * adc + 1222597)/(adc + -928.2));
            break;
        case 27:
            imp = fabs((-209.5 * adc + 1272644)/(adc + -926.3));
            break;
        case 28:
            imp = fabs((-213.4 * adc + 1318321)/(adc + -924.9));
            break;
        case 29:
            imp = fabs((-218.3 * adc + 1366569)/(adc + -922.4));
            break;
        case 30:
            imp = fabs((-225.8 * adc + 1421180)/(adc + -919.2));
            break;
        case 31:
            imp = fabs((-229.3 * adc + 1463800)/(adc + -919.3));
            break;
        case 32:
            imp = fabs((-227.8 * adc + 1481821)/(adc + -919.3));
            break;
        case 33:
            imp = fabs((-233.9 * adc + 1533731)/(adc + -916.4));
            break;
        case 34:
            imp = fabs((-237.5 * adc + 1578719)/(adc + -915.6));
            break;
        case 35:
            imp = fabs((-191.7 * adc + 1508194)/(adc + -929.4));
            break;
        case 36:
            imp = fabs((-197.0 * adc + 1556126)/(adc + -928.1));
            break;
        case 37:
            imp = fabs((-194.2 * adc + 1583138)/(adc + -929.9));
            break;
        case 38:
            imp = fabs((-199.0 * adc + 1632014)/(adc + -927.6));
            break;
        case 39:
            imp = fabs((-198.2 * adc + 1664153)/(adc + -929.8));
            break;
        case 40:
            imp = fabs((-207.1 * adc + 1722858)/(adc + -926.6));
            break;
        case 41:
            imp = fabs((-212.6 * adc + 1773220)/(adc + -924.8));
            break;
        case 42:
            imp = fabs((-191.0 * adc + 1754629)/(adc + -931.1));
            break;
        case 43:
            imp = fabs((-198.6 * adc + 1809671)/(adc + -929.0));
            break;
        case 44:
            imp = fabs((-211.7 * adc + 1879392)/(adc + -925.0));
            break;
        case 45:
            imp = fabs((-209.7 * adc + 1906503)/(adc + -927.1));
            break;
        case 46:
            imp = fabs((-200.9 * adc + 1915824)/(adc + -931.2));
            break;
        case 47:
            imp = fabs((-200.5 * adc + 1948994)/(adc + -930.8));
            break;
        case 48:
            imp = fabs((-209.3 * adc + 1995437)/(adc + -928.3));
            break;
        case 49:
            imp = fabs((-202.2 * adc + 2009153)/(adc + -930.7));
            break;
        case 50:
            imp = fabs((-205.0 * adc + 2051029)/(adc + -930.6));
            break;
        case 51:
            imp = fabs((-211.8 * adc + 2103898)/(adc + -928.8));
            break;
        case 52:
            imp = fabs((-219.3 * adc + 2160961)/(adc + -926.1));
            break;
        case 53:
            imp = fabs((-214.7 * adc + 2193326)/(adc + -924.9));
            break;
        case 54:
            imp = fabs((-207.9 * adc + 2208385)/(adc + -927.8));
            break;
        case 55:
            imp = fabs((-206.5 * adc + 2244410)/(adc + -927.0));
            break;
        case 56:
            imp = fabs((-210.5 * adc + 2288370)/(adc + -927.4));
            break;
        case 57:
            imp = fabs((-215.7 * adc + 2337190)/(adc + -926.4));
            break;
        case 58:
            imp = fabs((-224.0 * adc + 2395793)/(adc + -923.5));
            break;
        case 59:
            imp = fabs((-215.2 * adc + 2407469)/(adc + -926.5));
            break;
        case 60:
            imp = fabs((-227.6 * adc + 2475441)/(adc + -924.0));
            break;
        case 61:
            imp = fabs((-216.2 * adc + 2480357)/(adc + -926.7));
            break;
        case 62:
            imp = fabs((-233.1 * adc + 2560140)/(adc + -922.6));
            break;
        case 63:
            imp = fabs((-215.8 * adc + 2550451)/(adc + -926.9));
            break;
        case 64:
            imp = fabs((-228.6 * adc + 2607003)/(adc + -923.5));
            break;
        case 65:
            imp = fabs((-226.7 * adc + 2638666)/(adc + -923.6));
            break;
        case 66:
            imp = fabs((-230.6 * adc + 2681308)/(adc + -923.6));
            break;
        case 67:
            imp = fabs((-229.4 * adc + 2717132)/(adc + -922.5));
            break;
        case 68:
            imp = fabs((-228.2 * adc + 2743321)/(adc + -925.1));
            break;
        case 69:
            imp = fabs((-231.0 * adc + 2788408)/(adc + -923.5));
            break;
        case 70:
            imp = fabs((-234.9 * adc + 2839707)/(adc + -921.5));
            break;
        case 71:
            imp = fabs((-234.8 * adc + 2871676)/(adc + -923.1));
            break;
        case 72:
            imp = fabs((-228.9 * adc + 2890038)/(adc + -925.1));
            break;
        case 73:
            imp = fabs((-234.8 * adc + 2945717)/(adc + -923.4));
            break;
        case 74:
            imp = fabs((-242.9 * adc + 3008775)/(adc + -919.6));
            break;
        case 75:
            imp = fabs((-196.8 * adc + 2937734)/(adc + -927.7));
            break;
        case 76:
            imp = fabs((-189.5 * adc + 2965150)/(adc + -927.3));
            break;
        case 77:
            imp = fabs((-222.1 * adc + 3061703)/(adc + -925.4));
            break;
        case 78:
            imp = fabs((-206.5 * adc + 3072640)/(adc + -925.6));
            break;
        case 79:
            imp = fabs((-231.6 * adc + 3150844)/(adc + -924.5));
            break;
        case 80:
            imp = fabs((-181.6 * adc + 3082739)/(adc + -927.7));
            break;
        case 81:
            imp = fabs((-170.8 * adc + 3098568)/(adc + -928.1));
            break;
        case 82:
            imp = fabs((-157.7 * adc + 3101134)/(adc + -930.9));
            break;
        case 83:
            imp = fabs((-200.3 * adc + 3228629)/(adc + -925.6));
            break;
        case 84:
            imp = fabs((-174.2 * adc + 3210051)/(adc + -928.3));
            break;
        case 85:
            imp = fabs((-198.4 * adc + 3297926)/(adc + -925.7));
            break;
        case 86:
            imp = fabs((-176.3 * adc + 3284109)/(adc + -927.9));
            break;
        case 87:
            imp = fabs((-135.1 * adc + 3235116)/(adc + -932.2));
            break;
        case 88:
            imp = fabs((-224.4 * adc + 3465340)/(adc + -922.9));
            break;
        case 89:
            imp = fabs((-153.7 * adc + 3352075)/(adc + -930.0));
            break;
        case 90:
            imp = fabs((-121.4 * adc + 3322202)/(adc + -932.7));
            break;
        case 91:
            imp = fabs((-176.0 * adc + 3476447)/(adc + -926.8));
            break;
        case 92:
            imp = fabs((-186.4 * adc + 3533141)/(adc + -926.7));
            break;
        case 93:
            imp = fabs((-173.1 * adc + 3541427)/(adc + -927.4));
            break;
        case 94:
            imp = fabs((-167.0 * adc + 3564480)/(adc + -928.2));
            break;
        case 95:
            imp = fabs((-168.5 * adc + 3606566)/(adc + -927.0));
            break;
        case 96:
            imp = fabs((-159.6 * adc + 3603149)/(adc + -929.0));
            break;
        case 97:
            imp = fabs((-131.9 * adc + 3583303)/(adc + -931.0));
            break;
        case 98:
            imp = fabs((-144.4 * adc + 3639163)/(adc + -931.3));
            break;
        case 99:
            imp = fabs((-157.2 * adc + 3714350)/(adc + -927.6));
            break;
        case 100:
            imp = fabs((-143.7 * adc + 3714640)/(adc + -929.9));
            break;
        case 101:
            imp = fabs((-133.6 * adc + 3722422)/(adc + -931.7));
            break;
        case 102:
            imp = fabs((-138.1 * adc + 3778181)/(adc + -930.2));
            break;
        case 103:
            imp = fabs((-135.6 * adc + 3803681)/(adc + -930.7));
            break;
        case 104:
            imp = fabs((-103.4 * adc + 3766555)/(adc + -934.2));
            break;
        case 105:
            imp = fabs((-132.3 * adc + 3874449)/(adc + -930.9));
            break;
        case 106:
            imp = fabs((-140.4 * adc + 3928747)/(adc + -930.0));
            break;
        case 107:
            imp = fabs((-144.9 * adc + 3977139)/(adc + -929.5));
            break;
        case 108:
            imp = fabs((-143.6 * adc + 4013349)/(adc + -929.2));
            break;
        case 109:
            imp = fabs((-138.8 * adc + 4034537)/(adc + -929.3));
            break;
        case 110:
            imp = fabs((-166.3 * adc + 4134856)/(adc + -926.6));
            break;
        case 111:
            imp = fabs((-169.5 * adc + 4184088)/(adc + -924.5));
            break;
        case 112:
            imp = fabs((-188.9 * adc + 4244955)/(adc + -924.1));
            break;
        case 113:
            imp = fabs((-126.2 * adc + 4123717)/(adc + -932.3));
            break;
        case 114:
            imp = fabs((-121.3 * adc + 4147658)/(adc + -932.3));
            break;
        case 115:
            imp = fabs((-138.6 * adc + 4222974)/(adc + -930.8));
            break;
        case 116:
            imp = fabs((-150.4 * adc + 4285809)/(adc + -929.7));
            break;
        case 117:
            imp = fabs((-188.1 * adc + 4410293)/(adc + -926.2));
            break;
        case 118:
            imp = fabs((-178.7 * adc + 4429569)/(adc + -925.6));
            break;
        case 119:
            imp = fabs((-191.5 * adc + 4497331)/(adc + -923.8));
            break;
        case 120:
            imp = fabs((-186.7 * adc + 4517358)/(adc + -925.8));
            break;
        case 121:
            imp = fabs((-213.7 * adc + 4621223)/(adc + -922.7));
            break;
        case 122:
            imp = fabs((-213.0 * adc + 4658968)/(adc + -921.5));
            break;
        case 123:
            imp = fabs((-188.7 * adc + 4632456)/(adc + -925.1));
            break;
        case 124:
            imp = fabs((-199.0 * adc + 4691126)/(adc + -924.8));
            break;
        case 125:
            imp = fabs((-207.9 * adc + 4745206)/(adc + -924.1));
            break;
        case 126:
            imp = fabs((-217.1 * adc + 4808056)/(adc + -922.2));
            break;
        case 127:
            imp = fabs((-212.6 * adc + 4829087)/(adc + -923.0));
            break;
        case 128:
            imp = fabs((-204.7 * adc + 4830880)/(adc + -924.5));
            break;
        case 129:
            imp = fabs((-254.7 * adc + 4999433)/(adc + -917.3));
            break;
        case 130:
            imp = fabs((-257.5 * adc + 5040247)/(adc + -917.6));
            break;
        case 131:
            imp = fabs((-235.3 * adc + 5012959)/(adc + -921.3));
            break;
        case 132:
            imp = fabs((-223.8 * adc + 5021152)/(adc + -922.6));
            break;
        case 133:
            imp = fabs((-270.7 * adc + 5185702)/(adc + -915.0));
            break;
        case 134:
            imp = fabs((-254.1 * adc + 5175953)/(adc + -917.6));
            break;
        case 135:
            imp = fabs((-245.4 * adc + 5193500)/(adc + -918.1));
            break;
        case 136:
            imp = fabs((-268.3 * adc + 5288536)/(adc + -915.7));
            break;
        case 137:
            imp = fabs((-264.8 * adc + 5314270)/(adc + -916.7));
            break;
        case 138:
            imp = fabs((-272.5 * adc + 5371636)/(adc + -915.4));
            break;
        case 139:
            imp = fabs((-268.2 * adc + 5400849)/(adc + -915.0));
            break;
        case 140:
            imp = fabs((-223.0 * adc + 5306855)/(adc + -922.8));
            break;
        case 141:
            imp = fabs((-264.6 * adc + 5463065)/(adc + -915.9));
            break;
        case 142:
            imp = fabs((-279.0 * adc + 5543756)/(adc + -913.4));
            break;
        case 143:
            imp = fabs((-274.0 * adc + 5564020)/(adc + -914.3));
            break;
        case 144:
            imp = fabs((-252.3 * adc + 5522623)/(adc + -917.5));
            break;
        case 145:
            imp = fabs((-271.1 * adc + 5607409)/(adc + -915.7));
            break;
        case 146:
            imp = fabs((-245.8 * adc + 5574345)/(adc + -918.9));
            break;
        case 147:
            imp = fabs((-276.0 * adc + 5694084)/(adc + -914.5));
            break;
        case 148:
            imp = fabs((-254.7 * adc + 5673729)/(adc + -917.1));
            break;
        case 149:
            imp = fabs((-292.4 * adc + 5818627)/(adc + -911.1));
            break;
        case 150:
            imp = fabs((-288.7 * adc + 5855451)/(adc + -910.5));
            break;
        case 151:
            imp = fabs((-269.0 * adc + 5828218)/(adc + -915.2));
            break;
        case 152:
            imp = fabs((-271.5 * adc + 5873737)/(adc + -914.1));
            break;
        case 153:
            imp = fabs((-280.1 * adc + 5931957)/(adc + -913.8));
            break;
        case 154:
            imp = fabs((-255.2 * adc + 5896525)/(adc + -917.3));
            break;
        case 155:
            imp = fabs((-260.1 * adc + 5952946)/(adc + -915.7));
            break;
        case 156:
            imp = fabs((-256.5 * adc + 5974923)/(adc + -917.3));
            break;
        case 157:
            imp = fabs((-288.9 * adc + 6110955)/(adc + -910.9));
            break;
        case 158:
            imp = fabs((-285.8 * adc + 6134346)/(adc + -912.2));
            break;
        case 159:
            imp = fabs((-254.5 * adc + 6081879)/(adc + -916.1));
            break;
        case 160:
            imp = fabs((-288.7 * adc + 6202926)/(adc + -910.8));
            break;
        case 161:
            imp = fabs((-274.2 * adc + 6197712)/(adc + -912.9));
            break;
        case 162:
            imp = fabs((-254.9 * adc + 6166870)/(adc + -917.9));
            break;
        case 163:
            imp = fabs((-251.5 * adc + 6193440)/(adc + -917.7));
            break;
        case 164:
            imp = fabs((-271.5 * adc + 6289421)/(adc + -914.7));
            break;
        case 165:
            imp = fabs((-266.8 * adc + 6313484)/(adc + -915.2));
            break;
        case 166:
            imp = fabs((-267.4 * adc + 6352561)/(adc + -915.1));
            break;
        case 167:
            imp = fabs((-291.7 * adc + 6464570)/(adc + -910.9));
            break;
        case 168:
            imp = fabs((-277.2 * adc + 6449579)/(adc + -914.5));
            break;
        case 169:
            imp = fabs((-304.2 * adc + 6574670)/(adc + -909.1));
            break;
        case 170:
            imp = fabs((-285.3 * adc + 6553049)/(adc + -911.8));
            break;
        case 171:
            imp = fabs((-246.3 * adc + 6462133)/(adc + -920.0));
            break;
        case 172:
            imp = fabs((-256.9 * adc + 6530138)/(adc + -918.8));
            break;
        case 173:
            imp = fabs((-287.3 * adc + 6661467)/(adc + -912.9));
            break;
        case 174:
            imp = fabs((-170.5 * adc + 6382853)/(adc + -926.2));
            break;
        case 175:
            imp = fabs((-138.9 * adc + 6350819)/(adc + -927.1));
            break;
        case 176:
            imp = fabs((-184.2 * adc + 6465465)/(adc + -926.4));
            break;
        case 177:
            imp = fabs((-120.2 * adc + 6361253)/(adc + -928.1));
            break;
        case 178:
            imp = fabs((-219.4 * adc + 6612352)/(adc + -925.6));
            break;
        case 179:
            imp = fabs((-216.5 * adc + 6640047)/(adc + -925.6));
            break;
        case 180:
            imp = fabs((-283.6 * adc + 6817841)/(adc + -924.0));
            break;
        case 181:
            imp = fabs((-132.3 * adc + 6529011)/(adc + -927.5));
            break;
        case 182:
            imp = fabs((-254.5 * adc + 6833506)/(adc + -924.5));
            break;
        case 183:
            imp = fabs((-263.4 * adc + 6891210)/(adc + -924.0));
            break;
        case 184:
            imp = fabs((-251.6 * adc + 6907769)/(adc + -923.9));
            break;
        case 185:
            imp = fabs((-389.8 * adc + 7189221)/(adc + -922.7));
            break;
        case 186:
            imp = fabs((-295.6 * adc + 7047879)/(adc + -923.9));
            break;
        case 187:
            imp = fabs((-380.5 * adc + 7248612)/(adc + -922.5));
            break;
        case 188:
            imp = fabs((-224.1 * adc + 6997902)/(adc + -924.5));
            break;
        case 189:
            imp = fabs((-219.1 * adc + 7007915)/(adc + -925.0));
            break;
        case 190:
            imp = fabs((-347.3 * adc + 7298782)/(adc + -923.0));
            break;
        case 191:
            imp = fabs((-251.9 * adc + 7143994)/(adc + -924.8));
            break;
        case 192:
            imp = fabs((-270.7 * adc + 7205402)/(adc + -924.4));
            break;
        case 193:
            imp = fabs((-141.6 * adc + 6997160)/(adc + -926.1));
            break;
        case 194:
            imp = fabs((-213.5 * adc + 7169109)/(adc + -925.2));
            break;
        case 195:
            imp = fabs((-30.3 * adc + 6842674)/(adc + -928.5));
            break;
        case 196:
            imp = fabs((-197.5 * adc + 7211759)/(adc + -925.1));
            break;
        case 197:
            imp = fabs((-348.9 * adc + 7533240)/(adc + -923.5));
            break;
        case 198:
            imp = fabs((-195.2 * adc + 7275434)/(adc + -925.6));
            break;
        case 199:
            imp = fabs((-315.7 * adc + 7539222)/(adc + -924.1));
            break;
        case 200:
            imp = fabs((-165.1 * adc + 7282347)/(adc + -926.2));
            break;
        case 201:
            imp = fabs((-265.3 * adc + 7507255)/(adc + -924.7));
            break;
        case 202:
            imp = fabs((-230.5 * adc + 7486225)/(adc + -924.9));
            break;
        case 203:
            imp = fabs((-195.1 * adc + 7455418)/(adc + -924.8));
            break;
        case 204:
            imp = fabs((-354.4 * adc + 7817408)/(adc + -922.7));
            break;
        case 205:
            imp = fabs((-324.4 * adc + 7786092)/(adc + -923.5));
            break;
        case 206:
            imp = fabs((-183.2 * adc + 7529619)/(adc + -926.0));
            break;
        case 207:
            imp = fabs((-314.0 * adc + 7846433)/(adc + -923.1));
            break;
        case 208:
            imp = fabs((-181.1 * adc + 7595274)/(adc + -925.9));
            break;
        case 209:
            imp = fabs((-352.3 * adc + 7988918)/(adc + -922.4));
            break;
        case 210:
            imp = fabs((-229.9 * adc + 7756183)/(adc + -925.5));
            break;
        case 211:
            imp = fabs((-282.3 * adc + 7911193)/(adc + -923.7));
            break;
        case 212:
            imp = fabs((-308.0 * adc + 7984789)/(adc + -923.9));
            break;
        case 213:
            imp = fabs((-181.6 * adc + 7773292)/(adc + -925.6));
            break;
        case 214:
            imp = fabs((-196.6 * adc + 7840842)/(adc + -925.4));
            break;
        case 215:
            imp = fabs((-356.2 * adc + 8198047)/(adc + -922.8));
            break;
        case 216:
            imp = fabs((-224.1 * adc + 7973730)/(adc + -925.1));
            break;
        case 217:
            imp = fabs((-210.5 * adc + 7966925)/(adc + -926.2));
            break;
        case 218:
            imp = fabs((-194.7 * adc + 7970723)/(adc + -926.8));
            break;
        case 219:
            imp = fabs((-216.2 * adc + 8068980)/(adc + -924.9));
            break;
        case 220:
            imp = fabs((-192.9 * adc + 8051369)/(adc + -925.8));
            break;
        case 221:
            imp = fabs((-196.5 * adc + 8092830)/(adc + -926.1));
            break;
        case 222:
            imp = fabs((-213.7 * adc + 8180043)/(adc + -924.5));
            break;
        case 223:
            imp = fabs((-201.4 * adc + 8171970)/(adc + -926.6));
            break;
        case 224:
            imp = fabs((-195.0 * adc + 8184193)/(adc + -925.8));
            break;
        case 225:
            imp = fabs((-208.9 * adc + 8252881)/(adc + -925.1));
            break;
        case 226:
            imp = fabs((-208.4 * adc + 8286557)/(adc + -925.5));
            break;
        case 227:
            imp = fabs((-226.6 * adc + 8365934)/(adc + -925.1));
            break;
        case 228:
            imp = fabs((-208.5 * adc + 8353474)/(adc + -926.0));
            break;
        case 229:
            imp = fabs((-196.0 * adc + 8363181)/(adc + -926.0));
            break;
        case 230:
            imp = fabs((-203.5 * adc + 8418035)/(adc + -925.3));
            break;
        case 231:
            imp = fabs((-217.0 * adc + 8486812)/(adc + -925.3));
            break;
        case 232:
            imp = fabs((-211.7 * adc + 8507118)/(adc + -925.3));
            break;
        case 233:
            imp = fabs((-215.8 * adc + 8556690)/(adc + -925.3));
            break;
        case 234:
            imp = fabs((-217.6 * adc + 8603625)/(adc + -924.5));
            break;
        case 235:
            imp = fabs((-227.4 * adc + 8660467)/(adc + -924.6));
            break;
        case 236:
            imp = fabs((-223.1 * adc + 8688617)/(adc + -924.8));
            break;
        case 237:
            imp = fabs((-226.6 * adc + 8730468)/(adc + -924.3));
            break;
        case 238:
            imp = fabs((-211.4 * adc + 8725393)/(adc + -925.2));
            break;
        case 239:
            imp = fabs((-220.9 * adc + 8780613)/(adc + -925.5));
            break;
        case 240:
            imp = fabs((-219.7 * adc + 8808981)/(adc + -924.3));
            break;
        case 241:
            imp = fabs((-223.2 * adc + 8856598)/(adc + -924.4));
            break;
        case 242:
            imp = fabs((-200.9 * adc + 8825247)/(adc + -926.4));
            break;
        case 243:
            imp = fabs((-219.2 * adc + 8906692)/(adc + -925.3));
            break;
        case 244:
            imp = fabs((-216.8 * adc + 8937147)/(adc + -925.6));
            break;
        case 245:
            imp = fabs((-221.1 * adc + 8984311)/(adc + -925.4));
            break;
        case 246:
            imp = fabs((-227.3 * adc + 9037158)/(adc + -925.4));
            break;
        case 247:
            imp = fabs((-237.9 * adc + 9114903)/(adc + -922.9));
            break;
        case 248:
            imp = fabs((-225.8 * adc + 9112691)/(adc + -924.2));
            break;
        case 249:
            imp = fabs((-219.5 * adc + 9127045)/(adc + -925.2));
            break;
        case 250:
            imp = fabs((-239.8 * adc + 9222857)/(adc + -923.4));
            break;
        case 251:
            imp = fabs((-221.9 * adc + 9204492)/(adc + -925.2));
            break;
        case 252:
            imp = fabs((-223.0 * adc + 9246540)/(adc + -925.1));
            break;
        case 253:
            imp = fabs((-220.2 * adc + 9277435)/(adc + -925.3));
            break;
        case 254:
            imp = fabs((-221.0 * adc + 9307284)/(adc + -925.2));
            break;
       }
       return imp;
}
