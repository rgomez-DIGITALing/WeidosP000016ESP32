// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT


// #define BATCH_GENERAL_ROBOT
// #define BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
// #define BATCH_BARCELONA_SAI
// #define BATCH_MONTACARGAS
// #define BATCH_LETS_CONNECT
// #define BATCH_IT_SOPORTE
// #define BATCH_GAC_LETS_CONNECT
// #define BATCH_TRANSELEVADORES_FAST

// #define DEMO_COMERCIALES

#define BATCH_TEST
// #define FLOW_METER_TEST
#define EM750_TEST
// #define RTU_TEST
// #define HANDOVER_TEST


// Azure IoT Central
#define DPS_ID_SCOPE "0ne00A56BD4"
//#define DPS_ID_SCOPE "0ne00B219C5"//To be deleted hahah
#ifdef BATCH_TEST
#define DPS_ID_SCOPE "0ne00B219C5"
#endif
#ifdef DEMO_COMERCIALES
#define DPS_ID_SCOPE "0ne00C3AD83"
#endif
#ifdef HANDOVER_TEST
#define DPS_ID_SCOPE "0ne00B219C5"
#endif

#ifdef BATCH_GENERAL_ROBOT
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1iyt0p0nos5"                                   //GW General-Robot (2)
#define IOT_CONFIG_DEVICE_1_ID "1s5lc81kxju"                                        //General (2)
#define IOT_CONFIG_DEVICE_2_ID "1cssf7o7o2v"                                        //Transelevador 1 (2)
#define IOT_CONFIG_DEVICE_3_ID "12to0bk8bdm"                                         //Transelevador 2 (2)
#define IOT_CONFIG_DEVICE_4_ID "17r0wq1qv4h"                                        //Transelevador 3 (2)
#define IOT_CONFIG_DEVICE_5_ID "6vxabuk14d"                                         //Robot (2)

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "YJ44De/cAaFcdQaR50FZd7MuFTBWDH9tofaUwlJxUh8="    //GW General-Robot (2)
#define IOT_CONFIG_DEVICE_1_KEY "aybjmIKBaO95YG4Xc9Pdt1brIR45hMeof84j+VWIAjI="          //General (2)
#define IOT_CONFIG_DEVICE_2_KEY "ATbf/P+ND0O0NXFn0MlVj3k7vGlOrl2BxXKBlkv2nTo="          //Transelevador 1 (2)
#define IOT_CONFIG_DEVICE_3_KEY "TCBoEK1ufBgj3KrGjS1+VIbZd4TgjkImeJ9tFL/ucrM="          //Transelevador 2 (2)
#define IOT_CONFIG_DEVICE_4_KEY "g9u2jumpLcKZ2vYzNRbBs4ePpsUeCUIacSNiVAD8mlc="          //Transelevador 3 (2)
#define IOT_CONFIG_DEVICE_5_KEY "emH3afVfZL8YGz1+DWHgfeqXW0Vj5Hq70yqxrBeUL3E="          //Robot (2)
#endif




#ifdef BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1ygq9zppy8t"                                   //GW Linea empaquetado-AC oficinas (2)
#define IOT_CONFIG_DEVICE_1_ID "qhogh8wdhh"                                        //Linea Empaquetado (2)
#define IOT_CONFIG_DEVICE_2_ID "zh427e2mil"                                        //Modula 4 (2)
#define IOT_CONFIG_DEVICE_3_ID "1xx08bigre7"                                        //Modula 11 (2)
#define IOT_CONFIG_DEVICE_4_ID "1n67jcyxcef"                                        //Compresor aire comprimido (2)
#define IOT_CONFIG_DEVICE_5_ID "idxz6otb9n"                                         //AC oficinas (General por conductos)

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "YOLuq1gO0TPfARthf3w3lK0cLnC1X7lm/1qqbdxjjKc="    //GW Linea empaquetado-AC oficinas (2)
#define IOT_CONFIG_DEVICE_1_KEY "9cbOezaVa4b67RPrMcc61gGjzcBA3QLrmzf3hN31sPE="          //Linea Empaquetado (2)
#define IOT_CONFIG_DEVICE_2_KEY "5mSYxLkAR4ga7TmYVCYa+X/KKrVWynfgExIKsa9NvDU="          //Modula 4 (2)
#define IOT_CONFIG_DEVICE_3_KEY "p5PyvhiXNYhVtuvRNoxvaCm/AZxCkLxzWZJLQUEa+Jw="          //Modula 11 (2)
#define IOT_CONFIG_DEVICE_4_KEY "rjUQAd80tnTiBVITw8FjbdmNUxqNCJqetSEljngkBho="          //Compresor aire comprimido (2)
#define IOT_CONFIG_DEVICE_5_KEY "YFcaJRjCNx/AOYPcmXZh1toVzXe7JBUz/ap45zWR+OY="          //AC oficinas (General por conductos) (2)
#endif



#ifdef BATCH_LETS_CONNECT
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1ijc3kxoa38"     //Gateway let's connect
#define IOT_CONFIG_DEVICE_1_ID "2jb2239f0p6"           //Compresor Sala Let's connect
#define IOT_CONFIG_DEVICE_2_ID "1de5pvkyk9z"           //Compresor Sala Montaje
#define IOT_CONFIG_DEVICE_3_ID "16m9upxymh7"           //Compresor Calidad
#define IOT_CONFIG_DEVICE_4_ID "unusedDevic"           //Unused
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "MM/f1v3ctbpZTEcNPUoXvOVvxWozL2SOusfUZL/n3yM="    //Gateway let's connect
#define IOT_CONFIG_DEVICE_1_KEY "FWg4rwpIsSwk+apkcQJNJhRaQiEhB8j6GJiVbpwRi2g="          //Compresor Sala Let's connect
#define IOT_CONFIG_DEVICE_2_KEY "i9HVQ90Jl9BPibo0CzEa49RA0F5r5rAI6bvcZihNKGI="          //Compresor Sala Montaje
#define IOT_CONFIG_DEVICE_3_KEY "7XweH5eINLDPaNYmnoGFa90pwxbNfdVn1DF5rCVpsBY="          //Compresor Calidad
#define IOT_CONFIG_DEVICE_4_KEY "unusedunusedunusedunusedunusedunusedunusedun"                                                      //Unusedaa
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"                                                      //Unused
#endif

#ifdef BATCH_IT_SOPORTE
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1uv9j90f7ic"     //GW IT-Soporte
#define IOT_CONFIG_DEVICE_1_ID "1gt42big9ck"           //Compresor Soporte
#define IOT_CONFIG_DEVICE_2_ID "z8xt2ydr8d"           //Compresor IT 1 (ok)
#define IOT_CONFIG_DEVICE_3_ID "dpj8xlx0sc"           //Compresor IT 2 (ok)
#define IOT_CONFIG_DEVICE_4_ID "1s8n4mjky6m"           //Ascensor
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "aBMfmJMK8VrbSnXaHomUeazDXWD88g9nLnmlBAZ0nzE="    //GW IT-Soporte
#define IOT_CONFIG_DEVICE_1_KEY "qxI3X4O8KX36BbVoCptJ12BXzU8dgmFSbBFbjL+VeOU="          //Compresor Soporte
#define IOT_CONFIG_DEVICE_2_KEY "rwXJzhN0s8PQlwJHxp68TrloRZLurpTJUmmVTD3nSuo="          //Compresor IT 1 (ok)
#define IOT_CONFIG_DEVICE_3_KEY "P4u5eMu05ZJYX1A1uh5BQhf2iM3ZgkjdtLdJrIO1QLA="          //Compresor IT 2 (ok)
#define IOT_CONFIG_DEVICE_4_KEY "Fv31jlILxgZ0W2+hfXr12lOhneE1jA4hTkwaY+Jpb9I="          //Ascensor
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#endif


#ifdef BATCH_TRANSELEVADORES_FAST
#define IOT_CONFIG_DEVICE_GATEWAY_ID "cesql7bg96"     //Gateway
#define IOT_CONFIG_DEVICE_1_ID "1sbmjyrz1oa"           //Transelevador 1
#define IOT_CONFIG_DEVICE_2_ID "1b66i9vydmw"            //Transelevador 2
#define IOT_CONFIG_DEVICE_3_ID "oahkpmo0i1"            //Transelevador 3
#define IOT_CONFIG_DEVICE_4_ID "unusedDevic"           //Unused
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "cDluf2IWbhMz8wHGJQtA94pJrHTSFzAlP/2ZvLxomOo="    //Gateway 
#define IOT_CONFIG_DEVICE_1_KEY "ZCJOH3zvqDBusCCTdtMHO2rcv4qWgVq5bzgkxwwIQIM="          //Transelevador 1
#define IOT_CONFIG_DEVICE_2_KEY "FH7ktxpbRgW2Nq/ms0eANQS2ZKEpdKQorBa98xpM3+E="          //Transelevador 2
#define IOT_CONFIG_DEVICE_3_KEY "afq88WexxzEbz26qV9WNv+ZqdSE5BePaZOyjR9zVGjw="          //Transelevador 3
#define IOT_CONFIG_DEVICE_4_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#endif

#ifdef DEMO_COMERCIALES
#define IOT_CONFIG_DEVICE_GATEWAY_ID "20kgh6us67v"                                   //GW General-Robot (2)
#define IOT_CONFIG_DEVICE_1_ID "2jjtyms4mja"                                        //General (2)
#define IOT_CONFIG_DEVICE_2_ID "36u53dufev"                                        //Transelevador 1 (2)
#define IOT_CONFIG_DEVICE_3_ID "2ooyrqdla6g"                                         //Transelevador 2 (2)
#define IOT_CONFIG_DEVICE_4_ID "1zrl43tbkim"                                        //Transelevador 3 (2)
#define IOT_CONFIG_DEVICE_5_ID "1izset6ge61"                                         //Robot (2)

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "AIOEjePAlq4lAW12VzlKWPOp8MAd/jlWDlenyKOwOHU="    //GW General-Robot (2)
#define IOT_CONFIG_DEVICE_1_KEY "xLm5qRB61XyFWJblU6rPHIAFICH4IcU2j13f8P2SsUA="          //General (2)
#define IOT_CONFIG_DEVICE_2_KEY "3rXndM+ghy/DxBeSBwbZOCKqTBljO5VnN+PSjtRp5VA="          //Transelevador 1 (2)
#define IOT_CONFIG_DEVICE_3_KEY "LfVZhO/6l3zqpa4qRelRhlJhZjKP5rUGkjZG/bfWYT8="          //Transelevador 2 (2)
#define IOT_CONFIG_DEVICE_4_KEY "jxu/ZQrsm4BVps4BAWNR40DlMcmgvKzZyaU1VsvhBsI="          //Transelevador 3 (2)
#define IOT_CONFIG_DEVICE_5_KEY "zknhUkxaZTBeGvWGfKk/xHJ65hDdhom1btPm9VKGLOw="          //Robot (2)
#endif



#ifdef BATCH_TEST
#define IOT_CONFIG_DEVICE_GATEWAY_ID "2owqp9cpc1k"     //Gateway Test
#define IOT_CONFIG_DEVICE_1_ID "lqvsokgzkb"           //Test 1
#define IOT_CONFIG_DEVICE_2_ID "16wl1akgi3n"           //Test 2
#define IOT_CONFIG_DEVICE_3_ID "qogxopvz8v"           //Test 3
#define IOT_CONFIG_DEVICE_4_ID "2abmdx9g230"           //Test 4
#define IOT_CONFIG_DEVICE_5_ID "2n7f68p9bg2"           //Test 5

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "r3LfhSfYatuGI6OVV67ZF2ZONQ/WSimgM0grX3uZ7pM="    //Gateway Test
#define IOT_CONFIG_DEVICE_1_KEY "m50YTY6P2EeQ9jxBadh6V72t/kAmNTzTEedlFQUA7Co="          //Test 1
#define IOT_CONFIG_DEVICE_2_KEY "ROuQeq+SJHEPVwh/yBxrehvIJw4R6sZ9mqbY9nMzprY="          //Test 2
#define IOT_CONFIG_DEVICE_3_KEY "ywb9fgU7ILQhne6U79SD/x5azpz9AZXtcGAuqS/SlE8="     //Test 3
#define IOT_CONFIG_DEVICE_4_KEY "X/u+62h6n50qJrlZP91m0aVmeMWX/ygmoiKOuwfJH+A="           //Test 4
#define IOT_CONFIG_DEVICE_5_KEY "vLBPEJYxxO52B7koz0+xFTWPfP1o7vkD7qzVKuwSDYI="           //Test 5
#endif


#ifdef BATCH_BARCELONA_SAI
#define IOT_CONFIG_DEVICE_GATEWAY_ID "n9cmbjvg77"      //GW-BARCELONA-SAI
#define IOT_CONFIG_DEVICE_1_ID "2mtbdzsz410"           //Compresor Sala Barcelona
#define IOT_CONFIG_DEVICE_2_ID "2e7guwkqz75"           //Compresor Sala Automation
#define IOT_CONFIG_DEVICE_3_ID "c19bzm37cd"            //Compresor Sala París/Milán
#define IOT_CONFIG_DEVICE_4_ID "1yjx096rm9i"           //Compresor Sala Rack
#define IOT_CONFIG_DEVICE_5_ID "70fe8tx0wg"            //Enchufes Equipos (SAI)

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "F7yC04kCtTq9y6C8DdxxCAOS2uZEAsXWMmRH5eF3ZaI="    //GW-BARCELONA-SAI
#define IOT_CONFIG_DEVICE_1_KEY "PfWuTppfV481YWX8NK8giJsc/e79jqX1MipztTY2Ep0="          //Compresor Sala Barcelona
#define IOT_CONFIG_DEVICE_2_KEY "yxOAOb1UNP5EkaAdyuHqinVWE0Pr8IQ36vY/rE7Feg4="          //Compresor Sala Automation
#define IOT_CONFIG_DEVICE_3_KEY "3/iFSel6t9WK6vdKmcbd9TJhCeXmkqQ/ZjrAkVAL5HM="          //Compresor Sala París/Milán
#define IOT_CONFIG_DEVICE_4_KEY "5qs1F9qWas6i/GRNvig0vPvMh1T326S4s6mqng4N3e4="          //Compresor Sala Rack
#define IOT_CONFIG_DEVICE_5_KEY "v2XZ2RB0beMe7YjepqqQmtTcS8903KOz168RQiIUZ3o="          //Enchufes Equipos (SAI)
#endif




#ifdef BATCH_GAC_LETS_CONNECT
#define IOT_CONFIG_DEVICE_GATEWAY_ID "2d0grny8nhi"     //GW GAC-Let's Connect
#define IOT_CONFIG_DEVICE_1_ID "ck3uf3l0q8"           //Compresor Despacho 4 GAC
#define IOT_CONFIG_DEVICE_2_ID "2d617lqqq93"            //Compresor Despacho 5 GAC
#define IOT_CONFIG_DEVICE_3_ID "1r1ej68avhj"            //Compresor Sala Let's Connect - 3 fases
#define IOT_CONFIG_DEVICE_4_ID "unusedDevic"           //Unused
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "ge1CYbc5gnp+LDDmemqBvfVLklcafqW0KSRAaXzisVI="    //GW GAC-Let's Connect
#define IOT_CONFIG_DEVICE_1_KEY "6DY+uEF9KlRm9QLSLZP/Y71p1yvSfkVklN86aTu4lBo="          //Compresor Despacho 4 GAC
#define IOT_CONFIG_DEVICE_2_KEY "tmiXKe8Ewoyk9qh+DouQ8fpNl85ZeiY0ABfakIA6PaI="          //Compresor Despacho 5 GAC
#define IOT_CONFIG_DEVICE_3_KEY "qOgrO7v4Ar2qz9OCbyUEQoZCL12g82sj4ruge32s6rQ="          //Compresor Sala Let's Connect - 3 fases
#define IOT_CONFIG_DEVICE_4_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#endif


#ifdef BATCH_MONTACARGAS
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1m8ohg9md7a"     //Unused
#define IOT_CONFIG_DEVICE_1_ID "2dsan1n0rde"           //Unused
#define IOT_CONFIG_DEVICE_2_ID "unusedDevic"            //Unused
#define IOT_CONFIG_DEVICE_3_ID "unusedDevic"            //Unused
#define IOT_CONFIG_DEVICE_4_ID "unusedDevic"           //Unused
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "87LdeZcim8PeRYRI6A48Qb/2Nnjjs9dOPCcifEHYwu0="    //Unused
#define IOT_CONFIG_DEVICE_1_KEY "j0rlvl21V/zYqSzdpqzGyaHnxHBNkIokfNI0dlqWGe0="          //Unused
#define IOT_CONFIG_DEVICE_2_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_3_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_4_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#endif

#ifdef HANDOVER_TEST
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1z75u5euy4j"     //GW Handover
#define IOT_CONFIG_DEVICE_1_ID "1cdavb4mwh3"           //EM750-1-Handover
#define IOT_CONFIG_DEVICE_2_ID "1fde8bvba3l"            //EM750-2-Handover
#define IOT_CONFIG_DEVICE_3_ID "2nj4nhhc084"            //EM750-3-Handover
#define IOT_CONFIG_DEVICE_4_ID "gu416sr5sq"           //EM111-Handover
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "aIU2UsTF6za9Qdz/4goUyCVXVIxsfGAVeMDYcbb5q0Y="    //GW Handover
#define IOT_CONFIG_DEVICE_1_KEY "sCtS2zWfjiKiF8A43UsRrBqWK32viT84kl8rv9hTVZE="          //EM750-1-Handover
#define IOT_CONFIG_DEVICE_2_KEY "YX2Iv5VkpHOJ+MmoGjwxbuGWzkr196EqnSFOjBICAH8="          //EM750-2-Handover
#define IOT_CONFIG_DEVICE_3_KEY "6xCA6oPjVRJ+Wq8/UeJ37WmFeGW4kbk5mjL7CHBSFAE="          //EM750-3-Handover
#define IOT_CONFIG_DEVICE_4_KEY "qpmoTXKranVK6IuNhydx38C1ujDyxWa7+gGq/oPXMRc="          //EM111-Handover
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#endif


#ifdef BATCH_UNUSED
#define IOT_CONFIG_DEVICE_GATEWAY_ID "unusedDevic"     //Unused
#define IOT_CONFIG_DEVICE_1_ID "unusedDevic"           //Unused
#define IOT_CONFIG_DEVICE_2_ID "unusedDevic"            //Unused
#define IOT_CONFIG_DEVICE_3_ID "unusedDevic"            //Unused
#define IOT_CONFIG_DEVICE_4_ID "unusedDevic"           //Unused
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "unusedunusedunusedunusedunusedunusedunusedun"    //Unused
#define IOT_CONFIG_DEVICE_1_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_2_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_3_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_4_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
#endif

// User-agent (url-encoded) provided by the MQTT client to Azure IoT Services.
// When developing for your own Arduino-based platform,
// please update the suffix with the format '(ard;<platform>)' as an url-encoded string.
#define AZURE_SDK_CLIENT_USER_AGENT "c%2F" AZ_SDK_VERSION_STRING "(ard%3Besp32)"

// Publish 1 message every 2 seconds.
#define TELEMETRY_FREQUENCY_IN_SECONDS 2

// For how long the MQTT password (SAS token) is valid, in minutes.
// After that, the sample automatically generates a new password and re-connects.
#define MQTT_PASSWORD_LIFETIME_IN_MINUTES 2*60
