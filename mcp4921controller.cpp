#include "mcp4921controller.h"
#include <wiringPiSPI.h>

const float REFERENCE_VOLTAGE = 5.5;
const int DAC_MIN_VALUE = 0;
const int DAC_MAX_VALUE = 4095;
const int SPI_CHANNEL = 0; // Replace with the appropriate SPI channel
const int SPI_SPEED = 1000000; // Replace with the desired SPI speed

const byte CMD_WRITE = 0x30;

MCP4921Controller::MCP4921Controller(QObject *parent) : QObject(parent), dac_value(DAC_MAX_VALUE) {
    spiChannel = SPI_CHANNEL;
    spiSpeed = SPI_SPEED;
    wiringPiSPISetup(spiChannel, spiSpeed);
}

MCP4921Controller::~MCP4921Controller() {
    // Cleanup SPI communication if needed
}

void MCP4921Controller::initialize() {
    // Perform any initialization steps for the controller
}

void MCP4921Controller::setOutputVoltage(float voltage) {
    int outputValue = voltage * DAC_MAX_VALUE / REFERENCE_VOLTAGE;

    write_mcp4921(outputValue);

    emit outputVoltageChanged(voltage);
}

void MCP4921Controller::increaseInputPercentage() {
    if (dac_value < DAC_MAX_VALUE)
        dac_value++;

    setOutputVoltage((dac_value / (float)DAC_MAX_VALUE) * REFERENCE_VOLTAGE);

    float inputPercentage = (dac_value / (float)DAC_MAX_VALUE) * 100.0;
    emit inputPercentageChanged(inputPercentage);
}

void MCP4921Controller::decreaseInputPercentage() {
    if (dac_value > DAC_MIN_VALUE)
        dac_value--;

    setOutputVoltage((dac_value / (float)DAC_MAX_VALUE) * REFERENCE_VOLTAGE);

    float inputPercentage = (dac_value / (float)DAC_MAX_VALUE) * 100.0;
    emit inputPercentageChanged(inputPercentage);
}

void MCP4921Controller::write_mcp4921(int value) {
    unsigned char spiData[2];
    spiData[0] = CMD_WRITE | ((value >> 8) & 0x0F);
    spiData[1] = value & 0xFF;

    digitalWrite(SPI_CS_PIN, LOW);
    wiringPiSPIDataRW(spiChannel, spiData, 2);
    digitalWrite(SPI_CS_PIN, HIGH);
}

float MCP4921Controller::calculate_output_voltage(int digital_input) {
    return (digital_input / (float)DAC_MAX_VALUE) * REFERENCE_VOLTAGE;
}
