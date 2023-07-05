#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "mcp4921controller.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MCP4921Controller controller;
    controller.initialize();

    QWidget window;
    QVBoxLayout layout;
    QPushButton increaseButton("Increase");
    QPushButton decreaseButton("Decrease");

    layout.addWidget(&increaseButton);
    layout.addWidget(&decreaseButton);
    window.setLayout(&layout);

    QObject::connect(&increaseButton, &QPushButton::clicked, &controller, &MCP4921Controller::increaseInputPercentage);
    QObject::connect(&decreaseButton, &QPushButton::clicked, &controller, &MCP4921Controller::decreaseInputPercentage);

    window.show();

    return app.exec();
}
