#include "Dialog.h"
#include "Game.h"
#include "GameBar.h"
#include "Attr.h"

Dialog::Dialog(Game *game, const QIcon &icon, const QString &title)
    : QDialog(game), game(game) {
    setWindowIcon(icon);
    setWindowTitle(title);
    // Disable user interaction with the main window
    setModal(true);
    // Free memory on close
    setAttribute(Qt::WA_DeleteOnClose);

    // Set up the layout
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Container for any additional widgets
    mainFrame = new QFrame(this);
    mainLayout->addWidget(mainFrame);
    mainLayout->addStretch();

    // Container for buttons
    auto buttonFrame = new QFrame(this);
    mainLayout->addSpacing(45);
    mainLayout->addWidget(buttonFrame, 0, Qt::AlignCenter);

    // Display buttons horizontally
    buttonLayout = new QHBoxLayout(buttonFrame);
    buttonLayout->setSpacing(5);
    buttonLayout->setContentsMargins(0, 0, 0, 0);

    // Create a universal 'OK' button that closes a dialog on click.
    okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &close);
    buttonLayout->addWidget(okButton);
}

Dialog::~Dialog() {

}

void Dialog::show() {
    // Make this window not resizable
    setFixedSize(sizeHint());
    QDialog::show();
}

SettingsDialog::SettingsDialog(Game *game)
    : Dialog(game, Icon::load("Settings.svg"), "Settings") {
    // Set up the layout for the main frame
    vboxLayout = new QVBoxLayout(mainFrame);
    vboxLayout->setSpacing(10);
    vboxLayout->setContentsMargins(0, 0, 0, 0);

    // Add check boxes
    addBox("Play Against AI", Attr::get().playAI);
    addBox("Enable Animation", Attr::get().animated);
    addBox("Show Hint", Attr::get().hinted);

    // Update all settings on click
    connect(okButton, &QPushButton::clicked, this, &updateSettings);

    // Reset all settings on click
    auto resetButton = new QPushButton("Reset", this);
    connect(resetButton, &QPushButton::clicked, this, &resetSettings);
    buttonLayout->addWidget(resetButton);

    // Discard all changes on click
    auto cancelButton = new QPushButton("Cancel", this);
    connect(cancelButton, &QPushButton::clicked, this, &close);
    buttonLayout->addWidget(cancelButton);
}

SettingsDialog::~SettingsDialog() {

}

void SettingsDialog::addBox(const QString &name, bool &state) {
    auto box = new QCheckBox(name, this);
    box->setChecked(state);
    boxes.insert(box, &state);
    vboxLayout->addWidget(box);
}

void SettingsDialog::updateSettings() {
    for (auto it = boxes.begin(); it != boxes.end(); ++it) {
        *it.value() = it.key()->isChecked();
    }

    applySettings();
}

void SettingsDialog::resetSettings() {
    Attr::get().resetSettings();

    applySettings();
}

void SettingsDialog::applySettings() {
    game->continueRound();
    game->getGameBar()->setHintVisible(Attr::get().hinted);

    close();
}

StatsDialog::StatsDialog(Game *game)
    : Dialog(game, Icon::load("Stats.svg"), "Statistics") {
    // Set up the layout for the main frame
    formLayout = new QFormLayout(mainFrame);
    formLayout->setHorizontalSpacing(150);
    formLayout->setVerticalSpacing(10);
    formLayout->setContentsMargins(0, 0, 0, 0);

    // Display X's score
    addEntry(Icon::load("X.svg"), Attr::get().playAI ? "You" : "Player #1",
             Attr::get().xWins);

    // Display the number of ties between 'X' and 'O'
    addEntry(Icon::load("Tie.svg"), "Tie", Attr::get().ties);

    // Display O's score
    addEntry(Icon::load("O.svg"), Attr::get().playAI ? "AI" : "Player #2",
             Attr::get().oWins);

    // Reset all statistics on click
    auto resetButton = new QPushButton("Reset", this);
    connect(resetButton, &QPushButton::clicked, this, &resetStats);
    buttonLayout->addWidget(resetButton);
}

StatsDialog::~StatsDialog() {

}

void StatsDialog::addEntry(const QIcon &icon, const QString &name, int val) {
    // Display the icon and the name on the left
    auto nameButton = new QPushButton(icon, "   " + name + ":", this);
    nameButton->setStyleSheet("border: 0");

    // Display the value on the right
    auto valLabel = new QLabel(QString::number(val), this);
    valLabel->setStyleSheet("font-size: 24px");

    formLayout->addRow(nameButton, valLabel);
}

void StatsDialog::resetStats() {
    Attr::get().resetStats();
    close();
}

HelpDialog::HelpDialog(Game *game)
    : Dialog(game, Icon::load("Help.svg"), "Help") {
    // Set up the layout for the main frame
    auto vboxLayout = new QVBoxLayout(mainFrame);
    vboxLayout->setSpacing(0);
    vboxLayout->setContentsMargins(0, 0, 0, 0);

    // Create tabs for navigation
    auto tabWidget = new QTabWidget(this);
    tabWidget->addTab(newBrowser("Rules.html"), "Rules");
    tabWidget->addTab(newBrowser("About.html"), "About");
    vboxLayout->addWidget(tabWidget);
}

HelpDialog::~HelpDialog() {

}

QTextBrowser *HelpDialog::newBrowser(const QString &path) {
    auto browser = new QTextBrowser(this);
    // Display HTML content
    browser->setHtml(File::readAll(path));
    // Open hyperlinks in the HTML content on click
    browser->setOpenExternalLinks(true);
    connect(browser, &QTextBrowser::anchorClicked, this, [] {});

    return browser;
}
