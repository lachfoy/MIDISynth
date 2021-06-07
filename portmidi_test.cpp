#include <iostream>
#include "portmidi.h"

using namespace std;

int main(void)
{
    Pm_Initialize();
    
    int device_id = Pm_GetDefaultInputDeviceID();
    cout << device_id << endl;
    const PmDeviceInfo* info = Pm_GetDeviceInfo(device_id);
    cout << info->name << endl;

    PortMidiStream* midi_stream;
    Pm_OpenInput(&midi_stream, device_id, NULL, 32, NULL, NULL);

    PmEvent event;
    while (true)
    {
        if (Pm_Poll(midi_stream))
        {
            Pm_Read(midi_stream, &event, 1);
            PmMessage msg = event.message;
            long status = Pm_MessageStatus(msg);
            long data1 = Pm_MessageData1(msg);
            long data2 = Pm_MessageData2(msg);
            cout << "[[" << status << ", " << data1 << ", " << data2 << "], " << event.timestamp << "]" << endl;
        }
    }

    Pm_Close(midi_stream);
    Pm_Terminate();
    
    return 0;
}