#include "HelpDialog.h"

#include <QApplication>
#include <QGridLayout>
#include <QLabel>

#include "AppInfo.h"

HelpDialog::HelpDialog(QWidget *parent) : QDialog{parent} {
    setWindowTitle(tr("Help"));
    setModal(true);
    setContentsMargins(30, 30, 30, 30);

    const auto titleLabel = new QLabel{this};  // NOLINT
    const auto versionLabel = new QLabel{this};  // NOLINT
    const auto authorLabel = new QLabel{this};  // NOLINT

    titleLabel->setText(appinfo::name);
    titleLabel->setObjectName("title");
    versionLabel->setText(QString{"Version %1"}.arg(appinfo::version));
    authorLabel->setText(QString{"By %1"}.arg(appinfo::author));

    const auto gridLayout = new QGridLayout{this};  // NOLINT
    gridLayout->addWidget(titleLabel, 0, 0, Qt::AlignCenter);
    gridLayout->addWidget(versionLabel, 1, 0, Qt::AlignCenter);
    gridLayout->addWidget(authorLabel, 2, 0, Qt::AlignCenter);

    setFixedSize(QDialog::sizeHint());
}
