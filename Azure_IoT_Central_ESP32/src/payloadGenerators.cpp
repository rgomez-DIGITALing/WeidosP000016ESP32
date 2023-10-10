#include "payloadGenerators.h"
//#include "classes/EM750/EM750.h"
#include <LogModule.h>
//#include "classes/WeidosESP32Class/WeidosESP32Class.h"
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
    

    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");


  //########################              ENERGY METER TELEMETRY           #########################
  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_VOLTAGE_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_VOLTAGE_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1N property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_CURRENT_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_CURRENT_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL1 property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_TOTAL_REAL_POWER_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_TOTAL_APPARENT_POWER_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerTotal property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_TOTAL_REACTIVE_POWER_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerTotal property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_FREQUENCY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding frequency property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_FREQUENCY_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding frequency property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_ROT_FIELD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding rotField property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_ROTATION_FIELD_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding rotField property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_TOTAL_REAL_ENERGY_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyTotal property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_TOTAL_APPARENT_ENERGY_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyTotal property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_TOTAL_REACTIVE_ENERGY_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_POWER_FACTOR_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM1PH_TOTAL_POWER_FACTOR_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorTotal property value to telemetry payload. ");





  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COM_STATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, comError, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_int32(&jw, timestamp);
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

    rc = az_json_writer_init(&jw, payload_buffer_span, NULL);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed initializing json writer for telemetry.");

    rc = az_json_writer_append_begin_object(&jw);
    EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed setting telemetry json root.");



  //########################              ENERGY METER TELEMETRY           #########################
  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_VOLTAGE_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_VOLTAGE_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1N property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_VOLTAGE_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_VOLTAGE_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_VOLTAGE_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_VOLTAGE_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_AVG_VOLTAGE_LN));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLN property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_AVG_VOLTAGE_LN_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLN property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_VOLTAGE_L1L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_VOLTAGE_L1L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_VOLTAGE_L2L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_VOLTAGE_L2L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL2L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_VOLTAGE_L1L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_VOLTAGE_L1L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding voltageL1L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_AVG_VOLTAGE_LL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLL property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_AVG_VOLTAGE_LL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgVoltageLL property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_CURRENT_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_CURRENT_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_CURRENT_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_CURRENT_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_CURRENT_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_CURRENT_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentL3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_CURRENT_NEUTRAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentNeutral property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_CURRENT_NEUTRAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentNeutral property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_AVG_CURRENTL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCurrentL property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_AVG_CURRENTL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCurrentL property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_CURRENT_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_CURRENT_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding currentTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_POWER_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_POWER_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_POWER_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_POWER_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_POWER_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_POWER_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_POWER_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realPowerTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_POWER_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_POWER_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_POWER_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_POWER_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_POWER_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_POWER_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_POWER_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentPowerTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_POWER_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_POWER_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_POWER_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_POWER_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_POWER_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_POWER_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_POWER_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_POWER_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactivePowerTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COS_PHI_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_COS_PHI_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COS_PHI_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_COS_PHI_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COS_PHI_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_COS_PHI_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding cosPhiL3 property value to telemetry payload. ");
  
  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_AVG_COS_PHI));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCosPhi property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_AVG_COS_PHI_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgCosPhi property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_FREQUENCY));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding frequency property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_FREQUENCY_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding frequency property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_ROT_FIELD));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding rotField property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_ROT_FIELD_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding rotField property value to telemetry payload. ");


  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_ENERGY_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_ENERGY_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_ENERGY_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_ENERGY_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_ENERGY_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_ENERGY_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REAL_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REAL_ENERGY_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding realEnergyTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_ENERGY_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_ENERGY_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_ENERGY_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_ENERGY_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_ENERGY_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_ENERGY_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyL3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_APPARENT_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_APPARENT_ENERGY_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding apparentEnergyTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L1));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL1 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_ENERGY_L1_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL1 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_ENERGY_L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_ENERGY_L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyL3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_REACTIVE_ENERGY_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_REACTIVE_ENERGY_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding reactiveEnergyTotal property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_VOLTS_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_VOLTS_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_VOLTS_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_VOLTS_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_VOLTS_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_VOLTS_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LN));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_AVG_THD_VOLTS_LN_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDVoltsLN property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_CURRENT_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_CURRENT_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_CURRENT_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_CURRENT_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_CURRENT_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_CURRENT_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDCurrentL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_AVG_THD_CURRENT_LN));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDCurrentLN property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_AVG_THD_CURRENT_LN_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDCurrentLN property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_VOLTS_L1L2));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L2 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_VOLTS_L1L2_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L2 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_VOLTS_L2L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_VOLTS_L2L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL2L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_THD_VOLTS_L1L3));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L3 property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_THD_VOLTS_L1L3_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding THDVoltsL1L3 property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_AVG_THD_VOLTS_LL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDVoltsLL property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_AVG_THD_VOLTS_LL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding avgTHDVoltsLL property value to telemetry payload. ");



  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_POWER_FACTOR_L1N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL1N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_POWER_FACTOR_L1N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL1N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_POWER_FACTOR_L2N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL2N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_POWER_FACTOR_L2N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL2N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_POWER_FACTOR_L3N));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL3N property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_POWER_FACTOR_L3N_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorL3N property value to telemetry payload. ");

  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_POWER_FACTOR_TOTAL));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorTotal property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, data[EM3PH_POWER_FACTOR_TOTAL_INDEX], TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding powerFactorTotal property value to telemetry payload. ");





  rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_COM_STATE));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_double(&jw, comError, TRIPLE_DECIMAL_PLACE_DIGITS);
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property value to telemetry payload. ");

    rc = az_json_writer_append_property_name(&jw, az_span_create_from_str(TELEMETRY_PROP_NAME_TIMESTAMP));
  EXIT_IF_AZ_FAILED(rc, RESULT_ERROR, "Failed adding timestamp property name to telemetry payload.");
  rc = az_json_writer_append_int32(&jw, timestamp);
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
  bool isEA750Type = energyMeter->isEA750();
  char* model = EM750_MODEL_NAME;
  char* partNumber = EM750_PART_NUMBER;
  IPAddress ipAddress = energyMeter->getIpAddress();

  if(isEA750Type){
    model = EA750_MODEL_NAME;
    partNumber = EA750_PART_NUMBER;
  }

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
