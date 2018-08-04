// Copyright (c) 2018 The Bitcoin developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "script/sighashtype.h"
#include "test/test_bitcoin.h"

#include <boost/test/unit_test.hpp>

#include <set>

BOOST_FIXTURE_TEST_SUITE(sighashtype_tests, BasicTestingSetup)

static void CheckSigHashType(SigHashType t, BaseSigHashType baseType,
                             bool isDefined,
                             bool hasAnyoneCanPay) {
    BOOST_CHECK(t.getBaseType() == baseType);
    BOOST_CHECK_EQUAL(t.isDefined(), isDefined);
    BOOST_CHECK_EQUAL(t.hasAnyoneCanPay(), hasAnyoneCanPay);
}

BOOST_AUTO_TEST_CASE(sighash_construction_test) {
    // Check default values.
    CheckSigHashType(SigHashType(), BaseSigHashType::ALL, true, false);

    // Check all possible permutations.
    std::set<BaseSigHashType> baseTypes{
        BaseSigHashType::UNSUPPORTED, BaseSigHashType::SINGLE};
    std::set<bool> anyoneCanPayFlagValues{false, true};

    for (BaseSigHashType baseType : baseTypes) {
                for (bool hasAnyoneCanPay : anyoneCanPayFlagValues) {
                    const SigHashType t =
                        SigHashType()
                            .withBaseType(baseType)
                            .withAnyoneCanPay(hasAnyoneCanPay);

                    bool isDefined = baseType != BaseSigHashType::UNSUPPORTED;
                    CheckSigHashType(t, baseType, isDefined, hasAnyoneCanPay);

                    // Also check all possible alterations.
                    CheckSigHashType(t.withAnyoneCanPay(hasAnyoneCanPay),
                                     baseType, isDefined, hasAnyoneCanPay);
                    CheckSigHashType(t.withAnyoneCanPay(!hasAnyoneCanPay),
                                     baseType, isDefined, !hasAnyoneCanPay);

                    for (BaseSigHashType newBaseType : baseTypes) {
                        bool isNewDefined =
                            newBaseType != BaseSigHashType::UNSUPPORTED;
                        CheckSigHashType(t.withBaseType(newBaseType),
                                         newBaseType, isNewDefined, hasAnyoneCanPay);
                    }
                }
            }
}

BOOST_AUTO_TEST_SUITE_END()
