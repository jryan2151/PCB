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
            imp = fabs((-168.7 * adc + 305469)/(adc + -1010.2));
            break;
        case 3:
            imp = fabs((-161.1 * adc + 329336)/(adc + -1047.2));
            break;
        case 4:
            imp = fabs((-173.7 * adc + 389820)/(adc + -1000.3));
            break;
        case 5:
            imp = fabs((-240.4 * adc + 578478)/(adc + -763.9));
            break;
        case 6:
            imp = fabs((-366.3 * adc + 931028)/(adc + -300.9));
            break;
        case 7:
            imp = fabs((-334.8 * adc + 898972)/(adc + -507.1));
            break;
        case 8:
            imp = fabs((-249.9 * adc + 708633)/(adc + -938.8));
            break;
        case 9:
            imp = fabs((-384.4 * adc + 1128668)/(adc + -405.9));
            break;
        case 10:
            imp = fabs((-288.5 * adc + 898481)/(adc + -768.7));
            break;
        case 11:
            imp = fabs((-319.6 * adc + 1030760)/(adc + -695.3));
            break;
        case 12:
            imp = fabs((-230.8 * adc + 823824)/(adc + -904.9));
            break;
        case 13:
            imp = fabs((-248.3 * adc + 905761)/(adc + -882.8));
            break;
        case 14:
            imp = fabs((-264.7 * adc + 988155)/(adc + -860.9));
            break;
        case 15:
            imp = fabs((-280.0 * adc + 1069568)/(adc + -839.2));
            break;
        case 16:
            imp = fabs((-303.7 * adc + 1168190)/(adc + -799.0));
            break;
        case 17:
            imp = fabs((-224.3 * adc + 982937)/(adc + -919.7));
            break;
        case 18:
            imp = fabs((-234.2 * adc + 1044767)/(adc + -914.1));
            break;
        case 19:
            imp = fabs((-245.9 * adc + 1112072)/(adc + -902.7));
            break;
        case 20:
            imp = fabs((-255.2 * adc + 1174076)/(adc + -894.7));
            break;
        case 21:
            imp = fabs((-263.2 * adc + 1234101)/(adc + -887.2));
            break;
        case 22:
            imp = fabs((-274.4 * adc + 1305355)/(adc + -876.9));
            break;
        case 23:
            imp = fabs((-199.4 * adc + 1140438)/(adc + -947.9));
            break;
        case 24:
            imp = fabs((-204.4 * adc + 1189024)/(adc + -947.0));
            break;
        case 25:
            imp = fabs((-209.0 * adc + 1237790)/(adc + -945.4));
            break;
        case 26:
            imp = fabs((-214.6 * adc + 1288938)/(adc + -943.7));
            break;
        case 27:
            imp = fabs((-225.6 * adc + 1356370)/(adc + -938.4));
            break;
        case 28:
            imp = fabs((-224.7 * adc + 1390477)/(adc + -939.5));
            break;
        case 29:
            imp = fabs((-229.8 * adc + 1440209)/(adc + -936.7));
            break;
        case 30:
            imp = fabs((-235.5 * adc + 1491743)/(adc + -934.7));
            break;
        case 31:
            imp = fabs((-243.0 * adc + 1547953)/(adc + -931.9));
            break;
        case 32:
            imp = fabs((-240.2 * adc + 1563009)/(adc + -934.7));
            break;
        case 33:
            imp = fabs((-197.2 * adc + 1499876)/(adc + -948.1));
            break;
        case 34:
            imp = fabs((-190.6 * adc + 1521707)/(adc + -950.1));
            break;
        case 35:
            imp = fabs((-176.4 * adc + 1523540)/(adc + -954.1));
            break;
        case 36:
            imp = fabs((-183.0 * adc + 1574473)/(adc + -952.4));
            break;
        case 37:
            imp = fabs((-205.1 * adc + 1667006)/(adc + -945.6));
            break;
        case 38:
            imp = fabs((-214.0 * adc + 1725101)/(adc + -943.5));
            break;
        case 39:
            imp = fabs((-200.7 * adc + 1729944)/(adc + -946.9));
            break;
        case 40:
            imp = fabs((-211.8 * adc + 1794146)/(adc + -944.4));
            break;
        case 41:
            imp = fabs((-207.1 * adc + 1818500)/(adc + -946.5));
            break;
        case 42:
            imp = fabs((-202.9 * adc + 1841577)/(adc + -948.4));
            break;
        case 43:
            imp = fabs((-223.0 * adc + 1932755)/(adc + -942.7));
            break;
        case 44:
            imp = fabs((-210.2 * adc + 1935048)/(adc + -946.2));
            break;
        case 45:
            imp = fabs((-205.4 * adc + 1957217)/(adc + -948.1));
            break;
        case 46:
            imp = fabs((-223.3 * adc + 2042908)/(adc + -943.1));
            break;
        case 47:
            imp = fabs((-214.2 * adc + 2052774)/(adc + -945.8));
            break;
        case 48:
            imp = fabs((-207.8 * adc + 2057866)/(adc + -948.8));
            break;
        case 49:
            imp = fabs((-215.7 * adc + 2114644)/(adc + -946.7));
            break;
        case 50:
            imp = fabs((-220.6 * adc + 2163421)/(adc + -945.6));
            break;
        case 51:
            imp = fabs((-208.8 * adc + 2177122)/(adc + -947.1));
            break;
        case 52:
            imp = fabs((-213.8 * adc + 2227643)/(adc + -945.8));
            break;
        case 53:
            imp = fabs((-200.8 * adc + 2233576)/(adc + -947.8));
            break;
        case 54:
            imp = fabs((-217.6 * adc + 2309746)/(adc + -945.0));
            break;
        case 55:
            imp = fabs((-218.9 * adc + 2348444)/(adc + -945.4));
            break;
        case 56:
            imp = fabs((-206.4 * adc + 2353344)/(adc + -948.3));
            break;
        case 57:
            imp = fabs((-207.9 * adc + 2393533)/(adc + -948.7));
            break;
        case 58:
            imp = fabs((-215.5 * adc + 2453720)/(adc + -946.2));
            break;
        case 59:
            imp = fabs((-231.4 * adc + 2534790)/(adc + -942.1));
            break;
        case 60:
            imp = fabs((-230.9 * adc + 2571455)/(adc + -941.9));
            break;
        case 61:
            imp = fabs((-214.0 * adc + 2561495)/(adc + -946.6));
            break;
        case 62:
            imp = fabs((-232.0 * adc + 2647933)/(adc + -941.7));
            break;
        case 63:
            imp = fabs((-231.8 * adc + 2683061)/(adc + -942.1));
            break;
        case 64:
            imp = fabs((-236.5 * adc + 2718465)/(adc + -940.7));
            break;
        case 65:
            imp = fabs((-224.2 * adc + 2717351)/(adc + -945.3));
            break;
        case 66:
            imp = fabs((-237.7 * adc + 2793005)/(adc + -941.8));
            break;
        case 67:
            imp = fabs((-223.9 * adc + 2793879)/(adc + -944.6));
            break;
        case 68:
            imp = fabs((-228.3 * adc + 2845154)/(adc + -942.8));
            break;
        case 69:
            imp = fabs((-254.2 * adc + 2952029)/(adc + -937.3));
            break;
        case 70:
            imp = fabs((-235.3 * adc + 2939296)/(adc + -941.6));
            break;
        case 71:
            imp = fabs((-181.4 * adc + 2870913)/(adc + -946.7));
            break;
        case 72:
            imp = fabs((-167.9 * adc + 2883913)/(adc + -947.7));
            break;
        case 73:
            imp = fabs((-172.0 * adc + 2928046)/(adc + -947.5));
            break;
        case 74:
            imp = fabs((-199.4 * adc + 3014628)/(adc + -946.4));
            break;
        case 75:
            imp = fabs((-218.2 * adc + 3080819)/(adc + -946.7));
            break;
        case 76:
            imp = fabs((-168.0 * adc + 3030264)/(adc + -948.9));
            break;
        case 77:
            imp = fabs((-168.2 * adc + 3062286)/(adc + -949.5));
            break;
        case 78:
            imp = fabs((-180.4 * adc + 3134426)/(adc + -946.7));
            break;
        case 79:
            imp = fabs((-173.1 * adc + 3150227)/(adc + -948.2));
            break;
        case 80:
            imp = fabs((-123.9 * adc + 3066903)/(adc + -953.3));
            break;
        case 81:
            imp = fabs((-127.1 * adc + 3121308)/(adc + -951.3));
            break;
        case 82:
            imp = fabs((-123.5 * adc + 3151178)/(adc + -951.7));
            break;
        case 83:
            imp = fabs((-135.0 * adc + 3206868)/(adc + -951.7));
            break;
        case 84:
            imp = fabs((-136.4 * adc + 3247536)/(adc + -951.4));
            break;
        case 85:
            imp = fabs((-229.7 * adc + 3490047)/(adc + -941.1));
            break;
        case 86:
            imp = fabs((-175.9 * adc + 3407703)/(adc + -947.1));
            break;
        case 87:
            imp = fabs((-168.3 * adc + 3434643)/(adc + -947.6));
            break;
        case 88:
            imp = fabs((-198.7 * adc + 3538604)/(adc + -944.0));
            break;
        case 89:
            imp = fabs((-127.6 * adc + 3425420)/(adc + -950.2));
            break;
        case 90:
            imp = fabs((-138.6 * adc + 3478674)/(adc + -951.0));
            break;
        case 91:
            imp = fabs((-160.6 * adc + 3576388)/(adc + -947.2));
            break;
        case 92:
            imp = fabs((-153.5 * adc + 3592662)/(adc + -947.9));
            break;
        case 93:
            imp = fabs((-70.8 * adc + 3436506)/(adc + -958.4));
            break;
        case 94:
            imp = fabs((-92.0 * adc + 3529618)/(adc + -954.6));
            break;
        case 95:
            imp = fabs((-151.2 * adc + 3693881)/(adc + -948.7));
            break;
        case 96:
            imp = fabs((-121.7 * adc + 3657335)/(adc + -951.6));
            break;
        case 97:
            imp = fabs((-176.4 * adc + 3814739)/(adc + -946.7));
            break;
        case 98:
            imp = fabs((-127.6 * adc + 3742553)/(adc + -951.0));
            break;
        case 99:
            imp = fabs((-180.1 * adc + 3903965)/(adc + -945.4));
            break;
        case 100:
            imp = fabs((-183.1 * adc + 3948679)/(adc + -944.3));
            break;
        case 101:
            imp = fabs((-145.0 * adc + 3900647)/(adc + -947.5));
            break;
        case 102:
            imp = fabs((-173.9 * adc + 3992837)/(adc + -947.1));
            break;
        case 103:
            imp = fabs((-182.9 * adc + 4060472)/(adc + -944.3));
            break;
        case 104:
            imp = fabs((-160.7 * adc + 4042100)/(adc + -947.9));
            break;
        case 105:
            imp = fabs((-154.6 * adc + 4062953)/(adc + -949.2));
            break;
        case 106:
            imp = fabs((-186.2 * adc + 4184660)/(adc + -943.7));
            break;
        case 107:
            imp = fabs((-122.2 * adc + 4061862)/(adc + -951.8));
            break;
        case 108:
            imp = fabs((-119.0 * adc + 4082207)/(adc + -954.0));
            break;
        case 109:
            imp = fabs((-187.4 * adc + 4290385)/(adc + -945.3));
            break;
        case 110:
            imp = fabs((-153.6 * adc + 4239812)/(adc + -950.0));
            break;
        case 111:
            imp = fabs((-178.9 * adc + 4340015)/(adc + -946.5));
            break;
        case 112:
            imp = fabs((-165.1 * adc + 4325877)/(adc + -949.0));
            break;
        case 113:
            imp = fabs((-138.7 * adc + 4302007)/(adc + -951.2));
            break;
        case 114:
            imp = fabs((-189.7 * adc + 4467990)/(adc + -944.6));
            break;
        case 115:
            imp = fabs((-193.8 * adc + 4513091)/(adc + -944.8));
            break;
        case 116:
            imp = fabs((-229.0 * adc + 4633835)/(adc + -941.0));
            break;
        case 117:
            imp = fabs((-134.4 * adc + 4436709)/(adc + -951.8));
            break;
        case 118:
            imp = fabs((-221.3 * adc + 4689296)/(adc + -942.3));
            break;
        case 119:
            imp = fabs((-146.2 * adc + 4532145)/(adc + -951.3));
            break;
        case 120:
            imp = fabs((-200.2 * adc + 4713582)/(adc + -944.2));
            break;
        case 121:
            imp = fabs((-204.4 * adc + 4762540)/(adc + -943.3));
            break;
        case 122:
            imp = fabs((-163.7 * adc + 4692967)/(adc + -948.9));
            break;
        case 123:
            imp = fabs((-178.0 * adc + 4771432)/(adc + -947.4));
            break;
        case 124:
            imp = fabs((-204.1 * adc + 4873077)/(adc + -944.8));
            break;
        case 125:
            imp = fabs((-200.8 * adc + 4907532)/(adc + -944.0));
            break;
        case 126:
            imp = fabs((-177.8 * adc + 4864403)/(adc + -950.5));
            break;
        case 127:
            imp = fabs((-208.0 * adc + 4986313)/(adc + -945.1));
            break;
        case 128:
            imp = fabs((-229.2 * adc + 5085659)/(adc + -939.4));
            break;
        case 129:
            imp = fabs((-229.8 * adc + 5110942)/(adc + -940.8));
            break;
        case 130:
            imp = fabs((-221.6 * adc + 5124443)/(adc + -942.3));
            break;
        case 131:
            imp = fabs((-201.1 * adc + 5114898)/(adc + -943.5));
            break;
        case 132:
            imp = fabs((-229.6 * adc + 5226057)/(adc + -941.0));
            break;
        case 133:
            imp = fabs((-203.3 * adc + 5178404)/(adc + -945.9));
            break;
        case 134:
            imp = fabs((-219.9 * adc + 5280414)/(adc + -941.1));
            break;
        case 135:
            imp = fabs((-227.9 * adc + 5335787)/(adc + -940.7));
            break;
        case 136:
            imp = fabs((-256.3 * adc + 5451595)/(adc + -936.7));
            break;
        case 137:
            imp = fabs((-210.3 * adc + 5356436)/(adc + -943.5));
            break;
        case 138:
            imp = fabs((-267.0 * adc + 5549264)/(adc + -936.2));
            break;
        case 139:
            imp = fabs((-263.5 * adc + 5587304)/(adc + -935.2));
            break;
        case 140:
            imp = fabs((-249.4 * adc + 5584127)/(adc + -938.4));
            break;
        case 141:
            imp = fabs((-255.7 * adc + 5635072)/(adc + -937.5));
            break;
        case 142:
            imp = fabs((-273.7 * adc + 5731440)/(adc + -933.9));
            break;
        case 143:
            imp = fabs((-268.6 * adc + 5757069)/(adc + -933.7));
            break;
        case 144:
            imp = fabs((-241.9 * adc + 5697877)/(adc + -939.6));
            break;
        case 145:
            imp = fabs((-249.2 * adc + 5747686)/(adc + -939.2));
            break;
        case 146:
            imp = fabs((-272.6 * adc + 5851643)/(adc + -936.6));
            break;
        case 147:
            imp = fabs((-244.9 * adc + 5803217)/(adc + -941.6));
            break;
        case 148:
            imp = fabs((-278.3 * adc + 5958337)/(adc + -932.2));
            break;
        case 149:
            imp = fabs((-265.4 * adc + 5942867)/(adc + -937.8));
            break;
        case 150:
            imp = fabs((-282.3 * adc + 6039758)/(adc + -932.4));
            break;
        case 151:
            imp = fabs((-234.5 * adc + 5926828)/(adc + -941.8));
            break;
        case 152:
            imp = fabs((-273.7 * adc + 6083015)/(adc + -936.0));
            break;
        case 153:
            imp = fabs((-243.4 * adc + 6031134)/(adc + -940.0));
            break;
        case 154:
            imp = fabs((-246.7 * adc + 6075668)/(adc + -940.4));
            break;
        case 155:
            imp = fabs((-301.1 * adc + 6289191)/(adc + -929.8));
            break;
        case 156:
            imp = fabs((-259.5 * adc + 6198649)/(adc + -937.1));
            break;
        case 157:
            imp = fabs((-246.1 * adc + 6188266)/(adc + -939.9));
            break;
        case 158:
            imp = fabs((-279.3 * adc + 6326218)/(adc + -934.2));
            break;
        case 159:
            imp = fabs((-253.3 * adc + 6288226)/(adc + -938.5));
            break;
        case 160:
            imp = fabs((-254.8 * adc + 6299192)/(adc + -941.2));
            break;
        case 161:
            imp = fabs((-258.7 * adc + 6371434)/(adc + -937.2));
            break;
        case 162:
            imp = fabs((-263.8 * adc + 6420337)/(adc + -936.9));
            break;
        case 163:
            imp = fabs((-282.1 * adc + 6514314)/(adc + -933.4));
            break;
        case 164:
            imp = fabs((-305.2 * adc + 6625426)/(adc + -929.0));
            break;
        case 165:
            imp = fabs((-267.9 * adc + 6541732)/(adc + -935.9));
            break;
        case 166:
            imp = fabs((-287.3 * adc + 6637920)/(adc + -933.5));
            break;
        case 167:
            imp = fabs((-260.8 * adc + 6594935)/(adc + -938.3));
            break;
        case 168:
            imp = fabs((-255.2 * adc + 6603922)/(adc + -940.3));
            break;
        case 169:
            imp = fabs((-270.7 * adc + 6701255)/(adc + -936.4));
            break;
        case 170:
            imp = fabs((-274.2 * adc + 6750594)/(adc + -935.2));
            break;
        case 171:
            imp = fabs((-287.3 * adc + 6829073)/(adc + -932.8));
            break;
        case 172:
            imp = fabs((-281.8 * adc + 6854599)/(adc + -933.6));
            break;
        case 173:
            imp = fabs((-287.8 * adc + 6915256)/(adc + -931.7));
            break;
        case 174:
            imp = fabs((-445.4 * adc + 7195851)/(adc + -942.8));
            break;
        case 175:
            imp = fabs((-359.3 * adc + 7033471)/(adc + -943.8));
            break;
        case 176:
            imp = fabs((-115.7 * adc + 6572708)/(adc + -948.1));
            break;
        case 177:
            imp = fabs((-167.0 * adc + 6718480)/(adc + -948.4));
            break;
        case 178:
            imp = fabs((337.1 * adc + 5794328)/(adc + -954.8));
            break;
        case 179:
            imp = fabs((-119.4 * adc + 6700232)/(adc + -947.6));
            break;
        case 180:
            imp = fabs((-90.6 * adc + 6701993)/(adc + -948.2));
            break;
        case 181:
            imp = fabs((59.1 * adc + 6438098)/(adc + -950.3));
            break;
        case 182:
            imp = fabs((-416.9 * adc + 7412135)/(adc + -942.2));
            break;
        case 183:
            imp = fabs((-847.5 * adc + 8287029)/(adc + -935.6));
            break;
        case 184:
            imp = fabs((-523.6 * adc + 7656399)/(adc + -943.3));
            break;
        case 185:
            imp = fabs((-535.0 * adc + 7736088)/(adc + -942.3));
            break;
        case 186:
            imp = fabs((-763.8 * adc + 8260600)/(adc + -936.6));
            break;
        case 187:
            imp = fabs((-199.1 * adc + 7147993)/(adc + -948.3));
            break;
        case 188:
            imp = fabs((-429.6 * adc + 7656197)/(adc + -942.3));
            break;
        case 189:
            imp = fabs((-29.5 * adc + 6882096)/(adc + -949.4));
            break;
        case 190:
            imp = fabs((424.9 * adc + 6054022)/(adc + -956.3));
            break;
        case 191:
            imp = fabs((-489.9 * adc + 7896035)/(adc + -940.1));
            break;
        case 192:
            imp = fabs((-167.4 * adc + 7242886)/(adc + -947.8));
            break;
        case 193:
            imp = fabs((-587.6 * adc + 8148673)/(adc + -940.2));
            break;
        case 194:
            imp = fabs((-771.3 * adc + 8537291)/(adc + -937.2));
            break;
        case 195:
            imp = fabs((-507.5 * adc + 8015444)/(adc + -944.6));
            break;
        case 196:
            imp = fabs((-404.4 * adc + 7878740)/(adc + -944.0));
            break;
        case 197:
            imp = fabs((-357.0 * adc + 7804983)/(adc + -946.1));
            break;
        case 198:
            imp = fabs((26.6 * adc + 7081549)/(adc + -951.4));
            break;
        case 199:
            imp = fabs((-138.4 * adc + 7460428)/(adc + -947.5));
            break;
        case 200:
            imp = fabs((30.5 * adc + 1)/(adc + -0.0));
            break;
        case 201:
            imp = fabs((-342.1 * adc + 7981144)/(adc + -943.2));
            break;
        case 202:
            imp = fabs((366.6 * adc + 6541582)/(adc + -957.9));
            break;
        case 203:
            imp = fabs((-333.8 * adc + 8050515)/(adc + -942.4));
            break;
        case 204:
            imp = fabs((-472.4 * adc + 8309390)/(adc + -943.7));
            break;
        case 205:
            imp = fabs((-266.2 * adc + 7927388)/(adc + -947.0));
            break;
        case 206:
            imp = fabs((-402.7 * adc + 8238604)/(adc + -946.2));
            break;
        case 207:
            imp = fabs((-16.0 * adc + 7500342)/(adc + -952.2));
            break;
        case 208:
            imp = fabs((199.2 * adc + 7066310)/(adc + -955.8));
            break;
        case 209:
            imp = fabs((-65.7 * adc + 7680116)/(adc + -949.3));
            break;
        case 210:
            imp = fabs((179.2 * adc + 7217913)/(adc + -952.2));
            break;
        case 211:
            imp = fabs((-176.9 * adc + 8027989)/(adc + -944.9));
            break;
        case 212:
            imp = fabs((-438.9 * adc + 8599769)/(adc + -939.2));
            break;
        case 213:
            imp = fabs((-528.4 * adc + 8840064)/(adc + -939.4));
            break;
        case 214:
            imp = fabs((-875.2 * adc + 9556131)/(adc + -934.0));
            break;
        case 215:
            imp = fabs((-1029.9 * adc + 9915651)/(adc + -933.0));
            break;
        case 216:
            imp = fabs((-501.8 * adc + 8835696)/(adc + -942.4));
            break;
        case 217:
            imp = fabs((-220.8 * adc + 8293806)/(adc + -947.8));
            break;
        case 218:
            imp = fabs((-182.7 * adc + 8222729)/(adc + -950.1));
            break;
        case 219:
            imp = fabs((-205.9 * adc + 8323347)/(adc + -948.9));
            break;
        case 220:
            imp = fabs((-226.5 * adc + 8435587)/(adc + -943.9));
            break;
        case 221:
            imp = fabs((-198.0 * adc + 8375911)/(adc + -948.4));
            break;
        case 222:
            imp = fabs((-233.5 * adc + 8536828)/(adc + -942.9));
            break;
        case 223:
            imp = fabs((-224.8 * adc + 8531613)/(adc + -945.8));
            break;
        case 224:
            imp = fabs((-197.2 * adc + 8480404)/(adc + -947.7));
            break;
        case 225:
            imp = fabs((-193.7 * adc + 8512173)/(adc + -947.0));
            break;
        case 226:
            imp = fabs((-217.7 * adc + 8625501)/(adc + -944.4));
            break;
        case 227:
            imp = fabs((-210.1 * adc + 8619193)/(adc + -948.4));
            break;
        case 228:
            imp = fabs((-196.9 * adc + 8618955)/(adc + -949.1));
            break;
        case 229:
            imp = fabs((-191.9 * adc + 8643363)/(adc + -948.9));
            break;
        case 230:
            imp = fabs((-212.4 * adc + 8736909)/(adc + -946.5));
            break;
        case 231:
            imp = fabs((-202.4 * adc + 8753896)/(adc + -947.2));
            break;
        case 232:
            imp = fabs((-206.6 * adc + 8819409)/(adc + -945.6));
            break;
        case 233:
            imp = fabs((-202.2 * adc + 8823641)/(adc + -948.7));
            break;
        case 234:
            imp = fabs((-206.2 * adc + 8863470)/(adc + -948.6));
            break;
        case 235:
            imp = fabs((-194.9 * adc + 8859101)/(adc + -951.1));
            break;
        case 236:
            imp = fabs((-197.0 * adc + 8916099)/(adc + -948.9));
            break;
        case 237:
            imp = fabs((-196.4 * adc + 8954094)/(adc + -949.4));
            break;
        case 238:
            imp = fabs((-198.6 * adc + 8991698)/(adc + -949.5));
            break;
        case 239:
            imp = fabs((-192.5 * adc + 9035072)/(adc + -946.5));
            break;
        case 240:
            imp = fabs((-178.9 * adc + 8975903)/(adc + -953.9));
            break;
        case 241:
            imp = fabs((-253.8 * adc + 9272128)/(adc + -942.0));
            break;
        case 242:
            imp = fabs((-229.3 * adc + 9226845)/(adc + -945.5));
            break;
        case 243:
            imp = fabs((-245.5 * adc + 9308446)/(adc + -944.4));
            break;
        case 244:
            imp = fabs((-231.8 * adc + 9314318)/(adc + -944.4));
            break;
        case 245:
            imp = fabs((-231.6 * adc + 9344374)/(adc + -945.6));
            break;
        case 246:
            imp = fabs((-220.1 * adc + 9355630)/(adc + -945.2));
            break;
        case 247:
            imp = fabs((-229.1 * adc + 9400037)/(adc + -947.1));
            break;
        case 248:
            imp = fabs((-62.5 * adc + 9074020)/(adc + -950.4));
            break;
        case 249:
            imp = fabs((-131.5 * adc + 9278445)/(adc + -947.8));
            break;
        case 250:
            imp = fabs((-75.2 * adc + 9172770)/(adc + -950.9));
            break;
        case 251:
            imp = fabs((-516.0 * adc + 10239291)/(adc + -936.3));
            break;
        case 252:
            imp = fabs((-477.3 * adc + 10168239)/(adc + -939.8));
            break;
        case 253:
            imp = fabs((-317.9 * adc + 9840222)/(adc + -943.4));
            break;
        case 254:
            imp = fabs((-247.6 * adc + 9705292)/(adc + -946.9));
            break;
       }
       return imp;
}
