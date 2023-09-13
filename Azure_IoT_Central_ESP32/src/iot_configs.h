// Copyright (c) Microsoft Corporation. All rights reserved.
// SPDX-License-Identifier: MIT

// Wifi
#define IOT_CONFIG_WIFI_SSID "IoT_Hub"
#define IOT_CONFIG_WIFI_PASSWORD "DetmoldDetmold"


// Model and partNumber for "General"
// char* model = "EA750-230"; 
// char* partNumber = "2534130000";

// Model and partNumber for other devices
// char* model = "EM750-230"; 
// char* partNumber = "2540910000";

//#define BATCH_TESTS
//#define BATCH_TESTS_2
#define BATCH_JORDI_TESTS
//#define BATCH_MODULAS_TRANSELEVADORES
//#define BATCH_GENERAL_LINEA_EMPAQUETADO
#if defined BATCH_MODULAS_TRANSELEVADORES || defined BATCH_TESTS || defined BATCH_TESTS_2 || defined BATCH_JORDI_TESTS
    #define USING_MODULAS_TRANSELEVADORES
#endif


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

#define LOCATION_NAVE_400 "Nave 400"
#define LOCATION_CUADRO_ALMACEN "Cuadro general en Almacén"
#define LOCATION_CUADRO_ENTRADA "Cuadro General Entrada"

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




// Azure IoT Central
#define DPS_ID_SCOPE "0ne00A56BD4"

#ifdef BATCH_TESTS
#define IOT_CONFIG_DEVICE_GATEWAY_ID "sr784l8ibv"                                   //gateway
#define IOT_CONFIG_DEVICE_1_ID "cbl84hkbku"                                           //test1
#define IOT_CONFIG_DEVICE_2_ID "1smk92w41vv"                                       //test2
#define IOT_CONFIG_DEVICE_3_ID "52oy087dq8"                                         //test3
#define IOT_CONFIG_DEVICE_4_ID "1sdt0ef7ize"                                         //test4
#define IOT_CONFIG_DEVICE_5_ID "1svy19g7wea"                                         //test5

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "2Ac2bvVWMmCJPpg/+tMs68m7kzoQkjlGu6R5JWdHCKY="    //gateway
#define IOT_CONFIG_DEVICE_1_KEY "+KrRFHdebniEAqIHAalEwSm7G29fIF+IRVBsIsfhor0="        //test1
#define IOT_CONFIG_DEVICE_2_KEY "DpoHozpBxvJQzH9g6E+9/35llC3cWneophLVX4cA7tM="      //test2
#define IOT_CONFIG_DEVICE_3_KEY "3cyrUdEHaQmT5GIYipAlNAMvaNqDvRKmm6EQjhfgED8="      //test3
#define IOT_CONFIG_DEVICE_4_KEY "cnSmOvgZbyUfSuZNNy0JD9PRMTHe9Rpuh1+roTEy0dY="      //test4
#define IOT_CONFIG_DEVICE_5_KEY "MWOkRmoln4yeZyHwqvJISKgYd+ai9Rb4YmHO1sMK7OY="      //test5
#endif


#ifdef BATCH_TESTS_2
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1e540nonuu0"                                   //gateway (2)
#define IOT_CONFIG_DEVICE_1_ID "1y2nhmki350"                                           //test1 (2)
#define IOT_CONFIG_DEVICE_2_ID "1y6kj4it717"                                       //test2 (2)
#define IOT_CONFIG_DEVICE_3_ID "1hw2fyuk7pm"                                         //test3 (2)
#define IOT_CONFIG_DEVICE_4_ID "785ogil3h6"                                         //test4 (2)
#define IOT_CONFIG_DEVICE_5_ID "1dakf31sw0r"                                         //test5 (2)

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "dCOSCMoZhpP4VPyEl7AV/CnfCDTRBLPRMrQzNt2+v2E="    //gateway (2)
#define IOT_CONFIG_DEVICE_1_KEY "LiBMc/gEZL4eegVvETNHrnrTEKgkYraZubdZju5S3mE="        //test1 (2)
#define IOT_CONFIG_DEVICE_2_KEY "E4ZKrGYyYahqsIb97MoBKnsalP7f1Cp1EU2QcdU8MvE="      //test2 (2)
#define IOT_CONFIG_DEVICE_3_KEY "DriieJjrbMtK6q/T6m/OM80uvK/OemViGCs0XGWGyNg="      //test3 (2)
#define IOT_CONFIG_DEVICE_4_KEY "piiuR7ZgZ2jytD3K0G60Ptmpa9R8NGECkf4aIzEtguo="      //test4 (2)
#define IOT_CONFIG_DEVICE_5_KEY "Qol1J6PVK5S0wHZUo55L+a/PxaenBD1ODs9EJod8fo0="      //test5 (2)
#endif

#ifdef BATCH_JORDI_TESTS
#define IOT_CONFIG_DEVICE_GATEWAY_ID "123_Esp32"                                     //Gateway Test Jordi
#define IOT_CONFIG_DEVICE_1_ID "energyMeter_1"                                       //Test1 Jordi
#define IOT_CONFIG_DEVICE_2_ID "energyMeter_2"                                       //Test2 Jordi
#define IOT_CONFIG_DEVICE_3_ID "energyMeter_3"                                       //Test3 Jordi
#define IOT_CONFIG_DEVICE_4_ID "energyMeter_4"                                       //Test4 Jordi
#define IOT_CONFIG_DEVICE_5_ID "energyMeter_5"                                       //Test5 Jordi

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "HJbtprhebM3tQQNF4cdwPnRQhCyutJQHlkCMkEX6o2Y="    //Gateway Test Jordi
#define IOT_CONFIG_DEVICE_1_KEY "k5q1VSkChAJHJd6SLhiihKPZR4vVnpspEiAbHDoj3oQ="          //Test1 Jordi
#define IOT_CONFIG_DEVICE_2_KEY "iKH0cyREUxOdkysZSGloHwl5r4M39X9MYtJ3yq3omig="          //Test2 Jordi
#define IOT_CONFIG_DEVICE_3_KEY "OERFMDIljaB1y7GON/LrjXgE3bvZ9Xm3gTNLxWsjQh4="          //Test3 Jordi
#define IOT_CONFIG_DEVICE_4_KEY "Dj/qy5bfQ3BvTjd2vnmzUi/mFnda4ykXMMyL/3ZLx5g="          //Test4 Jordi
#define IOT_CONFIG_DEVICE_5_KEY "PgkH37MakkXxhiAYbm/Jv+ECukHFaKUv2K5b+eml67A="          //Test5 Jordi
#endif

#ifdef BATCH_MODULAS_TRANSELEVADORES
#define IOT_CONFIG_DEVICE_GATEWAY_ID "1ygq9zppy8t"                                      //Gateway Modulas-Transelevadores (2)
#define IOT_CONFIG_DEVICE_1_ID "zh427e2mil"                                             //Modula 4 (2)
#define IOT_CONFIG_DEVICE_2_ID "1xx08bigre7"                                            //Modula 11 (2)
#define IOT_CONFIG_DEVICE_3_ID "1cssf7o7o2v"                                            //Translevador 1 (2)
#define IOT_CONFIG_DEVICE_4_ID "12to0bk8bdm"                                            //Translevador 2 (2)
#define IOT_CONFIG_DEVICE_5_ID "17r0wq1qv4h"                                            //Translevador 3 (2)

#define IOT_CONFIG_DEVICE_GATEWAY_KEY "YOLuq1gO0TPfARthf3w3lK0cLnC1X7lm/1qqbdxjjKc="    //Gateway Modulas-Transelevadores (2)
#define IOT_CONFIG_DEVICE_1_KEY "5mSYxLkAR4ga7TmYVCYa+X/KKrVWynfgExIKsa9NvDU="          //Modula 4 (2)
#define IOT_CONFIG_DEVICE_2_KEY "p5PyvhiXNYhVtuvRNoxvaCm/AZxCkLxzWZJLQUEa+Jw="          //Modula 11 (2)
#define IOT_CONFIG_DEVICE_3_KEY "ATbf/P+ND0O0NXFn0MlVj3k7vGlOrl2BxXKBlkv2nTo="          //Translevador 1 (2)
#define IOT_CONFIG_DEVICE_4_KEY "TCBoEK1ufBgj3KrGjS1+VIbZd4TgjkImeJ9tFL/ucrM="          //Translevador 2 (2)
#define IOT_CONFIG_DEVICE_5_KEY "g9u2jumpLcKZ2vYzNRbBs4ePpsUeCUIacSNiVAD8mlc="          //Translevador 3 (2)
#endif

// Azure IoT Central
#ifdef BATCH_GENERAL_LINEA_EMPAQUETADO
#define IOT_CONFIG_DEVICE_GATEWAY_ID ""     ////Gateway General-Otros (2)
#define IOT_CONFIG_DEVICE_1_ID ""           ////General (2)
#define IOT_CONFIG_DEVICE_2_ID ""           ////Robot (2)
#define IOT_CONFIG_DEVICE_3_ID ""           ////Linea Empaquetado (2)
#define IOT_CONFIG_DEVICE_4_ID ""           ////Aire Condicionado (2)
#define IOT_CONFIG_DEVICE_5_ID ""           ////Aire Comprimido (2)

#define IOT_CONFIG_DEVICE_GATEWAY_KEY ""    //Gateway General-Otros (2)
#define IOT_CONFIG_DEVICE_1_KEY ""          //General (2)
#define IOT_CONFIG_DEVICE_2_KEY ""          //Robot (2)
#define IOT_CONFIG_DEVICE_3_KEY ""          //Linea Empaquetado (2)
#define IOT_CONFIG_DEVICE_4_KEY ""          //Aire Condicionado (2)
#define IOT_CONFIG_DEVICE_5_KEY ""          //Aire Comprimido (2)
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
