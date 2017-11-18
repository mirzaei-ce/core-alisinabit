// Copyright (c) 2011-2014 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ALISINABIT_QT_ALISINABITADDRESSVALIDATOR_H
#define ALISINABIT_QT_ALISINABITADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class AlisinabitAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AlisinabitAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Alisinabit address widget validator, checks for a valid alisinabit address.
 */
class AlisinabitAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit AlisinabitAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // ALISINABIT_QT_ALISINABITADDRESSVALIDATOR_H
