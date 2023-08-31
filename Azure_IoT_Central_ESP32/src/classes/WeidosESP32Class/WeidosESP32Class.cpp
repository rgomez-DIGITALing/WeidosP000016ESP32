#include "WeidosESP32Class.h"


weidosMetadata_t WeidosESP32Class::getMetadata(){
    weidosMetadata_t metadata;
    metadata.freeHeap = getFreeHeap();
    metadata.heapSize = getHeapSize();
    metadata.maxAllocHeap = getMaxAllocHeap();
    metadata.minFreeHeap = getMinFreeHeap();
    metadata.sketchSize = getSketchSize();
    metadata.internalTemperature = getTemperature();
    metadata.runningTime = millis();
    metadata.hallSensor = getHall();
    return metadata;
}
