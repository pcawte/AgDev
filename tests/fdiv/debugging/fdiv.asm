040000: C3450004      jp        __start

040040: 4D4F53        db        "MOS"
040043: 0001          db        00, 01
040045: F5            push      af
040046  C5            push      bc
040047  D5            push      de
040048: DDE5          push      ix
04004A: FDE5          push      iy
04004C: E5            push      hl
04004D: CD5E0004      call      _clear_bss
040051: E1            pop       hl
040052: CD281E04      call      _main
040056: FDE1          pop       iy
040058: DDE1          pop       ix
04005A: D1            pop       de
04005B: C1            pop       bc
04005C: F1            pop       af
04005D: C9            ret
                    _clear_bss:
04005E: 01000000      ld        bc, 000000
040062: 3E00          ld        a, 00
040064: B1            or        c
040065: B0            or        b
040066: C8            ret       z
040067: AF            xor       a
040068: 32000005      ld        (loc_050000), a
04006C: ED62          sbc       hl, hl
04006E: 0B            dec       bc
04006F: ED42          sbc       hl, bc
040071: C8            ret       z
040072: 21000005      ld        hl, 050000
040076: 11010005      ld        de, 050001
04007A: EDB0          ldir
04007C: C9            ret                               ; end of _clear_bss;

04007D: 01040004      ld        bc, 040004
040081: DD0F00        ld        (ix + 00), bc
040084: DD23          inc       ix
040086: DD23          inc       ix
040088: DD23          inc       ix
04008A: CDC50004      call      label_0400C5
04008E: 01010000      ld        bc, 000001
040092: 060F          ld        b, 0F
                    label_040094:
040094: C5            push      bc
040095: E5            push      hl
040096: CDB60004      call      label_0400B6
04009A: 79            ld        a, c
04009B: D1            pop       de
04009C: C1            pop       bc
04009D: B7            or        a
04009E: C8            ret       z
04009F: DD1F00        ld        (ix + 00), de
0400A2: E5            push      hl
0400A3: D1            pop       de
0400A4: CDC50004      call      label_0400C5
0400A8: AF            xor       a
0400A9: 12            ld        (de), a
0400AA: DD23          inc       ix
0400AC: DD23          inc       ix
0400AE: DD23          inc       ix
0400B0: 0C            inc       c
0400B1: 79            ld        a, c
0400B2: B8            cp        b
0400B3: 38DF          jr        c, label_040094
0400B5: C9            ret
                    label_0400B6:
0400B6: 0E00          ld        c, 00
                    label_0400B8:
0400B8: 7E            ld        a, (hl)
0400B9: B7            or        a
0400BA: C8            ret       z
0400BB: FE0D          cp        0D
0400BD: C8            ret       z
0400BE: FE20          cp        20
0400C0: C8            ret       z
0400C1: 23            inc       hl
0400C2: 0C            inc       c
0400C3: 18F3          jr        label_0400B8
                    label_0400C5:
0400C5: 7E            ld        a, (hl)
0400C6: FE20          cp        20
0400C8: C0            ret       nz
0400C9: 23            inc       hl
0400CA: 18F9          jr        label_0400C5
                    __frameset:
0400CC: D1            pop       de
0400CD: DDE5          push      ix
0400CF: DD21000000    ld        ix, 000000
0400D4: DD39          add       ix, sp
0400D6: 39            add       hl, sp
0400D7: F9            ld        sp, hl
0400D8: EB            ex        de, hl
0400D9: E9            jp        (hl)
                    __frameset0:
0400DA: E1            pop       hl
0400DB: DDE5          push      ix
0400DD: DD21000000    ld        ix, 000000
0400E2: DD39          add       ix, sp
0400E4: E9            jp        (hl)
                    label_0400E5:
0400E5: F5            push      af
0400E6: C5            push      bc
0400E7: 33            inc       sp
0400E8: 33            inc       sp
0400E9: E5            push      hl
0400EA: 21020000      ld        hl, 000002
0400EE: 39            add       hl, sp
0400EF: 7E            ld        a, (hl)
0400F0: 23            inc       hl
0400F1: A6            and       (hl)
0400F2: 2B            dec       hl
0400F3: 77            ld        (hl), a
0400F4: E1            pop       hl
0400F5: 33            inc       sp
0400F6: 7C            ld        a, h
0400F7: A0            and       b
0400F8: 67            ld        h, a
0400F9: 7D            ld        a, l
0400FA: A1            and       c
0400FB: 6F            ld        l, a
0400FC: F1            pop       af
0400FD: C9            ret
                    __imulu:
0400FE: F5            push      af
0400FF: D5            push      de
040100: 50            ld        d, b
040101: 5C            ld        e, h
040102: ED5C          mlt       de
040104: 7B            ld        a, e
040105: 3B            dec       sp
040106: E5            push      hl
040107: C5            push      bc
040108: 33            inc       sp
040109: D1            pop       de
04010A: 5D            ld        e, l
04010B: ED5C          mlt       de
04010D: 83            add       a, e
04010E: D1            pop       de
04010F: 59            ld        e, c
040110: ED5C          mlt       de
040112: 83            add       a, e
040113: 5D            ld        e, l
040114: 69            ld        l, c
040115: ED6C          mlt       hl
040117: 84            add       a, h
040118: 67            ld        h, a
040119: 7B            ld        a, e
04011A: 50            ld        d, b
04011B: ED5C          mlt       de
04011D: 19            add       hl, de
04011E: 29            add       hl, hl
04011F: 29            add       hl, hl
040120: 29            add       hl, hl
040121: 29            add       hl, hl
040122: 29            add       hl, hl
040123: 29            add       hl, hl
040124: 29            add       hl, hl
040125: 29            add       hl, hl
040126: 57            ld        d, a
040127: 59            ld        e, c
040128: ED5C          mlt       de
04012A: 19            add       hl, de
04012B: D1            pop       de
04012C: F1            pop       af
04012D: C9            ret
                    __indcallhl:
04012E: E9            jp        (hl)
                    label_04012F:
04012F: 19            add       hl, de
040130: EB            ex        de, hl
040131: B7            or        a
040132: ED52          sbc       hl, de
040134: EB            ex        de, hl
040135: 19            add       hl, de
040136: EB            ex        de, hl
040137: C9            ret
                    __ior:
040138: F5            push      af
040139: C5            push      bc
04013A: 33            inc       sp
04013B: 33            inc       sp
04013C: E5            push      hl
04013D: 21020000      ld        hl, 000002
040141: 39            add       hl, sp
040142: 7E            ld        a, (hl)
040143: 23            inc       hl
040144: B6            or        (hl)
040145: 2B            dec       hl
040146: 77            ld        (hl), a
040147: E1            pop       hl
040148: 33            inc       sp
040149: 7C            ld        a, h
04014A: B0            or        b
04014B: 67            ld        h, a
04014C: 7D            ld        a, l
04014D: B1            or        c
04014E: 6F            ld        l, a
04014F: F1            pop       af
040150: C9            ret

                    __ishl:
040151: CB41          bit       0, c
040153: 2801          jr        z, label_040156
040155: 29            add       hl, hl
                    label_040156:
040156: CB49          bit       1, c
040158: 2802          jr        z, label_04015C
04015A: 29            add       hl, hl
04015B: 29            add       hl, hl
                    label_04015C:
04015C: CB51          bit       2, c
04015E: 2804          jr        z, label_040164
040160: 29            add       hl, hl
040161: 29            add       hl, hl
040162: 29            add       hl, hl
040163: 29            add       hl, hl
                    label_040164:
040164: CB59          bit       3, c
040166: 2006          jr        nz, label_04016E
040168: CB61          bit       4, c
04016A: C8            ret       z
04016B: 65            ld        h, l
04016C: 2E00          ld        l, 00
                    label_04016E:
04016E: 29            add       hl, hl
04016F: 29            add       hl, hl
040170: 29            add       hl, hl
040171: 29            add       hl, hl
040172: 29            add       hl, hl
040173: 29            add       hl, hl
040174: 29            add       hl, hl
040175: 29            add       hl, hl
040176: C9            ret
                    __ishru:
040177: F5            push      af
040178: AF            xor       a
040179: 29            add       hl, hl
04017A: 17            rla
04017B: DAF5299F      jp        c, label_9F29F5
04017F: CB41          bit       0, c
040181: 2002          jr        nz, label_040185
040183: 29            add       hl, hl
040184: 17            rla
                    label_040185:
040185: CB49          bit       1, c
040187: 2004          jr        nz, label_04018D
040189: 29            add       hl, hl
04018A: 17            rla
04018B: 29            add       hl, hl
04018C: 17            rla
                    label_04018D:
04018D: CB51          bit       2, c
04018F: 2008          jr        nz, label_040199
040191: 29            add       hl, hl
040192: 17            rla
040193: 29            add       hl, hl
040194: 17            rla
040195: 29            add       hl, hl
040196: 17            rla
040197: 29            add       hl, hl
040198: 17            rla
                    label_040199:
040199: CB59          bit       3, c
04019B: 200C          jr        nz, label_0401A9
04019D: CB61          bit       4, c
04019F: 2012          jr        nz, label_0401B3
0401A1: F5            push      af
0401A2: 33            inc       sp
0401A3: E5            push      hl
0401A4: 33            inc       sp
0401A5: E1            pop       hl
0401A6: 33            inc       sp
0401A7: F1            pop       af
0401A8: C9            ret
                    label_0401A9:
0401A9: 3B            dec       sp
0401AA: E5            push      hl
0401AB: ED62          sbc       hl, hl
0401AD: 67            ld        h, a
0401AE: 33            inc       sp
0401AF: F1            pop       af
0401B0: 6F            ld        l, a
0401B1: F1            pop       af
0401B2: C9            ret
                    label_0401B3:
0401B3: ED62          sbc       hl, hl
0401B5: 6F            ld        l, a
0401B6: F1            pop       af
0401B7: C9            ret
                    __ixor:
0401B8: F5            push      af
0401B9: C5            push      bc
0401BA: 33            inc       sp
0401BB: 33            inc       sp
0401BC: E5            push      hl
0401BD: 21020000      ld        hl, 000002
0401C1: 39            add       hl, sp
0401C2: 7E            ld        a, (hl)
0401C3: 23            inc       hl
0401C4: AE            xor       (hl)
0401C5: 2B            dec       hl
0401C6: 77            ld        (hl), a
0401C7: E1            pop       hl
0401C8: 33            inc       sp
0401C9: 7C            ld        a, h
0401CA: A8            xor       b
0401CB: 67            ld        h, a
0401CC: 7D            ld        a, l
0401CD: A9            xor       c
0401CE: 6F            ld        l, a
0401CF: F1            pop       af
0401D0: C9            ret
                    label_0401D1:
0401D1: F5            push      af
0401D2: 09            add       hl, bc
0401D3: 8B            adc       a, e
0401D4: 5F            ld        e, a
0401D5: F1            pop       af
0401D6: C9            ret
                    label_0401D7:
0401D7: F5            push      af
0401D8: A3            and       e
0401D9: 5F            ld        e, a
0401DA: C5            push      bc
0401DB: 33            inc       sp
0401DC: 33            inc       sp
0401DD: E5            push      hl
0401DE: 21020000      ld        hl, 000002
0401E2: 39            add       hl, sp
0401E3: 7E            ld        a, (hl)
0401E4: 23            inc       hl
0401E5: A6            and       (hl)
0401E6: 2B            dec       hl
0401E7: 77            ld        (hl), a
0401E8: E1            pop       hl
0401E9: 33            inc       sp
0401EA: 7C            ld        a, h
0401EB: A0            and       b
0401EC: 67            ld        h, a
0401ED: 7D            ld        a, l
0401EE: A1            and       c
0401EF: 6F            ld        l, a
0401F0: F1            pop       af
0401F1: C9            ret
                    label_0401F2:
0401F2: BB            cp        e
0401F3: 3F            ccf
0401F4: C0            ret       nz
0401F5: B7            or        a
0401F6: ED42          sbc       hl, bc
0401F8: 09            add       hl, bc
0401F9: C9            ret
                    label_0401FA:
0401FA: 1C            inc       e
0401FB: 1D            dec       e
0401FC: C0            ret       nz
0401FD: 09            add       hl, bc
0401FE: B7            or        a
0401FF: ED42          sbc       hl, bc
040201: C9            ret
                    label_040202:
040202: FDE5          push      iy
040204: FD21000000    ld        iy, 000000
040209: FD39          add       iy, sp
04020B: C5            push      bc
04020C: FD0706        ld        bc, (iy + 06)
04020F: 09            add       hl, bc
040210: EB            ex        de, hl
040211: FD0709        ld        bc, (iy + 09)
040214: ED4A          adc       hl, bc
040216: EB            ex        de, hl
040217: C1            pop       bc
040218: 3001          jr        nc, label_04021B
04021A: 03            inc       bc
                    label_04021B:
04021B: FD370C        ld        iy, (iy + 0C)
04021E: FD09          add       iy, bc
040220: ED0300        lea       bc, IY + 00
040223: FDE1          pop       iy
040225: C9            ret
                    label_040226:
040226: F5            push      af
040227: FDE5          push      iy
040229: FD21000000    ld        iy, 000000
04022E: FD39          add       iy, sp
040230: E5            push      hl
040231: D5            push      de
040232: ED2310        lea       hl, IY + 10
040235: 78            ld        a, b
040236: A6            and       (hl)
040237: 47            ld        b, a
040238: 2B            dec       hl
040239: 79            ld        a, c
04023A: A6            and       (hl)
04023B: 4F            ld        c, a
04023C: 2B            dec       hl
04023D: ED13FC        lea       de, IY + FC
040240: 1A            ld        a, (de)
040241: A6            and       (hl)
040242: 12            ld        (de), a
040243: D1            pop       de
040244: 2B            dec       hl
040245: 7A            ld        a, d
040246: A6            and       (hl)
040247: 57            ld        d, a
040248: 2B            dec       hl
040249: 7B            ld        a, e
04024A: A6            and       (hl)
04024B: 5F            ld        e, a
04024C: 2B            dec       hl
04024D: FD7EFF        ld        a, (iy + -01)
040250: A6            and       (hl)
040251: FD77FF        ld        (iy + -01), a
040254: E1            pop       hl
040255: 7C            ld        a, h
040256: FDA60A        and       (iy + 0A)
040259: 67            ld        h, a
04025A: 7D            ld        a, l
04025B: FDA609        and       (iy + 09)
04025E: 6F            ld        l, a
04025F: FDE1          pop       iy
040261: F1            pop       af
040262: C9            ret
                    label_040263:
040263: FDE5          push      iy
040265: FD21000000    ld        iy, 000000
04026A: FD39          add       iy, sp
04026C: E5            push      hl
04026D: FD270C        ld        hl, (iy + 0C)
040270: 52ED42        sbc.lis   hl, bc
040273: 2013          jr        nz, label_040288
040275: FD2709        ld        hl, (iy + 09)
040278: ED52          sbc       hl, de
04027A: 200C          jr        nz, label_040288
04027C: E1            pop       hl
04027D: C5            push      bc
04027E: FD0706        ld        bc, (iy + 06)
040281: ED42          sbc       hl, bc
040283: 09            add       hl, bc
040284: C1            pop       bc
040285: FDE1          pop       iy
040287: C9            ret
                    label_040288:
040288: 3F            ccf
040289: E1            pop       hl
04028A: FDE1          pop       iy
04028C: C9            ret
                    label_04028D:
04028D: 04            inc       b
04028E: 05            dec       b
04028F: C0            ret       nz
040290: 5203          inc.lis   bc
040292: 0D            dec       c
040293: 2009          jr        nz, label_04029E
040295: B7            or        a
040296: ED42          sbc       hl, bc
040298: 2004          jr        nz, label_04029E
04029A: ED52          sbc       hl, de
04029C: C8            ret       z
04029D: 19            add       hl, de
                    label_04029E:
04029E: 04            inc       b
04029F: 0600          ld        b, 00
0402A1: C9            ret
                    label_0402A2:
0402A2: C5            push      bc
0402A3: D5            push      de
0402A4: E5            push      hl
0402A5: 37            scf
0402A6: 9F            sbc       a, a
                    label_0402A7:
0402A7: ED6A          adc       hl, hl
0402A9: EB            ex        de, hl
0402AA: ED6A          adc       hl, hl
0402AC: EB            ex        de, hl
0402AD: CB11          rl        c
0402AF: CB10          rl        b
0402B1: 3C            inc       a
0402B2: 30F3          jr        nc, label_0402A7
0402B4: E1            pop       hl
0402B5: D1            pop       de
0402B6: C1            pop       bc
0402B7: C9            ret
0402B8: 37            scf
0402B9: 30B7          jr        nc, label_040272
0402BB: FDE5          push      iy
0402BD: F5            push      af
0402BE: FD21020000    ld        iy, 000002
0402C3: FD39          add       iy, sp
0402C5: 78            ld        a, b
0402C6: FD7700        ld        (iy + 00), a
0402C9: FDAE0E        xor       (iy + 0E)
0402CC: FD770F        ld        (iy + 0F), a
0402CF: A8            xor       b
0402D0: 17            rla
0402D1: 3011          jr        nc, label_0402E4
0402D3: C5            push      bc
0402D4: E5            push      hl
0402D5: ED2307        lea       hl, IY + 07
0402D8: AF            xor       a
0402D9: 4F            ld        c, a
0402DA: 0608          ld        b, 08
                    label_0402DC:
0402DC: 79            ld        a, c
0402DD: 9E            sbc       a, (hl)
0402DE: 77            ld        (hl), a
0402DF: 23            inc       hl
0402E0: 10FA          djnz      label_0402DC
0402E2: E1            pop       hl
0402E3: C1            pop       bc
                    label_0402E4:
0402E4: CB78          bit       7, b
0402E6: C4D10304      call      nz, label_0403D1
0402EA: B7            or        a
0402EB: CD250304      call      label_040325
0402EF: F1            pop       af
0402F0: FDCB087E      bit       7, (iy + 08)
0402F4: 380D          jr        c, label_040303
0402F6: FD270F        ld        hl, (iy + 0F)
0402F9: FD1712        ld        de, (iy + 12)
0402FC: FD0715        ld        bc, (iy + 15)
0402FF: FDCB177E      bit       7, (iy + 17)
                    label_040303:
040303: C4D10304      call      nz, label_0403D1
040307: FDE1          pop       iy
040309: C9            ret
                    label_04030A:
04030A: FDE5          push      iy
04030C: F5            push      af
04030D: CD1E0304      call      label_04031E
040311: FD270F        ld        hl, (iy + 0F)
040314: FD1712        ld        de, (iy + 12)
040317: FD0715        ld        bc, (iy + 15)
04031A: F1            pop       af
04031B: FDE1          pop       iy
04031D: C9            ret
                    label_04031E:
04031E: FD21050000    ld        iy, 000005
040323: FD39          add       iy, sp
                    label_040325:
040325: ED57          ld         a, i
040327: F3            di
040328: F5            push      af
040329: C5            push      bc
04032A: D5            push      de
04032B: E5            push      hl
04032C: FD070A        ld        bc, (iy + 0A)
04032F: ED62          sbc       hl, hl
040331: EB            ex        de, hl
040332: ED62          sbc       hl, hl
040334: D9            exx
040335: FD270D        ld        hl, (iy + 0D)
040338: 52EB          ex.lis    de, hl
04033A: FD2707        ld        hl, (iy + 07)
04033D: F9            ld        sp, hl
04033E: ED62          sbc       hl, hl
040340: 0E08          ld        c, 08
                    label_040342:
040342: FD2B          dec       iy
040344: FD7EF7        ld        a, (iy + -09)
040347: 0608          ld        b, 08
                    label_040349:
040349: 8F            adc       a, a
04034A: D9            exx
04034B: ED6A          adc       hl, hl
04034D: EB            ex        de, hl
04034E: ED6A          adc       hl, hl
040350: EB            ex        de, hl
040351: D9            exx
040352: ED6A          adc       hl, hl
040354: D9            exx
040355: ED72          sbc       hl, sp
040357: EB            ex        de, hl
040358: ED42          sbc       hl, bc
04035A: EB            ex        de, hl
04035B: D9            exx
04035C: ED52          sbc       hl, de
04035E: 3009          jr        nc, label_040369
040360: D9            exx
040361: 39            add       hl, sp
040362: EB            ex        de, hl
040363: ED4A          adc       hl, bc
040365: EB            ex        de, hl
040366: D9            exx
040367: ED5A          adc       hl, de
                    label_040369:
040369: 10DE          djnz      label_040349
04036B: 8F            adc       a, a
04036C: 2F            cpl
04036D: FD770F        ld        (iy + 0F), a
040370: 0D            dec       c
040371: 20CF          jr        nz, label_040342
040373: FDF9          ld        sp, iy
040375: E5            push      hl
040376: D9            exx
040377: C1            pop       bc
040378: F1            pop       af
040379: E0            ret       po
04037A: FB            ei
04037B: C9            ret
                    label_04037C:
04037C: DDE5          push      ix
04037E: FDE5          push      iy
040380: F5            push      af
040381: DD21000000    ld        ix, 000000
040386: ED55FA        lea       iy, ix + -06
040389: FD39          add       iy, sp
04038B: D5            push      de
04038C: E5            push      hl
04038D: 69            ld        l, c
04038E: 60            ld        h, b
04038F: 52F9          ld.lis    sp, hl
040391: ED2312        lea       hl, IY + 12
040394: 0608          ld        b, 08
                    label_040396:
040396: F5            push      af
040397: 7E            ld        a, (hl)
040398: 23            inc       hl
040399: B7            or        a
04039A: 10FA          djnz      label_040396
04039C: ED62          sbc       hl, hl
04039E: 5D            ld        e, l
04039F: 54            ld        d, h
                    label_0403A0:
0403A0: 37            scf
0403A1: 8F            adc       a, a
                    label_0403A2:
0403A2: F5            push      af
0403A3: DD29          add       ix, ix
0403A5: ED6A          adc       hl, hl
0403A7: EB            ex        de, hl
0403A8: ED6A          adc       hl, hl
0403AA: EB            ex        de, hl
0403AB: F1            pop       af
0403AC: 300F          jr        nc, label_0403BD
0403AE: FD0700        ld        bc, (iy + 00)
0403B1: DD09          add       ix, bc
0403B3: FD0703        ld        bc, (iy + 03)
0403B6: ED4A          adc       hl, bc
0403B8: EB            ex        de, hl
0403B9: 52ED7A        adc.lis   hl, sp
0403BC: EB            ex        de, hl
                    label_0403BD:
0403BD: 87            add       a, a
0403BE: 20E2          jr        nz, label_0403A2
0403C0: F1            pop       af
0403C1: 30DD          jr        nc, label_0403A0
0403C3: 42            ld        b, d
0403C4: 4B            ld        c, e
0403C5: EB            ex        de, hl
0403C6: ED2200        lea       hl, IX + 00
0403C9: F1            pop       af
0403CA: F1            pop       af
0403CB: F1            pop       af
0403CC: FDE1          pop       iy
0403CE: DDE1          pop       ix
0403D0: C9            ret
                    label_0403D1:
0403D1: B7            or        a
0403D2: EB            ex        de, hl
0403D3: E5            push      hl
0403D4: ED62          sbc       hl, hl
0403D6: ED52          sbc       hl, de
0403D8: E3            ex        (sp), hl
0403D9: EB            ex        de, hl
0403DA: 21000000      ld        hl, 000000
0403DE: ED52          sbc       hl, de
0403E0: EB            ex        de, hl
0403E1: ED62          sbc       hl, hl
0403E3: B7            or        a
0403E4: ED42          sbc       hl, bc
0403E6: 4D            ld        c, l
0403E7: 44            ld        b, h
0403E8: E1            pop       hl
0403E9: C9            ret
                    label_0403EA:
0403EA: F5            push      af
0403EB: 78            ld        a, b
0403EC: E5            push      hl
0403ED: 21090000      ld        hl, 000009
0403F1: 39            add       hl, sp
0403F2: 46            ld        b, (hl)
0403F3: E1            pop       hl
0403F4: 04            inc       b
0403F5: 1808          jr        label_0403FF
                    label_0403F7:
0403F7: 29            add       hl, hl
0403F8: EB            ex        de, hl
0403F9: ED6A          adc       hl, hl
0403FB: EB            ex        de, hl
0403FC: CB11          rl        c
0403FE: 17            rla
                    label_0403FF:
0403FF: 10F6          djnz      label_0403F7
040401: 47            ld        b, a
040402: F1            pop       af
040403: C9            ret
040404: F5            push      af
040405: FDE5          push      iy
040407: FD21000000    ld        iy, 000000
04040C: FD39          add       iy, sp
04040E: FD7E09        ld        a, (iy + 09)
040411: B7            or        a
040412: 2823          jr        z, label_040437
040414: D5            push      de
040415: E5            push      hl
                    label_040416:
040416: CB28          sra       b
                    label_040418:
040418: CB19          rr        c
04041A: FDCBFF1E      rr        rr (iy + -01)
04041E: FDCBFE1E      rr        rr (iy + -02)
040422: FDCBFD1E      rr        rr (iy + -03)
040426: FDCBFC1E      rr        rr (iy + -04)
04042A: FDCBFB1E      rr        rr (iy + -05)
04042E: FDCBFA1E      rr        rr (iy + -06)
040432: 3D            dec       a
040433: 20E1          jr        nz, label_040416
040435: E1            pop       hl
040436: D1            pop       de
                    label_040437:
040437: FDE1          pop       iy
040439: F1            pop       af
04043A: C9            ret
                    label_04043B:
04043B: F5            push      af
04043C: FDE5          push      iy
04043E: FD21000000    ld        iy, 000000
040443: FD39          add       iy, sp
040445: FD7E09        ld        a, (iy + 09)
040448: B7            or        a
040449: CA370404      jp        z, label_040437
04044D: D5            push      de
04044E: E5            push      hl
04044F: CB38          srl       b
040451: C3180404      jp        label_040418
                    label_040455:
040455: FDE5          push      iy
040457: FD21000000    ld        iy, 000000
04045C: FD39          add       iy, sp
04045E: C5            push      bc
04045F: FD0706        ld        bc, (iy + 06)
040462: ED42          sbc       hl, bc
040464: EB            ex        de, hl
040465: FD0709        ld        bc, (iy + 09)
040468: ED42          sbc       hl, bc
04046A: EB            ex        de, hl
04046B: E3            ex        (sp), hl
04046C: FD070C        ld        bc, (iy + 0C)
04046F: ED42          sbc       hl, bc
040471: 4D            ld        c, l
040472: 44            ld        b, h
040473: E1            pop       hl
040474: FDE1          pop       iy
040476: C9            ret
040477: 2C            inc       l
040478: 2D            dec       l
040479: C8            ret       z
04047A: E5            push      hl
04047B: C5            push      bc
04047C: 45            ld        b, l
04047D: B7            or        a
04047E: ED62          sbc       hl, hl
040480: 39            add       hl, sp
                    label_040481:
040481: CB2F          sra       a
                    label_040483:
040483: 23            inc       hl
040484: 23            inc       hl
040485: CB1E          rr        (hl)
040487: 2B            dec       hl
040488: CB1E          rr        (hl)
04048A: 2B            dec       hl
04048B: CB1E          rr        (hl)
04048D: 10F2          djnz      label_040481
04048F: C1            pop       bc
040490: E1            pop       hl
040491: C9            ret
                    label_040492:
040492: 2C            inc       l
040493: 2D            dec       l
040494: C8            ret       z
040495: E5            push      hl
040496: C5            push      bc
040497: 45            ld        b, l
040498: B7            or        a
040499: ED62          sbc       hl, hl
04049B: 39            add       hl, sp
04049C: CB3F          srl       a
04049E: C3830404      jp        label_040483

                    _npf_vpprintf:
0404A2: 2174FFFF      ld        hl, FFFF74
0404A6: CDCC0004      call      __frameset
0404AA: DD310C        ld        iy, (ix + 0C)
0404AD: DD270F        ld        hl, (ix + 0F)
0404B0: DD2FBB        ld        (ix + -45), hl
0404B3: AF            xor       a
0404B4: ED62          sbc       hl, hl
0404B6: ED02F6        lea       bc, IX + F6
0404B9: DD0F9E        ld        (ix + -62), bc
0404BC: ED02F2        lea       bc, IX + F2
0404BF: DD0F9B        ld        (ix + -65), bc
0404C2: ED02EE        lea       bc, IX + EE
0404C5: DD0FA4        ld        (ix + -5C), bc
0404C8: ED02EA        lea       bc, IX + EA
0404CB: DD0FA1        ld        (ix + -5F), bc
0404CE: ED02CA        lea       bc, IX + CA
0404D1: DD0FAF        ld        (ix + -51), bc
0404D4: 47            ld        b, a
0404D5: 1E0A          ld        e, 0A
0404D7: DD1FA7        ld        (ix + -59), de
0404DA: DD2FC7        ld        (ix + -39), hl
                    label_0404DD:
0404DD: FD6E00        ld        l, (iy + 00)
0404E0: 7D            ld        a, l
0404E1: B7            or        a
0404E2: CA041C04      jp        z, label_041C04
0404E6: DD75B5        ld        (ix + -4B), l
0404E9: 7D            ld        a, l
0404EA: FE25          cp        25
0404EC: 68            ld        l, b
0404ED: 48            ld        c, b
0404EE: 3E01          ld        a, 01
0404F0: 67            ld        h, a
0404F1: 78            ld        a, b
0404F2: 58            ld        e, b
0404F3: DD3EC4        ld        (ix + -3C), iy
0404F6: C2740904      jp        nz, label_040974
                    label_0404FA:
0404FA: DD74AC        ld        (ix + -54), h
0404FD: DD778F        ld        (ix + -71), a
040500: DD708E        ld        (ix + -72), b
                    label_040503:
040503: DD71B2        ld        (ix + -4E), c
040506: DD75AB        ld        (ix + -55), l
040509: ED3302        lea       IY, IY + 02
                    label_04050C:
04050C: FD56FF        ld        d, (iy + -01)
04050F: 7A            ld        a, d
040510: B7            or        a
040511: ED2300        lea       hl, IY + 00
040514: FD21000000    ld        iy, 000000
040519: ED0300        lea       bc, IY + 00
04051C: CAF80504      jp        z, label_0405F8
040520: DD2FC1        ld        (ix + -3F), hl
040523: 7A            ld        a, d
040524: CB07          rlc       a
040526: ED62          sbc       hl, hl
040528: 6A            ld        l, d
040529: DD2FBE        ld        (ix + -42), hl
04052C: 01200000      ld        bc, 000020
040530: B7            or        a
040531: ED42          sbc       hl, bc
040533: 201B          jr        nz, label_040550
040535: 7B            ld        a, e
040536: B7            or        a
040537: 2EFF          ld        l, FF
040539: DD4EB2        ld        c, (ix + -4E)
04053C: 2802          jr        z, label_040540
04053E: 2E00          ld        l, 00
                    label_040540:
040540: CB45          bit       0, l
040542: 3E20          ld        a, 20
040544: 2001          jr        nz, label_040547
040546: 79            ld        a, c
                    label_040547:
040547: CB45          bit       0, l
040549: 2E20          ld        l, 20
04054B: 2022          jr        nz, label_04056F
04054D: 6B            ld        l, e
04054E: 181F          jr        label_04056F
                    label_040550:
040550: DD31C1        ld        iy, (ix + -3F)
040553: FD2B          dec       iy
040555: DD27BE        ld        hl, (ix + -42)
040558: 01230000      ld        bc, 000023
04055C: B7            or        a
04055D: ED42          sbc       hl, bc
04055F: 2819          jr        z, label_04057A
040561: DD27BE        ld        hl, (ix + -42)
040564: 012B0000      ld        bc, 00002B
040568: B7            or        a
040569: ED42          sbc       hl, bc
04056B: 69            ld        l, c
04056C: 7D            ld        a, l
04056D: 2013          jr        nz, label_040582
                    label_04056F:
04056F: DD31C1        ld        iy, (ix + -3F)
040572: FD23          inc       iy
040574: DD77B2        ld        (ix + -4E), a
040577: 5D            ld        e, l
040578: 1892          jr        label_04050C
                    label_04057A:
04057A: 3E23          ld        a, 23
04057C: 6F            ld        l, a
                    label_04057D:
04057D: DD4EB2        ld        c, (ix + -4E)
040580: 1881          jr        label_040503
                    label_040582:
040582: DD27BE        ld        hl, (ix + -42)
040585: 012D0000      ld        bc, 00002D
040589: B7            or        a
04058A: ED42          sbc       hl, bc
04058C: 2817          jr        z, label_0405A5
04058E: DD27BE        ld        hl, (ix + -42)
040591: 01300000      ld        bc, 000030
040595: B7            or        a
040596: ED42          sbc       hl, bc
040598: 2020          jr        nz, label_0405BA
04059A: DD7EAC        ld        a, (ix + -54)
04059D: DD778E        ld        (ix + -72), a
0405A0: DD6EAB        ld        l, (ix + -55)
0405A3: 18D8          jr        label_04057D
                    label_0405A5:
0405A5: DD31C1        ld        iy, (ix + -3F)
0405A8: FD2B          dec       iy
0405AA: 1600          ld        d, 00
0405AC: 42            ld        b, d
0405AD: 60            ld        h, b
0405AE: 3E2D          ld        a, 2D
0405B0: DD6EAB        ld        l, (ix + -55)
0405B3: DD4EB2        ld        c, (ix + -4E)
0405B6: C3FA0404      jp        label_0404FA
                    label_0405BA:
0405BA: 7A            ld        a, d
0405BB: FE2A          cp        2A
0405BD: FD21000000    ld        iy, 000000
0405C2: ED0300        lea       bc, IY + 00
0405C5: DD27C1        ld        hl, (ix + -3F)
0405C8: 202E          jr        nz, label_0405F8
0405CA: 56            ld        d, (hl)
0405CB: 21020000      ld        hl, 000002
                    label_0405CF:
0405CF: 7A            ld        a, d
0405D0: FE2E          cp        2E
0405D2: DD2F97        ld        (ix + -69), hl
0405D5: 2061          jr        nz, label_040638
0405D7: DD31C1        ld        iy, (ix + -3F)
0405DA: FD7E01        ld        a, (iy + 01)
0405DD: FE2A          cp        2A
0405DF: 2065          jr        nz, label_040646
0405E1: ED2302        lea       hl, IY + 02
0405E4: DD2FBE        ld        (ix + -42), hl
0405E7: FD5602        ld        d, (iy + 02)
0405EA: DD0F94        ld        (ix + -6C), bc
0405ED: 21020000      ld        hl, 000002
0405F1: DD2FAC        ld        (ix + -54), hl
0405F4: C3950604      jp        label_040695
                    label_0405F8:
0405F8: 2B            dec       hl
0405F9: DD2FC1        ld        (ix + -3F), hl
0405FC: C5            push      bc
0405FD: E1            pop       hl
0405FE: DD0FB8        ld        (ix + -48), bc
                    label_040601:
040601: 7A            ld        a, d
040602: C6D0          add       a, D0
040604: FE0A          cp        0A
040606: 30C7          jr        nc, label_0405CF
040608: DD27B8        ld        hl, (ix + -48)
04060B: C5            push      bc
04060C: FDE1          pop       iy
04060E: 010A0000      ld        bc, 00000A
040612: CDFE0004      call      __imulu
040616: 01000000      ld        bc, 000000
04061A: 4A            ld        c, d
04061B: 11D0FFFF      ld        de, FFFFD0
04061F: 19            add       hl, de
040620: 09            add       hl, bc
040621: ED0300        lea       bc, IY + 00
040624: DD2FB8        ld        (ix + -48), hl
040627: DD31C1        ld        iy, (ix + -3F)
04062A: FD5601        ld        d, (iy + 01)
04062D: FD23          inc       iy
04062F: DD3EC1        ld        (ix + -3F), iy
040632: 21010000      ld        hl, 000001
040636: 18C9          jr        label_040601
                    label_040638:
040638: DD0F94        ld        (ix + -6C), bc
04063B: DD0FAC        ld        (ix + -54), bc
04063E: DD27C1        ld        hl, (ix + -3F)
040641: DD2FBE        ld        (ix + -42), hl
040644: 184F          jr        label_040695
                    label_040646:
040646: FE2D          cp        2D
040648: 200E          jr        nz, label_040658
04064A: DD31C1        ld        iy, (ix + -3F)
04064D: ED3302        lea       IY, IY + 02
040650: ED1300        lea       de, IY + 00
040653: DD0FAC        ld        (ix + -54), bc
040656: 180B          jr        label_040663
                    label_040658:
040658: DD17C1        ld        de, (ix + -3F)
04065B: 13            inc       de
04065C: 21010000      ld        hl, 000001
040660: DD2FAC        ld        (ix + -54), hl
                    label_040663:
040663: C5            push      bc
040664: E1            pop       hl
040665: D5            push      de
040666: FDE1          pop       iy
                    label_040668:
040668: FD5600        ld        d, (iy + 00)
04066B: 7A            ld        a, d
04066C: C6D0          add       a, D0
04066E: FE0A          cp        0A
040670: 301D          jr        nc, label_04068F
040672: 01000000      ld        bc, 000000
040676: 4A            ld        c, d
040677: DD0FC1        ld        (ix + -3F), bc
04067A: 010A0000      ld        bc, 00000A
04067E: CDFE0004      call      __imulu
040682: FD23          inc       iy
040684: 11D0FFFF      ld        de, FFFFD0
040688: 19            add       hl, de
040689: DD17C1        ld        de, (ix + -3F)
04068C: 19            add       hl, de
04068D: 18D9          jr        label_040668
                    label_04068F:
04068F: DD2F94        ld        (ix + -6C), hl
040692: DD3EBE        ld        (ix + -42), iy
                    label_040695:
040695: 7A            ld        a, d
040696: CB07          rlc       a
040698: ED62          sbc       hl, hl
04069A: E5            push      hl
04069B: FDE1          pop       iy
04069D: FD            NONI
04069E: 6A            ld        l, d
04069F: 1198FFFF      ld        de, FFFF98
0406A3: FD19          add       iy, de
0406A5: ED2300        lea       hl, IY + 00
0406A8: 0E17          ld        c, 17
0406AA: CD510104      call      __ishl
0406AE: E5            push      hl
0406AF: D1            pop       de
0406B0: ED2300        lea       hl, IY + 00
0406B3: 0E01          ld        c, 01
0406B5: CD770104      call      __ishru
0406B9: E5            push      hl
0406BA: C1            pop       bc
0406BB: EB            ex        de, hl
0406BC: CD380104      call      __ior
0406C0: E5            push      hl
0406C1: D1            pop       de
0406C2: 010A0000      ld        bc, 00000A
0406C6: B7            or        a
0406C7: ED42          sbc       hl, bc
0406C9: 3809          jr        c, label_0406D4
0406CB: 11000000      ld        de, 000000
0406CF: DD31BE        ld        iy, (ix + -42)
0406D2: 1864          jr        label_040738
                    label_0406D4:
0406D4: DD31BE        ld        iy, (ix + -42)
0406D7: ED0300        lea       bc, IY + 00
0406DA: 03            inc       bc
0406DB: 21421E04      ld        hl, 041E42
0406DF: 19            add       hl, de
0406E0: 19            add       hl, de
0406E1: 19            add       hl, de
0406E2: ED27          ld        hl, (hl)
0406E4: 11000000      ld        de, 000000
0406E8: E9            jp        (hl)
0406E9: FD7E01        ld        a, (iy + 01)
0406EC: FE68          cp        68
0406EE: 3EFF          ld        a, FF
0406F0: 2802          jr        z, label_0406F4
0406F2: 3E00          ld        a, 00
                    label_0406F4:
0406F4: CB47          bit       0, a
0406F6: 11020000      ld        de, 000002
0406FA: 2023          jr        nz, label_04071F
0406FC: 11010000      ld        de, 000001
040700: 181D          jr        label_04071F
040702: 11050000      ld        de, 000005
040706: 182D          jr        label_040735
040708: FD7E01        ld        a, (iy + 01)
04070B: FE6C          cp        6C
04070D: 3EFF          ld        a, FF
04070F: 2802          jr        z, label_040713
040711: 3E00          ld        a, 00
                    label_040713:
040713: CB47          bit       0, a
040715: 11040000      ld        de, 000004
040719: 2004          jr        nz, label_04071F
04071B: 11030000      ld        de, 000003
                    label_04071F:
04071F: CB47          bit       0, a
040721: 2812          jr        z, label_040735
040723: DD31BE        ld        iy, (ix + -42)
040726: ED3302        lea       IY, IY + 02
040729: 180D          jr        label_040738
04072B: 11070000      ld        de, 000007
04072F: 1804          jr        label_040735
040731: 11060000      ld        de, 000006
                    label_040735:
040735: C5            push      bc
040736: FDE1          pop       iy
                    label_040738:
040738: DD3EBE        ld        (ix + -42), iy
04073B: FD7E00        ld        a, (iy + 00)
04073E: 6F            ld        l, a
04073F: CB05          rlc       l
040741: ED62          sbc       hl, hl
040743: E5            push      hl
040744: FDE1          pop       iy
040746: FD            NONI
040747: 6F            ld        l, a
040748: ED2300        lea       hl, IY + 00
04074B: 01250000      ld        bc, 000025
04074F: B7            or        a
040750: ED42          sbc       hl, bc
040752: DD1FC1        ld        (ix + -3F), de
040755: 2031          jr        nz, label_040788
040757: B7            or        a
040758: ED62          sbc       hl, hl
04075A: DD2FAC        ld        (ix + -54), hl
04075D: AF            xor       a
04075E: DD779A        ld        (ix + -66), a
040761: DD7793        ld        (ix + -6D), a
040764: 0E01          ld        c, 01
040766: DD71AA        ld        (ix + -56), c
040769: DD778C        ld        (ix + -74), a
04076C: DD7786        ld        (ix + -7A), a
04076F: DD7783        ld        (ix + -7D), a
040772: 010A0000      ld        bc, 00000A
040776: DD0F80        ld        (ix + -80), bc
040779: DD2F90        ld        (ix + -70), hl
04077C: 3E20          ld        a, 20
04077E: DD7789        ld        (ix + -77), a
040781: DD17C4        ld        de, (ix + -3C)
040784: C33E0804      jp        label_04083E
                    label_040788:
040788: ED2300        lea       hl, IY + 00
04078B: 01420000      ld        bc, 000042
04078F: B7            or        a
040790: ED42          sbc       hl, bc
040792: 2029          jr        nz, label_0407BD
040794: AF            xor       a
040795: DD07C4        ld        bc, (ix + -3C)
040798: DD7789        ld        (ix + -77), a
04079B: AF            xor       a
04079C: DD779A        ld        (ix + -66), a
04079F: DD7793        ld        (ix + -6D), a
0407A2: 2E01          ld        l, 01
0407A4: DD75AA        ld        (ix + -56), l
0407A7: DD758C        ld        (ix + -74), l
0407AA: DD7586        ld        (ix + -7A), l
0407AD: DD7783        ld        (ix + -7D), a
0407B0: 210A0000      ld        hl, 00000A
0407B4: DD2F80        ld        (ix + -80), hl
0407B7: 21040000      ld        hl, 000004
0407BB: 187C          jr        label_040839
                    label_0407BD:
0407BD: ED2300        lea       hl, IY + 00
0407C0: 01460000      ld        bc, 000046
0407C4: B7            or        a
0407C5: ED42          sbc       hl, bc
0407C7: 203B          jr        nz, label_040804
0407C9: AF            xor       a
0407CA: DD07C4        ld        bc, (ix + -3C)
0407CD: DD7789        ld        (ix + -77), a
0407D0: C5            push      bc
0407D1: D1            pop       de
0407D2: DD27AC        ld        hl, (ix + -54)
0407D5: 7D            ld        a, l
0407D6: B7            or        a
0407D7: 21060000      ld        hl, 000006
0407DB: 2803          jr        z, label_0407E0
0407DD: DD2794        ld        hl, (ix + -6C)
                    label_0407E0:
0407E0: DD2F94        ld        (ix + -6C), hl
0407E3: AF            xor       a
0407E4: DD779A        ld        (ix + -66), a
0407E7: 2E01          ld        l, 01
0407E9: DD7593        ld        (ix + -6D), l
0407EC: DD77AA        ld        (ix + -56), a
0407EF: DD778C        ld        (ix + -74), a
0407F2: DD7586        ld        (ix + -7A), l
0407F5: DD7783        ld        (ix + -7D), a
0407F8: 210A0000      ld        hl, 00000A
0407FC: DD2F80        ld        (ix + -80), hl
0407FF: DD2F90        ld        (ix + -70), hl
040802: 183A          jr        label_04083E
                    label_040804:
040804: ED2300        lea       hl, IY + 00
040807: 01580000      ld        bc, 000058
04080B: B7            or        a
04080C: ED42          sbc       hl, bc
04080E: C2600904      jp        nz, label_040960
040812: AF            xor       a
040813: DD07C4        ld        bc, (ix + -3C)
040816: DD7789        ld        (ix + -77), a
040819: AF            xor       a
04081A: DD779A        ld        (ix + -66), a
04081D: DD7793        ld        (ix + -6D), a
040820: 2E01          ld        l, 01
040822: DD75AA        ld        (ix + -56), l
040825: DD778C        ld        (ix + -74), a
040828: DD7586        ld        (ix + -7A), l
04082B: DD7783        ld        (ix + -7D), a
04082E: 21100000      ld        hl, 000010
040832: DD2F80        ld        (ix + -80), hl
040835: 21060000      ld        hl, 000006
                    label_040839:
040839: DD2F90        ld        (ix + -70), hl
                    label_04083C:
04083C: C5            push      bc
04083D: D1            pop       de
                    label_04083E:
04083E: DD31BE        ld        iy, (ix + -42)
040841: FD23          inc       iy
040843: ED2300        lea       hl, IY + 00
040846: D5            push      de
040847: C1            pop       bc
040848: B7            or        a
040849: ED42          sbc       hl, bc
04084B: 2006          jr        nz, label_040853
04084D: D5            push      de
04084E: C1            pop       bc
04084F: C3770904      jp        label_040977
                    label_040853:
040853: D5            push      de
040854: C1            pop       bc
040855: ED2300        lea       hl, IY + 00
040858: B7            or        a
040859: ED42          sbc       hl, bc
04085B: E5            push      hl
04085C: C1            pop       bc
04085D: EB            ex        de, hl
04085E: 09            add       hl, bc
04085F: DD2FC4        ld        (ix + -3C), hl
040862: DD0797        ld        bc, (ix + -69)
040865: 79            ld        a, c
040866: FE02          cp        02
040868: 2048          jr        nz, label_0408B2
04086A: DD31BB        ld        iy, (ix + -45)
04086D: FD2700        ld        hl, (iy + 00)
040870: DD2FBE        ld        (ix + -42), hl
040873: 01000000      ld        bc, 000000
040877: B7            or        a
040878: ED42          sbc       hl, bc
04087A: EC180200      call      pe, __setflag(OS)
04087E: 3E01          ld        a, 01
040880: DD778D        ld        (ix + -73), a
040883: FA8D0804      jp        m, label_04088D
040887: DD7E8F        ld        a, (ix + -71)
04088A: DD778D        ld        (ix + -73), a
                    label_04088D:
04088D: ED3303        lea       IY, IY + 03
040890: DD3EBB        ld        (ix + -45), iy
040893: DD17BE        ld        de, (ix + -42)
040896: D5            push      de
040897: E1            pop       hl
040898: D5            push      de
040899: FDE1          pop       iy
04089B: FD29          add       iy, iy
04089D: ED62          sbc       hl, hl
04089F: E5            push      hl
0408A0: C1            pop       bc
0408A1: EB            ex        de, hl
0408A2: 09            add       hl, bc
0408A3: CDB80104      call      __ixor
0408A7: DD2FB8        ld        (ix + -48), hl
0408AA: 21010000      ld        hl, 000001
0408AE: E5            push      hl
0408AF: C1            pop       bc
0408B0: 1806          jr        label_0408B8
                    label_0408B2:
0408B2: DD7E8F        ld        a, (ix + -71)
0408B5: DD778D        ld        (ix + -73), a
                    label_0408B8:
0408B8: DD27C1        ld        hl, (ix + -3F)
0408BB: DD27AC        ld        hl, (ix + -54)
0408BE: 7D            ld        a, l
0408BF: FE02          cp        02
0408C1: 2036          jr        nz, label_0408F9
0408C3: C5            push      bc
0408C4: D1            pop       de
0408C5: DD27BB        ld        hl, (ix + -45)
0408C8: ED27          ld        hl, (hl)
0408CA: DD2F94        ld        (ix + -6C), hl
0408CD: 01000000      ld        bc, 000000
0408D1: B7            or        a
0408D2: ED42          sbc       hl, bc
0408D4: EC180200      call      pe, __setflag(OS)
0408D8: 21010000      ld        hl, 000001
0408DC: DD2FAC        ld        (ix + -54), hl
0408DF: F2EA0804      jp        p, label_0408EA
0408E3: 21000000      ld        hl, 000000
0408E7: DD2FAC        ld        (ix + -54), hl
                    label_0408EA:
0408EA: DD31BB        ld        iy, (ix + -45)
0408ED: ED2303        lea       hl, IY + 03
0408F0: DD2FB5        ld        (ix + -4B), hl
0408F3: 2E00          ld        l, 00
0408F5: D5            push      de
0408F6: C1            pop       bc
0408F7: 1808          jr        label_040901
                    label_0408F9:
0408F9: DD27BB        ld        hl, (ix + -45)
0408FC: DD2FB5        ld        (ix + -4B), hl
0408FF: 2E00          ld        l, 00
                    label_040901:
040901: DD1790        ld        de, (ix + -70)
040904: 7B            ld        a, e
040905: FE0B          cp        0B
040907: 3829          jr        c, label_040932
040909: FD21000000    ld        iy, 000000
04090E: DD3E83        ld        (ix + -7D), iy
040911: FD            NONI
040912: 54            ld        d, h
040913: DD728F        ld        (ix + -71), d
040916: DD3EC1        ld        (ix + -3F), iy
040919: DD3EBE        ld        (ix + -42), iy
                    label_04091C:
04091C: DD7580        ld        (ix + -80), l
04091F: DD7589        ld        (ix + -77), l
040922: DD17AF        ld        de, (ix + -51)
040925: DD1F90        ld        (ix + -70), de
040928: DD17B5        ld        de, (ix + -4B)
04092B: DD1FBB        ld        (ix + -45), de
04092E: C3291104      jp        label_041129
                    label_040932:
040932: 21A51E04      ld        hl, 041EA5
040936: 19            add       hl, de
040937: 19            add       hl, de
040938: 19            add       hl, de
040939: ED27          ld        hl, (hl)
04093B: DD31B5        ld        iy, (ix + -4B)
04093E: ED1303        lea       de, IY + 03
040941: E9            jp        (hl)
040942: DD36CA25      ld        (ix + -36), 25
040946: FD21000000    ld        iy, 000000
04094B: DD3E83        ld        (ix + -7D), iy
04094E: FD            NONI
04094F: 54            ld        d, h
040950: DD728F        ld        (ix + -71), d
040953: 21010000      ld        hl, 000001
040957: DD2FC1        ld        (ix + -3F), hl
04095A: DD3EBE        ld        (ix + -42), iy
04095D: 2D            dec       l
04095E: 18BC          jr        label_04091C
                    label_040960:
040960: 019EFFFF      ld        bc, FFFF9E
040964: FD09          add       iy, bc
040966: ED0300        lea       bc, IY + 00
040969: C5            push      bc
04096A: E1            pop       hl
04096B: 11170000      ld        de, 000017
04096F: B7            or        a
040970: ED52          sbc       hl, de
040972: 382F          jr        c, label_0409A3
                    label_040974:
040974: DD07C4        ld        bc, (ix + -3C)
                    label_040977:
040977: DD27C7        ld        hl, (ix + -39)
04097A: 23            inc       hl
04097B: DD2FC7        ld        (ix + -39), hl
04097E: 03            inc       bc
04097F: DD0FC4        ld        (ix + -3C), bc
040982: DD5EB5        ld        e, (ix + -4B)
040985: 7B            ld        a, e
040986: CB07          rlc       a
040988: ED62          sbc       hl, hl
04098A: 6B            ld        l, e
04098B: DD1709        ld        de, (ix + 09)
04098E: D5            push      de
04098F: E5            push      hl
040990: DD2706        ld        hl, (ix + 06)
040993: CD2E0104      call      __indcallhl
040997: DD31C4        ld        iy, (ix + -3C)
04099A: E1            pop       hl
04099B: E1            pop       hl
                    label_04099C:
04099C: 1600          ld        d, 00
04099E: 42            ld        b, d
04099F: C3DD0404      jp        label_0404DD
                    label_0409A3:
0409A3: 21601E04      ld        hl, 041E60
0409A7: 09            add       hl, bc
0409A8: 09            add       hl, bc
0409A9: 09            add       hl, bc
0409AA: ED27          ld        hl, (hl)
0409AC: 3E20          ld        a, 20
0409AE: DD07C4        ld        bc, (ix + -3C)
0409B1: DD17C1        ld        de, (ix + -3F)
0409B4: E9            jp        (hl)
0409B5: B7            or        a
0409B6: ED62          sbc       hl, hl
0409B8: DD2FAC        ld        (ix + -54), hl
0409BB: AF            xor       a
0409BC: DD779A        ld        (ix + -66), a
0409BF: DD7793        ld        (ix + -6D), a
0409C2: 2C            inc       l
0409C3: DD75AA        ld        (ix + -56), l
0409C6: DD778C        ld        (ix + -74), a
0409C9: DD7786        ld        (ix + -7A), a
0409CC: DD7783        ld        (ix + -7D), a
0409CF: 210A0000      ld        hl, 00000A
0409D3: DD2F80        ld        (ix + -80), hl
0409D6: 21010000      ld        hl, 000001
0409DA: C35F1704      jp        label_04175F
0409DE: DD27B5        ld        hl, (ix + -4B)
0409E1: ED27          ld        hl, (hl)
0409E3: DD1FBB        ld        (ix + -45), de
0409E6: 11000000      ld        de, 000000
0409EA: E5            push      hl
0409EB: FDE1          pop       iy
                    label_0409ED:
0409ED: ED2300        lea       hl, IY + 00
0409F0: 19            add       hl, de
0409F1: 7E            ld        a, (hl)
0409F2: B7            or        a
0409F3: 2855          jr        z, label_040A4A
0409F5: 13            inc       de
0409F6: 18F5          jr        label_0409ED
0409F8: 21F61E04      ld        hl, 041EF6
0409FC: DD17C1        ld        de, (ix + -3F)
0409FF: 19            add       hl, de
040A00: 19            add       hl, de
040A01: 19            add       hl, de
040A02: ED27          ld        hl, (hl)
040A04: DD0F97        ld        (ix + -69), bc
040A07: E9            jp        (hl)
040A08: DD31B5        ld        iy, (ix + -4B)
040A0B: ED2303        lea       hl, IY + 03
040A0E: DD2FBB        ld        (ix + -45), hl
040A11: FD1700        ld        de, (iy + 00)
040A14: 7A            ld        a, d
040A15: 6F            ld        l, a
040A16: CB05          rlc       l
040A18: ED62          sbc       hl, hl
040A1A: 67            ld        h, a
040A1B: 6B            ld        l, e
040A1C: C3030F04      jp        label_040F03
040A20: DD0F97        ld        (ix + -69), bc
040A23: DD31B5        ld        iy, (ix + -4B)
040A26: ED0309        lea       bc, IY + 09
040A29: 21DE1E04      ld        hl, 041EDE
040A2D: DD17C1        ld        de, (ix + -3F)
040A30: 19            add       hl, de
040A31: 19            add       hl, de
040A32: 19            add       hl, de
040A33: ED27          ld        hl, (hl)
040A35: E9            jp        (hl)
040A36: DD31B5        ld        iy, (ix + -4B)
040A39: ED2303        lea       hl, IY + 03
040A3C: DD2FBB        ld        (ix + -45), hl
040A3F: FD2700        ld        hl, (iy + 00)
040A42: 01FFFF00      ld        bc, 00FFFF
040A46: C3080D04      jp        label_040D08
                    label_040A4A:
040A4A: DD2794        ld        hl, (ix + -6C)
040A4D: B7            or        a
040A4E: ED52          sbc       hl, de
040A50: EC180200      call      pe, __setflag(OS)
040A54: DD2794        ld        hl, (ix + -6C)
040A57: DD2FC1        ld        (ix + -3F), hl
040A5A: FA610A04      jp        m, label_040A61
040A5E: DD1FC1        ld        (ix + -3F), de
                    label_040A61:
040A61: DD3E90        ld        (ix + -70), iy
040A64: DD27AC        ld        hl, (ix + -54)
040A67: 7D            ld        a, l
040A68: FE01          cp        01
040A6A: 2E00          ld        l, 00
040A6C: 2803          jr        z, label_040A71
040A6E: DD1FC1        ld        (ix + -3F), de
                    label_040A71:
040A71: FD21000000    ld        iy, 000000
040A76: DD3E83        ld        (ix + -7D), iy
040A79: FD            NONI
040A7A: 54            ld        d, h
040A7B: DD728F        ld        (ix + -71), d
040A7E: DD3EBE        ld        (ix + -42), iy
040A81: DD7580        ld        (ix + -80), l
                    label_040A84:
040A84: DD7589        ld        (ix + -77), l
040A87: C3291104      jp        label_041129
040A8B: DD27B5        ld        hl, (ix + -4B)
040A8E: 7E            ld        a, (hl)
040A8F: DD77CA        ld        (ix + -36), a
040A92: FD21000000    ld        iy, 000000
040A97: DD3E83        ld        (ix + -7D), iy
040A9A: DD1FBB        ld        (ix + -45), de
040A9D: FD            NONI
040A9E: 54            ld        d, h
040A9F: DD728F        ld        (ix + -71), d
040AA2: 21010000      ld        hl, 000001
040AA6: DD2FC1        ld        (ix + -3F), hl
                    label_040AA9:
040AA9: DD3EBE        ld        (ix + -42), iy
040AAC: 1844          jr        label_040AF2
040AAE: DD27B5        ld        hl, (ix + -4B)
040AB1: ED27          ld        hl, (hl)
040AB3: DD1FBB        ld        (ix + -45), de
040AB6: 11000000      ld        de, 000000
040ABA: DD0F97        ld        (ix + -69), bc
040ABD: 01200000      ld        bc, 000020
040AC1: C5            push      bc
040AC2: 01100000      ld        bc, 000010
040AC6: C5            push      bc
040AC7: D5            push      de
040AC8: D5            push      de
040AC9: E5            push      hl
040ACA: DD27AF        ld        hl, (ix + -51)
040ACD: E5            push      hl
040ACE: CD0C1C04      call      _npf_utoa_rev
040AD2: DD0797        ld        bc, (ix + -69)
040AD5: FD21000000    ld        iy, 000000
040ADA: DD2FC1        ld        (ix + -3F), hl
040ADD: E1            pop       hl
040ADE: E1            pop       hl
040ADF: E1            pop       hl
040AE0: E1            pop       hl
040AE1: E1            pop       hl
040AE2: E1            pop       hl
040AE3: DD3E83        ld        (ix + -7D), iy
040AE6: FD            NONI
040AE7: 54            ld        d, h
040AE8: DD728F        ld        (ix + -71), d
040AEB: 21780000      ld        hl, 000078
040AEF: DD2FBE        ld        (ix + -42), hl
                    label_040AF2:
040AF2: 2E00          ld        l, 00
040AF4: DD7580        ld        (ix + -80), l
040AF7: DD7589        ld        (ix + -77), l
040AFA: DD17AF        ld        de, (ix + -51)
040AFD: DD1F90        ld        (ix + -70), de
040B00: C3291104      jp        label_041129
040B04: DD0F97        ld        (ix + -69), bc
040B07: DD1FBB        ld        (ix + -45), de
040B0A: 21C61E04      ld        hl, 041EC6
040B0E: DD17C1        ld        de, (ix + -3F)
040B11: 19            add       hl, de
040B12: 19            add       hl, de
040B13: 19            add       hl, de
040B14: ED27          ld        hl, (hl)
040B16: E9            jp        (hl)
040B17: DD27B5        ld        hl, (ix + -4B)
040B1A: ED27          ld        hl, (hl)
040B1C: DD17C7        ld        de, (ix + -39)
040B1F: ED1F          ld        (hl), de
040B21: C3180E04      jp        label_040E18
040B25: DD0F97        ld        (ix + -69), bc
040B28: DD31B5        ld        iy, (ix + -4B)
040B2B: FD2700        ld        hl, (iy + 00)
040B2E: FD5E03        ld        e, (iy + 03)
040B31: DD2FC1        ld        (ix + -3F), hl
040B34: DD73BE        ld        (ix + -42), e
040B37: 01000000      ld        bc, 000000
040B3B: AF            xor       a
040B3C: CD740200      call      __fcmp(OS)
040B40: 3E2D          ld        a, 2D
040B42: FA490B04      jp        m, label_040B49
040B46: DD7EB2        ld        a, (ix + -4E)
                    label_040B49:
040B49: DD778F        ld        (ix + -71), a
040B4C: DD31B5        ld        iy, (ix + -4B)
040B4F: ED3306        lea       IY, IY + 06
040B52: DD27C1        ld        hl, (ix + -3F)
040B55: DD2FEE        ld        (ix + -12), hl
040B58: DD7EBE        ld        a, (ix + -42)
040B5B: DD77F1        ld        (ix + -0F), a
040B5E: 11000000      ld        de, 000000
                    label_040B62:
040B62: D5            push      de
040B63: E1            pop       hl
040B64: 01040000      ld        bc, 000004
040B68: B7            or        a
040B69: ED42          sbc       hl, bc
040B6B: 280D          jr        z, label_040B7A
040B6D: DD27A4        ld        hl, (ix + -5C)
040B70: 19            add       hl, de
040B71: 7E            ld        a, (hl)
040B72: DD27A1        ld        hl, (ix + -5F)
040B75: 19            add       hl, de
040B76: 77            ld        (hl), a
040B77: 13            inc       de
040B78: 18E8          jr        label_040B62
                    label_040B7A:
040B7A: DD3EBB        ld        (ix + -45), iy
040B7D: DD27C1        ld        hl, (ix + -3F)
040B80: DD5EBE        ld        e, (ix + -42)
040B83: 01000000      ld        bc, 000000
040B87: AF            xor       a
040B88: CD740200      call      __fcmp(OS)
040B8C: 3E01          ld        a, 01
040B8E: 2802          jr        z, label_040B92
040B90: 3E00          ld        a, 00
                    label_040B92:
040B92: DD7780        ld        (ix + -80), a
040B95: DD31EA        ld        iy, (ix + -16)
040B98: DD56ED        ld        d, (ix + -13)
040B9B: ED2300        lea       hl, IY + 00
040B9E: 5A            ld        e, d
040B9F: 01000080      ld        bc, 800000
040BA3: 3E7F          ld        a, 7F
040BA5: CDD70104      call      label_0401D7
040BA9: CDF20104      call      label_0401F2
040BAD: 203B          jr        nz, label_040BEA
040BAF: ED2300        lea       hl, IY + 00
040BB2: 5A            ld        e, d
040BB3: 01FFFF7F      ld        bc, 7FFFFF
040BB7: AF            xor       a
040BB8: CDD70104      call      label_0401D7
040BBC: CDFA0104      call      label_0401FA
040BC0: FD21000000    ld        iy, 000000
040BC5: ED0300        lea       bc, IY + 00
040BC8: C5            push      bc
040BC9: D1            pop       de
040BCA: 2046          jr        nz, label_040C12
                    label_040BCC:
040BCC: C5            push      bc
040BCD: E1            pop       hl
040BCE: 11030000      ld        de, 000003
040BD2: B7            or        a
040BD3: ED52          sbc       hl, de
040BD5: CA7B0C04      jp        z, label_040C7B
040BD9: 21121F04      ld        hl, 041F12
040BDD: 09            add       hl, bc
040BDE: 7E            ld        a, (hl)
040BDF: DD8689        add       a, (ix + -77)
040BE2: DD27AF        ld        hl, (ix + -51)
040BE5: 09            add       hl, bc
040BE6: 77            ld        (hl), a
040BE7: 03            inc       bc
040BE8: 18E2          jr        label_040BCC
                    label_040BEA:
040BEA: DD27C1        ld        hl, (ix + -3F)
040BED: DD2FF6        ld        (ix + -0A), hl
040BF0: DD7EBE        ld        a, (ix + -42)
040BF3: DD77F9        ld        (ix + -07), a
040BF6: 11000000      ld        de, 000000
                    label_040BFA:
040BFA: D5            push      de
040BFB: E1            pop       hl
040BFC: 01040000      ld        bc, 000004
040C00: B7            or        a
040C01: ED42          sbc       hl, bc
040C03: 2829          jr        z, label_040C2E
040C05: DD279E        ld        hl, (ix + -62)
040C08: 19            add       hl, de
040C09: 7E            ld        a, (hl)
040C0A: DD279B        ld        hl, (ix + -65)
040C0D: 19            add       hl, de
040C0E: 77            ld        (hl), a
040C0F: 13            inc       de
040C10: 18E8          jr        label_040BFA
                    label_040C12:
040C12: D5            push      de
040C13: E1            pop       hl
040C14: 01030000      ld        bc, 000003
040C18: B7            or        a
040C19: ED42          sbc       hl, bc
040C1B: 285E          jr        z, label_040C7B
040C1D: 210E1F04      ld        hl, 041F0E
040C21: 19            add       hl, de
040C22: 7E            ld        a, (hl)
040C23: DD8689        add       a, (ix + -77)
040C26: DD27AF        ld        hl, (ix + -51)
040C29: 19            add       hl, de
040C2A: 77            ld        (hl), a
040C2B: 13            inc       de
040C2C: 18E4          jr        label_040C12
                    label_040C2E:
040C2E: DD17F2        ld        de, (ix + -0E)
040C31: DD7EF5        ld        a, (ix + -0B)
040C34: D5            push      de
040C35: C1            pop       bc
040C36: DD77C1        ld        (ix + -3F), a
040C39: 2E17          ld        l, 17
040C3B: CD920404      call      label_040492
040C3F: C5            push      bc
040C40: E1            pop       hl
040C41: 01FF0000      ld        bc, 0000FF
040C45: CDE50004      call      label_0400E5
040C49: E5            push      hl
040C4A: FDE1          pop       iy
040C4C: 016AFFFF      ld        bc, FFFF6A
040C50: FD09          add       iy, bc
040C52: 7D            ld        a, l
040C53: FEBF          cp        BF
040C55: 3847          jr        c, label_040C9E
040C57: FD21000000    ld        iy, 000000
040C5C: ED1300        lea       de, IY + 00
                    label_040C5F:
040C5F: D5            push      de
040C60: E1            pop       hl
040C61: 01030000      ld        bc, 000003
040C65: B7            or        a
040C66: ED42          sbc       hl, bc
040C68: 2811          jr        z, label_040C7B
040C6A: 21161F04      ld        hl, 041F16
040C6E: 19            add       hl, de
040C6F: 7E            ld        a, (hl)
040C70: DD8689        add       a, (ix + -77)
040C73: DD27AF        ld        hl, (ix + -51)
040C76: 19            add       hl, de
040C77: 77            ld        (hl), a
040C78: 13            inc       de
040C79: 18E4          jr        label_040C5F
                    label_040C7B:
040C7B: 11FDFFFF      ld        de, FFFFFD
040C7F: DD3E83        ld        (ix + -7D), iy
                    label_040C82:
040C82: EB            ex        de, hl
040C83: CD2F0104      call      label_04012F
040C87: DD2FC1        ld        (ix + -3F), hl
040C8A: DD3EBE        ld        (ix + -42), iy
040C8D: 3E01          ld        a, 01
040C8F: DD7789        ld        (ix + -77), a
040C92: DD27AF        ld        hl, (ix + -51)
040C95: DD2F90        ld        (ix + -70), hl
040C98: 2E00          ld        l, 00
040C9A: C3261104      jp        label_041126
                    label_040C9E:
040C9E: DD2FB5        ld        (ix + -4B), hl
040CA1: EB            ex        de, hl
040CA2: DD5EC1        ld        e, (ix + -3F)
040CA5: 01FFFF7F      ld        bc, 7FFFFF
040CA9: AF            xor       a
040CAA: CDD70104      call      label_0401D7
040CAE: 03            inc       bc
040CAF: CDD10104      call      label_0401D1
040CB3: DD07B5        ld        bc, (ix + -4B)
040CB6: 79            ld        a, c
040CB7: FE97          cp        97
040CB9: DA501604      jp        c, label_041650
040CBD: 01000000      ld        bc, 000000
040CC1: 4B            ld        c, e
040CC2: FDE5          push      iy
040CC4: C5            push      bc
040CC5: D1            pop       de
040CC6: 40010000      ld.sis    bc, 0000
040CCA: CDEA0304      call      label_0403EA
040CCE: DD0FFD        ld        (ix + -03), bc
040CD1: 0174FFFF      ld        bc, FFFF74
040CD5: ED5500        lea       iy, ix + 00
040CD8: FD09          add       iy, bc
040CDA: FD2F00        ld        (iy + 00), hl
040CDD: DD1FB2        ld        (ix + -4E), de
040CE0: E1            pop       hl
040CE1: DD07FD        ld        bc, (ix + -03)
040CE4: 69            ld        l, c
040CE5: 60            ld        h, b
040CE6: 11000000      ld        de, 000000
040CEA: D5            push      de
040CEB: FDE1          pop       iy
040CED: DD1FBE        ld        (ix + -42), de
040CF0: 40010000      ld.sis    bc, 0000
040CF4: C3411804      jp        label_041841
040CF8: DD31B5        ld        iy, (ix + -4B)
040CFB: ED2303        lea       hl, IY + 03
040CFE: DD2FBB        ld        (ix + -45), hl
040D01: FD2700        ld        hl, (iy + 00)
040D04: 01FF0000      ld        bc, 0000FF
                    label_040D08:
040D08: CDE50004      call      label_0400E5
040D0C: E5            push      hl
040D0D: FDE1          pop       iy
040D0F: 1838          jr        label_040D49
040D11: DD31B5        ld        iy, (ix + -4B)
040D14: ED2306        lea       hl, IY + 06
040D17: DD2FBB        ld        (ix + -45), hl
040D1A: FD2700        ld        hl, (iy + 00)
040D1D: 11000000      ld        de, 000000
040D21: FD5E03        ld        e, (iy + 03)
040D24: E5            push      hl
040D25: FDE1          pop       iy
040D27: 1824          jr        label_040D4D
040D29: DD0FBB        ld        (ix + -45), bc
040D2C: DD31B5        ld        iy, (ix + -4B)
040D2F: FD2700        ld        hl, (iy + 00)
040D32: FD1703        ld        de, (iy + 03)
040D35: FD0706        ld        bc, (iy + 06)
040D38: E5            push      hl
040D39: FDE1          pop       iy
040D3B: 1816          jr        label_040D53
040D3D: DD31B5        ld        iy, (ix + -4B)
040D40: ED2303        lea       hl, IY + 03
040D43: DD2FBB        ld        (ix + -45), hl
040D46: FD3700        ld        iy, (iy + 00)
                    label_040D49:
040D49: 11000000      ld        de, 000000
                    label_040D4D:
040D4D: 40210000      ld.sis    hl, 0000
040D51: 4D            ld        c, l
040D52: 44            ld        b, h
                    label_040D53:
040D53: DD3EB5        ld        (ix + -4B), iy
040D56: ED2300        lea       hl, IY + 00
040D59: DD1FBE        ld        (ix + -42), de
040D5C: DD0FB2        ld        (ix + -4E), bc
040D5F: CD8D0204      call      label_04028D
040D63: 2013          jr        nz, label_040D78
040D65: DD27AC        ld        hl, (ix + -54)
040D68: 7D            ld        a, l
040D69: FE01          cp        01
040D6B: 200B          jr        nz, label_040D78
040D6D: DD2794        ld        hl, (ix + -6C)
040D70: 09            add       hl, bc
040D71: B7            or        a
040D72: ED42          sbc       hl, bc
040D74: CAD31004      jp        z, label_0410D3
                    label_040D78:
040D78: DD2790        ld        hl, (ix + -70)
040D7B: 7D            ld        a, l
040D7C: FE04          cp        04
040D7E: 2042          jr        nz, label_040DC2
040D80: DD31B5        ld        iy, (ix + -4B)
040D83: ED2300        lea       hl, IY + 00
040D86: DD17BE        ld        de, (ix + -42)
040D89: DD07B2        ld        bc, (ix + -4E)
040D8C: CD8D0204      call      label_04028D
040D90: 21010000      ld        hl, 000001
040D94: 2816          jr        z, label_040DAC
040D96: ED2300        lea       hl, IY + 00
040D99: DD17BE        ld        de, (ix + -42)
040D9C: CDA20204      call      label_0402A2
040DA0: 11000000      ld        de, 000000
040DA4: 5F            ld        e, a
040DA5: 21400000      ld        hl, 000040
040DA9: B7            or        a
040DAA: ED52          sbc       hl, de
                    label_040DAC:
040DAC: DD2FC1        ld        (ix + -3F), hl
040DAF: DD3ECA        ld        (ix + -36), iy
040DB2: DD17BE        ld        de, (ix + -42)
040DB5: DD1FCD        ld        (ix + -33), de
040DB8: DD71D0        ld        (ix + -30), c
040DBB: DD70D1        ld        (ix + -2F), b
040DBE: C3FC1004      jp        label_0410FC
                    label_040DC2:
040DC2: 7D            ld        a, l
040DC3: FE05          cp        05
040DC5: 21080000      ld        hl, 000008
040DC9: DD07BE        ld        bc, (ix + -42)
040DCC: 2803          jr        z, label_040DD1
040DCE: DD2780        ld        hl, (ix + -80)
                    label_040DD1:
040DD1: 11000000      ld        de, 000000
040DD5: DD5E89        ld        e, (ix + -77)
040DD8: D5            push      de
040DD9: E5            push      hl
040DDA: DD27B2        ld        hl, (ix + -4E)
040DDD: E5            push      hl
040DDE: C5            push      bc
040DDF: DD27B5        ld        hl, (ix + -4B)
040DE2: E5            push      hl
040DE3: DD27AF        ld        hl, (ix + -51)
040DE6: E5            push      hl
040DE7: CD0C1C04      call      _npf_utoa_rev
040DEB: DD07B2        ld        bc, (ix + -4E)
040DEE: DD17BE        ld        de, (ix + -42)
040DF1: DD31B5        ld        iy, (ix + -4B)
040DF4: DD2FC1        ld        (ix + -3F), hl
040DF7: E1            pop       hl
040DF8: E1            pop       hl
040DF9: E1            pop       hl
040DFA: E1            pop       hl
040DFB: E1            pop       hl
040DFC: E1            pop       hl
040DFD: C3FC1004      jp        label_0410FC
040E01: DD27B5        ld        hl, (ix + -4B)
040E04: ED27          ld        hl, (hl)
040E06: DD17C7        ld        de, (ix + -39)
040E09: 73            ld        (hl), e
040E0A: 23            inc       hl
040E0B: 72            ld        (hl), d
040E0C: 180A          jr        label_040E18
040E0E: DD27C7        ld        hl, (ix + -39)
040E11: 7D            ld        a, l
040E12: DD27B5        ld        hl, (ix + -4B)
040E15: ED27          ld        hl, (hl)
040E17: 77            ld        (hl), a
                    label_040E18:
040E18: FD21000000    ld        iy, 000000
040E1D: DD3E83        ld        (ix + -7D), iy
040E20: FD            NONI
040E21: 54            ld        d, h
040E22: DD728F        ld        (ix + -71), d
040E25: DD3EC1        ld        (ix + -3F), iy
040E28: DD3EBE        ld        (ix + -42), iy
040E2B: 6A            ld        l, d
040E2C: DD7580        ld        (ix + -80), l
040E2F: C3C61004      jp        label_0410C6
040E33: DD17C7        ld        de, (ix + -39)
040E36: D5            push      de
040E37: E1            pop       hl
040E38: D5            push      de
040E39: FDE1          pop       iy
040E3B: FD29          add       iy, iy
040E3D: ED62          sbc       hl, hl
040E3F: 7D            ld        a, l
040E40: DD27B5        ld        hl, (ix + -4B)
040E43: ED31          ld        iy, (hl)
040E45: FD1F00        ld        (iy + 00), de
040E48: FD7703        ld        (iy + 03), a
040E4B: 181E          jr        label_040E6B
040E4D: DD17C7        ld        de, (ix + -39)
040E50: D5            push      de
040E51: E1            pop       hl
040E52: D5            push      de
040E53: FDE1          pop       iy
040E55: FD29          add       iy, iy
040E57: ED62          sbc       hl, hl
040E59: DD31B5        ld        iy, (ix + -4B)
040E5C: FD3700        ld        iy, (iy + 00)
040E5F: FD1F00        ld        (iy + 00), de
040E62: FD2F03        ld        (iy + 03), hl
040E65: FD7506        ld        (iy + 06), l
040E68: FD7407        ld        (iy + 07), h
                    label_040E6B:
040E6B: FD21000000    ld        iy, 000000
040E70: DD3E83        ld        (ix + -7D), iy
040E73: FD            NONI
040E74: 54            ld        d, h
040E75: DD728F        ld        (ix + -71), d
040E78: DD3EC1        ld        (ix + -3F), iy
040E7B: DD3EBE        ld        (ix + -42), iy
040E7E: 6A            ld        l, d
040E7F: DD7580        ld        (ix + -80), l
040E82: C31D1104      jp        label_04111D
040E86: DD31B5        ld        iy, (ix + -4B)
040E89: ED2303        lea       hl, IY + 03
040E8C: DD2FBB        ld        (ix + -45), hl
040E8F: FD7E00        ld        a, (iy + 00)
040E92: 6F            ld        l, a
040E93: CB05          rlc       l
040E95: ED62          sbc       hl, hl
040E97: 6F            ld        l, a
040E98: 1869          jr        label_040F03
040E9A: DD31B5        ld        iy, (ix + -4B)
040E9D: ED2306        lea       hl, IY + 06
040EA0: DD2FBB        ld        (ix + -45), hl
040EA3: FD2700        ld        hl, (iy + 00)
040EA6: DD2F90        ld        (ix + -70), hl
040EA9: FD7E03        ld        a, (iy + 03)
040EAC: 6F            ld        l, a
040EAD: CB05          rlc       l
040EAF: ED62          sbc       hl, hl
040EB1: E5            push      hl
040EB2: D1            pop       de
040EB3: 5F            ld        e, a
040EB4: D5            push      de
040EB5: E1            pop       hl
040EB6: D5            push      de
040EB7: FDE1          pop       iy
040EB9: FD29          add       iy, iy
040EBB: ED62          sbc       hl, hl
040EBD: E5            push      hl
040EBE: C1            pop       bc
040EBF: 1850          jr        label_040F11
040EC1: DD31B5        ld        iy, (ix + -4B)
040EC4: ED2309        lea       hl, IY + 09
040EC7: ED0300        lea       bc, IY + 00
040ECA: DD2FBB        ld        (ix + -45), hl
040ECD: C5            push      bc
040ECE: E1            pop       hl
040ECF: ED27          ld        hl, (hl)
040ED1: DD2F90        ld        (ix + -70), hl
040ED4: FD1703        ld        de, (iy + 03)
040ED7: FD0706        ld        bc, (iy + 06)
040EDA: 1835          jr        label_040F11
040EDC: DD31B5        ld        iy, (ix + -4B)
040EDF: ED2303        lea       hl, IY + 03
040EE2: DD2FBB        ld        (ix + -45), hl
040EE5: FD2700        ld        hl, (iy + 00)
040EE8: DD2F90        ld        (ix + -70), hl
040EEB: 11000000      ld        de, 000000
040EEF: 40210000      ld.sis    hl, 0000
040EF3: 4D            ld        c, l
040EF4: 44            ld        b, h
040EF5: 181A          jr        label_040F11
040EF7: DD31B5        ld        iy, (ix + -4B)
040EFA: ED2303        lea       hl, IY + 03
040EFD: DD2FBB        ld        (ix + -45), hl
040F00: FD2700        ld        hl, (iy + 00)
                    label_040F03:
040F03: DD2F90        ld        (ix + -70), hl
040F06: E5            push      hl
040F07: FDE1          pop       iy
040F09: FD29          add       iy, iy
040F0B: ED62          sbc       hl, hl
040F0D: E5            push      hl
040F0E: D1            pop       de
040F0F: 4B            ld        c, e
040F10: 42            ld        b, d
                    label_040F11:
040F11: DD2790        ld        hl, (ix + -70)
040F14: DD1F89        ld        (ix + -77), de
040F17: DD0F83        ld        (ix + -7D), bc
040F1A: CD8D0204      call      label_04028D
040F1E: 3E2D          ld        a, 2D
040F20: FA270F04      jp        m, label_040F27
040F24: DD7EB2        ld        a, (ix + -4E)
                    label_040F27:
040F27: DD778F        ld        (ix + -71), a
040F2A: DD2790        ld        hl, (ix + -70)
040F2D: DD1789        ld        de, (ix + -77)
040F30: DD0783        ld        bc, (ix + -7D)
040F33: CD8D0204      call      label_04028D
040F37: 3E01          ld        a, 01
040F39: 2802          jr        z, label_040F3D
040F3B: 3E00          ld        a, 00
                    label_040F3D:
040F3D: DD7780        ld        (ix + -80), a
040F40: DD2790        ld        hl, (ix + -70)
040F43: DD1789        ld        de, (ix + -77)
040F46: DD0783        ld        bc, (ix + -7D)
040F49: CD8D0204      call      label_04028D
040F4D: DD17AF        ld        de, (ix + -51)
040F50: 2013          jr        nz, label_040F65
040F52: DD27AC        ld        hl, (ix + -54)
040F55: 7D            ld        a, l
040F56: FE01          cp        01
040F58: 200B          jr        nz, label_040F65
040F5A: DD2794        ld        hl, (ix + -6C)
040F5D: 09            add       hl, bc
040F5E: B7            or        a
040F5F: ED42          sbc       hl, bc
040F61: CA361604      jp        z, label_041636
                    label_040F65:
040F65: DD2790        ld        hl, (ix + -70)
040F68: DD2FBE        ld        (ix + -42), hl
040F6B: DD1789        ld        de, (ix + -77)
040F6E: DD1FB5        ld        (ix + -4B), de
040F71: DD0783        ld        bc, (ix + -7D)
040F74: 69            ld        l, c
040F75: 60            ld        h, b
040F76: DD2FB2        ld        (ix + -4E), hl
040F79: B7            or        a
040F7A: ED62          sbc       hl, hl
040F7C: DD2FC1        ld        (ix + -3F), hl
                    label_040F7F:
040F7F: DD2790        ld        hl, (ix + -70)
040F82: CD8D0204      call      label_04028D
040F86: 3E01          ld        a, 01
040F88: FA8E0F04      jp        m, label_040F8E
040F8C: 3E00          ld        a, 00
                    label_040F8E:
040F8E: DD27AF        ld        hl, (ix + -51)
040F91: DD17C1        ld        de, (ix + -3F)
040F94: 19            add       hl, de
040F95: 0174FFFF      ld        bc, FFFF74
040F99: ED5500        lea       iy, ix + 00
040F9C: FD09          add       iy, bc
040F9E: FD2F00        ld        (iy + 00), hl
040FA1: B7            or        a
040FA2: ED62          sbc       hl, hl
040FA4: E5            push      hl
040FA5: FD21000000    ld        iy, 000000
040FAA: FDE5          push      iy
040FAC: 210A0000      ld        hl, 00000A
040FB0: E5            push      hl
040FB1: DD27BE        ld        hl, (ix + -42)
040FB4: DD17B5        ld        de, (ix + -4B)
040FB7: DD07B2        ld        bc, (ix + -4E)
040FBA: CDBA0204      call      label_0402BA
040FBE: E5            push      hl
040FBF: FDE1          pop       iy
040FC1: E1            pop       hl
040FC2: E1            pop       hl
040FC3: E1            pop       hl
040FC4: B7            or        a
040FC5: ED62          sbc       hl, hl
040FC7: E5            push      hl
040FC8: E5            push      hl
040FC9: 210A0000      ld        hl, 00000A
040FCD: E5            push      hl
040FCE: DD0FFD        ld        (ix + -03), bc
040FD1: 017DFFFF      ld        bc, FFFF7D
040FD5: ED2200        lea       hl, IX + 00
040FD8: 09            add       hl, bc
040FD9: ED3E          ld        (hl), iy
040FDB: ED2300        lea       hl, IY + 00
040FDE: 017AFFFF      ld        bc, FFFF7A
040FE2: ED5500        lea       iy, ix + 00
040FE5: FD09          add       iy, bc
040FE7: FD1F00        ld        (iy + 00), de
040FEA: DD07FD        ld        bc, (ix + -03)
040FED: DD1FFD        ld        (ix + -03), de
040FF0: DDE5          push      ix
040FF2: 1177FFFF      ld        de, FFFF77
040FF6: DD19          add       ix, de
040FF8: DD0F00        ld        (ix + 00), bc
040FFB: DDE1          pop       ix
040FFD: DD17FD        ld        de, (ix + -03)
041000: CD7C0304      call      label_04037C
041004: FDE1          pop       iy
041006: FDE1          pop       iy
041008: FDE1          pop       iy
04100A: C5            push      bc
04100B: D5            push      de
04100C: E5            push      hl
04100D: DD27BE        ld        hl, (ix + -42)
041010: DD17B5        ld        de, (ix + -4B)
041013: DD07B2        ld        bc, (ix + -4E)
041016: CD550404      call      label_040455
04101A: E5            push      hl
04101B: FDE1          pop       iy
04101D: E1            pop       hl
04101E: E1            pop       hl
04101F: E1            pop       hl
041020: ED2300        lea       hl, IY + 00
041023: CDD10304      call      label_0403D1
041027: CB47          bit       0, a
041029: 2003          jr        nz, label_04102E
04102B: ED2300        lea       hl, IY + 00
                    label_04102E:
04102E: 7D            ld        a, l
04102F: C630          add       a, 30
041031: 0174FFFF      ld        bc, FFFF74
041035: ED2200        lea       hl, IX + 00
041038: 09            add       hl, bc
041039: ED27          ld        hl, (hl)
04103B: 77            ld        (hl), a
04103C: DD27C1        ld        hl, (ix + -3F)
04103F: 23            inc       hl
041040: DD2FC1        ld        (ix + -3F), hl
041043: B7            or        a
041044: ED62          sbc       hl, hl
041046: E5            push      hl
041047: E5            push      hl
041048: 21090000      ld        hl, 000009
04104C: E5            push      hl
04104D: DD27BE        ld        hl, (ix + -42)
041050: DD17B5        ld        de, (ix + -4B)
041053: DD07B2        ld        bc, (ix + -4E)
041056: CD020204      call      label_040202
04105A: FDE1          pop       iy
04105C: FDE1          pop       iy
04105E: FDE1          pop       iy
041060: FD21000000    ld        iy, 000000
041065: FDE5          push      iy
041067: FDE5          push      iy
041069: FD21130000    ld        iy, 000013
04106E: FDE5          push      iy
041070: CD630204      call      label_040263
041074: E1            pop       hl
041075: E1            pop       hl
041076: E1            pop       hl
041077: 3F            ccf
041078: 9F            sbc       a, a
041079: 3C            inc       a
04107A: CB47          bit       0, a
04107C: DD0FFD        ld        (ix + -03), bc
04107F: 017DFFFF      ld        bc, FFFF7D
041083: ED2200        lea       hl, IX + 00
041086: F5            push      af
041087: 09            add       hl, bc
041088: F1            pop       af
041089: ED27          ld        hl, (hl)
04108B: DD2FBE        ld        (ix + -42), hl
04108E: 017AFFFF      ld        bc, FFFF7A
041092: ED2200        lea       hl, IX + 00
041095: F5            push      af
041096: 09            add       hl, bc
041097: F1            pop       af
041098: ED27          ld        hl, (hl)
04109A: DD2FB5        ld        (ix + -4B), hl
04109D: 0177FFFF      ld        bc, FFFF77
0410A1: ED2200        lea       hl, IX + 00
0410A4: F5            push      af
0410A5: 09            add       hl, bc
0410A6: F1            pop       af
0410A7: ED27          ld        hl, (hl)
0410A9: DD2FB2        ld        (ix + -4E), hl
0410AC: DD1789        ld        de, (ix + -77)
0410AF: DD07FD        ld        bc, (ix + -03)
0410B2: DD0783        ld        bc, (ix + -7D)
0410B5: CA7F0F04      jp        z, label_040F7F
0410B9: FD21000000    ld        iy, 000000
0410BE: DD3E83        ld        (ix + -7D), iy
0410C1: DD3EBE        ld        (ix + -42), iy
0410C4: 2E00          ld        l, 00
                    label_0410C6:
0410C6: DD7589        ld        (ix + -77), l
0410C9: DD17AF        ld        de, (ix + -51)
                    label_0410CC:
0410CC: DD1F90        ld        (ix + -70), de
0410CF: C3261104      jp        label_041126
                    label_0410D3:
0410D3: DD7EAB        ld        a, (ix + -55)
0410D6: B7            or        a
0410D7: 2EFF          ld        l, FF
0410D9: 2002          jr        nz, label_0410DD
0410DB: 2E00          ld        l, 00
                    label_0410DD:
0410DD: DD7E83        ld        a, (ix + -7D)
0410E0: A5            and       l
0410E1: 6F            ld        l, a
0410E2: 01010000      ld        bc, 000001
0410E6: CDE50004      call      label_0400E5
0410EA: DD2F94        ld        (ix + -6C), hl
0410ED: B7            or        a
0410EE: ED62          sbc       hl, hl
0410F0: DD2FC1        ld        (ix + -3F), hl
0410F3: DD31B5        ld        iy, (ix + -4B)
0410F6: DD17BE        ld        de, (ix + -42)
0410F9: DD07B2        ld        bc, (ix + -4E)
                    label_0410FC:
0410FC: ED2300        lea       hl, IY + 00
0410FF: CD8D0204      call      label_04028D
041103: C2AD1504      jp        nz, label_0415AD
041107: FD21000000    ld        iy, 000000
04110C: DD3E83        ld        (ix + -7D), iy
04110F: FD            NONI
041110: 54            ld        d, h
041111: DD728F        ld        (ix + -71), d
041114: DD3EBE        ld        (ix + -42), iy
041117: 3E01          ld        a, 01
041119: DD7780        ld        (ix + -80), a
04111C: 6A            ld        l, d
                    label_04111D:
04111D: DD7589        ld        (ix + -77), l
041120: DD07AF        ld        bc, (ix + -51)
041123: DD0F90        ld        (ix + -70), bc
                    label_041126:
041126: DD0797        ld        bc, (ix + -69)
                    label_041129:
041129: 79            ld        a, c
04112A: FE01          cp        01
04112C: 1E01          ld        e, 01
04112E: DD73B2        ld        (ix + -4E), e
041131: 4D            ld        c, l
041132: 2057          jr        nz, label_04118B
041134: DDCB8E46      bit       0, (ix + -72)
041138: DD75B2        ld        (ix + -4E), l
04113B: 4D            ld        c, l
04113C: 1E01          ld        e, 01
04113E: FD21200000    ld        iy, 000020
041143: FD            NONI
041144: 7C            ld        a, h
041145: 2844          jr        z, label_04118B
041147: DDCB8646      bit       0, (ix + -7A)
04114B: 1E01          ld        e, 01
04114D: DD73B2        ld        (ix + -4E), e
041150: 4F            ld        c, a
041151: FD21000000    ld        iy, 000000
041156: 2833          jr        z, label_04118B
041158: DD27AC        ld        hl, (ix + -54)
04115B: 7D            ld        a, l
04115C: FE01          cp        01
04115E: 3EFF          ld        a, FF
041160: 2802          jr        z, label_041164
041162: 3E00          ld        a, 00
                    label_041164:
041164: DD2794        ld        hl, (ix + -6C)
041167: 09            add       hl, bc
041168: B7            or        a
041169: ED42          sbc       hl, bc
04116B: 2EFF          ld        l, FF
04116D: 2802          jr        z, label_041171
04116F: 2E00          ld        l, 00
                    label_041171:
041171: A5            and       l
041172: DDA680        and       (ix + -80)
041175: 5F            ld        e, a
041176: EE01          xor       01
041178: 4F            ld        c, a
041179: CB43          bit       0, e
04117B: FD21200000    ld        iy, 000020
041180: 2005          jr        nz, label_041187
041182: FD21300000    ld        iy, 000030
                    label_041187:
041187: AF            xor       a
041188: DD77B2        ld        (ix + -4E), a
                    label_04118B:
04118B: DD7186        ld        (ix + -7A), c
04118E: DD738E        ld        (ix + -72), e
041191: DD7E9A        ld        a, (ix + -66)
041194: DDB689        or        (ix + -77)
041197: DDCB9346      bit       0, (ix + -6D)
04119B: DD1783        ld        de, (ix + -7D)
04119E: 2003          jr        nz, label_0411A3
0411A0: DD17C1        ld        de, (ix + -3F)
                    label_0411A3:
0411A3: DD2794        ld        hl, (ix + -6C)
0411A6: B7            or        a
0411A7: ED52          sbc       hl, de
0411A9: E5            push      hl
0411AA: C1            pop       bc
0411AB: 11010000      ld        de, 000001
0411AF: B7            or        a
0411B0: ED52          sbc       hl, de
0411B2: EC180200      call      pe, __setflag(OS)
0411B6: F2BE1104      jp        p, label_0411BE
0411BA: 01000000      ld        bc, 000000
                    label_0411BE:
0411BE: CB47          bit       0, a
0411C0: 21000000      ld        hl, 000000
0411C4: DD5EAB        ld        e, (ix + -55)
0411C7: DD56AA        ld        d, (ix + -56)
0411CA: 2002          jr        nz, label_0411CE
0411CC: C5            push      bc
0411CD: E1            pop       hl
                    label_0411CE:
0411CE: DD2FB5        ld        (ix + -4B), hl
0411D1: DD3E97        ld        (ix + -69), iy
0411D4: DD27B8        ld        hl, (ix + -48)
0411D7: DD07C1        ld        bc, (ix + -3F)
0411DA: B7            or        a
0411DB: ED42          sbc       hl, bc
0411DD: DD7E8F        ld        a, (ix + -71)
0411E0: B7            or        a
0411E1: 01FFFFFF      ld        bc, FFFFFF
0411E5: 2004          jr        nz, label_0411EB
0411E7: 01000000      ld        bc, 000000
                    label_0411EB:
0411EB: 09            add       hl, bc
0411EC: E5            push      hl
0411ED: FDE1          pop       iy
0411EF: 01FEFFFF      ld        bc, FFFFFE
0411F3: FD09          add       iy, bc
0411F5: DD07BE        ld        bc, (ix + -42)
0411F8: 79            ld        a, c
0411F9: B7            or        a
0411FA: 2003          jr        nz, label_0411FF
0411FC: E5            push      hl
0411FD: FDE1          pop       iy
                    label_0411FF:
0411FF: DD2794        ld        hl, (ix + -6C)
041202: 09            add       hl, bc
041203: B7            or        a
041204: ED42          sbc       hl, bc
041206: 2EFF          ld        l, FF
041208: 2002          jr        nz, label_04120C
04120A: 2E00          ld        l, 00
                    label_04120C:
04120C: DD72AA        ld        (ix + -56), d
04120F: 7A            ld        a, d
041210: B5            or        l
041211: 6F            ld        l, a
041212: 7B            ld        a, e
041213: B7            or        a
041214: 0EFF          ld        c, FF
041216: 2002          jr        nz, label_04121A
041218: 0E00          ld        c, 00
                    label_04121A:
04121A: 7D            ld        a, l
04121B: B1            or        c
04121C: EE01          xor       01
04121E: 6F            ld        l, a
04121F: 01010000      ld        bc, 000001
041223: CDE50004      call      label_0400E5
041227: E5            push      hl
041228: C1            pop       bc
041229: FD09          add       iy, bc
04122B: ED2300        lea       hl, IY + 00
04122E: DD07B5        ld        bc, (ix + -4B)
041231: B7            or        a
041232: ED42          sbc       hl, bc
041234: E5            push      hl
041235: C1            pop       bc
041236: 11010000      ld        de, 000001
04123A: B7            or        a
04123B: ED52          sbc       hl, de
04123D: EC180200      call      pe, __setflag(OS)
041241: F2491204      jp        p, label_041249
041245: 01000000      ld        bc, 000000
                    label_041249:
041249: DD0FAC        ld        (ix + -54), bc
04124C: DDCBB246      bit       0, (ix + -4E)
041250: DD31C4        ld        iy, (ix + -3C)
041253: DD17C1        ld        de, (ix + -3F)
041256: 0600          ld        b, 00
041258: 2006          jr        nz, label_041260
04125A: DD7E8D        ld        a, (ix + -73)
04125D: B7            or        a
04125E: 2847          jr        z, label_0412A7
                    label_041260:
041260: DD27BE        ld        hl, (ix + -42)
041263: 7D            ld        a, l
041264: B7            or        a
041265: CA751304      jp        z, label_041375
                    label_041269:
041269: DD2FBE        ld        (ix + -42), hl
04126C: DD2709        ld        hl, (ix + 09)
04126F: E5            push      hl
041270: 21300000      ld        hl, 000030
041274: E5            push      hl
041275: DD2706        ld        hl, (ix + 06)
041278: CD2E0104      call      __indcallhl
04127C: E1            pop       hl
04127D: E1            pop       hl
04127E: 11020000      ld        de, 000002
041282: DD27C7        ld        hl, (ix + -39)
041285: 19            add       hl, de
041286: DD2FC7        ld        (ix + -39), hl
041289: DD2709        ld        hl, (ix + 09)
04128C: E5            push      hl
04128D: DD27BE        ld        hl, (ix + -42)
041290: E5            push      hl
041291: DD2706        ld        hl, (ix + 06)
041294: CD2E0104      call      __indcallhl
041298: 1600          ld        d, 00
04129A: 42            ld        b, d
04129B: DD17C1        ld        de, (ix + -3F)
04129E: DD31C4        ld        iy, (ix + -3C)
0412A1: E1            pop       hl
0412A2: E1            pop       hl
0412A3: C3751304      jp        label_041375
                    label_0412A7:
0412A7: DDCB8646      bit       0, (ix + -7A)
0412AB: 2864          jr        z, label_041311
0412AD: DD5E8F        ld        e, (ix + -71)
0412B0: 7B            ld        a, e
0412B1: B7            or        a
0412B2: 2819          jr        z, label_0412CD
0412B4: B7            or        a
0412B5: ED62          sbc       hl, hl
0412B7: 6B            ld        l, e
0412B8: DD17C7        ld        de, (ix + -39)
0412BB: 13            inc       de
0412BC: DD1FC7        ld        (ix + -39), de
0412BF: DD1709        ld        de, (ix + 09)
0412C2: D5            push      de
0412C3: E5            push      hl
0412C4: DD2706        ld        hl, (ix + 06)
0412C7: CD2E0104      call      __indcallhl
0412CB: E1            pop       hl
0412CC: E1            pop       hl
                    label_0412CD:
0412CD: DD27BE        ld        hl, (ix + -42)
0412D0: 7D            ld        a, l
0412D1: B7            or        a
0412D2: 2831          jr        z, label_041305
0412D4: DD2FBE        ld        (ix + -42), hl
0412D7: DD2709        ld        hl, (ix + 09)
0412DA: E5            push      hl
0412DB: 21300000      ld        hl, 000030
0412DF: E5            push      hl
0412E0: DD2706        ld        hl, (ix + 06)
0412E3: CD2E0104      call      __indcallhl
0412E7: E1            pop       hl
0412E8: E1            pop       hl
0412E9: 11020000      ld        de, 000002
0412ED: DD27C7        ld        hl, (ix + -39)
0412F0: 19            add       hl, de
0412F1: DD2FC7        ld        (ix + -39), hl
0412F4: DD2709        ld        hl, (ix + 09)
0412F7: E5            push      hl
0412F8: DD27BE        ld        hl, (ix + -42)
0412FB: E5            push      hl
0412FC: DD2706        ld        hl, (ix + 06)
0412FF: CD2E0104      call      __indcallhl
041303: E1            pop       hl
041304: E1            pop       hl
                    label_041305:
041305: 1600          ld        d, 00
041307: 42            ld        b, d
041308: DD708F        ld        (ix + -71), b
04130B: DD31C4        ld        iy, (ix + -3C)
04130E: DD17C1        ld        de, (ix + -3F)
                    label_041311:
041311: DD27AC        ld        hl, (ix + -54)
041314: DD2F86        ld        (ix + -7A), hl
                    label_041317:
041317: DD2786        ld        hl, (ix + -7A)
04131A: 09            add       hl, bc
04131B: B7            or        a
04131C: ED42          sbc       hl, bc
04131E: 2823          jr        z, label_041343
041320: DD2786        ld        hl, (ix + -7A)
041323: 2B            dec       hl
041324: DD2F86        ld        (ix + -7A), hl
041327: DD2709        ld        hl, (ix + 09)
04132A: E5            push      hl
04132B: DD2797        ld        hl, (ix + -69)
04132E: E5            push      hl
04132F: DD2706        ld        hl, (ix + 06)
041332: CD2E0104      call      __indcallhl
041336: 1600          ld        d, 00
041338: 42            ld        b, d
041339: DD17C1        ld        de, (ix + -3F)
04133C: DD31C4        ld        iy, (ix + -3C)
04133F: E1            pop       hl
041340: E1            pop       hl
041341: 18D4          jr        label_041317
                    label_041343:
041343: DD1FC1        ld        (ix + -3F), de
041346: DD27C7        ld        hl, (ix + -39)
041349: DD17AC        ld        de, (ix + -54)
04134C: 19            add       hl, de
04134D: DD2FC7        ld        (ix + -39), hl
041350: DDCB8E46      bit       0, (ix + -72)
041354: 2816          jr        z, label_04136C
041356: DD17BE        ld        de, (ix + -42)
041359: 7B            ld        a, e
04135A: B7            or        a
04135B: 21FFFFFF      ld        hl, FFFFFF
04135F: DD2FAC        ld        (ix + -54), hl
041362: EB            ex        de, hl
041363: DD17C1        ld        de, (ix + -3F)
041366: C2691204      jp        nz, label_041269
04136A: 1809          jr        label_041375
                    label_04136C:
04136C: 37            scf
04136D: ED62          sbc       hl, hl
04136F: DD2FAC        ld        (ix + -54), hl
041372: DD17C1        ld        de, (ix + -3F)
                    label_041375:
041375: DDCB9A46      bit       0, (ix + -66)
041379: 2854          jr        z, label_0413CF
04137B: EB            ex        de, hl
04137C: 11010000      ld        de, 000001
041380: B7            or        a
041381: ED52          sbc       hl, de
041383: DD17C1        ld        de, (ix + -3F)
041386: EC180200      call      pe, __setflag(OS)
04138A: F2921304      jp        p, label_041392
04138E: B7            or        a
04138F: ED62          sbc       hl, hl
041391: EB            ex        de, hl
                    label_041392:
041392: D5            push      de
041393: C1            pop       bc
                    label_041394:
041394: C5            push      bc
041395: E1            pop       hl
041396: 09            add       hl, bc
041397: B7            or        a
041398: ED42          sbc       hl, bc
04139A: CA211404      jp        z, label_041421
04139E: DD2790        ld        hl, (ix + -70)
0413A1: 7E            ld        a, (hl)
0413A2: 6F            ld        l, a
0413A3: CB05          rlc       l
0413A5: ED62          sbc       hl, hl
0413A7: 6F            ld        l, a
0413A8: DD1FC1        ld        (ix + -3F), de
0413AB: DD1709        ld        de, (ix + 09)
0413AE: D5            push      de
0413AF: E5            push      hl
0413B0: DD2706        ld        hl, (ix + 06)
0413B3: DD0FBE        ld        (ix + -42), bc
0413B6: CD2E0104      call      __indcallhl
0413BA: DD07BE        ld        bc, (ix + -42)
0413BD: DD17C1        ld        de, (ix + -3F)
0413C0: DD31C4        ld        iy, (ix + -3C)
0413C3: E1            pop       hl
0413C4: E1            pop       hl
0413C5: 0B            dec       bc
0413C6: DD2790        ld        hl, (ix + -70)
0413C9: 23            inc       hl
0413CA: DD2F90        ld        (ix + -70), hl
0413CD: 18C5          jr        label_041394
                    label_0413CF:
0413CF: DD5E8F        ld        e, (ix + -71)
0413D2: 7B            ld        a, e
0413D3: B7            or        a
0413D4: 281C          jr        z, label_0413F2
0413D6: B7            or        a
0413D7: ED62          sbc       hl, hl
0413D9: 6B            ld        l, e
0413DA: DD17C7        ld        de, (ix + -39)
0413DD: 13            inc       de
0413DE: DD1FC7        ld        (ix + -39), de
0413E1: DD1709        ld        de, (ix + 09)
0413E4: D5            push      de
0413E5: E5            push      hl
0413E6: DD2706        ld        hl, (ix + 06)
0413E9: CD2E0104      call      __indcallhl
0413ED: 1600          ld        d, 00
0413EF: 42            ld        b, d
0413F0: E1            pop       hl
0413F1: E1            pop       hl
                    label_0413F2:
0413F2: DD27C7        ld        hl, (ix + -39)
0413F5: DD2FBE        ld        (ix + -42), hl
0413F8: DD7EAB        ld        a, (ix + -55)
0413FB: DD31B5        ld        iy, (ix + -4B)
0413FE: DDCB9346      bit       0, (ix + -6D)
041402: 282B          jr        z, label_04142F
041404: DD2794        ld        hl, (ix + -6C)
041407: 09            add       hl, bc
041408: B7            or        a
041409: ED42          sbc       hl, bc
04140B: DD6E8C        ld        l, (ix + -74)
04140E: DD31C1        ld        iy, (ix + -3F)
041411: 2063          jr        nz, label_041476
041413: B7            or        a
041414: 2060          jr        nz, label_041476
041416: DD1790        ld        de, (ix + -70)
041419: 13            inc       de
04141A: DD1F90        ld        (ix + -70), de
04141D: FD2B          dec       iy
04141F: 1855          jr        label_041476
                    label_041421:
041421: DD27C7        ld        hl, (ix + -39)
041424: 19            add       hl, de
041425: DD2FC7        ld        (ix + -39), hl
                    label_041428:
041428: 1600          ld        d, 00
04142A: 42            ld        b, d
04142B: C32F1504      jp        label_04152F
                    label_04142F:
04142F: ED2300        lea       hl, IY + 00
041432: 11010000      ld        de, 000001
041436: B7            or        a
041437: ED52          sbc       hl, de
041439: EC180200      call      pe, __setflag(OS)
04143D: FA601404      jp        m, label_041460
041441: FD2B          dec       iy
041443: DD3EC7        ld        (ix + -39), iy
041446: DD2709        ld        hl, (ix + 09)
041449: E5            push      hl
04144A: 21300000      ld        hl, 000030
04144E: E5            push      hl
04144F: DD2706        ld        hl, (ix + 06)
041452: CD2E0104      call      __indcallhl
041456: DD31C7        ld        iy, (ix + -39)
041459: 1600          ld        d, 00
04145B: 42            ld        b, d
04145C: E1            pop       hl
04145D: E1            pop       hl
04145E: 18CF          jr        label_04142F
                    label_041460:
041460: DD27B5        ld        hl, (ix + -4B)
041463: DD17BE        ld        de, (ix + -42)
041466: 19            add       hl, de
041467: DD2FBE        ld        (ix + -42), hl
04146A: DD31C1        ld        iy, (ix + -3F)
04146D: 37            scf
04146E: ED62          sbc       hl, hl
041470: DD2FB5        ld        (ix + -4B), hl
041473: DD6E8C        ld        l, (ix + -74)
                    label_041476:
041476: CB45          bit       0, l
041478: CAC91404      jp        z, label_0414C9
04147C: DD3EC7        ld        (ix + -39), iy
04147F: ED2300        lea       hl, IY + 00
                    label_041482:
041482: 2B            dec       hl
041483: E5            push      hl
041484: FDE1          pop       iy
041486: 11FFFFFF      ld        de, FFFFFF
04148A: B7            or        a
04148B: ED52          sbc       hl, de
04148D: CA0D1504      jp        z, label_04150D
041491: DD27CA        ld        hl, (ix + -36)
041494: DD17CD        ld        de, (ix + -33)
041497: DD07D0        ld        bc, (ix + -30)
04149A: DD3EC1        ld        (ix + -3F), iy
04149D: FDE5          push      iy
04149F: CD3B0404      call      label_04043B
0414A3: D1            pop       de
0414A4: 01010000      ld        bc, 000001
0414A8: CDE50004      call      label_0400E5
0414AC: 11300000      ld        de, 000030
0414B0: 19            add       hl, de
0414B1: DD1709        ld        de, (ix + 09)
0414B4: D5            push      de
0414B5: E5            push      hl
0414B6: DD2706        ld        hl, (ix + 06)
0414B9: CD2E0104      call      __indcallhl
0414BD: 1600          ld        d, 00
0414BF: 42            ld        b, d
0414C0: E1            pop       hl
0414C1: E1            pop       hl
0414C2: DD27C1        ld        hl, (ix + -3F)
0414C5: C3821404      jp        label_041482
                    label_0414C9:
0414C9: DD3EC7        ld        (ix + -39), iy
                    label_0414CC:
0414CC: DD27C7        ld        hl, (ix + -39)
0414CF: 11010000      ld        de, 000001
0414D3: B7            or        a
0414D4: ED52          sbc       hl, de
0414D6: EC180200      call      pe, __setflag(OS)
0414DA: DD3190        ld        iy, (ix + -70)
0414DD: FA161504      jp        m, label_041516
0414E1: DD17C7        ld        de, (ix + -39)
0414E4: FD19          add       iy, de
0414E6: 1B            dec       de
0414E7: DD1FC7        ld        (ix + -39), de
0414EA: FD7EFF        ld        a, (iy + -01)
0414ED: 6F            ld        l, a
0414EE: CB05          rlc       l
0414F0: ED62          sbc       hl, hl
0414F2: 6F            ld        l, a
0414F3: DD17BE        ld        de, (ix + -42)
0414F6: 13            inc       de
0414F7: DD1FBE        ld        (ix + -42), de
0414FA: DD1709        ld        de, (ix + 09)
0414FD: D5            push      de
0414FE: E5            push      hl
0414FF: DD2706        ld        hl, (ix + 06)
041502: CD2E0104      call      __indcallhl
041506: 1600          ld        d, 00
041508: 42            ld        b, d
041509: E1            pop       hl
04150A: E1            pop       hl
04150B: 18BF          jr        label_0414CC
                    label_04150D:
04150D: DD17BE        ld        de, (ix + -42)
041510: DD27C7        ld        hl, (ix + -39)
041513: 19            add       hl, de
041514: 1803          jr        label_041519
                    label_041516:
041516: DD27BE        ld        hl, (ix + -42)
                    label_041519:
041519: DD2FC7        ld        (ix + -39), hl
04151C: DD31C4        ld        iy, (ix + -3C)
04151F: DDCBAA46      bit       0, (ix + -56)
041523: DD7E89        ld        a, (ix + -77)
041526: DD27B5        ld        hl, (ix + -4B)
041529: 2004          jr        nz, label_04152F
04152B: CB47          bit       0, a
04152D: 2848          jr        z, label_041577
                    label_04152F:
04152F: DD7E8D        ld        a, (ix + -73)
041532: B7            or        a
041533: CADD0404      jp        z, label_0404DD
041537: DDCBB246      bit       0, (ix + -4E)
04153B: C2DD0404      jp        nz, label_0404DD
04153F: DD07AC        ld        bc, (ix + -54)
                    label_041542:
041542: C5            push      bc
041543: E1            pop       hl
041544: 11010000      ld        de, 000001
041548: B7            or        a
041549: ED52          sbc       hl, de
04154B: EC180200      call      pe, __setflag(OS)
04154F: FA9C0904      jp        m, label_04099C
041553: 0B            dec       bc
041554: DD0FAC        ld        (ix + -54), bc
041557: DD27C7        ld        hl, (ix + -39)
04155A: 23            inc       hl
04155B: DD2FC7        ld        (ix + -39), hl
04155E: DD2709        ld        hl, (ix + 09)
041561: E5            push      hl
041562: DD2797        ld        hl, (ix + -69)
041565: E5            push      hl
041566: DD2706        ld        hl, (ix + 06)
041569: CD2E0104      call      __indcallhl
04156D: DD07AC        ld        bc, (ix + -54)
041570: DD31C4        ld        iy, (ix + -3C)
041573: E1            pop       hl
041574: E1            pop       hl
041575: 18CB          jr        label_041542
                    label_041577:
041577: E5            push      hl
041578: C1            pop       bc
041579: 11010000      ld        de, 000001
04157D: B7            or        a
04157E: ED52          sbc       hl, de
041580: EC180200      call      pe, __setflag(OS)
041584: FA281404      jp        m, label_041428
041588: 0B            dec       bc
041589: DD0FB5        ld        (ix + -4B), bc
04158C: DD27C7        ld        hl, (ix + -39)
04158F: 23            inc       hl
041590: DD2FC7        ld        (ix + -39), hl
041593: DD2709        ld        hl, (ix + 09)
041596: E5            push      hl
041597: 21300000      ld        hl, 000030
04159B: E5            push      hl
04159C: DD2706        ld        hl, (ix + 06)
04159F: CD2E0104      call      __indcallhl
0415A3: DD31C4        ld        iy, (ix + -3C)
0415A6: E1            pop       hl
0415A7: E1            pop       hl
0415A8: DD27B5        ld        hl, (ix + -4B)
0415AB: 18CA          jr        label_041577
                    label_0415AD:
0415AD: DD7EAB        ld        a, (ix + -55)
0415B0: B7            or        a
0415B1: 2E00          ld        l, 00
0415B3: 281B          jr        z, label_0415D0
0415B5: DDCB8346      bit       0, (ix + -7D)
0415B9: 2815          jr        z, label_0415D0
0415BB: DD27AF        ld        hl, (ix + -51)
0415BE: DD17C1        ld        de, (ix + -3F)
0415C1: 19            add       hl, de
0415C2: 13            inc       de
0415C3: DD1FC1        ld        (ix + -3F), de
0415C6: 3630          ld        (hl), 30
0415C8: DD0797        ld        bc, (ix + -69)
0415CB: DD5E86        ld        e, (ix + -7A)
0415CE: 1830          jr        label_041600
                    label_0415D0:
0415D0: DD7EAB        ld        a, (ix + -55)
0415D3: B7            or        a
0415D4: DD0797        ld        bc, (ix + -69)
0415D7: DD5E86        ld        e, (ix + -7A)
0415DA: 2024          jr        nz, label_041600
0415DC: DD7386        ld        (ix + -7A), e
0415DF: 11000000      ld        de, 000000
0415E3: DD1F83        ld        (ix + -7D), de
0415E6: AF            xor       a
0415E7: DD778F        ld        (ix + -71), a
0415EA: DD1FBE        ld        (ix + -42), de
0415ED: DD7580        ld        (ix + -80), l
0415F0: DD7589        ld        (ix + -77), l
0415F3: DD31AF        ld        iy, (ix + -51)
0415F6: DD3E90        ld        (ix + -70), iy
0415F9: D5            push      de
0415FA: FDE1          pop       iy
0415FC: C3291104      jp        label_041129
                    label_041600:
041600: DD2790        ld        hl, (ix + -70)
041603: 7D            ld        a, l
041604: FE04          cp        04
041606: DD7386        ld        (ix + -7A), e
041609: 2006          jr        nz, label_041611
04160B: 21420000      ld        hl, 000042
04160F: 180B          jr        label_04161C
                    label_041611:
041611: 7D            ld        a, l
041612: FE06          cp        06
041614: 21580000      ld        hl, 000058
041618: C26B1704      jp        nz, label_04176B
                    label_04161C:
04161C: 11000000      ld        de, 000000
041620: DD5E89        ld        e, (ix + -77)
041623: 19            add       hl, de
041624: DD2FBE        ld        (ix + -42), hl
041627: FD21000000    ld        iy, 000000
04162C: DD3E83        ld        (ix + -7D), iy
04162F: DD728F        ld        (ix + -71), d
041632: C3F20A04      jp        label_040AF2
                    label_041636:
041636: FD21000000    ld        iy, 000000
04163B: DD3E94        ld        (ix + -6C), iy
04163E: DD3E83        ld        (ix + -7D), iy
041641: DD3EC1        ld        (ix + -3F), iy
041644: DD3EBE        ld        (ix + -42), iy
041647: 2E00          ld        l, 00
041649: DD7589        ld        (ix + -77), l
04164C: C3CC1004      jp        label_0410CC
                    label_041650:
041650: 79            ld        a, c
041651: FE96          cp        96
041653: C27B1704      jp        nz, label_04177B
041657: 7B            ld        a, e
041658: 11000000      ld        de, 000000
04165C: 5F            ld        e, a
04165D: DD1FB2        ld        (ix + -4E), de
041660: 1174FFFF      ld        de, FFFF74
041664: ED5500        lea       iy, ix + 00
041667: FD19          add       iy, de
041669: FD2F00        ld        (iy + 00), hl
04166C: 40210000      ld.sis    hl, 0000
041670: 4D            ld        c, l
041671: 44            ld        b, h
041672: DD0FC1        ld        (ix + -3F), bc
041675: 11000000      ld        de, 000000
041679: D5            push      de
04167A: FDE1          pop       iy
04167C: DD1FBE        ld        (ix + -42), de
04167F: DD27C1        ld        hl, (ix + -3F)
041682: C3411804      jp        label_041841
041686: AF            xor       a
041687: DD779A        ld        (ix + -66), a
04168A: DD7793        ld        (ix + -6D), a
04168D: 2E01          ld        l, 01
04168F: DD75AA        ld        (ix + -56), l
041692: DD778C        ld        (ix + -74), a
041695: DD7586        ld        (ix + -7A), l
041698: DD7783        ld        (ix + -7D), a
04169B: 210A0000      ld        hl, 00000A
04169F: DD2F80        ld        (ix + -80), hl
0416A2: 21030000      ld        hl, 000003
0416A6: C35F1704      jp        label_04175F
0416AA: B7            or        a
0416AB: ED62          sbc       hl, hl
0416AD: DD2FAC        ld        (ix + -54), hl
0416B0: AF            xor       a
0416B1: DD779A        ld        (ix + -66), a
0416B4: DD7793        ld        (ix + -6D), a
0416B7: 2C            inc       l
0416B8: DD75AA        ld        (ix + -56), l
0416BB: DD778C        ld        (ix + -74), a
0416BE: DD7586        ld        (ix + -7A), l
0416C1: DD7783        ld        (ix + -7D), a
0416C4: 210A0000      ld        hl, 00000A
0416C8: DD2F80        ld        (ix + -80), hl
0416CB: 2B            dec       hl
0416CC: C35F1704      jp        label_04175F
0416D0: AF            xor       a
0416D1: DD779A        ld        (ix + -66), a
0416D4: DD7793        ld        (ix + -6D), a
0416D7: 2E01          ld        l, 01
0416D9: DD75AA        ld        (ix + -56), l
0416DC: DD778C        ld        (ix + -74), a
0416DF: DD7586        ld        (ix + -7A), l
0416E2: DD7583        ld        (ix + -7D), l
0416E5: 210A0000      ld        hl, 00000A
0416E9: DD2F80        ld        (ix + -80), hl
0416EC: 21050000      ld        hl, 000005
0416F0: 186D          jr        label_04175F
0416F2: B7            or        a
0416F3: ED62          sbc       hl, hl
0416F5: DD2FAC        ld        (ix + -54), hl
0416F8: AF            xor       a
0416F9: DD779A        ld        (ix + -66), a
0416FC: DD7793        ld        (ix + -6D), a
0416FF: 2C            inc       l
041700: DD75AA        ld        (ix + -56), l
041703: DD778C        ld        (ix + -74), a
041706: DD7586        ld        (ix + -7A), l
041709: DD7783        ld        (ix + -7D), a
04170C: 210A0000      ld        hl, 00000A
041710: DD2F80        ld        (ix + -80), hl
041713: 21080000      ld        hl, 000008
041717: 1846          jr        label_04175F
041719: AF            xor       a
04171A: DD778E        ld        (ix + -72), a
04171D: 3C            inc       a
04171E: 6F            ld        l, a
04171F: DD759A        ld        (ix + -66), l
041722: 3D            dec       a
041723: DD7793        ld        (ix + -6D), a
041726: DD75AA        ld        (ix + -56), l
041729: DD778C        ld        (ix + -74), a
04172C: DD7786        ld        (ix + -7A), a
04172F: DD7783        ld        (ix + -7D), a
041732: 210A0000      ld        hl, 00000A
041736: DD2F80        ld        (ix + -80), hl
041739: 21020000      ld        hl, 000002
04173D: 1820          jr        label_04175F
04173F: AF            xor       a
041740: DD779A        ld        (ix + -66), a
041743: DD7793        ld        (ix + -6D), a
041746: 2E01          ld        l, 01
041748: DD75AA        ld        (ix + -56), l
04174B: DD778C        ld        (ix + -74), a
04174E: DD7586        ld        (ix + -7A), l
041751: DD7783        ld        (ix + -7D), a
041754: 210A0000      ld        hl, 00000A
041758: DD2F80        ld        (ix + -80), hl
04175B: 21070000      ld        hl, 000007
                    label_04175F:
04175F: DD2F90        ld        (ix + -70), hl
041762: 3E20          ld        a, 20
041764: DD7789        ld        (ix + -77), a
041767: C33C0804      jp        label_04083C
                    label_04176B:
04176B: FD21000000    ld        iy, 000000
041770: DD3E83        ld        (ix + -7D), iy
041773: AF            xor       a
041774: DD778F        ld        (ix + -71), a
041777: C3A90A04      jp        label_040AA9
                    label_04177B:
04177B: DD2FC1        ld        (ix + -3F), hl
04177E: 79            ld        a, c
04177F: FE7F          cp        7F
041781: 3036          jr        nc, label_0417B9
041783: ED2300        lea       hl, IY + 00
041786: 01C4FFFF      ld        bc, FFFFC4
04178A: B7            or        a
04178B: ED42          sbc       hl, bc
04178D: 01000000      ld        bc, 000000
041791: DD1FFD        ld        (ix + -03), de
041794: 1174FFFF      ld        de, FFFF74
041798: ED2200        lea       hl, IX + 00
04179B: F5            push      af
04179C: 19            add       hl, de
04179D: F1            pop       af
04179E: ED0F          ld        (hl), bc
0417A0: DD0FB2        ld        (ix + -4E), bc
0417A3: 40210000      ld.sis    hl, 0000
0417A7: C5            push      bc
0417A8: FDE1          pop       iy
0417AA: DD17FD        ld        de, (ix + -03)
0417AD: 7B            ld        a, e
0417AE: DD0FBE        ld        (ix + -42), bc
0417B1: C5            push      bc
0417B2: D1            pop       de
0417B3: 3030          jr        nc, label_0417E5
0417B5: C3411804      jp        label_041841
                    label_0417B9:
0417B9: 21960000      ld        hl, 000096
0417BD: DD07B5        ld        bc, (ix + -4B)
0417C0: B7            or        a
0417C1: ED42          sbc       hl, bc
0417C3: DD07C1        ld        bc, (ix + -3F)
0417C6: 7B            ld        a, e
0417C7: CD920404      call      label_040492
0417CB: DD1FFD        ld        (ix + -03), de
0417CE: 1174FFFF      ld        de, FFFF74
0417D2: ED5500        lea       iy, ix + 00
0417D5: FD19          add       iy, de
0417D7: FD0F00        ld        (iy + 00), bc
0417DA: B7            or        a
0417DB: ED62          sbc       hl, hl
0417DD: 6F            ld        l, a
0417DE: DD2FB2        ld        (ix + -4E), hl
0417E1: DD17FD        ld        de, (ix + -03)
0417E4: 7B            ld        a, e
                    label_0417E5:
0417E5: 01A6FFFF      ld        bc, FFFFA6
0417E9: DD27B5        ld        hl, (ix + -4B)
0417EC: 09            add       hl, bc
0417ED: 01000000      ld        bc, 000000
0417F1: 4F            ld        c, a
0417F2: E5            push      hl
0417F3: DD27C1        ld        hl, (ix + -3F)
0417F6: C5            push      bc
0417F7: D1            pop       de
0417F8: 40010000      ld.sis    bc, 0000
0417FC: CDEA0304      call      label_0403EA
041800: FDE1          pop       iy
041802: FD21FF0F00    ld        iy, 000FFF
041807: FDE5          push      iy
041809: FD21FFFFFF    ld        iy, FFFFFF
04180E: FDE5          push      iy
041810: FDE5          push      iy
041812: CD260204      call      label_040226
041816: FDE1          pop       iy
041818: FDE1          pop       iy
04181A: FDE1          pop       iy
04181C: FD21000000    ld        iy, 000000
041821: FDE5          push      iy
041823: FDE5          push      iy
041825: FD210A0000    ld        iy, 00000A
04182A: FDE5          push      iy
04182C: CD7C0304      call      label_04037C
041830: E5            push      hl
041831: FDE1          pop       iy
041833: DD1FBE        ld        (ix + -42), de
041836: E1            pop       hl
041837: E1            pop       hl
041838: E1            pop       hl
041839: 11000000      ld        de, 000000
04183D: 40210000      ld.sis    hl, 0000
                    label_041841:
041841: DD2FC1        ld        (ix + -3F), hl
041844: DD0FFD        ld        (ix + -03), bc
041847: 017AFFFF      ld        bc, FFFF7A
04184B: ED2200        lea       hl, IX + 00
04184E: 09            add       hl, bc
04184F: ED1F          ld        (hl), de
041851: DD17BE        ld        de, (ix + -42)
041854: DD07FD        ld        bc, (ix + -03)
                    label_041857:
041857: DD3E83        ld        (ix + -7D), iy
04185A: 37            scf
04185B: ED62          sbc       hl, hl
04185D: E5            push      hl
04185E: E5            push      hl
04185F: E5            push      hl
041860: ED2300        lea       hl, IY + 00
041863: DD1FBE        ld        (ix + -42), de
041866: DD0F90        ld        (ix + -70), bc
041869: CD020204      call      label_040202
04186D: FDE1          pop       iy
04186F: FDE1          pop       iy
041871: FDE1          pop       iy
041873: FD21FF0F00    ld        iy, 000FFF
041878: FDE5          push      iy
04187A: FD21FFFFFF    ld        iy, FFFFFF
04187F: FDE5          push      iy
041881: FDE5          push      iy
041883: CD630204      call      label_040263
041887: E1            pop       hl
041888: E1            pop       hl
041889: E1            pop       hl
04188A: 3032          jr        nc, label_0418BE
04188C: 017AFFFF      ld        bc, FFFF7A
041890: ED2200        lea       hl, IX + 00
041893: 09            add       hl, bc
041894: ED27          ld        hl, (hl)
041896: 23            inc       hl
041897: ED5500        lea       iy, ix + 00
04189A: FD09          add       iy, bc
04189C: FD2F00        ld        (iy + 00), hl
04189F: B7            or        a
0418A0: ED62          sbc       hl, hl
0418A2: E5            push      hl
0418A3: E5            push      hl
0418A4: 210A0000      ld        hl, 00000A
0418A8: E5            push      hl
0418A9: DD2783        ld        hl, (ix + -7D)
0418AC: DD17BE        ld        de, (ix + -42)
0418AF: DD0790        ld        bc, (ix + -70)
0418B2: CD7C0304      call      label_04037C
0418B6: E5            push      hl
0418B7: FDE1          pop       iy
0418B9: E1            pop       hl
0418BA: E1            pop       hl
0418BB: E1            pop       hl
0418BC: 1899          jr        label_041857
                    label_0418BE:
0418BE: FD21000000    ld        iy, 000000
0418C3: 0177FFFF      ld        bc, FFFF77
0418C7: ED2200        lea       hl, IX + 00
0418CA: 09            add       hl, bc
0418CB: ED3E          ld        (hl), iy
0418CD: DD3EB5        ld        (ix + -4B), iy
0418D0: 40210000      ld.sis    hl, 0000
0418D4: DD2F89        ld        (ix + -77), hl
0418D7: 017DFFFF      ld        bc, FFFF7D
0418DB: ED2200        lea       hl, IX + 00
0418DE: 09            add       hl, bc
0418DF: ED3E          ld        (hl), iy
0418E1: DD17BE        ld        de, (ix + -42)
0418E4: DD0790        ld        bc, (ix + -70)
                    label_0418E7:
0418E7: DD2783        ld        hl, (ix + -7D)
0418EA: DD1FBE        ld        (ix + -42), de
0418ED: DD0F90        ld        (ix + -70), bc
0418F0: CD8D0204      call      label_04028D
0418F4: CAF01904      jp        z, label_0419F0
0418F8: 017DFFFF      ld        bc, FFFF7D
0418FC: ED2200        lea       hl, IX + 00
0418FF: 09            add       hl, bc
041900: ED27          ld        hl, (hl)
041902: 11080000      ld        de, 000008
041906: B7            or        a
041907: ED52          sbc       hl, de
041909: D2F01904      jp        nc, label_0419F0
04190D: B7            or        a
04190E: ED62          sbc       hl, hl
041910: E5            push      hl
041911: FDE5          push      iy
041913: 210A0000      ld        hl, 00000A
041917: E5            push      hl
041918: 0177FFFF      ld        bc, FFFF77
04191C: ED2200        lea       hl, IX + 00
04191F: 09            add       hl, bc
041920: ED27          ld        hl, (hl)
041922: DD17B5        ld        de, (ix + -4B)
041925: DD0789        ld        bc, (ix + -77)
041928: CD7C0304      call      label_04037C
04192C: DD2FB5        ld        (ix + -4B), hl
04192F: DD1F89        ld        (ix + -77), de
041932: DD1FFD        ld        (ix + -03), de
041935: 1177FFFF      ld        de, FFFF77
041939: ED5500        lea       iy, ix + 00
04193C: FD19          add       iy, de
04193E: FD0F00        ld        (iy + 00), bc
041941: E1            pop       hl
041942: E1            pop       hl
041943: E1            pop       hl
041944: 213C0000      ld        hl, 00003C
041948: E5            push      hl
041949: DD2783        ld        hl, (ix + -7D)
04194C: DD17FD        ld        de, (ix + -03)
04194F: DD17BE        ld        de, (ix + -42)
041952: DD0790        ld        bc, (ix + -70)
041955: CD3B0404      call      label_04043B
041959: FDE1          pop       iy
04195B: C5            push      bc
04195C: D5            push      de
04195D: E5            push      hl
04195E: DD27B5        ld        hl, (ix + -4B)
041961: DD1789        ld        de, (ix + -77)
041964: DD1FFD        ld        (ix + -03), de
041967: 1177FFFF      ld        de, FFFF77
04196B: ED5500        lea       iy, ix + 00
04196E: FD19          add       iy, de
041970: FD0700        ld        bc, (iy + 00)
041973: DD17FD        ld        de, (ix + -03)
041976: CD020204      call      label_040202
04197A: DD0FFD        ld        (ix + -03), bc
04197D: DDE5          push      ix
04197F: 0177FFFF      ld        bc, FFFF77
041983: DD09          add       ix, bc
041985: DD2F00        ld        (ix + 00), hl
041988: DDE1          pop       ix
04198A: DD1FB5        ld        (ix + -4B), de
04198D: DD07FD        ld        bc, (ix + -03)
041990: DD0F89        ld        (ix + -77), bc
041993: E1            pop       hl
041994: E1            pop       hl
041995: E1            pop       hl
041996: 21FF0F00      ld        hl, 000FFF
04199A: E5            push      hl
04199B: 37            scf
04199C: ED62          sbc       hl, hl
04199E: E5            push      hl
04199F: E5            push      hl
0419A0: DD2783        ld        hl, (ix + -7D)
0419A3: DD17BE        ld        de, (ix + -42)
0419A6: DD0790        ld        bc, (ix + -70)
0419A9: CD260204      call      label_040226
0419AD: FDE1          pop       iy
0419AF: FDE1          pop       iy
0419B1: FDE1          pop       iy
0419B3: FD21000000    ld        iy, 000000
0419B8: FDE5          push      iy
0419BA: FDE5          push      iy
0419BC: FD210A0000    ld        iy, 00000A
0419C1: FDE5          push      iy
0419C3: FD21000000    ld        iy, 000000
0419C8: CD7C0304      call      label_04037C
0419CC: DD2F83        ld        (ix + -7D), hl
0419CF: E1            pop       hl
0419D0: E1            pop       hl
0419D1: E1            pop       hl
0419D2: DD0FFD        ld        (ix + -03), bc
0419D5: 017DFFFF      ld        bc, FFFF7D
0419D9: ED2200        lea       hl, IX + 00
0419DC: 09            add       hl, bc
0419DD: ED27          ld        hl, (hl)
0419DF: 23            inc       hl
0419E0: DDE5          push      ix
0419E2: DD09          add       ix, bc
0419E4: DD2F00        ld        (ix + 00), hl
0419E7: DDE1          pop       ix
0419E9: DD07FD        ld        bc, (ix + -03)
0419EC: C3E71804      jp        label_0418E7
                    label_0419F0:
0419F0: DD2794        ld        hl, (ix + -6C)
0419F3: CD2F0104      call      label_04012F
0419F7: DDE5          push      ix
0419F9: 117DFFFF      ld        de, FFFF7D
0419FD: DD19          add       ix, de
0419FF: DD2F00        ld        (ix + 00), hl
041A02: DDE1          pop       ix
041A04: DD3E83        ld        (ix + -7D), iy
041A07: DD27AF        ld        hl, (ix + -51)
041A0A: DD2FBE        ld        (ix + -42), hl
041A0D: DD07B5        ld        bc, (ix + -4B)
041A10: 1177FFFF      ld        de, FFFF77
041A14: ED2200        lea       hl, IX + 00
041A17: 19            add       hl, de
041A18: ED31          ld        iy, (hl)
                    label_041A1A:
041A1A: DD0FB5        ld        (ix + -4B), bc
041A1D: ED2300        lea       hl, IY + 00
041A20: C5            push      bc
041A21: D1            pop       de
041A22: DD0789        ld        bc, (ix + -77)
041A25: CD8D0204      call      label_04028D
041A29: 2862          jr        z, label_041A8D
041A2B: B7            or        a
041A2C: ED62          sbc       hl, hl
041A2E: E5            push      hl
041A2F: E5            push      hl
041A30: 210A0000      ld        hl, 00000A
041A34: E5            push      hl
041A35: ED2300        lea       hl, IY + 00
041A38: DD17B5        ld        de, (ix + -4B)
041A3B: DD0789        ld        bc, (ix + -77)
041A3E: CD0A0304      call      label_04030A
041A42: DD1FB5        ld        (ix + -4B), de
041A45: DD0F89        ld        (ix + -77), bc
041A48: D1            pop       de
041A49: D1            pop       de
041A4A: D1            pop       de
041A4B: 55            ld        d, l
041A4C: DD07A7        ld        bc, (ix + -59)
041A4F: 59            ld        e, c
041A50: DD07B5        ld        bc, (ix + -4B)
041A53: ED5C          mlt       de
041A55: FD            NONI
041A56: 7D            ld        a, l
041A57: 93            sub       e
041A58: F630          or        30
041A5A: DD31BE        ld        iy, (ix + -42)
041A5D: FD7700        ld        (iy + 00), a
041A60: FD23          inc       iy
041A62: DD3EBE        ld        (ix + -42), iy
041A65: DD1783        ld        de, (ix + -7D)
041A68: 13            inc       de
041A69: DD1F83        ld        (ix + -7D), de
041A6C: DD0FFD        ld        (ix + -03), bc
041A6F: 017DFFFF      ld        bc, FFFF7D
041A73: ED5500        lea       iy, ix + 00
041A76: FD09          add       iy, bc
041A78: FD1700        ld        de, (iy + 00)
041A7B: 13            inc       de
041A7C: DDE5          push      ix
041A7E: DD09          add       ix, bc
041A80: DD1F00        ld        (ix + 00), de
041A83: DDE1          pop       ix
041A85: E5            push      hl
041A86: FDE1          pop       iy
041A88: DD07FD        ld        bc, (ix + -03)
041A8B: 188D          jr        label_041A1A
                    label_041A8D:
041A8D: DD31AF        ld        iy, (ix + -51)
041A90: 017AFFFF      ld        bc, FFFF7A
041A94: ED2200        lea       hl, IX + 00
041A97: 09            add       hl, bc
041A98: ED17          ld        de, (hl)
                    label_041A9A:
041A9A: D5            push      de
041A9B: E1            pop       hl
041A9C: 01010000      ld        bc, 000001
041AA0: B7            or        a
041AA1: ED42          sbc       hl, bc
041AA3: EC180200      call      pe, __setflag(OS)
041AA7: FACF1A04      jp        m, label_041ACF
041AAB: 1B            dec       de
041AAC: ED2300        lea       hl, IY + 00
041AAF: DD0783        ld        bc, (ix + -7D)
041AB2: 09            add       hl, bc
041AB3: 3630          ld        (hl), 30
041AB5: 03            inc       bc
041AB6: DD0F83        ld        (ix + -7D), bc
041AB9: 017DFFFF      ld        bc, FFFF7D
041ABD: ED2200        lea       hl, IX + 00
041AC0: 09            add       hl, bc
041AC1: ED27          ld        hl, (hl)
041AC3: 23            inc       hl
041AC4: DDE5          push      ix
041AC6: DD09          add       ix, bc
041AC8: DD2F00        ld        (ix + 00), hl
041ACB: DDE1          pop       ix
041ACD: 18CB          jr        label_041A9A
                    label_041ACF:
041ACF: ED2300        lea       hl, IY + 00
041AD2: DD1783        ld        de, (ix + -7D)
041AD5: 19            add       hl, de
041AD6: 362E          ld        (hl), 2E
041AD8: EB            ex        de, hl
041AD9: 1174FFFF      ld        de, FFFF74
041ADD: ED5500        lea       iy, ix + 00
041AE0: FD19          add       iy, de
041AE2: FD0700        ld        bc, (iy + 00)
041AE5: DD31B2        ld        iy, (ix + -4E)
041AE8: DD17C1        ld        de, (ix + -3F)
                    label_041AEB:
041AEB: DD1FC1        ld        (ix + -3F), de
041AEE: DD2FBE        ld        (ix + -42), hl
041AF1: DD27AF        ld        hl, (ix + -51)
041AF4: DD17BE        ld        de, (ix + -42)
041AF7: 19            add       hl, de
041AF8: DDE5          push      ix
041AFA: 117AFFFF      ld        de, FFFF7A
041AFE: DD19          add       ix, de
041B00: DD2F00        ld        (ix + 00), hl
041B03: DDE1          pop       ix
041B05: B7            or        a
041B06: ED62          sbc       hl, hl
041B08: E5            push      hl
041B09: E5            push      hl
041B0A: 210A0000      ld        hl, 00000A
041B0E: E5            push      hl
041B0F: C5            push      bc
041B10: E1            pop       hl
041B11: DD3EB2        ld        (ix + -4E), iy
041B14: ED1300        lea       de, IY + 00
041B17: C5            push      bc
041B18: FDE1          pop       iy
041B1A: DD07C1        ld        bc, (ix + -3F)
041B1D: CD0A0304      call      label_04030A
041B21: DD2F89        ld        (ix + -77), hl
041B24: DD1FB5        ld        (ix + -4B), de
041B27: DD0F90        ld        (ix + -70), bc
041B2A: D1            pop       de
041B2B: D1            pop       de
041B2C: D1            pop       de
041B2D: DD17A7        ld        de, (ix + -59)
041B30: 55            ld        d, l
041B31: DD1FA7        ld        (ix + -59), de
041B34: ED5C          mlt       de
041B36: FD            NONI
041B37: 7D            ld        a, l
041B38: ED2300        lea       hl, IY + 00
041B3B: 93            sub       e
041B3C: F630          or        30
041B3E: 117AFFFF      ld        de, FFFF7A
041B42: ED5500        lea       iy, ix + 00
041B45: FD19          add       iy, de
041B47: FD3700        ld        iy, (iy + 00)
041B4A: FD7701        ld        (iy + 01), a
041B4D: FD21000000    ld        iy, 000000
041B52: 11000000      ld        de, 000000
041B56: D5            push      de
041B57: FDE5          push      iy
041B59: 110A0000      ld        de, 00000A
041B5D: D5            push      de
041B5E: DD17B2        ld        de, (ix + -4E)
041B61: DD07C1        ld        bc, (ix + -3F)
041B64: CD630204      call      label_040263
041B68: E1            pop       hl
041B69: E1            pop       hl
041B6A: E1            pop       hl
041B6B: 3F            ccf
041B6C: 9F            sbc       a, a
041B6D: 3C            inc       a
041B6E: DD27BE        ld        hl, (ix + -42)
041B71: 23            inc       hl
041B72: CB47          bit       0, a
041B74: DD0789        ld        bc, (ix + -77)
041B77: DD31B5        ld        iy, (ix + -4B)
041B7A: DD1790        ld        de, (ix + -70)
041B7D: CAEB1A04      jp        z, label_041AEB
041B81: EB            ex        de, hl
041B82: DD1FBE        ld        (ix + -42), de
041B85: 13            inc       de
041B86: D5            push      de
041B87: E1            pop       hl
041B88: 01000000      ld        bc, 000000
041B8C: B7            or        a
041B8D: ED42          sbc       hl, bc
041B8F: EC180200      call      pe, __setflag(OS)
041B93: F2A01B04      jp        p, label_041BA0
041B97: FD21000000    ld        iy, 000000
041B9C: C3820C04      jp        label_040C82
                    label_041BA0:
041BA0: DD2783        ld        hl, (ix + -7D)
041BA3: DD1794        ld        de, (ix + -6C)
041BA6: B7            or        a
041BA7: ED52          sbc       hl, de
041BA9: E5            push      hl
041BAA: D1            pop       de
041BAB: 01010000      ld        bc, 000001
041BAF: B7            or        a
041BB0: ED42          sbc       hl, bc
041BB2: EC180200      call      pe, __setflag(OS)
041BB6: F2BE1B04      jp        p, label_041BBE
041BBA: 11000000      ld        de, 000000
                    label_041BBE:
041BBE: DD27AF        ld        hl, (ix + -51)
041BC1: 19            add       hl, de
041BC2: DD2F90        ld        (ix + -70), hl
041BC5: 117DFFFF      ld        de, FFFF7D
041BC9: ED2200        lea       hl, IX + 00
041BCC: 19            add       hl, de
041BCD: ED07          ld        bc, (hl)
041BCF: C5            push      bc
041BD0: E1            pop       hl
041BD1: 11010000      ld        de, 000001
041BD5: B7            or        a
041BD6: ED52          sbc       hl, de
041BD8: C5            push      bc
041BD9: D1            pop       de
041BDA: EC180200      call      pe, __setflag(OS)
041BDE: DD0797        ld        bc, (ix + -69)
041BE1: FD21000000    ld        iy, 000000
041BE6: F2ED1B04      jp        p, label_041BED
041BEA: ED1300        lea       de, IY + 00
                    label_041BED:
041BED: 21010000      ld        hl, 000001
041BF1: B7            or        a
041BF2: ED52          sbc       hl, de
041BF4: DD17BE        ld        de, (ix + -42)
041BF7: 19            add       hl, de
041BF8: DD2FC1        ld        (ix + -3F), hl
041BFB: DD3EBE        ld        (ix + -42), iy
041BFE: 2E00          ld        l, 00
041C00: C3840A04      jp        label_040A84
                    label_041C04:
041C04: DD27C7        ld        hl, (ix + -39)
041C07: DDF9          ld        sp, ix
041C09: DDE1          pop       ix
041C0B: C9            ret
                    _npf_utoa_rev:
041C0C: 21E5FFFF      ld        hl, FFFFE5
041C10: CDCC0004      call      __frameset
041C14: DD2709        ld        hl, (ix + 09)
041C17: DD2FF7        ld        (ix + -09), hl
041C1A: DD170C        ld        de, (ix + 0C)
041C1D: DD270F        ld        hl, (ix + 0F)
041C20: DD2FFA        ld        (ix + -06), hl
041C23: FD21000000    ld        iy, 000000
041C28: 01370000      ld        bc, 000037
041C2C: DD2715        ld        hl, (ix + 15)
041C2F: 09            add       hl, bc
041C30: DD2FE5        ld        (ix + -1B), hl
041C33: DD3EFD        ld        (ix + -03), iy
                    label_041C36:
041C36: DD2706        ld        hl, (ix + 06)
041C39: DD07FD        ld        bc, (ix + -03)
041C3C: 09            add       hl, bc
041C3D: DD2FE8        ld        (ix + -18), hl
041C40: FDE5          push      iy
041C42: FDE5          push      iy
041C44: DD2712        ld        hl, (ix + 12)
041C47: E5            push      hl
041C48: DD27F7        ld        hl, (ix + -09)
041C4B: DD1FF1        ld        (ix + -0F), de
041C4E: DD07FA        ld        bc, (ix + -06)
041C51: CD0A0304      call      label_04030A
041C55: DD2FF4        ld        (ix + -0C), hl
041C58: E1            pop       hl
041C59: E1            pop       hl
041C5A: E1            pop       hl
041C5B: FDE5          push      iy
041C5D: FDE5          push      iy
041C5F: DD2712        ld        hl, (ix + 12)
041C62: E5            push      hl
041C63: DD27F4        ld        hl, (ix + -0C)
041C66: DD1FEE        ld        (ix + -12), de
041C69: DD0FEB        ld        (ix + -15), bc
041C6C: CD7C0304      call      label_04037C
041C70: E5            push      hl
041C71: C1            pop       bc
041C72: E1            pop       hl
041C73: E1            pop       hl
041C74: E1            pop       hl
041C75: DD17F7        ld        de, (ix + -09)
041C78: D5            push      de
041C79: E1            pop       hl
041C7A: B7            or        a
041C7B: ED42          sbc       hl, bc
041C7D: E5            push      hl
041C7E: FDE1          pop       iy
041C80: 010A0000      ld        bc, 00000A
041C84: B7            or        a
041C85: ED42          sbc       hl, bc
041C87: 21300000      ld        hl, 000030
041C8B: 3803          jr        c, label_041C90
041C8D: DD27E5        ld        hl, (ix + -1B)
                    label_041C90:
041C90: 7D            ld        a, l
041C91: FD85          add       a, iyl
041C93: DD27E8        ld        hl, (ix + -18)
041C96: 77            ld        (hl), a
041C97: DD27FD        ld        hl, (ix + -03)
041C9A: 23            inc       hl
041C9B: DD2FFD        ld        (ix + -03), hl
041C9E: FD21000000    ld        iy, 000000
041CA3: FDE5          push      iy
041CA5: FDE5          push      iy
041CA7: DD2712        ld        hl, (ix + 12)
041CAA: E5            push      hl
041CAB: EB            ex        de, hl
041CAC: DD17F1        ld        de, (ix + -0F)
041CAF: DD07FA        ld        bc, (ix + -06)
041CB2: CD630204      call      label_040263
041CB6: E1            pop       hl
041CB7: E1            pop       hl
041CB8: E1            pop       hl
041CB9: DD27F4        ld        hl, (ix + -0C)
041CBC: DD2FF7        ld        (ix + -09), hl
041CBF: DD17EE        ld        de, (ix + -12)
041CC2: DD27EB        ld        hl, (ix + -15)
041CC5: DD2FFA        ld        (ix + -06), hl
041CC8: D2361C04      jp        nc, label_041C36
041CCC: DD27FD        ld        hl, (ix + -03)
041CCF: DDF9          ld        sp, ix
041CD1: DDE1          pop       ix
041CD3: C9            ret

                    _printf:
041CD4: 21FDFFFF      ld        hl, FFFFFD
041CD8: CDCC0004      call      __frameset
041CDC: DD2706        ld        hl, (ix + 06)
041CDF: ED1209        lea       de, IX + 09
041CE2: DD1FFD        ld        (ix + -03), de
041CE5: DD17FD        ld        de, (ix + -03)
041CE8: D5            push      de
041CE9: E5            push      hl
041CEA: CDC81D04      call      __vprintf_c
041CEE: DDF9          ld        sp, ix
041CF0: DDE1          pop       ix
041CF2: C9            ret

                    vsnprintf:
041CF3: 21EEFFFF      ld        hl, FFFFEE
041CF7: CDCC0004      call      __frameset
041CFB: DD2706        ld        hl, (ix + 06)
041CFE: DD1709        ld        de, (ix + 09)
041D01: FD21000000    ld        iy, 000000
041D06: ED02F7        lea       bc, IX + F7
041D09: DD2FF7        ld        (ix + -09), hl
041D0C: DD1FFA        ld        (ix + -06), de
041D0F: DD3EFD        ld        (ix + -03), iy
041D12: 09            add       hl, bc
041D13: B7            or        a
041D14: ED42          sbc       hl, bc
041D16: 2806          jr        z, label_041D1E
041D18: 11561D04      ld        de, 041D56
041D1C: 1804          jr        label_041D22
                    label_041D1E:
041D1E: 117B1D04      ld        de, 041D7B
                    label_041D22:
041D22: DD1FF1        ld        (ix + -0F), de
041D25: DD270F        ld        hl, (ix + 0F)
041D28: E5            push      hl
041D29: DD270C        ld        hl, (ix + 0C)
041D2C: E5            push      hl
041D2D: DD0FEE        ld        (ix + -12), bc
041D30: C5            push      bc
041D31: D5            push      de
041D32: CDA20404      call      _npf_vpprintf
041D36: DD2FF4        ld        (ix + -0C), hl
041D39: E1            pop       hl
041D3A: E1            pop       hl
041D3B: E1            pop       hl
041D3C: E1            pop       hl
041D3D: DD27EE        ld        hl, (ix + -12)
041D40: E5            push      hl
041D41: B7            or        a
041D42: ED62          sbc       hl, hl
041D44: E5            push      hl
041D45: DD27F1        ld        hl, (ix + -0F)
041D48: CD2E0104      call      __indcallhl
041D4C: E1            pop       hl
041D4D: E1            pop       hl
041D4E: DD27F4        ld        hl, (ix + -0C)
041D51: DDF9          ld        sp, ix
041D53: DDE1          pop       ix
041D55: C9            ret
041D56: CDDA0004      call      __frameset0
041D5A: DD3109        ld        iy, (ix + 09)
041D5D: FD1706        ld        de, (iy + 06)
041D60: FD0703        ld        bc, (iy + 03)
041D63: D5            push      de
041D64: E1            pop       hl
041D65: B7            or        a
041D66: ED42          sbc       hl, bc
041D68: 300E          jr        nc, label_041D78
041D6A: DD7E06        ld        a, (ix + 06)
041D6D: FD2700        ld        hl, (iy + 00)
041D70: D5            push      de
041D71: C1            pop       bc
041D72: 03            inc       bc
041D73: FD0F06        ld        (iy + 06), bc
041D76: 19            add       hl, de
041D77: 77            ld        (hl), a
                    label_041D78:
041D78: DDE1          pop       ix
041D7A: C9            ret
041D7B: CDDA0004      call      __frameset0
041D7F: DDE1          pop       ix
041D81: C9            ret
041D82: 21FDFFFF      ld        hl, FFFFFD
041D86: CDCC0004      call      __frameset
041D8A: DD3106        ld        iy, (ix + 06)
041D8D: DD1709        ld        de, (ix + 09)
041D90: DD070C        ld        bc, (ix + 0C)
041D93: ED220F        lea       hl, IX + 0F
041D96: DD2FFD        ld        (ix + -03), hl
041D99: DD27FD        ld        hl, (ix + -03)
041D9C: E5            push      hl
041D9D: C5            push      bc
041D9E: D5            push      de
041D9F: FDE5          push      iy
041DA1: CDF31C04      call      label_041CF3
041DA5: DDF9          ld        sp, ix
041DA7: DDE1          pop       ix
041DA9: C9            ret
041DAA: CDDA0004      call      __frameset0
041DAE: DD3106        ld        iy, (ix + 06)
041DB1: DD1709        ld        de, (ix + 09)
041DB4: DD070C        ld        bc, (ix + 0C)
041DB7: 37            scf
041DB8: ED62          sbc       hl, hl
041DBA: C5            push      bc
041DBB: D5            push      de
041DBC: E5            push      hl
041DBD: FDE5          push      iy
041DBF: CDF31C04      call      label_041CF3
041DC3: DDF9          ld        sp, ix
041DC5: DDE1          pop       ix
041DC7: C9            ret

                    __vprintf_c:                                ; same as _vprintf
041DC8: CDDA0004      call      __frameset0
041DCC: DD3106        ld        iy, (ix + 06)
041DCF: DD1709        ld        de, (ix + 09)
041DD2: 01E81D04      ld        bc, 041DE8                      ; _npf_putc_std
041DD6: 21000000      ld        hl, 000000
041DDA: D5            push      de
041DDB: FDE5          push      iy
041DDD: E5            push      hl
041DDE: C5            push      bc
041DDF: CDA20404      call      _npf_vpprintf
041DE3: DDF9          ld        sp, ix
041DE5: DDE1          pop       ix
041DE7: C9            ret                                       ; end of __vprintf_c

041DE8: CDDA0004      call      __frameset0
041DEC: DD7E06        ld        a, (ix + 06)
041DEF: DD7706        ld        (ix + 06), a
041DF2: DDE1          pop       ix
041DF4: C3211E04      jp        label_041E21
041DF8: 21FDFFFF      ld        hl, FFFFFD
041DFC: CDCC0004      call      __frameset
041E00: DD3106        ld        iy, (ix + 06)
041E03: DD1709        ld        de, (ix + 09)
041E06: 01FFFFFF      ld        bc, FFFFFF
041E0A: ED220C        lea       hl, IX + 0C
041E0D: DD2FFD        ld        (ix + -03), hl
041E10: DD27FD        ld        hl, (ix + -03)
041E13: E5            push      hl
041E14: D5            push      de
041E15: C5            push      bc
041E16: FDE5          push      iy
041E18: CDF31C04      call      label_041CF3
041E1C: DDF9          ld        sp, ix
041E1E: DDE1          pop       ix
041E20: C9            ret
                    label_041E21:
041E21: D1            pop       de
041E22: E3            ex        (sp), hl
041E23: D5            push      de
041E24: 7D            ld        a, l
041E25: 5BD7          rst.lil   10h
041E27: C9            ret
                    _main:
041E28: 211A1F04      ld        hl, 041F1A
041E2C: 111CC7B1      ld        de, B1C71C
041E30: 01400000      ld        bc, 000040
041E34: C5            push      bc
041E35: D5            push      de
041E36: E5            push      hl
041E37: CDD41C04      call      _printf
041E3B: E1            pop       hl
041E3C: E1            pop       hl
041E3D: E1            pop       hl
041E3E: B7            or        a
041E3F: ED62          sbc       hl, hl
041E41: C9            ret                               ; end of _main

041E42: E9            jp        (hl)
041E43: 0604          ld        b, 04
041E45: 02            ld        (bc), a
041E46: 07            rlca
041E47: 04            inc       b
041E48: 08            ex        af, af'
041E49: 07            rlca
041E4A: 04            inc       b
041E4B: 3807          jr        c, label_041E54
041E4D: 04            inc       b
041E4E: 3807          jr        c, label_041E57
041E50: 04            inc       b
041E51: 3807          jr        c, label_041E5A
041E53: 04            inc       b
                    label_041E54:
041E54: 2B            dec       hl
041E55: 07            rlca
041E56: 04            inc       b
                    label_041E57:
041E57: 3807          jr        c, label_041E60
041E59: 04            inc       b
                    label_041E5A:
041E5A: 3807          jr        c, label_041E63
041E5C: 04            inc       b
041E5D: 31070498      ld        sp, 980407
041E61: 07            rlca
041E62: 04            inc       b
                    label_041E63:
041E63: B5            or        l
041E64: 09            add       hl, bc
041E65: 04            inc       b
041E66: 86            add       a, (hl)
041E67: 1604          ld        d, 04
041E69: 77            ld        (hl), a
041E6A: 09            add       hl, bc
041E6B: 04            inc       b
041E6C: CD070477      call      label_770407
041E70: 09            add       hl, bc
041E71: 04            inc       b
041E72: 77            ld        (hl), a
041E73: 09            add       hl, bc
041E74: 04            inc       b
041E75: 86            add       a, (hl)
041E76: 1604          ld        d, 04
041E78: 77            ld        (hl), a
041E79: 09            add       hl, bc
041E7A: 04            inc       b
041E7B: 77            ld        (hl), a
041E7C: 09            add       hl, bc
041E7D: 04            inc       b
041E7E: 77            ld        (hl), a
041E7F: 09            add       hl, bc
041E80: 04            inc       b
041E81: 77            ld        (hl), a
041E82: 09            add       hl, bc
041E83: 04            inc       b
041E84: AA            xor       d
041E85: 1604          ld        d, 04
041E87: D0            ret       nc
041E88: 1604          ld        d, 04
041E8A: F2160477      jp        p, label_770416
041E8E: 09            add       hl, bc
041E8F: 04            inc       b
041E90: 77            ld        (hl), a
041E91: 09            add       hl, bc
041E92: 04            inc       b
041E93: 19            add       hl, de
041E94: 17            rla
041E95: 04            inc       b
041E96: 77            ld        (hl), a
041E97: 09            add       hl, bc
041E98: 04            inc       b
041E99: 3F            ccf
041E9A: 17            rla
041E9B: 04            inc       b
041E9C: 77            ld        (hl), a
041E9D: 09            add       hl, bc
041E9E: 04            inc       b
041E9F: 77            ld        (hl), a
041EA0: 09            add       hl, bc
041EA1: 04            inc       b
041EA2: 1608          ld        d, 08
041EA4: 04            inc       b
041EA5: 42            ld        b, d
041EA6: 09            add       hl, bc
041EA7: 04            inc       b
041EA8: 8B            adc       a, e
041EA9: 0A            ld        a, (bc)
041EAA: 04            inc       b
041EAB: DE09          sbc       a, 09
041EAD: 04            inc       b
041EAE: F8            ret       m
041EAF: 09            add       hl, bc
041EB0: 04            inc       b
041EB1: 200A          jr        nz, label_041EBD
041EB3: 04            inc       b
041EB4: 200A          jr        nz, label_041EC0
041EB6: 04            inc       b
041EB7: 200A          jr        nz, label_041EC3
041EB9: 04            inc       b
041EBA: 200A          jr        nz, label_041EC6
041EBC: 04            inc       b
                    label_041EBD:
041EBD: AE            xor       (hl)
041EBE: 0A            ld        a, (bc)
041EBF: 04            inc       b
                    label_041EC0:
041EC0: 04            inc       b
041EC1: 0B            dec       bc
041EC2: 04            inc       b
                    label_041EC3:
041EC3: 25            dec       h
041EC4: 0B            dec       bc
041EC5: 04            inc       b
                    label_041EC6:
041EC6: 17            rla
041EC7: 0B            dec       bc
041EC8: 04            inc       b
041EC9: 010E040E      ld        bc, 0E040E
041ECD: 0E04          ld        c, 04
041ECF: 33            inc       sp
041ED0: 0E04          ld        c, 04
041ED2: 4D            ld        c, l
041ED3: 0E04          ld        c, 04
041ED5: 4D            ld        c, l
041ED6: 0E04          ld        c, 04
041ED8: 17            rla
041ED9: 0B            dec       bc
041EDA: 04            inc       b
041EDB: 17            rla
041EDC: 0B            dec       bc
041EDD: 04            inc       b
041EDE: 3D            dec       a
041EDF: 0D            dec       c
041EE0: 04            inc       b
041EE1: 360A          ld        (hl), 0A
041EE3: 04            inc       b
041EE4: F8            ret       m
041EE5: 0C            inc       c
041EE6: 04            inc       b
041EE7: 110D0429      ld        de, 29040D
041EEB: 0D            dec       c
041EEC: 04            inc       b
041EED: 29            add       hl, hl
041EEE: 0D            dec       c
041EEF: 04            inc       b
041EF0: 3D            dec       a
041EF1: 0D            dec       c
041EF2: 04            inc       b
041EF3: 3D            dec       a
041EF4: 0D            dec       c
041EF5: 04            inc       b
041EF6: F7            rst       30h
041EF7: 0E04          ld        c, 04
041EF9: 08            ex        af, af'
041EFA: 0A            ld        a, (bc)
041EFB: 04            inc       b
041EFC: 86            add       a, (hl)
041EFD: 0E04          ld        c, 04
041EFF: 9A            sbc       a, d
041F00: 0E04          ld        c, 04
041F02: C1            pop       bc
041F03: 0E04          ld        c, 04
041F05: C1            pop       bc
041F06: 0E04          ld        c, 04
041F08: DC0E04F7      call      c, label_F7040E
041F0C: 0E04          ld        c, 04
041F0E: 4E            ld        c, (hl)
041F0F: 41            ld        b, c
041F10: 4E            ld        c, (hl)
041F11: 00            nop
041F12: 46            ld        b, (hl)
041F13: 4E            ld        c, (hl)
041F14: 4900          nop.sil
041F16: 52            noni.lis
041F17: 4F            ld        c, a
041F18: 4F            ld        c, a
041F19: 00            nop
041F1A: 25            dec       h
041F1B: 66            ld        h, (hl)
041F1C: 0A            ld        a, (bc)
041F1D: 0D            dec       c
041F1E: 00            nop