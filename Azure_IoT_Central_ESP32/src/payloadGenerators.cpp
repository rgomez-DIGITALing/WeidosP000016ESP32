#include "payloadGenerators.h"
#include <LogModule.h>
#include <RTClib.h>

#include <az_core.h>
#include <az_iot.h>

#define EXIT_IF_TRUE(condition, retcode, message, ...) \
  do                                                   \
  {                                                    \
    if (condition)                                     \
    {                                                  \
      LogError(message, ##__VA_ARGS__);                \
      return retcode;                                  \
    }                                                  \
  } while (0)

#define EXIT_IF_AZ_FAILED(azresult, retcode, message, ...) \
  EXIT_IF_TRUE(az_result_failed(azresult), retcode, message, ##__VA_ARGS__)




#define EXIT_IF_TRUE2(condition, retcode, message, ...) \
  do                                                   \
  {                                                    \
    if (condition)                                     \
    {                                                  \
      LogError2(message, ##__VA_ARGS__);                \
      return retcode;                                  \
    }                                                  \
  } while (0)

#define EXIT_IF_AZ_FAILED2(azresult, retcode, message, ...) \
  EXIT_IF_TRUE2(az_result_failed(azresult), retcode, message, ##__VA_ARGS__)

static const uint8_t null_terminator = '\0';


/* --- Function Checks and Returns --- */
#define RESULT_OK 0
#define RESULT_ERROR __LINE__

#define DOUBLE_DECIMAL_PLACE_DIGITS 2
#define TRIPLE_DECIMAL_PLACE_DIGITS 3
#define SAMPLE_DEVICE_INFORMATION_NAME "deviceInformation"

static const double ERROR_DOUBLE = (double)999999999999999;





int flowMeter_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, flowMeterManagerData_t& fmData){
      az_json_writer jw;
    az_result rc;
    az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
    az_span json_span;

    unsigned long timestamp = fmData.timestamp;
    flowMeterData_t data = fmData.payload;

    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");



    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(FM_TELEMETRY_PROP_NAME_TOTAL_CONSUMPTION));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", FM_TELEMETRY_PROP_NAME_TOTAL_CONSUMPTION);
    rc = az_json_writer_append_double(&jw, data.totalConsumption, TRIPLE_DECIMAL_PLACE_DIGITS);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", FM_TELEMETRY_PROP_NAME_TOTAL_CONSUMPTION);

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(FM_TELEMETRY_PROP_NAME_PERIOD_CONSUMPTION));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", FM_TELEMETRY_PROP_NAME_PERIOD_CONSUMPTION);
    rc = az_json_writer_append_double(&jw, data.periodConsumption, TRIPLE_DECIMAL_PLACE_DIGITS);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", FM_TELEMETRY_PROP_NAME_PERIOD_CONSUMPTION);

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(FM_TELEMETRY_PROP_NAME_AVERAGE_FLOW));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", FM_TELEMETRY_PROP_NAME_AVERAGE_FLOW);
    rc = az_json_writer_append_double(&jw, data.averageFlow, TRIPLE_DECIMAL_PLACE_DIGITS);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", FM_TELEMETRY_PROP_NAME_AVERAGE_FLOW);

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(FM_TELEMETRY_PROP_NAME_INITIAL_TIME));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", FM_TELEMETRY_PROP_NAME_INITIAL_TIME);
    rc = az_json_writer_append_int32(&jw, data.t0);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", FM_TELEMETRY_PROP_NAME_INITIAL_TIME);

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(FM_TELEMETRY_PROP_NAME_FINAL_TIME));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", FM_TELEMETRY_PROP_NAME_FINAL_TIME);
    rc = az_json_writer_append_int32(&jw, data.tf);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", FM_TELEMETRY_PROP_NAME_FINAL_TIME);

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(FM_TELEMETRY_PROP_NAME_ERROR_STATE));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
    rc = az_json_writer_append_int32(&jw, data.error);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

    rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_TIMESTAMP));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
    DateTime date = DateTime(timestamp);
    char dateFormat[] = "YYYY-MM-DDThh:mm:ss.000Z";
    date.toString(dateFormat);
    rc = az_json_writer_append_string(&jw, az_span_create_from_str(dateFormat));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");



    rc = az_json_writer_append_end_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

    payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

    if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
    {
      LogError("Insufficient space for telemetry payload null terminator.");
      return RESULT_ERROR;
    }

    payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
    *payload_buffer_length = az_span_size(payload_buffer_span);
  
  return RESULT_OK;
}



int em1ph_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, em1phManagerData_t& emData){

    az_json_writer jw;
    az_result rc;
    az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
    az_span json_span;

    unsigned long timestamp = emData.timestamp;
    int comError = emData.payload.comError;
    float* data = emData.payload.data;
    int dataErrorCounter = 0;


    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");



  if(!comError){
    for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++){
      rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM1PH_DATA_TELEMETRY_NAMES[i]));
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM1PH_DATA_TELEMETRY_NAMES[i]);
      int dataError = isEMDataValid(data[i]);

      if(!dataError) rc = az_json_writer_append_double(&jw, data[i], TRIPLE_DECIMAL_PLACE_DIGITS);
      else{
        dataErrorCounter++;
        rc = az_json_writer_append_double(&jw, ERROR_DOUBLE, DOUBLE_DECIMAL_PLACE_DIGITS);
      }

      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM1PH_DATA_TELEMETRY_NAMES[i]);
    }

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
    rc = az_json_writer_append_int32(&jw, dataErrorCounter);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");
  }else
  {
    for(int i=0; i<NUM_TOTAL_DATA_3PHASE; i++){
      rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM3PH_DATA_TELEMETRY_NAMES[i]));
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM3PH_DATA_TELEMETRY_NAMES[i]);
      rc = az_json_writer_append_null(&jw);
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM3PH_DATA_TELEMETRY_NAMES[i]);
    }
  }
  
  

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COM_ERROR));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, comError, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  DateTime date = DateTime(timestamp);
  char dateFormat[] = "YYYY-MM-DDThh:mm:ss.000Z";
  date.toString(dateFormat);
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(dateFormat));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");



  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);
  
  return RESULT_OK;
    
}


int em3ph_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, em3phManagerData_t& emData){

    az_json_writer jw;
    az_result rc;
    az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
    az_span json_span;

    unsigned long timestamp = emData.timestamp;
    int comError = emData.payload.comError;
    float* data = emData.payload.data;
    int dataErrorCounter = 0;

    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");


  if(!comError){
    for(int i=0; i<NUM_TOTAL_DATA_3PHASE; i++){
      rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM3PH_DATA_TELEMETRY_NAMES[i]));
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM3PH_DATA_TELEMETRY_NAMES[i]);
      int dataError = isEMDataValid(data[i]);

      if(!dataError) rc = az_json_writer_append_double(&jw, data[i], TRIPLE_DECIMAL_PLACE_DIGITS);
      else{
        dataErrorCounter++;
        rc = az_json_writer_append_double(&jw, ERROR_DOUBLE, DOUBLE_DECIMAL_PLACE_DIGITS);
      }

      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM3PH_DATA_TELEMETRY_NAMES[i]);
    }

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER);
    rc = az_json_writer_append_int32(&jw, dataErrorCounter);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload. ", TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER);
  }
  else{
    for(int i=0; i<NUM_TOTAL_DATA_3PHASE; i++){
      rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM3PH_DATA_TELEMETRY_NAMES[i]));
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM3PH_DATA_TELEMETRY_NAMES[i]);
      rc = az_json_writer_append_null(&jw);
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM3PH_DATA_TELEMETRY_NAMES[i]);
    }
  }


  

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COM_ERROR));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, comError, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload.");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  DateTime date = DateTime(timestamp);
  char dateFormat[] = "YYYY-MM-DDThh:mm:ss.000Z";
  date.toString(dateFormat);
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(dateFormat));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");



  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);
  
  return RESULT_OK;
    
}


int weidosESP32_generete_payload(uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, WeidosManagerData_t& weidosData){

      az_json_writer jw;
    az_result rc;
    az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
    az_span json_span;

    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");


  //########################              Weidos ESP32 TELEMETRY           #########################
  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_FREE_HEAP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freeHeap property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.freeHeap, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freeHeap property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_HEAP_SIZE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding heapSize property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.heapSize, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding heapSize property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_MAX_ALLOC_HEAP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocHeap property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.maxAllocHeap, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocHeap property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_MIN_FREE_HEAP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreeHeap property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.minFreeHeap, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreeHeap property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_FREE_PSRAM));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freePsram property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.freePsram, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding freePsram property value to telemetry payload. ");
  
  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_PSRAM_SIZE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding psramSize property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.psramSize, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding psramSize property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_MAX_ALLOC_PSRAM));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocPsram property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.maxAllocPsram, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding maxAllocPsram property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_MIN_FREE_PSRAM));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreePsram property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.minFreePsram, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding minFreePsram property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_SKETCH_SIZE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding sketchSize property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.sketchSize, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding sketchSize property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_INTERNAL_TEMPERATURE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding internalTemperature property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.internalTemperature, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding internalTemperature property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_RUNNING_TIME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding runningTime property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.runningTime, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding runningTime property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_HALL_SENSOR));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding hallSensor property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, weidosData.payload.hallSensor, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding hallSensor property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  DateTime date = DateTime(weidosData.timestamp);
  char dateFormat[] = "YYYY-MM-DDThh:mm:ss.000Z";
  date.toString(dateFormat);
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(dateFormat));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

  


  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);
  
  return RESULT_OK;
}






int em750_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM750* energyMeter){
      
  az_json_writer jw;
  az_result rc;
  az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
  az_span json_span;


  rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

  rc = az_json_writer_append_begin_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");

  rc = az_iot_hub_client_properties_writer_begin_component(
      hub_client, &jw, az_span_create_from_str(SAMPLE_DEVICE_INFORMATION_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting component name.");


  char* identifier = energyMeter->getIdentifier();
  char* asset = energyMeter->getAsset();
  char* location1 = energyMeter->getLocation1();
  char* location2 = energyMeter->getLocation2();
  char* model = EM750_MODEL_NAME;
  char* partNumber = EM750_PART_NUMBER;
  IPAddress ipAddress = energyMeter->getIpAddress();


  char ipAddressArray[16];
  ipAddress.toString().toCharArray(ipAddressArray, 16);


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IDENTIFIER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(identifier));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_ASSET_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(asset));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_LOCATION_1_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(location1));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_LOCATION_2_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(location2));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_BRAND_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(WEIDMULLER_BRAND));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_NUM_PHASES_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_NUMPHASES_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM3PHASES_NUM_PHASES));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_NUMPHASES_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODEL_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODEL_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM750_MODEL_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODEL_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_PART_NUMBER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM750_PART_NUMBER));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_COM_TYPE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_COM_TYPE_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(TCP_COM_TYPE));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_COM_TYPE_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IP_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(ipAddressArray));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_TCP_PORT_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_TCP_PORT_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(DEFAULT_TCP_PORT));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_TCP_PORT_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODBUS_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str("1"));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_BAUDRATE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_PARITY_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_STOP_BITS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MEASUREMENT_METHOD_PROPERY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_DIRECT_METHOD));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. "));



  rc = az_iot_hub_client_properties_writer_end_component(hub_client, &jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing component object.");

  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);

  return RESULT_OK;
}


int ea750_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EA750* energyMeter){
      
  az_json_writer jw;
  az_result rc;
  az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
  az_span json_span;


  rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

  rc = az_json_writer_append_begin_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");

  rc = az_iot_hub_client_properties_writer_begin_component(
      hub_client, &jw, az_span_create_from_str(SAMPLE_DEVICE_INFORMATION_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting component name.");


  char* identifier = energyMeter->getIdentifier();
  char* asset = energyMeter->getAsset();
  char* location1 = energyMeter->getLocation1();
  char* location2 = energyMeter->getLocation2();
  char* model = EA750_MODEL_NAME;
  char* partNumber = EA750_PART_NUMBER;
  IPAddress ipAddress = energyMeter->getIpAddress();

 
  char ipAddressArray[16];
  ipAddress.toString().toCharArray(ipAddressArray, 16);


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IDENTIFIER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(identifier));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_ASSET_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(asset));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_LOCATION_1_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(location1));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_LOCATION_2_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(location2));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_BRAND_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(WEIDMULLER_BRAND));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_BRAND_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_NUM_PHASES_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_NUMPHASES_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM3PHASES_NUM_PHASES));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_NUMPHASES_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODEL_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODEL_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM750_MODEL_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODEL_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_PART_NUMBER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM750_PART_NUMBER));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_COM_TYPE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_COM_TYPE_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(TCP_COM_TYPE));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_COM_TYPE_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IP_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(ipAddressArray));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_TCP_PORT_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_TCP_PORT_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(DEFAULT_TCP_PORT));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_TCP_PORT_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODBUS_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str("1"));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_BAUDRATE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_PARITY_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_STOP_BITS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. "));

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MEASUREMENT_METHOD_PROPERY_NAME));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload."));
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_DIRECT_METHOD));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. "));



  rc = az_iot_hub_client_properties_writer_end_component(hub_client, &jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing component object.");

  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);

  return RESULT_OK;
}


int em110_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM110* energyMeter){
      
  az_json_writer jw;
  az_result rc;
  az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
  az_span json_span;

  rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

  rc = az_json_writer_append_begin_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");

  rc = az_iot_hub_client_properties_writer_begin_component(
      hub_client, &jw, az_span_create_from_str(SAMPLE_DEVICE_INFORMATION_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting component name.");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_BRAND_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(WEIDMULLER_BRAND));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IDENTIFIER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_NUM_PHASES_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM1PHASES_NUM_PHASES));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODEL_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM110_MODEL_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_PART_NUMBER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM110_PART_NUMBER));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_COM_TYPE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(RTU_COM_TYPE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IP_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_TCP_PORT_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODBUS_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getModusId());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_BAUDRATE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_BAUDRATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_PARITY_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(NONE_PARITY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_STOP_BITS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_STOP_BITS));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MEASUREMENT_METHOD_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_INDIRECT_METHOD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_CT_PRIMARY_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getCTPrimary());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_CT_SECONDARY_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getCTSecondary());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");



  rc = az_iot_hub_client_properties_writer_end_component(hub_client, &jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing component object.");

  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);

  return RESULT_OK;
}


int em111_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM111* energyMeter){
      
  az_json_writer jw;
  az_result rc;
  az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
  az_span json_span;

  rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

  rc = az_json_writer_append_begin_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");

  rc = az_iot_hub_client_properties_writer_begin_component(
      hub_client, &jw, az_span_create_from_str(SAMPLE_DEVICE_INFORMATION_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting component name.");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_BRAND_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(WEIDMULLER_BRAND));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IDENTIFIER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_NUM_PHASES_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM1PHASES_NUM_PHASES));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODEL_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM111_MODEL_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_PART_NUMBER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM111_PART_NUMBER));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_COM_TYPE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(RTU_COM_TYPE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IP_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_TCP_PORT_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODBUS_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getModusId());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_BAUDRATE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_BAUDRATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_PARITY_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(NONE_PARITY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_STOP_BITS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_STOP_BITS));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MEASUREMENT_METHOD_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_DIRECT_METHOD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");



  rc = az_iot_hub_client_properties_writer_end_component(hub_client, &jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing component object.");

  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);

  return RESULT_OK;
}


int em120_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM120* energyMeter){

  az_json_writer jw;
  az_result rc;
  az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
  az_span json_span;

  rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

  rc = az_json_writer_append_begin_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");

  rc = az_iot_hub_client_properties_writer_begin_component(
      hub_client, &jw, AZ_SPAN_FROM_STR(SAMPLE_DEVICE_INFORMATION_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting component name.");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_BRAND_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(WEIDMULLER_BRAND));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IDENTIFIER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_NUM_PHASES_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM3PHASES_NUM_PHASES));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODEL_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM120_MODEL_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_PART_NUMBER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM120_PART_NUMBER));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_COM_TYPE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(RTU_COM_TYPE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IP_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_TCP_PORT_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODBUS_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getModusId());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_BAUDRATE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_BAUDRATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_PARITY_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(NONE_PARITY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_STOP_BITS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_STOP_BITS));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MEASUREMENT_METHOD_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_INDIRECT_METHOD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_CT_PRIMARY_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getCTPrimary());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_CT_SECONDARY_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getCTSecondary());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");



  rc = az_iot_hub_client_properties_writer_end_component(hub_client, &jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing component object.");

  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);

  return RESULT_OK;
}


int em122_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM122* energyMeter){
      
  az_json_writer jw;
  az_result rc;
  az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
  az_span json_span;

  rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

  rc = az_json_writer_append_begin_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");

  rc = az_iot_hub_client_properties_writer_begin_component(
      hub_client, &jw, az_span_create_from_str(SAMPLE_DEVICE_INFORMATION_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting component name.");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_BRAND_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(WEIDMULLER_BRAND));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IDENTIFIER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_NUM_PHASES_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM3PHASES_NUM_PHASES));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODEL_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM122_MODEL_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_PART_NUMBER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM122_PART_NUMBER));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_COM_TYPE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(RTU_COM_TYPE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IP_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_TCP_PORT_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODBUS_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getModusId());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_BAUDRATE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_BAUDRATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_PARITY_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(NONE_PARITY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_STOP_BITS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_STOP_BITS));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MEASUREMENT_METHOD_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_DIRECT_METHOD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_iot_hub_client_properties_writer_end_component(hub_client, &jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing component object.");

  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);

  return RESULT_OK;
}


int em220_generete_properties(az_iot_hub_client const* hub_client,
    uint8_t* payload_buffer,
    size_t payload_buffer_size,
    size_t* payload_buffer_length, EM220* energyMeter){
      
  az_json_writer jw;
  az_result rc;
  az_span payload_buffer_span = az_span_create(payload_buffer, payload_buffer_size);
  az_span json_span;

  rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

  rc = az_json_writer_append_begin_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");

  rc = az_iot_hub_client_properties_writer_begin_component(
      hub_client, &jw, az_span_create_from_str(SAMPLE_DEVICE_INFORMATION_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting component name.");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IDENTIFIER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_LOCATION1_PROPERTY_NAME to payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODEL_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM220_MODEL_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODEL_PROPERTY_NAME to payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_BRAND_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(WEIDMULLER_BRAND));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_BRAND_PROPERTY_NAME to payload. ");
  

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_NUM_PHASES_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM3PHASES_NUM_PHASES));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_NUMPHASES_PROPERTY_NAME to payload. ");
  

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_PART_NUMBER_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM220_PART_NUMBER));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_PART_NUMBER_PROPERTY_NAME to payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_COM_TYPE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(RTU_COM_TYPE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_COM_TYPE_PROPERTY_NAME to payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_IP_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_IP_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_TCP_PORT_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(""));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_TCP_PORT_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MODBUS_ADDRESS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getModusId());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_MODBUS_ADDRESS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_BAUDRATE_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_BAUDRATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_BAUDRATE_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_PARITY_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(NONE_PARITY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_PARITY_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_RTU_STOP_BITS_PROPERTY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_STOP_BITS));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_MEASUREMENT_METHOD_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(EM_INDIRECT_METHOD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_CT_PRIMARY_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getCTPrimary());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM_CT_SECONDARY_PROPERY_NAME));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload.");
  rc = az_json_writer_append_int32(&jw, energyMeter->getCTSecondary());
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding EM_RTU_STOP_BITS_PROPERTY_NAME to payload. ");



  rc = az_iot_hub_client_properties_writer_end_component(hub_client, &jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing component object.");

  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed closing telemetry json payload.");

  payload_buffer_span = az_json_writer_get_bytes_used_in_destination(&jw);

  if ((payload_buffer_size - az_span_size(payload_buffer_span)) < 1)
  {
    LogError("Insufficient space for telemetry payload null terminator.");
    return RESULT_ERROR;
  }

  payload_buffer[az_span_size(payload_buffer_span)] = null_terminator;
  *payload_buffer_length = az_span_size(payload_buffer_span);

  return RESULT_OK;
}
