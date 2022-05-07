#ifndef PS_HARDWARE_HPP
#define PS_HARDWARE_HPP

#include <string>
#include <vector>

/**
 * This class contains information about
 * an audio device (may be physical or
 * virtual). The class is abstract, the
 * implementations are in
 * src/Implementation/ALSA/HardwareALSA.hpp (Linux)
 * src/Implementation/CoreWin/HardwareCore.hpp (Windows)
 */ 
class Device {
    public:
        std::string name;
        int id;

        virtual ~Device() {}

        //Open the device internally
        virtual bool open() = 0;
        
        //Close the device internally
        virtual bool close() = 0;
};

/**
 * This class handles the communication
 * with the sound APIs of the different
 * operating systems (ALSA for Linux,
 * Core Audio for Windows). The class is
 * abstract, the implementations are in
 * src/Implementation/ALSA/HardwareALSA.hpp (Linux)
 * src/Implementation/CoreWin/HardwareCore.hpp (Windows)
 */ 
class HardwareHandler {
    protected:
        Device* activeDevice;

    public:
        std::vector<Device*> devices;

        /**
         * Creates a new HardwareHandler instance (according to your OS)
         * and returns it
         * @returns The instance or NULL, if there was an error
         */ 
        static HardwareHandler* getHandler();

        /**
         * Initializes the handler and the OS API with it
         * @returns If the initialization was successfull
         */ 
        virtual bool init() = 0;

        /**
         * Closes the handler and the OS API with it
         */ 
        virtual ~HardwareHandler() {}

        /**
         * Set the active output device to the given one
         * @param device The initialized device (can be NULL)
         * @returns If the action was successfull (returns true if the device is NULL)
         */ 
        virtual bool setActiveDevice(Device* device) = 0;

        /**
         * Set the active output device to the one with the given internal index
         * @param index The index of the device in the devices vector
         * @returns If the action was successfull (returns false if the index is out of bounds)
         */ 
        virtual bool setActiveDevice(const int& index) = 0;

        /**
         * Returns the currently active device
         * @returns The device or NULL, if none is initialized
         */ 
        Device* getActiveDevice() {return activeDevice;}
};

#endif //PS_HARDWARE_HPP