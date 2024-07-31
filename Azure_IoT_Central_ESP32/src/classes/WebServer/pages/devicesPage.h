#include <ESPAsyncWebServer.h>


void sendDevicesPage(AsyncResponseStream *response);
void sendDeviceFormPage(AsyncResponseStream *response, int slot);