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
            imp = fabs((-142035.8 * adc + 413930185)/(adc + 954657.7));
            break;
        case 3:
            imp = fabs((-732.8 * adc + 3407460)/(adc + 3620.0));
            break;
        case 4:
            imp = fabs((-891.3 * adc + 4597942)/(adc + 3571.3));
            break;
        case 5:
            imp = fabs((-1012.8 * adc + 5630551)/(adc + 3438.4));
            break;
        case 6:
            imp = fabs((58.2 * adc + 2004249)/(adc + 574.7));
            break;
        case 7:
            imp = fabs((-317.7 * adc + 3602035)/(adc + 1065.8));
            break;
        case 8:
            imp = fabs((-743.9 * adc + 5641045)/(adc + 1691.8));
            break;
        case 9:
            imp = fabs((-1334.8 * adc + 8666112)/(adc + 2615.7));
            break;
        case 10:
            imp = fabs((3087033.3 * adc + -10737242889)/(adc + -2676337.2));
            break;
        case 11:
            imp = fabs((567.8 * adc + 2269926)/(adc + 448.6));
            break;
        case 12:
            imp = fabs((-179.2 * adc + 5391477)/(adc + 1112.7));
            break;
        case 13:
            imp = fabs((3176.7 * adc + -93182)/(adc + -38.0));
            break;
        case 14:
            imp = fabs((3111.0 * adc + 32252)/(adc + -20.5));
            break;
        case 15:
            imp = fabs((2779.3 * adc + 749728)/(adc + 82.2));
            break;
        case 16:
            imp = fabs((2265.3 * adc + 2083259)/(adc + 274.5));
            break;
        case 17:
            imp = fabs((1531.5 * adc + 4338664)/(adc + 600.1));
            break;
        case 18:
            imp = fabs((586.4 * adc + 7619216)/(adc + 1073.3));
            break;
        case 19:
            imp = fabs((-641.6 * adc + 12304352)/(adc + 1748.2));
            break;
        case 20:
            imp = fabs((-2182.2 * adc + 18598562)/(adc + 2645.3));
            break;
        case 21:
            imp = fabs((-4019.2 * adc + 26427000)/(adc + 3720.5));
            break;
        case 22:
            imp = fabs((-4615.2 * adc + 29528758)/(adc + 4000.0));
            break;
        case 23:
            imp = fabs((-4779.6 * adc + 30758771)/(adc + 3993.8));
            break;
        case 24:
            imp = fabs((-5019.5 * adc + 32237844)/(adc + 4028.9));
            break;
        case 25:
            imp = fabs((-5109.1 * adc + 33185153)/(adc + 3969.8));
            break;
        case 26:
            imp = fabs((-5331.0 * adc + 34679289)/(adc + 3987.8));
            break;
        case 27:
            imp = fabs((-5472.1 * adc + 35822483)/(adc + 3960.3));
            break;
        case 28:
            imp = fabs((-5701.1 * adc + 37354781)/(adc + 3984.8));
            break;
        case 29:
            imp = fabs((-5893.2 * adc + 38679176)/(adc + 3983.5));
            break;
        case 30:
            imp = fabs((-5993.7 * adc + 39634115)/(adc + 3937.3));
            break;
        case 31:
            imp = fabs((-6276.2 * adc + 41345586)/(adc + 3983.8));
            break;
        case 32:
            imp = fabs((-6381.3 * adc + 42307740)/(adc + 3960.4));
            break;
        case 33:
            imp = fabs((-6234.6 * adc + 42154814)/(adc + 3797.8));
            break;
        case 34:
            imp = fabs((-6342.3 * adc + 43124695)/(adc + 3763.7));
            break;
        case 35:
            imp = fabs((-6520.2 * adc + 44383786)/(adc + 3759.2));
            break;
        case 36:
            imp = fabs((-6632.3 * adc + 45384439)/(adc + 3733.3));
            break;
        case 37:
            imp = fabs((-6860.3 * adc + 46819575)/(adc + 3744.2));
            break;
        case 38:
            imp = fabs((-6984.6 * adc + 47838985)/(adc + 3716.3));
            break;
        case 39:
            imp = fabs((-7194.8 * adc + 49196776)/(adc + 3727.9));
            break;
        case 40:
            imp = fabs((-7341.3 * adc + 50245602)/(adc + 3716.9));
            break;
        case 41:
            imp = fabs((-7507.2 * adc + 51450403)/(adc + 3706.2));
            break;
        case 42:
            imp = fabs((-7694.0 * adc + 52734527)/(adc + 3704.0));
            break;
        case 43:
            imp = fabs((-7802.2 * adc + 53671990)/(adc + 3674.6));
            break;
        case 44:
            imp = fabs((-7999.5 * adc + 54935151)/(adc + 3668.4));
            break;
        case 45:
            imp = fabs((-8398.3 * adc + 57253965)/(adc + 3753.4));
            break;
        case 46:
            imp = fabs(-12.7 * adc + 30735);
            break;
        case 47:
            imp = fabs(-12.4 * adc + 30906);
            break;
        case 48:
            imp = fabs(-12.2 * adc + 31049);
            break;
        case 49:
            imp = fabs(-11.9 * adc + 31200);
            break;
        case 50:
            imp = fabs(-11.7 * adc + 31341);
            break;
        case 51:
            imp = fabs(-11.5 * adc + 31460);
            break;
        case 52:
            imp = fabs(-11.2 * adc + 31570);
            break;
        case 53:
            imp = fabs(-11.0 * adc + 31675);
            break;
        case 54:
            imp = fabs(-10.8 * adc + 31778);
            break;
        case 55:
            imp = fabs(-10.7 * adc + 31857);
            break;
        case 56:
            imp = fabs(-10.5 * adc + 31936);
            break;
        case 57:
            imp = fabs(-10.3 * adc + 32008);
            break;
        case 58:
            imp = fabs(-10.2 * adc + 32080);
            break;
        case 59:
            imp = fabs(-10.0 * adc + 32146);
            break;
        case 60:
            imp = fabs(-9.9 * adc + 32207);
            break;
        case 61:
            imp = fabs(-9.7 * adc + 32263);
            break;
        case 62:
            imp = fabs(-9.6 * adc + 32312);
            break;
        case 63:
            imp = fabs(-9.4 * adc + 32359);
            break;
        case 64:
            imp = fabs(-9.3 * adc + 32407);
            break;
        case 65:
            imp = fabs(-9.2 * adc + 32456);
            break;
        case 66:
            imp = fabs(-9.1 * adc + 32498);
            break;
        case 67:
            imp = fabs(-9.0 * adc + 32539);
            break;
        case 68:
            imp = fabs(-9.0 * adc + 32645);
            break;
        case 69:
            imp = fabs(-9.0 * adc + 32754);
            break;
        case 70:
            imp = fabs(-9.0 * adc + 32850);
            break;
        case 71:
            imp = fabs(-8.9 * adc + 32939);
            break;
        case 72:
            imp = fabs(-8.9 * adc + 33010);
            break;
        case 73:
            imp = fabs(-8.9 * adc + 33088);
            break;
        case 74:
            imp = fabs(-8.9 * adc + 33160);
            break;
        case 75:
            imp = fabs(-8.9 * adc + 33221);
            break;
        case 76:
            imp = fabs(-8.8 * adc + 33272);
            break;
        case 77:
            imp = fabs(-8.8 * adc + 33323);
            break;
        case 78:
            imp = fabs(-8.8 * adc + 33368);
            break;
        case 79:
            imp = fabs(-8.8 * adc + 33407);
            break;
        case 80:
            imp = fabs(-8.7 * adc + 33441);
            break;
        case 81:
            imp = fabs(-8.7 * adc + 33475);
            break;
        case 82:
            imp = fabs(-8.7 * adc + 33501);
            break;
        case 83:
            imp = fabs(-8.6 * adc + 33525);
            break;
        case 84:
            imp = fabs(-8.6 * adc + 33542);
            break;
        case 85:
            imp = fabs(-8.6 * adc + 33564);
            break;
        case 86:
            imp = fabs(-8.5 * adc + 33574);
            break;
        case 87:
            imp = fabs(-8.5 * adc + 33589);
            break;
        case 88:
            imp = fabs(-8.5 * adc + 33602);
            break;
        case 89:
            imp = fabs(-8.4 * adc + 33609);
            break;
        case 90:
            imp = fabs(-8.4 * adc + 33619);
            break;
        case 91:
            imp = fabs(-8.3 * adc + 33624);
            break;
        case 92:
            imp = fabs(-8.3 * adc + 33631);
            break;
        case 93:
            imp = fabs(-8.3 * adc + 33642);
            break;
        case 94:
            imp = fabs(-8.2 * adc + 33652);
            break;
        case 95:
            imp = fabs(-8.2 * adc + 33665);
            break;
        case 96:
            imp = fabs(-8.2 * adc + 33674);
            break;
        case 97:
            imp = fabs(-11.3 * adc + 45032);
            break;
        case 98:
            imp = fabs(-11.3 * adc + 45066);
            break;
        case 99:
            imp = fabs(-11.3 * adc + 45118);
            break;
        case 100:
            imp = fabs(-11.4 * adc + 45181);
            break;
        case 101:
            imp = fabs(-11.4 * adc + 45267);
            break;
        case 102:
            imp = fabs(-11.5 * adc + 45385);
            break;
        case 103:
            imp = fabs(-11.5 * adc + 45523);
            break;
        case 104:
            imp = fabs(-11.6 * adc + 45683);
            break;
        case 105:
            imp = fabs(-11.7 * adc + 45860);
            break;
        case 106:
            imp = fabs(-11.8 * adc + 46055);
            break;
        case 107:
            imp = fabs(-11.9 * adc + 46252);
            break;
        case 108:
            imp = fabs(-11.9 * adc + 46442);
            break;
        case 109:
            imp = fabs(-12.0 * adc + 46631);
            break;
        case 110:
            imp = fabs(-12.1 * adc + 46827);
            break;
        case 111:
            imp = fabs(-12.2 * adc + 47013);
            break;
        case 112:
            imp = fabs(-12.3 * adc + 47191);
            break;
        case 113:
            imp = fabs(-12.3 * adc + 47382);
            break;
        case 114:
            imp = fabs(-12.4 * adc + 47576);
            break;
        case 115:
            imp = fabs(-12.5 * adc + 47766);
            break;
        case 116:
            imp = fabs(-12.6 * adc + 47953);
            break;
        case 117:
            imp = fabs(-12.7 * adc + 48136);
            break;
        case 118:
            imp = fabs(-12.7 * adc + 48328);
            break;
        case 119:
            imp = fabs(-12.8 * adc + 48496);
            break;
        case 120:
            imp = fabs(-12.9 * adc + 48684);
            break;
        case 121:
            imp = fabs(-12.9 * adc + 48866);
            break;
        case 122:
            imp = fabs(-13.0 * adc + 49048);
            break;
        case 123:
            imp = fabs(-13.1 * adc + 49241);
            break;
        case 124:
            imp = fabs(-13.2 * adc + 49407);
            break;
        case 125:
            imp = fabs(-13.2 * adc + 49583);
            break;
        case 126:
            imp = fabs(-13.3 * adc + 49754);
            break;
        case 127:
            imp = fabs(-13.4 * adc + 49930);
            break;
        case 128:
            imp = fabs(-13.4 * adc + 50096);
            break;
        case 129:
            imp = fabs(-13.5 * adc + 50274);
            break;
        case 130:
            imp = fabs(-13.5 * adc + 50443);
            break;
        case 131:
            imp = fabs(-13.6 * adc + 50617);
            break;
        case 132:
            imp = fabs(-13.7 * adc + 50789);
            break;
        case 133:
            imp = fabs(-13.7 * adc + 50949);
            break;
        case 134:
            imp = fabs(-13.8 * adc + 51125);
            break;
        case 135:
            imp = fabs(-13.8 * adc + 51269);
            break;
        case 136:
            imp = fabs(-13.9 * adc + 51428);
            break;
        case 137:
            imp = fabs(-13.9 * adc + 51592);
            break;
        case 138:
            imp = fabs(-14.0 * adc + 51750);
            break;
        case 139:
            imp = fabs(-14.0 * adc + 51913);
            break;
        case 140:
            imp = fabs(-14.1 * adc + 52078);
            break;
        case 141:
            imp = fabs(-14.1 * adc + 52221);
            break;
        case 142:
            imp = fabs(-14.2 * adc + 52384);
            break;
        case 143:
            imp = fabs(-14.2 * adc + 52514);
            break;
        case 144:
            imp = fabs(-14.2 * adc + 52662);
            break;
        case 145:
            imp = fabs(-14.3 * adc + 52830);
            break;
        case 146:
            imp = fabs(-14.3 * adc + 52974);
            break;
        case 147:
            imp = fabs(-14.4 * adc + 53124);
            break;
        case 148:
            imp = fabs(-14.4 * adc + 53266);
            break;
        case 149:
            imp = fabs(-14.4 * adc + 53408);
            break;
        case 150:
            imp = fabs(-14.5 * adc + 53549);
            break;
        case 151:
            imp = fabs(-14.5 * adc + 53684);
            break;
        case 152:
            imp = fabs(-14.5 * adc + 53812);
            break;
        case 153:
            imp = fabs(-14.6 * adc + 53957);
            break;
        case 154:
            imp = fabs(-14.6 * adc + 54097);
            break;
        case 155:
            imp = fabs(-14.6 * adc + 54228);
            break;
        case 156:
            imp = fabs(-14.7 * adc + 54375);
            break;
        case 157:
            imp = fabs(-14.7 * adc + 54508);
            break;
        case 158:
            imp = fabs(-14.7 * adc + 54650);
            break;
        case 159:
            imp = fabs(-14.8 * adc + 54775);
            break;
        case 160:
            imp = fabs(-14.8 * adc + 54898);
            break;
        case 161:
            imp = fabs(-14.8 * adc + 55035);
            break;
        case 162:
            imp = fabs(-14.8 * adc + 55173);
            break;
        case 163:
            imp = fabs(-14.9 * adc + 55323);
            break;
        case 164:
            imp = fabs(-14.9 * adc + 55453);
            break;
        case 165:
            imp = fabs(-14.9 * adc + 55614);
            break;
        case 166:
            imp = fabs(-15.0 * adc + 55765);
            break;
        case 167:
            imp = fabs(-15.0 * adc + 55924);
            break;
        case 168:
            imp = fabs(-15.0 * adc + 56092);
            break;
        case 169:
            imp = fabs(-15.1 * adc + 56283);
            break;
        case 170:
            imp = fabs(-15.1 * adc + 56481);
            break;
        case 171:
            imp = fabs(-15.2 * adc + 56706);
            break;
        case 172:
            imp = fabs(-15.3 * adc + 56940);
            break;
        case 173:
            imp = fabs(-15.3 * adc + 57181);
            break;
        case 174:
            imp = fabs(-15.4 * adc + 57452);
            break;
        case 175:
            imp = fabs(-15.5 * adc + 57724);
            break;
        case 176:
            imp = fabs(-15.5 * adc + 57983);
            break;
        case 177:
            imp = fabs(-15.6 * adc + 58277);
            break;
        case 178:
            imp = fabs(-15.7 * adc + 58560);
            break;
        case 179:
            imp = fabs(-15.8 * adc + 58841);
            break;
        case 180:
            imp = fabs(-15.9 * adc + 59145);
            break;
        case 181:
            imp = fabs(-15.9 * adc + 59428);
            break;
        case 182:
            imp = fabs(-16.0 * adc + 59721);
            break;
        case 183:
            imp = fabs(-16.1 * adc + 60008);
            break;
        case 184:
            imp = fabs(-16.2 * adc + 60294);
            break;
        case 185:
            imp = fabs(-16.3 * adc + 60584);
            break;
        case 186:
            imp = fabs(-16.4 * adc + 60890);
            break;
        case 187:
            imp = fabs(-16.4 * adc + 61200);
            break;
        case 188:
            imp = fabs(-16.5 * adc + 61492);
            break;
        case 189:
            imp = fabs(-16.6 * adc + 61785);
            break;
        case 190:
            imp = fabs(-16.7 * adc + 62092);
            break;
        case 191:
            imp = fabs(-16.8 * adc + 62384);
            break;
        case 192:
            imp = fabs(-16.8 * adc + 62661);
            break;
        case 193:
            imp = fabs(-16.9 * adc + 62972);
            break;
        case 194:
            imp = fabs(-17.0 * adc + 63291);
            break;
        case 195:
            imp = fabs(-17.1 * adc + 63590);
            break;
        case 196:
            imp = fabs(-17.2 * adc + 63891);
            break;
        case 197:
            imp = fabs(-17.3 * adc + 64190);
            break;
        case 198:
            imp = fabs(-17.3 * adc + 64520);
            break;
        case 199:
            imp = fabs(-17.4 * adc + 64803);
            break;
        case 200:
            imp = fabs(-17.5 * adc + 65114);
            break;
        case 201:
            imp = fabs(-17.6 * adc + 65424);
            break;
        case 202:
            imp = fabs(-17.7 * adc + 65749);
            break;
        case 203:
            imp = fabs(-17.8 * adc + 66059);
            break;
        case 204:
            imp = fabs(-17.8 * adc + 66376);
            break;
        case 205:
            imp = fabs(-17.9 * adc + 66686);
            break;
        case 206:
            imp = fabs(-18.0 * adc + 66996);
            break;
        case 207:
            imp = fabs(-18.1 * adc + 67320);
            break;
        case 208:
            imp = fabs(-18.2 * adc + 67625);
            break;
        case 209:
            imp = fabs(-18.3 * adc + 67953);
            break;
        case 210:
            imp = fabs(-18.4 * adc + 68252);
            break;
        case 211:
            imp = fabs(-18.4 * adc + 68578);
            break;
        case 212:
            imp = fabs(-18.5 * adc + 68900);
            break;
        case 213:
            imp = fabs(-18.6 * adc + 69217);
            break;
        case 214:
            imp = fabs(-18.7 * adc + 69560);
            break;
        case 215:
            imp = fabs(-18.8 * adc + 69842);
            break;
        case 216:
            imp = fabs(-18.8 * adc + 70152);
            break;
        case 217:
            imp = fabs(-18.9 * adc + 70487);
            break;
        case 218:
            imp = fabs(-19.0 * adc + 70820);
            break;
        case 219:
            imp = fabs(-19.1 * adc + 71165);
            break;
        case 220:
            imp = fabs(-19.2 * adc + 71482);
            break;
        case 221:
            imp = fabs(-19.3 * adc + 71794);
            break;
        case 222:
            imp = fabs(-19.4 * adc + 72149);
            break;
        case 223:
            imp = fabs(-19.4 * adc + 72461);
            break;
        case 224:
            imp = fabs(-19.5 * adc + 72732);
            break;
        case 225:
            imp = fabs(-19.6 * adc + 73086);
            break;
        case 226:
            imp = fabs(-19.7 * adc + 73460);
            break;
        case 227:
            imp = fabs(-19.8 * adc + 73781);
            break;
        case 228:
            imp = fabs(-19.9 * adc + 74090);
            break;
        case 229:
            imp = fabs(-19.9 * adc + 74428);
            break;
        case 230:
            imp = fabs(-20.0 * adc + 74770);
            break;
        case 231:
            imp = fabs(-20.1 * adc + 75075);
            break;
        case 232:
            imp = fabs(-20.2 * adc + 75415);
            break;
        case 233:
            imp = fabs(-20.3 * adc + 75757);
            break;
        case 234:
            imp = fabs(-20.4 * adc + 76077);
            break;
        case 235:
            imp = fabs(-20.4 * adc + 76413);
            break;
        case 236:
            imp = fabs(-20.5 * adc + 76745);
            break;
        case 237:
            imp = fabs(-20.6 * adc + 77075);
            break;
        case 238:
            imp = fabs(-20.7 * adc + 77408);
            break;
        case 239:
            imp = fabs(-20.8 * adc + 77730);
            break;
        case 240:
            imp = fabs(-20.8 * adc + 78045);
            break;
        case 241:
            imp = fabs(-20.9 * adc + 78393);
            break;
        case 242:
            imp = fabs(-21.0 * adc + 78748);
            break;
        case 243:
            imp = fabs(-21.1 * adc + 79095);
            break;
        case 244:
            imp = fabs(-21.2 * adc + 79456);
            break;
        case 245:
            imp = fabs(-21.3 * adc + 79737);
            break;
        case 246:
            imp = fabs(-21.3 * adc + 80073);
            break;
        case 247:
            imp = fabs(-21.4 * adc + 80396);
            break;
        case 248:
            imp = fabs(-21.5 * adc + 80778);
            break;
        case 249:
            imp = fabs(-21.6 * adc + 81080);
            break;
        case 250:
            imp = fabs(-21.7 * adc + 81436);
            break;
        case 251:
            imp = fabs(-21.7 * adc + 81745);
            break;
        case 252:
            imp = fabs(-21.8 * adc + 82070);
            break;
        case 253:
            imp = fabs(-21.9 * adc + 82389);
            break;
        case 254:
            imp = fabs(-22.0 * adc + 82731);
            break;
       }
       return imp;
}
