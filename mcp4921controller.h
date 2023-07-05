#ifndef MCP4921CONTROLLER_H
#define MCP4921CONTROLLER_H

#include <QObject>

class MCP4921Controller : public QObject {
    Q_OBJECT
public:
    explicit MCP4921Controller(QObject *parent = nullptr);
    ~MCP4921Controller();

    void initialize();
    void setOutputVoltage(float voltage);
    void increaseInputPercentage();
    void decreaseInputPercentage();

signals:
    void outputVoltageChanged(float voltage);
    void inputPercentageChanged(float percentage);

private:
    int spiChannel;
    int spiSpeed;
    int dac_value;

    void write_mcp4921(int value);
    float calculate_output_voltage(int digital_input);

};

#endif // MCP4921CONTROLLER_H
