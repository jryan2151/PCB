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
            imp = fabs((-168.2 * adc + 304748)/(adc + -1010.7));
            break;
        case 3:
            imp = fabs((-161.8 * adc + 330940)/(adc + -1043.9));
            break;
        case 4:
            imp = fabs((-176.2 * adc + 395535)/(adc + -991.5));
            break;
        case 5:
            imp = fabs((-242.9 * adc + 584512)/(adc + -753.7));
            break;
        case 6:
            imp = fabs((-369.7 * adc + 939942)/(adc + -285.8));
            break;
        case 7:
            imp = fabs((-341.6 * adc + 917292)/(adc + -476.9));
            break;
        case 8:
            imp = fabs((-249.8 * adc + 708550)/(adc + -938.1));
            break;
        case 9:
            imp = fabs((-383.5 * adc + 1126335)/(adc + -410.7));
            break;
        case 10:
            imp = fabs((-292.7 * adc + 911050)/(adc + -755.6));
            break;
        case 11:
            imp = fabs((-318.0 * adc + 1026530)/(adc + -699.7));
            break;
        case 12:
            imp = fabs((-230.3 * adc + 823193)/(adc + -905.1));
            break;
        case 13:
            imp = fabs((-247.3 * adc + 903292)/(adc + -884.9));
            break;
        case 14:
            imp = fabs((-263.9 * adc + 985969)/(adc + -863.9));
            break;
        case 15:
            imp = fabs((-277.4 * adc + 1061644)/(adc + -845.1));
            break;
        case 16:
            imp = fabs((-298.7 * adc + 1153696)/(adc + -807.8));
            break;
        case 17:
            imp = fabs((-222.8 * adc + 977971)/(adc + -923.1));
            break;
        case 18:
            imp = fabs((-234.8 * adc + 1047759)/(adc + -911.8));
            break;
        case 19:
            imp = fabs((-244.9 * adc + 1108701)/(adc + -905.4));
            break;
        case 20:
            imp = fabs((-253.1 * adc + 1168735)/(adc + -897.5));
            break;
        case 21:
            imp = fabs((-260.8 * adc + 1226992)/(adc + -891.6));
            break;
        case 22:
            imp = fabs((-272.1 * adc + 1299843)/(adc + -877.7));
            break;
        case 23:
            imp = fabs((-199.4 * adc + 1140941)/(adc + -948.7));
            break;
        case 24:
            imp = fabs((-203.6 * adc + 1186721)/(adc + -948.2));
            break;
        case 25:
            imp = fabs((-212.6 * adc + 1247238)/(adc + -943.9));
            break;
        case 26:
            imp = fabs((-212.2 * adc + 1284160)/(adc + -944.2));
            break;
        case 27:
            imp = fabs((-223.6 * adc + 1351506)/(adc + -939.2));
            break;
        case 28:
            imp = fabs((-227.7 * adc + 1398667)/(adc + -938.7));
            break;
        case 29:
            imp = fabs((-226.0 * adc + 1429406)/(adc + -940.1));
            break;
        case 30:
            imp = fabs((-236.1 * adc + 1494463)/(adc + -934.6));
            break;
        case 31:
            imp = fabs((-238.9 * adc + 1537005)/(adc + -934.4));
            break;
        case 32:
            imp = fabs((-239.8 * adc + 1561558)/(adc + -936.2));
            break;
        case 33:
            imp = fabs((-169.0 * adc + 1435958)/(adc + -955.0));
            break;
        case 34:
            imp = fabs((-179.8 * adc + 1495608)/(adc + -953.7));
            break;
        case 35:
            imp = fabs((-191.9 * adc + 1563050)/(adc + -949.0));
            break;
        case 36:
            imp = fabs((-202.9 * adc + 1624721)/(adc + -946.5));
            break;
        case 37:
            imp = fabs((-194.7 * adc + 1642122)/(adc + -948.5));
            break;
        case 38:
            imp = fabs((-194.2 * adc + 1675171)/(adc + -949.5));
            break;
        case 39:
            imp = fabs((-196.2 * adc + 1717465)/(adc + -949.5));
            break;
        case 40:
            imp = fabs((-205.7 * adc + 1779895)/(adc + -945.7));
            break;
        case 41:
            imp = fabs((-195.8 * adc + 1789214)/(adc + -949.9));
            break;
        case 42:
            imp = fabs((-202.7 * adc + 1843291)/(adc + -948.1));
            break;
        case 43:
            imp = fabs((-210.4 * adc + 1899842)/(adc + -946.0));
            break;
        case 44:
            imp = fabs((-210.6 * adc + 1936394)/(adc + -947.3));
            break;
        case 45:
            imp = fabs((-225.8 * adc + 2014406)/(adc + -941.4));
            break;
        case 46:
            imp = fabs((-212.1 * adc + 2010397)/(adc + -947.3));
            break;
        case 47:
            imp = fabs((-217.4 * adc + 2061185)/(adc + -945.3));
            break;
        case 48:
            imp = fabs((-220.1 * adc + 2091898)/(adc + -944.5));
            break;
        case 49:
            imp = fabs((-222.2 * adc + 2131895)/(adc + -945.0));
            break;
        case 50:
            imp = fabs((-223.5 * adc + 2173259)/(adc + -944.4));
            break;
        case 51:
            imp = fabs((-202.0 * adc + 2164335)/(adc + -947.9));
            break;
        case 52:
            imp = fabs((-204.9 * adc + 2204737)/(adc + -947.9));
            break;
        case 53:
            imp = fabs((-203.4 * adc + 2238415)/(adc + -947.9));
            break;
        case 54:
            imp = fabs((-206.5 * adc + 2282734)/(adc + -947.5));
            break;
        case 55:
            imp = fabs((-203.5 * adc + 2312643)/(adc + -948.3));
            break;
        case 56:
            imp = fabs((-213.5 * adc + 2375901)/(adc + -945.6));
            break;
        case 57:
            imp = fabs((-209.7 * adc + 2402512)/(adc + -946.4));
            break;
        case 58:
            imp = fabs((-226.3 * adc + 2481099)/(adc + -943.8));
            break;
        case 59:
            imp = fabs((-225.0 * adc + 2519654)/(adc + -943.2));
            break;
        case 60:
            imp = fabs((-234.9 * adc + 2580708)/(adc + -941.9));
            break;
        case 61:
            imp = fabs((-232.6 * adc + 2609683)/(adc + -942.3));
            break;
        case 62:
            imp = fabs((-219.1 * adc + 2609684)/(adc + -945.8));
            break;
        case 63:
            imp = fabs((-211.6 * adc + 2622195)/(adc + -949.6));
            break;
        case 64:
            imp = fabs((-235.9 * adc + 2716412)/(adc + -941.6));
            break;
        case 65:
            imp = fabs((-227.8 * adc + 2733882)/(adc + -943.2));
            break;
        case 66:
            imp = fabs((-231.3 * adc + 2774474)/(adc + -944.1));
            break;
        case 67:
            imp = fabs((-234.7 * adc + 2826485)/(adc + -941.4));
            break;
        case 68:
            imp = fabs((-247.3 * adc + 2896679)/(adc + -939.2));
            break;
        case 69:
            imp = fabs((-242.0 * adc + 2918759)/(adc + -940.0));
            break;
        case 70:
            imp = fabs((-241.5 * adc + 2954628)/(adc + -940.9));
            break;
        case 71:
            imp = fabs((-181.8 * adc + 2866827)/(adc + -948.0));
            break;
        case 72:
            imp = fabs((-234.6 * adc + 3010789)/(adc + -943.4));
            break;
        case 73:
            imp = fabs((-194.2 * adc + 2963986)/(adc + -948.0));
            break;
        case 74:
            imp = fabs((-181.7 * adc + 2980490)/(adc + -948.5));
            break;
        case 75:
            imp = fabs((-191.3 * adc + 3043168)/(adc + -946.7));
            break;
        case 76:
            imp = fabs((-142.9 * adc + 2976353)/(adc + -951.8));
            break;
        case 77:
            imp = fabs((-184.1 * adc + 3104472)/(adc + -946.7));
            break;
        case 78:
            imp = fabs((-142.2 * adc + 3046244)/(adc + -951.6));
            break;
        case 79:
            imp = fabs((-136.2 * adc + 3077808)/(adc + -951.4));
            break;
        case 80:
            imp = fabs((-199.4 * adc + 3223327)/(adc + -946.8));
            break;
        case 81:
            imp = fabs((-164.3 * adc + 3198257)/(adc + -948.8));
            break;
        case 82:
            imp = fabs((-154.0 * adc + 3222713)/(adc + -947.8));
            break;
        case 83:
            imp = fabs((-190.3 * adc + 3329301)/(adc + -945.7));
            break;
        case 84:
            imp = fabs((-136.4 * adc + 3246647)/(adc + -951.5));
            break;
        case 85:
            imp = fabs((-169.4 * adc + 3357140)/(adc + -947.9));
            break;
        case 86:
            imp = fabs((-110.5 * adc + 3268804)/(adc + -954.2));
            break;
        case 87:
            imp = fabs((-146.5 * adc + 3387855)/(adc + -949.4));
            break;
        case 88:
            imp = fabs((-150.6 * adc + 3436623)/(adc + -948.9));
            break;
        case 89:
            imp = fabs((-169.7 * adc + 3513958)/(adc + -947.3));
            break;
        case 90:
            imp = fabs((-142.5 * adc + 3484662)/(adc + -951.9));
            break;
        case 91:
            imp = fabs((-92.6 * adc + 3418182)/(adc + -955.3));
            break;
        case 92:
            imp = fabs((-179.4 * adc + 3654505)/(adc + -945.9));
            break;
        case 93:
            imp = fabs((-104.1 * adc + 3513050)/(adc + -954.9));
            break;
        case 94:
            imp = fabs((-145.5 * adc + 3645482)/(adc + -950.3));
            break;
        case 95:
            imp = fabs((-108.6 * adc + 3603269)/(adc + -953.2));
            break;
        case 96:
            imp = fabs((-125.9 * adc + 3674586)/(adc + -949.7));
            break;
        case 97:
            imp = fabs((-160.6 * adc + 3784270)/(adc + -947.3));
            break;
        case 98:
            imp = fabs((-124.0 * adc + 3733681)/(adc + -952.0));
            break;
        case 99:
            imp = fabs((-147.8 * adc + 3824458)/(adc + -949.9));
            break;
        case 100:
            imp = fabs((-153.8 * adc + 3882642)/(adc + -947.7));
            break;
        case 101:
            imp = fabs((-138.6 * adc + 3876611)/(adc + -951.0));
            break;
        case 102:
            imp = fabs((-130.7 * adc + 3899689)/(adc + -950.2));
            break;
        case 103:
            imp = fabs((-201.4 * adc + 4112422)/(adc + -941.6));
            break;
        case 104:
            imp = fabs((-163.9 * adc + 4043431)/(adc + -948.6));
            break;
        case 105:
            imp = fabs((-198.1 * adc + 4166193)/(adc + -944.0));
            break;
        case 106:
            imp = fabs((-129.8 * adc + 4043573)/(adc + -951.8));
            break;
        case 107:
            imp = fabs((-149.5 * adc + 4127470)/(adc + -949.6));
            break;
        case 108:
            imp = fabs((-120.7 * adc + 4096747)/(adc + -952.6));
            break;
        case 109:
            imp = fabs((-144.8 * adc + 4179004)/(adc + -952.2));
            break;
        case 110:
            imp = fabs((-153.2 * adc + 4245554)/(adc + -948.9));
            break;
        case 111:
            imp = fabs((-182.0 * adc + 4351041)/(adc + -946.1));
            break;
        case 112:
            imp = fabs((-143.2 * adc + 4271793)/(adc + -952.4));
            break;
        case 113:
            imp = fabs((-156.3 * adc + 4345009)/(adc + -949.1));
            break;
        case 114:
            imp = fabs((-171.8 * adc + 4418143)/(adc + -947.7));
            break;
        case 115:
            imp = fabs((-193.5 * adc + 4511824)/(adc + -944.2));
            break;
        case 116:
            imp = fabs((-167.5 * adc + 4488319)/(adc + -947.2));
            break;
        case 117:
            imp = fabs((-194.0 * adc + 4588519)/(adc + -944.0));
            break;
        case 118:
            imp = fabs((-219.3 * adc + 4697734)/(adc + -939.7));
            break;
        case 119:
            imp = fabs((-175.4 * adc + 4611151)/(adc + -947.6));
            break;
        case 120:
            imp = fabs((-178.7 * adc + 4661502)/(adc + -946.2));
            break;
        case 121:
            imp = fabs((-177.0 * adc + 4685482)/(adc + -948.4));
            break;
        case 122:
            imp = fabs((-225.6 * adc + 4860068)/(adc + -939.9));
            break;
        case 123:
            imp = fabs((-190.2 * adc + 4801103)/(adc + -945.9));
            break;
        case 124:
            imp = fabs((-218.0 * adc + 4904401)/(adc + -943.2));
            break;
        case 125:
            imp = fabs((-168.6 * adc + 4814897)/(adc + -949.8));
            break;
        case 126:
            imp = fabs((-171.4 * adc + 4864758)/(adc + -948.2));
            break;
        case 127:
            imp = fabs((-223.0 * adc + 5033683)/(adc + -942.0));
            break;
        case 128:
            imp = fabs((-228.7 * adc + 5066185)/(adc + -942.3));
            break;
        case 129:
            imp = fabs((-170.4 * adc + 4951801)/(adc + -949.3));
            break;
        case 130:
            imp = fabs((-231.2 * adc + 5152770)/(adc + -940.6));
            break;
        case 131:
            imp = fabs((-232.1 * adc + 5193038)/(adc + -940.7));
            break;
        case 132:
            imp = fabs((-231.3 * adc + 5228806)/(adc + -940.5));
            break;
        case 133:
            imp = fabs((-262.7 * adc + 5356973)/(adc + -935.4));
            break;
        case 134:
            imp = fabs((-211.2 * adc + 5260197)/(adc + -941.0));
            break;
        case 135:
            imp = fabs((-206.8 * adc + 5275866)/(adc + -943.7));
            break;
        case 136:
            imp = fabs((-242.8 * adc + 5411441)/(adc + -938.6));
            break;
        case 137:
            imp = fabs((-231.6 * adc + 5420411)/(adc + -940.7));
            break;
        case 138:
            imp = fabs((-236.7 * adc + 5463410)/(adc + -942.1));
            break;
        case 139:
            imp = fabs((-226.0 * adc + 5480836)/(adc + -941.8));
            break;
        case 140:
            imp = fabs((-241.6 * adc + 5560935)/(adc + -939.1));
            break;
        case 141:
            imp = fabs((-268.1 * adc + 5680850)/(adc + -933.9));
            break;
        case 142:
            imp = fabs((-230.9 * adc + 5606297)/(adc + -940.9));
            break;
        case 143:
            imp = fabs((-250.0 * adc + 5691785)/(adc + -938.8));
            break;
        case 144:
            imp = fabs((-271.0 * adc + 5768997)/(adc + -937.2));
            break;
        case 145:
            imp = fabs((-204.9 * adc + 5614336)/(adc + -947.3));
            break;
        case 146:
            imp = fabs((-227.1 * adc + 5722854)/(adc + -942.5));
            break;
        case 147:
            imp = fabs((-256.7 * adc + 5842647)/(adc + -938.4));
            break;
        case 148:
            imp = fabs((-230.0 * adc + 5794399)/(adc + -943.9));
            break;
        case 149:
            imp = fabs((-241.1 * adc + 5870865)/(adc + -940.3));
            break;
        case 150:
            imp = fabs((-253.2 * adc + 5958651)/(adc + -937.1));
            break;
        case 151:
            imp = fabs((-236.7 * adc + 5936150)/(adc + -941.3));
            break;
        case 152:
            imp = fabs((-257.3 * adc + 6031061)/(adc + -938.5));
            break;
        case 153:
            imp = fabs((-227.8 * adc + 5984582)/(adc + -943.0));
            break;
        case 154:
            imp = fabs((-244.7 * adc + 6067633)/(adc + -940.6));
            break;
        case 155:
            imp = fabs((-260.8 * adc + 6166816)/(adc + -936.2));
            break;
        case 156:
            imp = fabs((-234.6 * adc + 6120597)/(adc + -941.3));
            break;
        case 157:
            imp = fabs((-260.7 * adc + 6237588)/(adc + -936.8));
            break;
        case 158:
            imp = fabs((-271.0 * adc + 6305337)/(adc + -935.7));
            break;
        case 159:
            imp = fabs((-284.8 * adc + 6387384)/(adc + -933.3));
            break;
        case 160:
            imp = fabs((-243.7 * adc + 6279689)/(adc + -940.5));
            break;
        case 161:
            imp = fabs((-277.5 * adc + 6415424)/(adc + -935.4));
            break;
        case 162:
            imp = fabs((-239.3 * adc + 6342536)/(adc + -941.3));
            break;
        case 163:
            imp = fabs((-288.5 * adc + 6530745)/(adc + -933.1));
            break;
        case 164:
            imp = fabs((-249.0 * adc + 6439257)/(adc + -940.7));
            break;
        case 165:
            imp = fabs((-247.0 * adc + 6474980)/(adc + -940.3));
            break;
        case 166:
            imp = fabs((-241.4 * adc + 6491374)/(adc + -941.7));
            break;
        case 167:
            imp = fabs((-277.9 * adc + 6651478)/(adc + -935.0));
            break;
        case 168:
            imp = fabs((-263.2 * adc + 6645521)/(adc + -935.8));
            break;
        case 169:
            imp = fabs((-243.1 * adc + 6609553)/(adc + -941.8));
            break;
        case 170:
            imp = fabs((-231.6 * adc + 6617954)/(adc + -942.0));
            break;
        case 171:
            imp = fabs((-282.8 * adc + 6818388)/(adc + -933.5));
            break;
        case 172:
            imp = fabs((-299.9 * adc + 6926131)/(adc + -928.2));
            break;
        case 173:
            imp = fabs((-258.3 * adc + 6818864)/(adc + -937.5));
            break;
        case 174:
            imp = fabs((-198.2 * adc + 6666559)/(adc + -947.2));
            break;
        case 175:
            imp = fabs((-674.2 * adc + 7627415)/(adc + -938.7));
            break;
        case 176:
            imp = fabs((-84.9 * adc + 6519033)/(adc + -949.5));
            break;
        case 177:
            imp = fabs((-133.5 * adc + 6662780)/(adc + -948.2));
            break;
        case 178:
            imp = fabs((-417.5 * adc + 7268007)/(adc + -941.5));
            break;
        case 179:
            imp = fabs((-596.4 * adc + 7607976)/(adc + -940.7));
            break;
        case 180:
            imp = fabs((-63.6 * adc + 6631951)/(adc + -949.4));
            break;
        case 181:
            imp = fabs((-224.3 * adc + 7009534)/(adc + -945.5));
            break;
        case 182:
            imp = fabs((109.9 * adc + 6365231)/(adc + -953.1));
            break;
        case 183:
            imp = fabs((-195.4 * adc + 6976013)/(adc + -948.6));
            break;
        case 184:
            imp = fabs((-849.1 * adc + 8316016)/(adc + -936.6));
            break;
        case 185:
            imp = fabs((-381.2 * adc + 7428498)/(adc + -943.9));
            break;
        case 186:
            imp = fabs((-573.3 * adc + 7839943)/(adc + -941.2));
            break;
        case 187:
            imp = fabs((144.2 * adc + 6466738)/(adc + -952.9));
            break;
        case 188:
            imp = fabs((-194.3 * adc + 7189815)/(adc + -947.4));
            break;
        case 189:
            imp = fabs((-188.5 * adc + 7196216)/(adc + -948.6));
            break;
        case 190:
            imp = fabs((-143.5 * adc + 7149534)/(adc + -949.4));
            break;
        case 191:
            imp = fabs((3.1 * adc + 6907909)/(adc + -950.4));
            break;
        case 192:
            imp = fabs((-437.4 * adc + 7793961)/(adc + -944.4));
            break;
        case 193:
            imp = fabs((-366.2 * adc + 7680251)/(adc + -944.8));
            break;
        case 194:
            imp = fabs((-388.4 * adc + 7800876)/(adc + -942.3));
            break;
        case 195:
            imp = fabs((-976.0 * adc + 8989650)/(adc + -934.7));
            break;
        case 196:
            imp = fabs((-161.9 * adc + 7432190)/(adc + -947.0));
            break;
        case 197:
            imp = fabs((-115.6 * adc + 7345750)/(adc + -947.1));
            break;
        case 198:
            imp = fabs((-200.8 * adc + 7545060)/(adc + -947.5));
            break;
        case 199:
            imp = fabs((-61.9 * adc + 7344295)/(adc + -947.6));
            break;
        case 200:
            imp = fabs((14.5 * adc + 7205867)/(adc + -951.1));
            break;
        case 201:
            imp = fabs((-181.2 * adc + 7631514)/(adc + -947.5));
            break;
        case 202:
            imp = fabs((-150.9 * adc + 7580215)/(adc + -948.8));
            break;
        case 203:
            imp = fabs((-243.9 * adc + 7846639)/(adc + -945.3));
            break;
        case 204:
            imp = fabs((-772.9 * adc + 8979624)/(adc + -936.1));
            break;
        case 205:
            imp = fabs((-624.8 * adc + 8699484)/(adc + -937.4));
            break;
        case 206:
            imp = fabs((-670.8 * adc + 8859156)/(adc + -936.3));
            break;
        case 207:
            imp = fabs((-427.6 * adc + 8376084)/(adc + -941.0));
            break;
        case 208:
            imp = fabs((19.5 * adc + 7459595)/(adc + -950.6));
            break;
        case 209:
            imp = fabs((80.3 * adc + 7393506)/(adc + -950.8));
            break;
        case 210:
            imp = fabs((-176.5 * adc + 7943609)/(adc + -946.4));
            break;
        case 211:
            imp = fabs((-428.4 * adc + 8477135)/(adc + -944.9));
            break;
        case 212:
            imp = fabs((-175.2 * adc + 8022101)/(adc + -948.0));
            break;
        case 213:
            imp = fabs((-393.7 * adc + 8512271)/(adc + -943.2));
            break;
        case 214:
            imp = fabs((-207.3 * adc + 8132904)/(adc + -947.6));
            break;
        case 215:
            imp = fabs((-109.5 * adc + 7959156)/(adc + -949.5));
            break;
        case 216:
            imp = fabs((-299.4 * adc + 8369149)/(adc + -947.1));
            break;
        case 217:
            imp = fabs((-200.3 * adc + 8235231)/(adc + -948.0));
            break;
        case 218:
            imp = fabs((-191.9 * adc + 8248631)/(adc + -949.5));
            break;
        case 219:
            imp = fabs((-197.2 * adc + 8313417)/(adc + -946.4));
            break;
        case 220:
            imp = fabs((-221.9 * adc + 8417865)/(adc + -945.8));
            break;
        case 221:
            imp = fabs((-230.2 * adc + 8461474)/(adc + -946.7));
            break;
        case 222:
            imp = fabs((-228.8 * adc + 8519568)/(adc + -944.1));
            break;
        case 223:
            imp = fabs((-204.4 * adc + 8478794)/(adc + -947.2));
            break;
        case 224:
            imp = fabs((-200.8 * adc + 8491194)/(adc + -947.4));
            break;
        case 225:
            imp = fabs((-202.9 * adc + 8561655)/(adc + -943.7));
            break;
        case 226:
            imp = fabs((-193.0 * adc + 8529501)/(adc + -950.3));
            break;
        case 227:
            imp = fabs((-188.9 * adc + 8554202)/(adc + -949.8));
            break;
        case 228:
            imp = fabs((-206.3 * adc + 8652842)/(adc + -947.1));
            break;
        case 229:
            imp = fabs((-173.1 * adc + 8584802)/(adc + -951.1));
            break;
        case 230:
            imp = fabs((-210.9 * adc + 8742194)/(adc + -946.2));
            break;
        case 231:
            imp = fabs((-191.2 * adc + 8716033)/(adc + -948.6));
            break;
        case 232:
            imp = fabs((-179.3 * adc + 8721456)/(adc + -949.9));
            break;
        case 233:
            imp = fabs((-247.1 * adc + 8955748)/(adc + -944.1));
            break;
        case 234:
            imp = fabs((-227.5 * adc + 8922700)/(adc + -947.8));
            break;
        case 235:
            imp = fabs((-186.1 * adc + 8848491)/(adc + -950.6));
            break;
        case 236:
            imp = fabs((-228.8 * adc + 9018994)/(adc + -945.8));
            break;
        case 237:
            imp = fabs((-192.9 * adc + 8947669)/(adc + -949.4));
            break;
        case 238:
            imp = fabs((-228.4 * adc + 9070404)/(adc + -948.0));
            break;
        case 239:
            imp = fabs((-237.8 * adc + 9159508)/(adc + -944.1));
            break;
        case 240:
            imp = fabs((-235.5 * adc + 9158071)/(adc + -946.4));
            break;
        case 241:
            imp = fabs((-204.3 * adc + 9113982)/(adc + -947.7));
            break;
        case 242:
            imp = fabs((-243.7 * adc + 9261799)/(adc + -945.8));
            break;
        case 243:
            imp = fabs((-244.4 * adc + 9317834)/(adc + -943.3));
            break;
        case 244:
            imp = fabs((-236.5 * adc + 9333428)/(adc + -944.1));
            break;
        case 245:
            imp = fabs((-212.8 * adc + 9289694)/(adc + -947.0));
            break;
        case 246:
            imp = fabs((-233.6 * adc + 9378431)/(adc + -946.9));
            break;
        case 247:
            imp = fabs((-240.0 * adc + 9422627)/(adc + -947.9));
            break;
        case 248:
            imp = fabs((-196.2 * adc + 9330681)/(adc + -950.9));
            break;
        case 249:
            imp = fabs((-290.1 * adc + 9614785)/(adc + -945.5));
            break;
        case 250:
            imp = fabs((-221.7 * adc + 9505503)/(adc + -946.4));
            break;
        case 251:
            imp = fabs((-280.8 * adc + 9678657)/(adc + -944.9));
            break;
        case 252:
            imp = fabs((-165.4 * adc + 9452270)/(adc + -948.2));
            break;
        case 253:
            imp = fabs((-260.8 * adc + 9694771)/(adc + -946.3));
            break;
        case 254:
            imp = fabs((-278.8 * adc + 9785940)/(adc + -945.7));
            break;
       }
       return imp;
}
