// Copyright 2019, Nawin
#include "Workspace.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include <sstream>
#include <iostream>

using ::testing::StartsWith;
using ::testing::HasSubstr;
using ::testing::StrCaseEq;
using ::testing::IsTrue;
using ::testing::IsFalse;

using std::string_literals::operator""s;


namespace {

  TEST(BasicTest, Positive) {
    EXPECT_EQ(2 + 3, 5);
  }

  TEST(DynamicProcessor, Positive) {
    TextProcessor tp;
    tp.set_output_format(OutputFormat::markdown);
    tp.append_list({ "foo", "bar", "baz" });
    std::cout << tp.str() << std::endl;

    tp.clear();
    tp.set_output_format(OutputFormat::html);
    tp.append_list({ "foo", "bar", "baz" });
    std::cout << tp.str() << std::endl;
  }

  TEST(StaticProcessor, Positive) {
    StaticTextProcessor<MarkdownListStrategy> tpm;
    tpm.append_list({ "foo", "bar", "baz" });
    std::cout << tpm.str() << std::endl;

    StaticTextProcessor<HtmlListStrategy> tmh;
    tmh.append_list({ "foo", "bar", "baz" });
    std::cout << tmh.str() << std::endl;
  }
 } // namespace
