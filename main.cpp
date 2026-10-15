#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    // Inicializa el entorno y el bucle de eventos de la aplicación Qt
    QApplication app(argc, argv);

    // Instancia y muestra la ventana principal
    MainWindow window;
    window.show();

    // Inicia el bucle principal de la aplicación gráfica
    return app.exec();
}