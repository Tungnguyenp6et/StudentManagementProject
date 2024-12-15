#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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
    QString SubmittedUsername = LogInWidget->UsernameSpace->text();
    QString SubmittedPassword = LogInWidget->PasswordSpace->text();
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
        QString SubmittedUsername = RegisterWidget->UsernameSpace->text();
        QString SubmittedPassword = RegisterWidget->PasswordSpace->text();
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
