#ifndef PS_HARDWARE_HPP
#define PS_HARDWARE_HPP

#include <string>
#include <vector>
#include "SDL_audio.h"
#include "SDL_events.h"

class HardwareHandler;

enum DeviceSpecValues {Frequency = 48000, Format = AUDIO_S16SYS, Samples = 4096};

class Mixer; //Mixer.hpp

/**
 * This class contains information about
 * an audio device
 */ 
class Device {
    friend class HardwareHandler;
    private:
        SDL_AudioSpec spec;
        SDL_AudioDeviceID dev;

        Device(const std::string& name, const int& id);

        bool init();

        //Open the device
        bool open(Mixer* mixer);
        
        //Close the device
        void close();

    public:
        const std::string name;
        const int id;
        int channels;
        bool isOpen, isRunning;

        bool operator == (const Device& other) const;

        //Pause the device
        void pause();

        //Play the device
        void play();
};

/**
 * This class handles the communication
 * with SDL audio
 */ 
class HardwareHandler {
    private:
        Device* activeDevice;
        static HardwareHandler* instance;
        SDL_Event event;
        Mixer* mixer;

        HardwareHandler(): activeDevice(NULL), mixer(NULL) {}

    public:
        std::vector<Device> devices;

        /**
         * Creates a new HardwareHandler instance and returns it
         * @returns The instance or NULL, if there was an error
         */ 
        static HardwareHandler* getHandler();

        /**
         * Initializes the handler and SDL with it
         * @returns If the initialization was successfull
         */ 
        bool init();

        /**
         * Closes the handler and SDL with it
         */ 
        ~HardwareHandler();

        /**
         * Set the active mixer for the devices to use
         * @param mixer The initialized mixer to use
         */ 
        void setMixer(Mixer* mixer);

        /**
         * Set the active output device to the given one
         * @param device The initialized device
         * @returns If the action was successfull
         */ 
        bool setActiveDevice(const Device& device);

        /**
         * Set the active output device to the one with the given internal index
         * @param index The index of the device in the devices vector
         * @returns If the action was successfull
         */ 
        bool setActiveDevice(const int& index);

        /**
         * Checks with SDL_Events, if the device
         * availabilities have changed
         * @returns If something has changed
         */ 
        bool checkForDeviceChanges();

        /**
         * Returns the currently active device
         * @returns The device or NULL, if none is initialized
         */ 
        Device getActiveDevice() {return *activeDevice;}
};

#endif //PS_HARDWARE_HPP