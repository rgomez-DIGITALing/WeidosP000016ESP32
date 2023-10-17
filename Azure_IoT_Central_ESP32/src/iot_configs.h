// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT


//#define BATCH_GENERAL_ROBOT
//#define BATCH_LINEA_EMPAQUETADO_AC_OFICINAS
//#define BATCH_LETS_CONNECT
//#define BATCH_IT_SOPORTE
#define BATCH_TEST



#define IDENTIFIER_GENERAL "400-03-EA750-01"
#define IDENTIFIER_TRANSELEVADOR_1 "400-03-EM750-02"
#define IDENTIFIER_TRANSELEVADOR_2 "400-03-EM750-03"
#define IDENTIFIER_TRANSELEVADOR_3 "400-03-EM750-04"
#define IDENTIFIER_ROBOT "400-03-EM750-05"
#define IDENTIFIER_LINEA_EMPAQUETADO "400-03-EM750-06"
#define IDENTIFIER_MODULA_4 "400-03-EM750-07"
#define IDENTIFIER_MODULA_11 "400-03-EM750-08"
#define IDENTIFIER_AIRE_ACONDICIONADO "400-03-EM750-09"
#define IDENTIFIER_AIRE_COMPRIMIDO "400-03-EM750-10"
#define IDENTIFIER_COMPRESOR_IT_1 "400-03-EM750-11"
#define IDENTIFIER_COMPRESOR_IT_2 "400-03-EM750-12"
#define IDENTIFIER_COMPRESSOR_LETS_CONNECT "400-01-EM110-17"
#define IDENTIFIER_COMPRESOR_MONTAJE_ALMACEN "400-03-EM120-18"
#define IDENTIFIER_COMPRESOR_CALIDAD "400-01-EM110-19"

#define LOCATION_NAVE_400 "Nave 400"
#define LOCATION_CUADRO_ALMACEN "Cuadro general en Almacén"
#define LOCATION_CUADRO_ENTRADA "Cuadro General Entrada"
#define LOCATION_CUADRO_LETS_CONNECT "Cuadro Let's Connect"
#define LOCATION_SALA_IT "Sala IT"

#define ASSET_MODULA_4 "Modula 4"
#define ASSET_MODULA_11 "Modula 11"
#define ASSET_TRANSELEVADOR_1 "Transelevador 1"
#define ASSET_TRANSELEVADOR_2 "Transelevador 2"
#define ASSET_TRANSELEVADOR_3 "Transelevador 3"
#define ASSET_GENERAL "General"
#define ASSET_ROBOT "Robot"
#define ASSET_LINEA_EMPAQUETADO "Linea empaquetado"
#define ASSET_AIRE_ACONDICIONADO "AC Oficinas (General por conducto)"
#define ASSET_AIRE_COMPRIMIDO "Aire comprimido"
#define ASSET_COMPRESOR_IT_1 "Compresor IT 1"
#define ASSET_COMPRESOR_IT_2 "Compresor IT 2"
#define ASSET_COMPRESSOR_LETS_CONNECT "Compresor Cafetería Let's Connect"
#define ASSET_COMPRESOR_MONTAJE_ALMACEN "Compresor Sala Montaje Almacén - 3 fases"
#define ASSET_COMPRESOR_CALIDAD "Compresor Calidad"




// Azure IoT Central
#define DPS_ID_SCOPE "0ne00A56BD4"
#ifdef BATCH_TEST
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
#define IOT_CONFIG_DEVICE_1_ID "z8xt2ydr8d"           //Compresor IT 1 (ok)
#define IOT_CONFIG_DEVICE_2_ID "dpj8xlx0sc"           //Compresor IT 2 (ok)
#define IOT_CONFIG_DEVICE_3_ID "1gt42big9ck"           //Compresor Soporte
#define IOT_CONFIG_DEVICE_4_ID "unusedDevic"           //Unused
#define IOT_CONFIG_DEVICE_5_ID "unusedDevic"           //Unused

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "aBMfmJMK8VrbSnXaHomUeazDXWD88g9nLnmlBAZ0nzE="    //GW IT-Soporte
#define IOT_CONFIG_DEVICE_1_KEY "rwXJzhN0s8PQlwJHxp68TrloRZLurpTJUmmVTD3nSuo="          //Compresor IT 1 (ok)
#define IOT_CONFIG_DEVICE_2_KEY "P4u5eMu05ZJYX1A1uh5BQhf2iM3ZgkjdtLdJrIO1QLA="          //Compresor IT 2 (ok)
#define IOT_CONFIG_DEVICE_3_KEY "qxI3X4O8KX36BbVoCptJ12BXzU8dgmFSbBFbjL+VeOU="          //Compresor Soporte
#define IOT_CONFIG_DEVICE_4_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unusedaa
#define IOT_CONFIG_DEVICE_5_KEY "unusedunusedunusedunusedunusedunusedunusedun"          //Unused
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




// User-agent (url-encoded) provided by the MQTT client to Azure IoT Services.
// When developing for your own Arduino-based platform,
// please update the suffix with the format '(ard;<platform>)' as an url-encoded string.
#define AZURE_SDK_CLIENT_USER_AGENT "c%2F" AZ_SDK_VERSION_STRING "(ard%3Besp32)"

// Publish 1 message every 2 seconds.
#define TELEMETRY_FREQUENCY_IN_SECONDS 2

// For how long the MQTT password (SAS token) is valid, in minutes.
// After that, the sample automatically generates a new password and re-connects.
#define MQTT_PASSWORD_LIFETIME_IN_MINUTES 60
