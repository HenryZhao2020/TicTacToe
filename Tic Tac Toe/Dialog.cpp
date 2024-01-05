#include "Dialog.h"
#include "Game.h"
#include "GameBar.h"
#include "Attr.h"

Dialog::Dialog(Game *game, const QIcon &icon, const QString &title)
    : QDialog(game, Qt::MSWindowsFixedSizeDialogHint) {
    this->game = game;

    setWindowIcon(icon);
    setWindowTitle(title);
    setModal(true);
    setAttribute(Qt::WA_DeleteOnClose);

    vboxLayout = new QVBoxLayout(this);
    vboxLayout->setSpacing(10);
    vboxLayout->setContentsMargins(30, 30, 30, 30);

    auto buttonFrame = new QFrame(this);
    vboxLayout->addSpacing(40);
    vboxLayout->addWidget(buttonFrame);

    buttonLayout = new QHBoxLayout(buttonFrame);
    buttonLayout->setSpacing(5);
    buttonLayout->setContentsMargins(0, 0, 0, 0);
    buttonLayout->setAlignment(Qt::AlignCenter);

    okButton = new QPushButton("OK", this);
    okButton->setDefault(true);
    connect(okButton, &QPushButton::clicked, this, &Dialog::close);
    buttonLayout->addWidget(okButton);
}

void Dialog::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    }
    QDialog::keyPressEvent(event);
}

SettingsDialog::SettingsDialog(Game *game)
    : Dialog(game, getIcon("Settings.svg"), "Settings") {
    addBox("Enable Animation", &Attr::animated);
    addBox("Show Hint", &Attr::hintVisible);

    connect(okButton, &QPushButton::clicked, this, &SettingsDialog::apply);

    auto cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::clicked, this, &Dialog::close);
    buttonLayout->addWidget(cancelButton);
}

void SettingsDialog::addBox(const QString &text, bool *var) {
    auto box = new QCheckBox(text, this);
    box->setChecked(*var);
    vboxLayout->insertWidget(boxes.size(), box);
    boxes[box] = var;
}

void SettingsDialog::apply() {
    for (auto it = boxes.begin(); it != boxes.end(); it++) {
        *it.value() = it.key()->isChecked();
    }

    game->getGameBar()->setHintVisible(Attr::hintVisible);
}

StatsDialog::StatsDialog(Game *game)
    : Dialog(game, getIcon("Stats.svg"), "Statistics") {
    auto formFrame = new QFrame(this);
    vboxLayout->insertWidget(0, formFrame);

    formLayout = new QFormLayout(formFrame);
    formLayout->setHorizontalSpacing(80);
    formLayout->setVerticalSpacing(10);
    formLayout->setContentsMargins(0, 0, 0, 0);

    addRow("You (X):", Attr::xScore);
    addRow("Tie:", Attr::numTied);
    addRow("Computer (O):", Attr::oScore);

    auto resetButton = new QPushButton("Reset", this);
    connect(resetButton, &QPushButton::clicked, this, &StatsDialog::reset);
    buttonLayout->insertWidget(0, resetButton);
}

void StatsDialog::addRow(const QString &labelText, int value) {
    formLayout->addRow(labelText, new QLabel(QString::number(value), this));
}

void StatsDialog::reset() {
    Attr::xScore = 0;
    Attr::numTied = 0;
    Attr::oScore = 0;

    close();
}

HelpDialog::HelpDialog(Game *game)
    : Dialog(game, getIcon("Help.svg"), "Help") {
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(newTextEdit("Rules.html"), "Rules");
    vboxLayout->insertWidget(0, tabWidget);

    auto aboutFrame = new QFrame(this);
    tabWidget->addTab(aboutFrame, "About");

    auto aboutLayout = new QGridLayout(aboutFrame);
    aboutLayout->setSpacing(0);
    aboutLayout->setContentsMargins(0, 0, 0, 0);
    aboutLayout->addWidget(newTextEdit("About.html"), 0, 0, 1, 0);

    auto webButton = new QPushButton("Website", this);
    webButton->setCursor(Qt::PointingHandCursor);
    connect(webButton, &QPushButton::clicked, this, [] {
        static QUrl url("https://github.com/HenryZhao2020/TicTacToe");
        QDesktopServices::openUrl(url);
    });
    aboutLayout->addWidget(webButton, 1, 0);

    auto qtButton = new QPushButton("About Qt", this);
    qtButton->setCursor(Qt::PointingHandCursor);
    connect(qtButton, &QPushButton::clicked, this, &QApplication::aboutQt);
    aboutLayout->addWidget(qtButton, 1, 1);
}

QTextEdit *HelpDialog::newTextEdit(const QString &htmlFile) {
    auto textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);
    textEdit->setHtml(File::readAll(htmlFile));
    return textEdit;
}