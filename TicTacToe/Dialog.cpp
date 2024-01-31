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
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(30, 30, 30, 30);

    // Container for buttons
    auto buttonFrame = new QFrame(this);
    mainLayout->addSpacing(30);
    mainLayout->addWidget(buttonFrame, 0, Qt::AlignCenter);

    // Display buttons horizontally
    buttonLayout = new QHBoxLayout(buttonFrame);
    buttonLayout->setSpacing(5);
    buttonLayout->setContentsMargins(0, 0, 0, 0);

    // Create a universal 'OK' button that closes a dialog on click.
    okButton = new QPushButton(tr("OK"), this);
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
    : Dialog(game, Icon::load("Settings.svg"), tr("Settings")) {
    // Add check boxes
    auto checkLayout = newGroupLayout(tr("Gameplay"));
    checkLayout->addWidget(newCheckBox(tr("Play Against AI"),
                                       Attr::get().playAI));
    checkLayout->addWidget(newCheckBox(tr("Enable Animation"),
                                       Attr::get().animated));
    checkLayout->addWidget(newCheckBox(tr("Show Hint"),
                                       Attr::get().hinted));

    // Select language
    langBox = new QComboBox(this);
    langBox->addItem(Lang::ENGLISH);
    langBox->addItem(Lang::CHINESE_SIMPLIFIED);
    langBox->setCurrentText(Attr::get().lang);

    auto langLayout = newGroupLayout(tr("Language"));
    langLayout->addWidget(langBox);

    // Reset all settings on click
    auto resetButton = new QPushButton(tr("Reset"), this);
    connect(resetButton, &QPushButton::clicked, this, &resetSettings);
    buttonLayout->insertWidget(0, resetButton);
    buttonLayout->insertSpacing(1, 45);
    buttonLayout->insertStretch(2);

    // Update all settings on click
    connect(okButton, &QPushButton::clicked, this, &updateSettings);

    // Discard all changes on click
    auto cancelButton = new QPushButton(tr("Cancel"), this);
    connect(cancelButton, &QPushButton::clicked, this, &close);
    buttonLayout->addWidget(cancelButton);
}

SettingsDialog::~SettingsDialog() {

}

QVBoxLayout *SettingsDialog::newGroupLayout(const QString &title) {
    // Create a group box
    auto box = new QGroupBox(title, this);
    mainLayout->insertWidget(mainLayout->count() - 2, box);

    // Set up the layout for the group box
    auto vboxLayout = new QVBoxLayout(box);
    vboxLayout->setSpacing(10);
    vboxLayout->setContentsMargins(25, 25, 25, 25);

    return vboxLayout;
}

QCheckBox *SettingsDialog::newCheckBox(const QString &name, bool &state) {
    auto box = new QCheckBox(name, this);
    box->setChecked(state);
    boxes.insert(box, &state);
    return box;
}

void SettingsDialog::updateSettings() {
    for (auto it = boxes.begin(); it != boxes.end(); ++it) {
        *it.value() = it.key()->isChecked();
    }

    langChanged = Attr::get().lang != langBox->currentText();
    Attr::get().lang = langBox->currentText();

    applySettings();
}

void SettingsDialog::resetSettings() {
    Attr::get().resetSettings();

    langChanged = Attr::get().lang != langBox->currentText();

    applySettings();
}

void SettingsDialog::applySettings() {
    game->continueRound();
    game->getGameBar()->setHintVisible(Attr::get().hinted);

    // Relaunch the program after changing the language
    if (langChanged) {
        WinGui::relaunch();
    }

    close();
}

StatsDialog::StatsDialog(Game *game)
    : Dialog(game, Icon::load("Stats.svg"), tr("Statistics")) {
    auto formFrame = new QFrame(this);
    mainLayout->insertWidget(0, formFrame);

    // Set up the layout for the main frame
    formLayout = new QFormLayout(formFrame);
    formLayout->setHorizontalSpacing(150);
    formLayout->setVerticalSpacing(10);
    formLayout->setContentsMargins(0, 0, 0, 0);

    // Display X's score
    addRow(Icon::load("X.svg"),
           Attr::get().playAI ? tr("You") : tr("Player 1"),
           Attr::get().xWins);

    // Display the number of ties between 'X' and 'O'
    addRow(Icon::load("Tie.svg"), tr("Tie"), Attr::get().ties);

    // Display O's score
    addRow(Icon::load("O.svg"),
           Attr::get().playAI ? tr("AI") : tr("Player 2"),
           Attr::get().oWins);

    // Reset all statistics on click
    auto resetButton = new QPushButton(tr("Reset"), this);
    connect(resetButton, &QPushButton::clicked, this, &resetStats);
    buttonLayout->insertWidget(0, resetButton);
}

StatsDialog::~StatsDialog() {

}

void StatsDialog::addRow(const QIcon &icon, const QString &name, int value) {
    // Display the icon and the name on the left
    auto nameButton = new QPushButton(icon, "   " + name + ":", this);
    nameButton->setStyleSheet("border: 0");

    // Display the value on the right
    auto valLabel = new QLabel(QString::number(value), this);
    valLabel->setStyleSheet("font-size: 24px");

    formLayout->addRow(nameButton, valLabel);
}

void StatsDialog::resetStats() {
    Attr::get().resetStats();
    close();
}

HelpDialog::HelpDialog(Game *game)
    : Dialog(game, Icon::load("Help.svg"), tr("Help")) {
    // Create tabs for navigation
    auto tabWidget = new QTabWidget(this);
    tabWidget->addTab(newBrowser(tr("Rules.html")), tr("Rules"));
    tabWidget->addTab(newBrowser(tr("About.html")), tr("About"));
    mainLayout->insertWidget(0, tabWidget);
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
