#include "1phPayloadGenerators.h"

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






int writeNormalData(az_json_writer& jw, em1phManagerData_t& emData){
    az_result rc;
    float* data = emData.payload.data;
    int dataErrorCounter = 0;

    for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++){
      rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM1PH_DATA_TELEMETRY_NAMES[i]));
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM1PH_DATA_TELEMETRY_NAMES[i]);
      int dataError = isEMDataValid(data[i]);
      if(dataError){
        dataErrorCounter++;
        double errorValue = getEMErrorValue(dataError);
        rc = az_json_writer_append_double(&jw, errorValue, DOUBLE_DECIMAL_PLACE_DIGITS);
      }
      else rc = az_json_writer_append_double(&jw, data[i], TRIPLE_DECIMAL_PLACE_DIGITS);
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM1PH_DATA_TELEMETRY_NAMES[i]);
    }

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER);
    rc = az_json_writer_append_int32(&jw, dataErrorCounter);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload. ", TELEMETRY_PROP_NAME_DATA_ERROR_COUNTER);
    return RESULT_OK;
}

int writeIncrementalData(az_json_writer& jw, em1phManagerData_t& emData){
    az_result rc;
    float* incrementalData = emData.payload.incrementalData;
    int incrementalDataErrorCounter = 0;

    //Incremental Data
    for(int i=0; i<NUM_TOTAL_INCREMENTAL_DATA_1PHASE; i++){
      rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM1PH_INCREMENTAL_DATA_TELEMETRY_NAMES[i]));
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM1PH_INCREMENTAL_DATA_TELEMETRY_NAMES[i]);
      int dataError = isEMDataValid(incrementalData[i]);
      if(dataError){
        incrementalDataErrorCounter++;
        double errorValue = getEMErrorValue(dataError);
        rc = az_json_writer_append_double(&jw, errorValue, DOUBLE_DECIMAL_PLACE_DIGITS);
      }
      else rc = az_json_writer_append_double(&jw, incrementalData[i], TRIPLE_DECIMAL_PLACE_DIGITS);
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM1PH_INCREMENTAL_DATA_TELEMETRY_NAMES[i]);
    }

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_INCREMENTAL_DATA_ERROR_COUNTER));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", TELEMETRY_PROP_NAME_INCREMENTAL_DATA_ERROR_COUNTER);
    rc = az_json_writer_append_int32(&jw, incrementalDataErrorCounter);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload. ", TELEMETRY_PROP_NAME_INCREMENTAL_DATA_ERROR_COUNTER);
  //End Period Data
  return RESULT_OK;
}

int writeConsDelivData(az_json_writer& jw, em1phManagerData_t& emData){
    az_result rc;
    float* consDelivData = emData.payload.consDelivData;
    int consDelivDataErrorCounter = 0;

    //Consumed/Delivered Data
    for(int i=0; i<NUM_TOTAL_CONS_DELIV_DATA_1PHASE; i++){
      rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[i]));
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[i]);
      int dataError = isEMDataValid(consDelivData[i]);
      Serial.print(EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[i]);
      Serial.print(": ");
      Serial.println(consDelivData[i]);
      if(dataError){
        consDelivDataErrorCounter++;
        double errorValue = getEMErrorValue(dataError);
        rc = az_json_writer_append_double(&jw, errorValue, DOUBLE_DECIMAL_PLACE_DIGITS);
      }
      else rc = az_json_writer_append_double(&jw, consDelivData[i], TRIPLE_DECIMAL_PLACE_DIGITS);
      EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[i]);
    }

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_CONS_DELIV_DATA_ERROR_COUNTER));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", TELEMETRY_PROP_NAME_CONS_DELIV_DATA_ERROR_COUNTER);
    rc = az_json_writer_append_int32(&jw, consDelivDataErrorCounter);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload. ", TELEMETRY_PROP_NAME_CONS_DELIV_DATA_ERROR_COUNTER);
  //End Consumed/Delivered Data
  return RESULT_OK;
}

int writeNullValues(az_json_writer& jw, em1phManagerData_t& emData){
  az_result rc;

  for(int i=0; i<NUM_TOTAL_DATA_1PHASE; i++){
    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM3PH_DATA_TELEMETRY_NAMES[i]));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM1PH_DATA_TELEMETRY_NAMES[i]);
    rc = az_json_writer_append_null(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM1PH_DATA_TELEMETRY_NAMES[i]);
  }

  for(int i=0; i<NUM_TOTAL_CONS_DELIV_DATA_1PHASE; i++){
    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[i]));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[i]);
    rc = az_json_writer_append_null(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM1PH_CONS_DELIV_DATA_TELEMETRY_NAMES[i]);
  }

  for(int i=0; i<NUM_TOTAL_INCREMENTAL_DATA_1PHASE; i++){
    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(EM1PH_INCREMENTAL_DATA_TELEMETRY_NAMES[i]));
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property name to telemetry payload.", EM1PH_INCREMENTAL_DATA_TELEMETRY_NAMES[i]);
    rc = az_json_writer_append_null(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding %s property value to telemetry payload.", EM1PH_INCREMENTAL_DATA_TELEMETRY_NAMES[i]);
  }

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
    
    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed initializing json writer for telemetry."));

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed setting telemetry json root."));


  if(!comError){
    rc = writeNormalData(jw, emData);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting Normal Data");

    rc = writeConsDelivData(jw, emData);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting Cons/Deliv Data");

    rc = writeIncrementalData(jw, emData);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting Incremental Data");
  }
  else{
    rc = writeConsDelivData(jw, emData);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed writting NULL values");
  }


  
  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_DATA_SOURCE_STATUS));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_int32(&jw, emData.dataSourceStatus);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COM_ERROR));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding timestamp property name to telemetry payload."));
  rc = az_json_writer_append_double(&jw, comError, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding timestamp property value to telemetry payload."));

  rc = az_json_writer_append_property_name(&jw, AZ_SPAN_FROM_STR(WEIDOS_TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding timestamp property name to telemetry payload."));
  DateTime date = DateTime(timestamp);
  char dateFormat[] = "YYYY-MM-DDThh:mm:ss.000Z";
  date.toString(dateFormat);
  rc = az_json_writer_append_string(&jw, az_span_create_from_str(dateFormat));
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed adding timestamp property value to telemetry payload. "));



  rc = az_json_writer_append_end_object(&jw);
  EXIT_IF_AZ_FAILED2(rc, RESULT_ERROR, F("Failed closing telemetry json payload."));

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

