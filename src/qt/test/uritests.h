// Copyright (c) 2012-2018 The Bitcoin Core developers
// Copyright (c) 2017 The Raven Core developers
// Copyright (c) 2018 The Rito Core developers
// Copyright (c) 2019 The Kimora Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef KMR_QT_TEST_URITESTS_H
#define KMR_QT_TEST_URITESTS_H

#include <QObject>
#include <QTest>

class URITests : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void uriTests();
};

#endif // KMR_QT_TEST_URITESTS_H
