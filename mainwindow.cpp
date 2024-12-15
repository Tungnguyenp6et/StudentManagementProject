#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SubmittedUsername = "";
    SetUpTheDatabase();
    this->setCentralWidget(LogInWidget);
    this->setMaximumSize(400,100);
    QObject::connect(LogInWidget->SubmitButton, &QPushButton::clicked, this, &MainWindow::OnSubmitButtonClicked);
    QObject::connect(LogInWidget->Register, &QLabel::linkActivated, this, &MainWindow::OnRegisterButtonClicked);
}

void MainWindow::OnSubmitButtonClicked() {
    if(!db.isOpen()){
        qDebug() << "Database is not open: "<< db.lastError().text();
        return;
    }
    QSqlQuery LogInQuery(db);
    SubmittedUsername = LogInWidget->UsernameSpace->text();
    SubmittedPassword = LogInWidget->PasswordSpace->text();
    QString LogInQueryStatement = QString("SELECT * FROM UserInfor WHERE Username = '%1' AND Password = '%2'").arg(SubmittedUsername).arg(SubmittedPassword);
    if (!LogInQuery.exec(LogInQueryStatement)){
        qDebug() << "Can't retrieve the password: "<< LogInQuery.lastError().text();
        return;
    }
    else if (LogInQuery.next()){
        QMessageBox::information(this, "LOG IN SUCCESSFULLY", "YAH");
        IsLogedIn = true;
        delete LogInWidget;

        ClassLayout = new ClassViewLayout(this);
        this->setCentralWidget(ClassLayout);
        this->setMaximumHeight(600);
        this->setMinimumHeight(400);
        this->setMinimumWidth(400);
        this->setMaximumWidth(600);
        AfterLogIn();
        return;
    }
    else{
        QMessageBox::information(this, "LOG IN UNSUCCESSFULLY", "Please try again!");
    }
}
void MainWindow::OnRegisterButtonClicked() {
    if (!db.isOpen()) {
        qDebug() << "Database is not open: " << db.lastError().text();
        return;
    }

    RegisterForm *RegisterWidget = new RegisterForm(this);
    this->setCentralWidget(RegisterWidget);
    QObject::connect(RegisterWidget->SubmitButton, &QPushButton::clicked, this, [=](){
        QSqlQuery RegisterQuery(db);
        SubmittedUsername = RegisterWidget->UsernameSpace->text();
        SubmittedPassword = RegisterWidget->PasswordSpace->text();
        QString SubmittedClassID = RegisterWidget->ClassIDSpace->text();
        QString SubmittedClassName = RegisterWidget->ClassNameSpace->text();
        if (SubmittedUsername.isEmpty() || SubmittedPassword.isEmpty() || SubmittedClassID.isEmpty() || SubmittedClassName.isEmpty()) {
            QMessageBox::information(this, "Register failed", "Please fill all the boxes");
            return;
        }

        // Check if username already exists
        QString RegisterQueryStatement = "SELECT * FROM UserInfor WHERE Username = :Username";
        RegisterQuery.prepare(RegisterQueryStatement);
        RegisterQuery.bindValue(":Username", SubmittedUsername);

        if (!RegisterQuery.exec()) {
            qDebug() << "Can't extract the username" << RegisterQuery.lastError().text();
            return;
        } else if (RegisterQuery.next()) {
            QMessageBox::information(this, "Register failed", "Username already exists");
            return;
        }

        // Insert new user information
        RegisterQueryStatement = "INSERT INTO UserInfor (Username, Password, ClassID, ClassName) "
                                 "VALUES (:Username, :Password, :ClassID, :ClassName)";
        if (!RegisterQuery.prepare(RegisterQueryStatement)) {
            qDebug() << "Prepare error:" << RegisterQuery.lastError().text();
            return;
        }

        RegisterQuery.bindValue(":Username", SubmittedUsername);
        RegisterQuery.bindValue(":Password", SubmittedPassword);
        RegisterQuery.bindValue(":ClassID", SubmittedClassID);
        RegisterQuery.bindValue(":ClassName", SubmittedClassName);

        // Debugging: Print the bound values
        qDebug() << "Username:" << SubmittedUsername;
        qDebug() << "Password:" << SubmittedPassword;
        qDebug() << "ClassID:" << SubmittedClassID;
        qDebug() << "ClassName:" << SubmittedClassName;

        if (!RegisterQuery.exec()) {
            qDebug() << "Exec error:" << RegisterQuery.lastError().text();
            return;
        }

        QMessageBox::information(this, "Register successfully", "Register successfully");
        delete RegisterWidget;
        delete LogInWidget;
        ClassLayout = new ClassViewLayout(this);
        this->setCentralWidget(ClassLayout);
        this->setMaximumHeight(600);
        this->setMinimumHeight(400);
        this->setMinimumWidth(400);
        this->setMaximumWidth(600);
        AfterLogIn();
    });
}
QString MainWindow::GenerateRandomString(){
    const QString PossibleCharacters{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"};
    QString RandomString;
    for (int i =0; i<10; i++){
        int index = QRandomGenerator::global()->bounded(PossibleCharacters.length());
        RandomString.append(PossibleCharacters.at(index));
    }
    return RandomString;
}


void MainWindow::AfterLogIn(){
    QSqlTableModel *ClassModel = new QSqlTableModel(this,db);
    ClassModel->setTable("UserInfor");
    ClassLayout->ClassView->setModel(ClassModel);
    ClassModel->setEditStrategy(QSqlTableModel::OnFieldChange);
    ClassModel->select();
    int Column = ClassModel->fieldIndex("Username");
    if (Column == -1) {
        qDebug() << "Cant find Username";
    }
    for (int Row = 0; Row < ClassModel->rowCount(); Row ++) {
        QModelIndex Index = ClassModel->index(Row, Column);
        if (ClassModel->data(Index) == SubmittedUsername){
            QItemSelectionModel *SelectionModel = ClassLayout->ClassView->selectionModel();
            SelectionModel->select(Index, QItemSelectionModel::Select | QItemSelectionModel::Rows);
        }
    }
    PercentageDelegate *DelegatePercentage = new PercentageDelegate(this);
    ClassLayout->ClassView->setItemDelegateForColumn(4, DelegatePercentage);
    ClassLayout->ClassView->setItemDelegateForColumn(5, DelegatePercentage);
    ClassLayout->ClassView->hideColumn(1);
    ClassLayout->ClassView->hideColumn(0);
    // Ensuring that classID can't be the same
    QObject::connect(ClassModel, &QSqlTableModel::dataChanged, this, [=](const QModelIndex topLeft, const QModelIndex bottomRight, const QVector<int> &roles){
        Q_UNUSED(bottomRight);
        Q_UNUSED(roles);
        if(!ClassModel->submitAll()){
            QString ErrorMessage = ClassModel->lastError().text();
            QMessageBox::critical(nullptr, "Database error", "Failed to update database: " + ErrorMessage);
            ClassModel->revertAll();
        }
        if (topLeft.column() == 4){
            double Value = topLeft.data().toDouble();
            double NewValue = 1 - Value;
            QModelIndex RelevantIndex = ClassModel->index(topLeft.row(), 5, QModelIndex());
            if(!ClassModel->setData(RelevantIndex, NewValue)){
                qDebug() << "Cant not update column 5";
            }
        }
        else if (topLeft.column() == 5){
            double Value = topLeft.data().toDouble();
            double NewValue = 1 - Value;
            QModelIndex RelevantIndex = ClassModel->index(topLeft.row(), 4, QModelIndex());
            if(!ClassModel->setData(RelevantIndex, NewValue)){
                qDebug() << "Cant not update column 5";}
        }
    });
    QObject::connect(ClassLayout->AddButton, &QPushButton::clicked, this, [=](){
        QSqlQuery AddQuery(db);
        QString AddQueryStatement = QString("INSERT INTO UserInfor(Username, Password, ClassID, ClassName) "
                                            "VALUES (:Username, :Password, :ClassID, :ClassName)");
        if (!AddQuery.prepare(AddQueryStatement)){
            qDebug() << "Failed to prepare query:" << AddQuery.lastError();
            return;
        }
        AddQuery.bindValue(":Username", SubmittedUsername);
        AddQuery.bindValue(":Password", SubmittedPassword);
        AddQuery.bindValue(":ClassID", GenerateRandomString());
        AddQuery.bindValue(":ClassName", GenerateRandomString());
        if (!AddQuery.exec()){
            qDebug() << "Failed to execute query:" << AddQuery.lastError();
            return;
        }

        qDebug() << "Successfully inserted new row";

        // Refresh the model to reflect the new row
        ClassModel->select();

        // Find and select the newly added row
        for (int Row = 0; Row < ClassModel->rowCount(); Row++) {
            QModelIndex Index = ClassModel->index(Row, 0);
            if (ClassModel->data(Index) == SubmittedUsername){
                QItemSelectionModel *AddModel = ClassLayout->ClassView->selectionModel();
                AddModel->select(Index, QItemSelectionModel::Select | QItemSelectionModel::Rows);
                break;
            }
        }
    });

}
void MainWindow::SetUpTheDatabase(){
    MyForm->setFileName(":/Database/DatabaseForm.accdb");
    WriteablePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    TargetFilePath = WriteablePath + QDir::separator() + "MyDatabase.accdb";
    MyFile->setFileName(TargetFilePath);

    if (QFile::exists(TargetFilePath)) {
        goto open;
    }
    QDir().mkdir(WriteablePath);
    if (!MyForm->open(QIODevice::ReadOnly)){
        qDebug() << "Open form unsuccessfully";
    }
    if (!MyFile->open(QIODevice::WriteOnly)){
        qDebug() << "Open file unsuccessfully";
    }
    MyFile->write(MyForm->readAll());
    MyFile->close();
    MyForm->close();

    open:
    qDebug() << "Successfully extract the file";
    qDebug() << TargetFilePath;
    db = QSqlDatabase::addDatabase("QODBC", "accdb_connection");
    db.setDatabaseName("Driver={Microsoft Access Driver (*.mdb, *.accdb)};DBQ=" + TargetFilePath);
    if(!db.open()) qDebug()<< db.lastError().text();
    else qDebug() << "Open!";


}
MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}
