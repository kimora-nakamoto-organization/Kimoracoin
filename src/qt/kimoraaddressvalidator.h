// Copyright (c)  The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Copyright (c) 2019 The Kimora Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KMR_QT_KMRADDRESSVALIDATOR_H
#define KMR_QT_KMRADDRESSVALIDATOR_H

#include <QValidator>

/** Base58 entry widget validator, checks for valid characters and
 * removes some whitespace.
 */
class KimoraAddressEntryValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KimoraAddressEntryValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

/** Kimora address widget validator, checks for a valid kimora address.
 */
class KimoraAddressCheckValidator : public QValidator
{
    Q_OBJECT

public:
    explicit KimoraAddressCheckValidator(QObject *parent);

    State validate(QString &input, int &pos) const;
};

#endif // KMR_QT_KMRADDRESSVALIDATOR_H
