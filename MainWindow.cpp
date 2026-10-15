#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Gestor de Tareas");
    resize(850, 500);
    configurarUI();
    refrescarTabla();
}

void MainWindow::configurarUI() {
    auto *central = new QWidget(this);
    auto *mainLayout = new QHBoxLayout(central);

    // ==========================================
    // PANEL IZQUIERDO: Formulario de Nueva Tarea
    // ==========================================
    auto *leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("<b>Nueva Tarea</b>"));

    leftLayout->addWidget(new QLabel("Título:"));
    txtTitulo = new QLineEdit();
    leftLayout->addWidget(txtTitulo);

    leftLayout->addWidget(new QLabel("Descripción:"));
    txtDescripcion = new QTextEdit();
    txtDescripcion->setMaximumHeight(90);
    leftLayout->addWidget(txtDescripcion);

    leftLayout->addWidget(new QLabel("Prioridad:"));
    comboPrioridad = new QComboBox();
    comboPrioridad->addItems({"Alta", "Media", "Baja"});
    leftLayout->addWidget(comboPrioridad);

    leftLayout->addWidget(new QLabel("Fecha Límite:"));
    dateLimite = new QDateEdit(QDate::currentDate());
    dateLimite->setCalendarPopup(true);
    dateLimite->setDisplayFormat("yyyy-MM-dd");
    leftLayout->addWidget(dateLimite);

    btnAgregar = new QPushButton("➕ Agregar Tarea");
    btnAgregar->setStyleSheet("padding: 8px; font-weight: bold;");
    leftLayout->addWidget(btnAgregar);
    leftLayout->addStretch();

    // ==========================================
    // PANEL DERECHO: Tabla y Acciones
    // ==========================================
    auto *rightLayout = new QVBoxLayout();

    auto *topBarLayout = new QHBoxLayout();
    topBarLayout->addWidget(new QLabel("<b>Filtro:</b>"));
    comboFiltro = new QComboBox();
    comboFiltro->addItems({"Mostrar Todas", "Solo Pendientes"});
    topBarLayout->addWidget(comboFiltro);
    topBarLayout->addStretch();
    lblResumen = new QLabel();
    topBarLayout->addWidget(lblResumen);
    rightLayout->addLayout(topBarLayout);

    tablaTareas = new QTableWidget();
    tablaTareas->setColumnCount(5);
    tablaTareas->setHorizontalHeaderLabels({"Estado", "Título", "Prioridad", "Fecha Límite", "Descripción"});
    tablaTareas->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    tablaTareas->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablaTareas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rightLayout->addWidget(tablaTareas);

    auto *bottomBarLayout = new QHBoxLayout();
    btnEliminar = new QPushButton("🗑️ Eliminar Tarea Seleccionada");
    bottomBarLayout->addWidget(btnEliminar);
    bottomBarLayout->addStretch();
    rightLayout->addLayout(bottomBarLayout);

    // Integrar paneles
    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 2);
    setCentralWidget(central);

    // Conexiones de Eventos
    connect(btnAgregar, &QPushButton::clicked, this, &MainWindow::onAgregarClicked);
    connect(btnEliminar, &QPushButton::clicked, this, &MainWindow::onEliminarClicked);
    connect(comboFiltro, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::onFiltroCambiado);
    connect(tablaTareas, &QTableWidget::cellChanged, this, &MainWindow::onTareaItemChanged);
}

void MainWindow::onAgregarClicked() {
    std::string titulo = txtTitulo->text().toStdString();
    if (titulo.empty()) {
        QMessageBox::warning(this, "Aviso", "El título no puede estar vacío.");
        return;
    }

    std::string desc = txtDescripcion->toPlainText().toStdString();
    std::string fecha = dateLimite->date().toString("yyyy-MM-dd").toStdString();

    Prioridad p = Prioridad::BAJA;
    if (comboPrioridad->currentIndex() == 0) p = Prioridad::ALTA;
    else if (comboPrioridad->currentIndex() == 1) p = Prioridad::MEDIA;

    Tarea nueva(titulo, desc, p, fecha);
    miLista.agregarTarea(nueva);

    txtTitulo->clear();
    txtDescripcion->clear();
    dateLimite->setDate(QDate::currentDate());

    refrescarTabla();
}

void MainWindow::onEliminarClicked() {
    int fila = tablaTareas->currentRow();
    if (fila < 0) {
        QMessageBox::information(this, "Aviso", "Por favor selecciona una tarea en la tabla.");
        return;
    }

    // El índice original se almacena en los datos del primer elemento
    int indiceOriginal = tablaTareas->item(fila, 0)->data(Qt::UserRole).toInt();
    miLista.eliminarTarea(indiceOriginal);
    refrescarTabla();
}

void MainWindow::onFiltroCambiado(int) {
    refrescarTabla();
}

void MainWindow::onTareaItemChanged(int row, int column) {
    if (actualizandoTabla || column != 0) return;

    QTableWidgetItem *item = tablaTareas->item(row, column);
    if (!item) return;

    int indiceOriginal = item->data(Qt::UserRole).toInt();
    if (item->checkState() == Qt::Checked) {
        miLista.marcarCompletada(indiceOriginal);
    }
    refrescarTabla();
}

void MainWindow::refrescarTabla() {
    actualizandoTabla = true;
    tablaTareas->setRowCount(0);

    const auto &tareas = miLista.obtenerTareas();
    bool soloPendientes = (comboFiltro->currentIndex() == 1);

    int pendientesCount = 0;

    for (size_t i = 0; i < tareas.size(); ++i) {
        const auto &t = tareas[i];
        if (!t.estaCompletada()) pendientesCount++;

        if (soloPendientes && t.estaCompletada()) continue;

        int row = tablaTareas->rowCount();
        tablaTareas->insertRow(row);

        // Checkbox de estado
        auto *itemCheck = new QTableWidgetItem(t.estaCompletada() ? "Completada" : "Pendiente");
        itemCheck->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        itemCheck->setCheckState(t.estaCompletada() ? Qt::Checked : Qt::Unchecked);
        itemCheck->setData(Qt::UserRole, static_cast<int>(i)); // Guardar índice original
        tablaTareas->setItem(row, 0, itemCheck);

        // Título
        auto *itemTitulo = new QTableWidgetItem(QString::fromStdString(t.getTitulo()));
        if (t.estaCompletada()) {
            QFont font = itemTitulo->font();
            font.setStrikeOut(true);
            itemTitulo->setFont(font);
            itemTitulo->setForeground(Qt::gray);
        }
        tablaTareas->setItem(row, 1, itemTitulo);

        // Prioridad con color
        auto *itemPrioridad = new QTableWidgetItem(QString::fromStdString(t.prioridadATexto(t.getPrioridad())));
        if (t.getPrioridad() == Prioridad::ALTA) itemPrioridad->setForeground(QBrush(QColor(220, 53, 69)));
        else if (t.getPrioridad() == Prioridad::MEDIA) itemPrioridad->setForeground(QBrush(QColor(255, 153, 0)));
        else itemPrioridad->setForeground(QBrush(QColor(40, 167, 69)));
        tablaTareas->setItem(row, 2, itemPrioridad);

        // Fecha
        tablaTareas->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(t.getFechaLimite())));

        // Descripción
        tablaTareas->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(t.getDescripcion())));
    }

    lblResumen->setText(QString("Total: %1 | Pendientes: %2")
                        .arg(miLista.cantidad())
                        .arg(pendientesCount));
    actualizandoTabla = false;
}