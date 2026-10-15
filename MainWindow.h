#pragma once

#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include "ListaDeTareas.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void onAgregarClicked();
    void onEliminarClicked();
    void onFiltroCambiado(int index);
    void onTareaItemChanged(int row, int column);

private:
    ListaDeTareas miLista;

    // Entradas del formulario
    QLineEdit   *txtTitulo;
    QTextEdit   *txtDescripcion;
    QComboBox   *comboPrioridad;
    QDateEdit   *dateLimite;
    QPushButton *btnAgregar;

    // Filtros y tabla
    QComboBox   *comboFiltro;
    QTableWidget* tablaTareas;
    QPushButton *btnEliminar;
    QLabel      *lblResumen;

    bool actualizandoTabla = false;

    void configurarUI();
    void refrescarTabla();
};