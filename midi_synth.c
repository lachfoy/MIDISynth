#include <stdio.h>
#include <math.h>
#include "portaudio.h"
#include "portmidi.h"

#define SAMPLE_RATE (44100)
#define PA_SAMPLE_TYPE paFloat32
#define FRAMES_PER_BUFFER (512)

typedef struct
{
    long status;
    long data1;
    // long data2;
    float phase;
}
paData;

static int paCallback(const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{
    float *out = (float*)outputBuffer;
    paData *data = (paData*)userData;
    unsigned int i;
    (void) timeInfo; /* Prevent unused variable warnings. */
    (void) statusFlags;
    (void) inputBuffer; 
    //(void) userData;
 
    float amp = 1.0f;
    double freq = pow(2,(data->data1 - 69) / 12) * 440;
    for (i=0; i < framesPerBuffer; i++)
    {
        *out++ = data->phase;
        data->phase += 2.0f/(SAMPLE_RATE/freq);

        if(data->phase >= amp) data->phase -= amp*2;
    }

    return paContinue;
}

static paData data;
int main(void);
int main(void)
{
    PortMidiStream *midi_stream;
	PaStream *stream;

    data.phase = 0.0;
    data.status = 0x80;
    data.data1 = 0x39;

    Pm_Initialize();

    PmDeviceID device_id = Pm_GetDefaultInputDeviceID();
    const PmDeviceInfo* info = Pm_GetDeviceInfo(device_id);
    //printf((const char*)device_id);
    //printf(info->name);

    Pm_OpenInput(&midi_stream, device_id, NULL, 2048, NULL, NULL);

	//Pa_Initialize();
	//Pa_OpenDefaultStream(&stream, 0, 1, PA_SAMPLE_TYPE, SAMPLE_RATE, FRAMES_PER_BUFFER, paCallback, &data);

	//Pa_StartStream(stream);
    //Pa_Sleep(5*1000);
    //Pa_StopStream(stream);

    PmEvent event;
    while (1)
    {
        if (Pm_Poll(midi_stream))
        {
            Pm_Read(midi_stream, &event, 1);
            PmMessage msg = event.message;
            long status = Pm_MessageStatus(msg);
            //data.data1 = Pm_MessageData1(msg);
            //long data2 = Pm_MessageData2(msg);
            prinf(status);
            if (status == 0x80)
            {

            }
            else if (status == 0x90)
            {
                printf("note played");
            }
        }
    }

    //Pa_StopStream(stream);

    Pm_Close(midi_stream);
    Pm_Terminate();

    //Pa_CloseStream(stream);
	//Pa_Terminate();
	return 0;
}